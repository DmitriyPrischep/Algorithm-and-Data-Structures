#include <iostream>
#include <assert.h>

using namespace std;
//Дан массив неотрицательных целых 64-разрядных чисел.
//Количество чисел не больше 10^6. Отсортировать массив методом MSD по битам (бинарный QuickSort).

bool get_digit(long long n, int r)
{
    assert(r > 0);
    return (n >> r) & 1;
}

int binary_msd(long long* array, int left, int right, int bits)
{
    assert(array);
    if(left >= right || bits < 0)
        return 1;
    long long i = left;
    long long j = right;

    while(i != j){
        while(get_digit(array[i], bits) == 0 && i < j){
            i++;
        }
        while(get_digit(array[j], bits) == 1 && i < j){
            j--;
        }
        std::swap(array[i], array[j]);
    }
    if(get_digit(array[j], bits) == 0){
        j++;
    }
    binary_msd(array, left, j - 1, bits - 1);
    binary_msd(array, j, right, bits - 1);
    return 0;
}

int main()
{
    int size = 0;
    cin >> size;
    long long* array = new long long[size];
    for(int i = 0; i < size; i++){
        cin >> array[i];
    }
    binary_msd(array, 0, size - 1, 63);

    for(int i = 0; i < size; i++){
        cout << array[i] << " ";
    }

    delete[] array;
    return 0;
}
