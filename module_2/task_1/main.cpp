#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int DEFAULT_TABLE_SIZE = 8;
const double MAX_ALPHA = 0.75;
const int FACTOR_GROW = 2;
const int FACTOR_GORNER = 137;
const int FACTOR_GORNER_2 = 211;

int doubleHash(int tableSize, int firstHash, int secondHash, int index)
{
    return (firstHash + index * secondHash) % tableSize;
}

int firstHash(const std::string data, int tableSize)
{
    int hashCode = 0;
    for(unsigned int i = 0; i < data.size(); i++ ){
        hashCode = (hashCode * FACTOR_GORNER + data[i]) % tableSize;
    }
    return hashCode;
}

int secondHash(const std::string data, int tableSize)
{
//    return data.length() * 2 + 1;
    int hashCode = 0;
    for(unsigned int i = 0; i < data.size(); i++ ){
        hashCode = (hashCode * FACTOR_GORNER_2 + data[i]) % tableSize;
    }
    return hashCode * 2 + 1;
}

template<class T>
class HashTable{
public:
    HashTable(const T& delValue, const T& emptyValue);

    HashTable(const HashTable<T>& table) = delete;
    HashTable(HashTable<T>& table) = delete;
    ~HashTable() = default;

    HashTable<T>& operator = (const HashTable<T>& table) = delete;
    bool has(const T& data) const;
    bool add(const T& data);
    bool remove(const T& data);

private:
    void growTable();
    std::vector<T> table;
    unsigned int countKeys;
    T _emptyValue;
    T _delValue;
};

template<class T>
HashTable<T>::HashTable(const T &delValue, const T &emptyValue) :
    countKeys(0),
    _emptyValue(emptyValue),
    _delValue(delValue)
{
    table.resize(DEFAULT_TABLE_SIZE);
    for (size_t i = 0; i < table.size(); i++){
        table[i] = emptyValue;
    }
}

template<class T>
bool HashTable<T>::add(const T& data)
{
    if(countKeys + 1 > table.size() * MAX_ALPHA)
        growTable();
    int hashOne = firstHash(data, table.size());
    int hashTwo = 0;
    int allHash = 0;
    for(size_t i = 0;; i++){
        if(i == 1)
            hashTwo = secondHash(data, table.size());
        allHash = doubleHash(table.size(), hashOne, hashTwo, i);
        if(table[allHash] == data)
            return false;
        if(table[allHash] == _emptyValue || table[allHash] == _delValue)
            break;
    }
    table[allHash] = data;
    countKeys++;
    return true;
}

template<class T>
bool HashTable<T>::has(const T &data) const
{
    int hashOne = firstHash(data, table.size());
    if(table[hashOne] == data){
        return true;
    } else if (table[hashOne] == _emptyValue) {
        return false;
    } else {
        int hashTwo = secondHash(data, table.size());
        int allHash = 0;
        size_t i = 0;
        do {
            allHash = doubleHash(table.size(), hashOne, hashTwo, i);
            i++;
            if (table[allHash] == _emptyValue){
                return false;
            }
        } while (table[allHash] != data  && i < table.size());

        if(table[allHash] == data){
            return true;
        } else {
            return false;
        }
    }
}

template<class T>
bool HashTable<T>::remove(const T& data)
{
    int hashOne = firstHash(data, table.size());
    int hashTwo = 0;
    int allHash = 0;
    for(unsigned int i = 0;  i < table.size() ; i++){
        (i == 1) ? hashTwo = secondHash(data, table.size()) : 0 ;
        allHash = doubleHash(table.size(), hashOne, hashTwo, i);
        if(table[allHash] == data){
            table[allHash] = _delValue;
            countKeys--;
            return true;
        }
        if (table[allHash] == _emptyValue){
            return false;
        }
    }
    return false;
}

template<class T>
void HashTable<T>::growTable()
{
    size_t new_size = table.size() * FACTOR_GROW;
    std::vector<T> newTable(new_size);
    for (size_t i = 0; i < newTable.size(); i++){
        newTable[i] = _emptyValue;
    }
    for (size_t i = 0; i < table.size(); i++){
        if(!(table[i] == _delValue || table[i] == _emptyValue)){
            int hashOne = firstHash(table[i], new_size);
            if (newTable[hashOne] == _emptyValue){
                newTable[hashOne] = table[i];
            } else {
                int allHash = hashOne;
                int hashTwo = secondHash(table[i], newTable.size());
                for(size_t j = 0; j < newTable.size() && newTable[allHash] != _emptyValue; j++){
                    allHash = doubleHash(newTable.size(), hashOne, hashTwo, j);
                }
                newTable[allHash] = table[i];
            }
        }
    }
    table = newTable;
}

int main()
{
    HashTable<string> table("DEL_PRISCHEP", "EMP_PRISCHEP");
    char operation = 0;
    string data;
    while(cin >> operation >> data) {
        if(operation == '+')
            cout << (table.add(data) ? "OK" : "FAIL") << endl;
        if(operation == '?')
            cout << (table.has(data) ? "OK" : "FAIL") << endl;
        if(operation == '-')
            cout << (table.remove(data) ? "OK" : "FAIL") << endl;
    }
    return 0;
}