#include <iostream>
#include <stdlib.h>
#include <assert.h>

//Формат входных данных.
//В первой строке количество команд n. n ≤ 1000000.
//Каждая команда задаётся как 2 целых числа: a b.
//a = 2 - pop front
//a = 3 - push back
//Команда добавления элемента 3 заданы с неотрицательным параметром b.
//Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
//Если дана команда pop*, то число b - ожидаемое значение.
//Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
//Формат выходных данных.
//Требуется напечатать YES - если все ожидаемые значения совпали.
//Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

//Реализовать очередь с динамическим зацикленным буфером.



using namespace std;

template <class T>
class Queue
{
public:
    Queue();
    ~Queue();

    void pushBack(const T& data);
    T popFront();
    bool IsEmpty(){return (!countElements ? 1 : 0);}

private:
    T* reallocQueue(const int size);
    T* buffer;
    size_t allocSize;
    size_t countElements;
    T* head;
    T* tail;
};

template<class T>
Queue<T>::Queue():
    allocSize(5),
    countElements(0),
    head(nullptr),
    tail(nullptr)
{
    buffer = new T[allocSize];
    if(!buffer){
        allocSize = 0;
        buffer = nullptr;
    }
    head = buffer;
    tail = buffer;
}

template<class T>
Queue<T>::~Queue()
{
    delete[] buffer;
}

template<class T>
T* Queue<T>::reallocQueue(const int size){
    T* newBuffer = new T[size];
    if(!newBuffer)
        return nullptr;
    T* newTail = newBuffer;
    int currentSize = countElements;
    for(int i = 0; i < currentSize; i++){
        *newTail = popFront();
        newTail++;
    }
    countElements = currentSize;
    delete[] buffer;
    allocSize = size;
    buffer = newBuffer;
    head = newBuffer;
    tail = newTail;
    return buffer;
}

template<class T>
void Queue<T>::pushBack(const T& data)
{
    if(countElements == allocSize){
        int newAllocSize = allocSize * 2;
        buffer = reallocQueue(newAllocSize);
    }
    if(tail == buffer + allocSize){
        tail = buffer;
    }
    *tail++ = data;
    countElements++;
}

template<class T>
T Queue<T>::popFront()
{
    assert(!IsEmpty());
    T tempData;
    if(head != buffer + allocSize - 1){
        tempData = *head;
        head++;
    } else {
        tempData = *head;
        head = buffer;
    }
    countElements--;
    return tempData;
}

int main()
{
    Queue<int> queue;
    int n = 0;
    cin >> n;
    bool result = true;
    for(int i = 0; i < n; i++){
        int command = 0;
        int data = 0;
        cin >> command >> data;
        switch (command) {
        case 2:
            if(queue.IsEmpty()) {
                result = result && data == -1;
            }else{
                result = result && queue.popFront() == data;
            }
            break;
        case 3:
            queue.pushBack(data);
        default:
            break;
        }
    }
    cout << (result ? "YES" : "NO");
    return 0;
}
