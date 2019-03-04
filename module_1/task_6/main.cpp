#include <iostream>
#include <random>
#include <ctime>
#include <assert.h>

//Реализуйте стратегию выбора опорного элемента “случайный элемент”.
//Функцию Partition реализуйте методом прохода двумя итераторами
//от начала массива к концу.

template<class T>
class IsLess
{
public:
    bool operator () (const T& l, const T& r){return l < r;}
};

template<typename T, class Compare>
unsigned int partition(T* array, unsigned int start, unsigned int finish, Compare comp = IsLess<T>())
{
    if (start == finish) {
        return start;
    }
    T& pivot = array[start + std::rand() % (finish - start)];
    std::swap(array[finish], pivot);
    unsigned int iter_i = start, iter_j = iter_i;

    while(iter_j != finish){
        if(comp(array[iter_j], array[finish])){
            std::swap(array[iter_i], array[iter_j]);
            iter_i++;
        }
        iter_j++;
    }
    std::swap(array[finish], array[iter_i]);
    return iter_i;
}


template<typename T>
unsigned int k_statistic(T* array, unsigned int size, unsigned int position)
{
    unsigned int start = 0;
    unsigned int finish = size - 1;

    while(true){
        unsigned int pivot = partition(array, start, finish, IsLess<T>());
        std::cout << std::endl;
        if(pivot == position){
            return array[position];
        } else if (pivot > position){
            finish = pivot - 1;
        } else {
            start = pivot + 1;
        }
    }
}

int main()
{
    std::srand(std::time(NULL));
    int n = 0;
    std::cin >> n;
    int k = 0;
    std::cin >> k;

    int* array = new int[n];
    for(int i = 0; i < n; i++){
        std::cin >> array[i];
    }
    std::cout << k_statistic(array, n, k);
    delete[] array;
    return 0;
}
