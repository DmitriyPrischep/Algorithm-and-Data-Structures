#include <iostream>
#include <assert.h>

//5_2. Современники.
//Группа людей называется современниками если был такой момент,
//когда они могли собраться вместе. Для этого в этот момент
//каждому из них должно было  уже исполниться 18 лет,
//но ещё не исполниться 80 лет.
//Дан список Жизни Великих Людей. Необходимо получить максимальное
//количество современников. В день 18летия человек уже может
//принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
//Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия.
//В этих случаях принимать участие в собраниях он не мог.

using namespace std;

class Date
{
public:
    int day;
    int month;
    int year;
    bool born;
    Date() {
        day = 0;
        month = 0;
        year = 0;
        born = false;
    }
};

//std=c17++
//bool operator < (const Date& first, const Date& second){
//    return std::tie(first.day, first.month, first.year) < std::tie(second.day, second.month, second.year);
//}


template<class T>
class IsLess
{
public:
    bool operator () (const T& first, const T& second)
    {
        if (first.year == second.year){
            if(first.month == second.month){
                return first.day <= second.day;
            }
            return first.month <= second.month;
        }
        return first.year <= second.year;
    }
};

bool operator < (const Date& first, const Date& second)
{
    if (first.year == second.year){
        if(first.month == second.month){
            return first.day < second.day;
        }
        return first.month < second.month;
    }
    return first.year < second.year;
}

void swap(Date first, Date second)
{
    Date temp = first;
    first = second;
    second = temp;
}

template<typename T, class Compare>
void merge(T* array, int low, int middle, int high, Compare comp)
{
    T* buffer = new T[high - low + 1];
    int i = low;
    int j = middle + 1;
    int k = 0;
    while(i <= middle && j <= high){
        if(comp(array[i], array[j]))
            buffer[k++] = array[i++];
        else
            buffer[k++] = array[j++];
    }
    while(i <= middle){
        buffer[k++] = array[i++];
    }
    while(j <= high){
        buffer[k++] = array[j++];
    }
    for(k = 0, i = low; i <= high; ++i, ++k){
        array[i] = buffer[k];
    }
    delete[] buffer;
}

template<typename T, class Compare>
void split_array(T* array, unsigned int low, unsigned int high, Compare comp)
{
    if(low >= high)
        return;
    int middle = (low + high) >> 1;
    split_array(array, low, middle, comp);
    split_array(array, middle + 1, high, comp);
    merge(array, low, middle, high, comp);
}

template<typename T, class Compare>
void merge_sort(T* array, int n, Compare comp = IsLess<T>())
{
    split_array(array, 0, n - 1, comp);
}

int count_contemporaries(Date* people, int n)
{
    merge_sort(people, n, IsLess<Date>());
    int max_count = 0;
    int count = 0;
    for(int i = 0; i < n; i++){
        if(people[i].born)
            count++;
        else
            count--;
        if(count > max_count)
            max_count = count;
    }
    return max_count;
}


int main()
{
    int n = 0;
    cin >> n;
    n *= 2;

    Date* people = new Date[n];

    int real_size = 0;
    for(int i = 0; i < n/2; i++){
        Date born;
        born.born = true;
        cin >> born.day >> born.month >> born.year;
        Date dead;
        dead.born = false;
        cin >> dead.day >> dead.month >> dead.year;

        born.year += 18;
        if(born < dead){
            people[2*real_size] = born;
            born.year += 62;
            if(born < dead){
                born.born = false;
                people[2*real_size + 1] = born;
            } else {
                people[2*real_size + 1] = dead;
            }
            real_size++;
        }
    }

    cout << count_contemporaries(people, real_size * 2) << endl;
    delete[] people;

    return 0;
}
