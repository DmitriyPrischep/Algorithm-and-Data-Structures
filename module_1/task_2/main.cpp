#include <iostream>
#include <math.h>
#include <assert.h>

//Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
//A[0..n-1] и B[0..m-1]. n >> m. Найдите их пересечение. Требуемое время работы: O(m * log k),
//где k - позиция элемента B[m-1] в массиве A.. В процессе поиска очередного элемента B[i]
//в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.

using namespace std;

int binarySearch(const int* array, const int start, const int end, const int element)
{
    assert(array);
    assert(start >= 0);
    assert(end >= 0);

    int left = start;
    int right = end;

    while(left <= right){
        int middle = (left + right) / 2;
        if(array[middle] == element){
            return middle;
        }
        if(array[middle] > element){
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return -1;
}


int* intersection(const int* array1, int size1, int* array2, const int size2, int* index_res){
    int begin = 0;
    int* result = new int[size2];
    for(int i = 0; i <size2; i++){
        for(int k = 0, j = 0; j < size1; k++){
            if(i == 0 && j == 0 && array1[j] == array2[i]){
                result[(*index_res)++] = array1[j];
            }

            begin = j;
            j = pow(2, k);
            if(j > size1)
                j = size1 - 1;
            if(array2[i] > array1[begin] && array2[i] <= array1[j]){
                int index = 0;
                index = binarySearch(array1, begin, j, array2[i]);
                if(index != -1){
                    result[(*index_res)++] = array1[index];
                }
            }
            if (j == size1 -1)
                j++;
        }
    }
    return result;
}

int main()
{
    int n = 0 ;
    int m = 0;
    cin >> n >> m;

    int* array1 = new int[n];
    int* array2 = new int[m];

    for(int i = 0; i < n; i++){
        cin >> array1[i];
    }
    for(int i = 0; i < m; i++){
        cin >> array2[i];
    }

    int* result= nullptr;
    int index_res = 0;

    result = intersection(array1, n, array2, m, &index_res);

    if(!result)
        return -1;

    for(int i = 0; i < index_res; i++){
        cout << result[i] << " ";
    }
    delete[] array1;
    delete[] array2;
    delete[] result;
    return 0;
}
