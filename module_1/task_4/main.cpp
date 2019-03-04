#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

template<class T>
struct items{
    T element;
    long index;
};

template<class T>
class IsMore
{
public:
    bool operator () (const items<T>& first, const items<T> second) {return first.element > second.element;}
};

template<class T, class Compare>
class BinaryHeap{
public:
    BinaryHeap(T *source_array, long n);
    ~BinaryHeap();

    void add(const T value);
    T extract_max();
    T get_max();

private:
    int build_binary_heap();
    void shift_up(long index);
    T* realloc_heap(T* array, int size);
    void heapify(long i);
    int get_max(int win_end);

private:
    T* array;
    long heap_size;
    long real_size;
};

template<class T, class Compare>
BinaryHeap<T, Compare>::BinaryHeap(T *source_array, long n) :
    heap_size(n),
    real_size(n)
{
    array = new T[heap_size];
    for(int i = 0; i < heap_size; i++){
        array[i] = source_array[i];
    }
    build_binary_heap();
}

template<typename T, class Compare>
BinaryHeap<T, Compare>::~BinaryHeap()
{
    delete[] array;
}

template<typename T, class Compare>
void BinaryHeap<T, Compare>::heapify(long i)
{
    long left_child = 0;
    long right_child = 0;
    long largest_child = 0;

    while(true){
        left_child = 2 * i + 1;
        right_child = 2 * i + 2;
        largest_child = i;

        if(left_child < real_size && Compare()(array[left_child], array[i])){
            largest_child = left_child;
        }
        if(right_child < real_size && Compare()(array[right_child], array[largest_child])){
            largest_child = right_child;
        }

        if(largest_child == i){
            return;
        }

        std::swap(array[i], array[largest_child]);
        i = largest_child;
    }
}

template<typename T, class Compare>
void BinaryHeap<T, Compare>::shift_up(long index)
{
    while( index > 0 ){
        int parent = (index - 1) / 2;
        if(!Compare()(array[index], array[parent]))
            return;
        std::swap(array[index], array[parent]);
        index = parent;
    }
}

template<typename T, class Compare>
int BinaryHeap<T, Compare>::build_binary_heap()
{
    for(long i = real_size / 2 - 1; i >= 0; i--){
        heapify(i);
    }
    return 0;
}

template<typename T, class Compare>
T BinaryHeap<T, Compare>::get_max()
{
    assert(real_size > 0);
    return array[0];
}

template<typename T, class Compare>
T BinaryHeap<T, Compare>::extract_max()
{
    assert(real_size > 0);
    T result = array[0];
    array[0] = array[--real_size];
    array[real_size].element = 0;
    if(real_size > 0){
        heapify(0);
    }
    return result;
}

template<typename T, class Compare>
T* BinaryHeap<T, Compare>::realloc_heap(T* array, int size)
{
    heap_size *= 2;
    T* new_array = new T[heap_size];
    if(!new_array){
        heap_size /= 2;
        return nullptr;
    }
    for(int i = 0; i < size; i++){
        new_array[i] = array[i];
    }
    delete[] array;
    return new_array;
}

template<typename T, class Compare>
void BinaryHeap<T, Compare>::add(const T value)
{
    if(real_size == heap_size){
        array = realloc_heap(array, heap_size);
    }
    array[real_size++] = value;
    shift_up(real_size - 1);
}

int main()
{
    long size = 0;
    cin >> size;

    items<int> *array = new items<int>[size];
    if(!array)
        return -1;
    for(int i = 0; i < size; i++){
        cin >> array[i].element;
        array[i].index = i;
    }

    int window_size = 0;
    cin >> window_size;

    BinaryHeap<items<int>, IsMore<int>>* bh = new BinaryHeap<items<int>, IsMore<int>>(array, window_size);
    cout << (bh->get_max()).element << " ";
    for(int i = window_size; i < size; i++){
        bh->add(array[i]);
        items<int> temp = bh->get_max();
        while(temp.index < (i + 1 - window_size)){
            temp = bh->extract_max();
        }
        cout << temp.element << " ";
    }
    delete[] array;
    return 0;
}
