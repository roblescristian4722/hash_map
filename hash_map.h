#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <iostream>
#include <sstream>
#include "LSL.h"
#define DEFAULT_MOD 13
using namespace std;

/////////////////////////
//// EXTRA FUNCTIONS ////
/////////////////////////
size_t string_to_size_t(string str);

template <typename T>
long binary_search(LSL<T> &list, T data);

//////////////
//// NODE ////
//////////////
template <typename K, typename V>
class Node
{
private:
    K key;
    V value;

public:
    Node() {}
    Node(K _key, V _val) : key(_key), value(_val) {}
    ~Node() {}

    void setKey(const K &val)
    { key = val; }
    void setValue(const V &val)
    { value = val; }

    K getKey() const
    { return key; }
    V *getValue()
    { return &value; }
    bool operator>(Node<K, V> &other)
    { return this->getKey() > other.getKey(); }

    bool operator==(Node<K, V> &other)
    { return this->getKey() == other.getKey(); }

    bool operator<(Node<K, V> &other)
    { return this->getKey() < other.getKey(); }
};

////////////////
//// BUCKET ////
////////////////
template <typename K, typename V>
class Bucket
{
private:
    size_t m_hashValue;
    LSL<Node<K, V>> m_values;

public:
    Bucket() {}
    ~Bucket()
    { m_values.clear(); }

    size_t size_bucket()
    { return m_values.size(); }

    //funciones para la lista ligada
    LSL<Node<K, V>> &getValues()
    { return m_values; }

    void append(const Node<K, V> &node)
    { m_values.push_back(node); }

    //funciones para el valor de hash
    void setHashValue(size_t val)
    { m_hashValue = val; }

    size_t getHashValue() const
    { return m_hashValue; }

    bool operator>(Bucket<K, V> &other)
    { return this->getHashValue() > other.getHashValue(); }

    bool operator<(Bucket<K, V> &other)
    { return this->getHashValue() < other.getHashValue(); }

    bool operator==(Bucket<K, V> &other)
    { return this->getHashValue() == other.getHashValue(); }
};
//////////////////
//// HASH MAP ////
//////////////////
template <typename K, typename V>
class HashMap
{
private:
    LSL<Bucket<K, V>> m_buckets;
    size_t m_mod;

public:
    HashMap(size_t mod = DEFAULT_MOD) : m_mod(mod) {}
    ~HashMap()
    { clear(); }

    bool is_empty();
    long is_colide(size_t hash);
    size_t size();

    void insert(const K &keyVal, const V &val);
    void delete_value(const K &keyVal);
    void clear();
    V *operator[](K index);
    size_t hash_function(K val);
};

//////////////////////
//// HASH MAP     ////
//// DEFINITIONS  ////
//////////////////////

// Returns true if empty
// and false otherwise
template <typename K, typename V>
bool HashMap<K, V>::is_empty()
{ return m_buckets.empty(); }

// indicates wheter the hash value returned
// by hash_function already exists and if it does this
// method gives you it's exact position
template <typename K, typename V>
long HashMap<K, V>::is_colide(size_t hash)
{
    if (is_empty())
        return -1;

    Bucket<K, V> bucketTmp;
    bucketTmp.setHashValue(hash);
    return binary_search(m_buckets, bucketTmp);
}

// Returns the total size of the hash map (i.e. the
// summation of the size of every bucket in buckets list)
template <typename K, typename V>
size_t HashMap<K, V>::size()
{
    size_t sizeTotal = 0;
    for (size_t i = 0; i < m_buckets.size(); ++i)
        sizeTotal += m_buckets[i].size_bucket();
    return sizeTotal;
}

// Inserts a new node in the hash map
template <typename K, typename V>
void HashMap<K, V>::insert(const K &keyVal, const V &val)
{
    Node<K, V> n(keyVal, val);
    Bucket<K, V> b;
    long pos;
    size_t hash;

    hash = hash_function(keyVal);
    pos = is_colide(hash);
    if (pos != -1) {
        m_buckets[pos].append(n);
        sort(m_buckets[pos].getValues());
    }

    else {
        b.setHashValue(hash);
        b.append(n);
        m_buckets.push_back(b);
        sort(m_buckets);
    }
}

// Deletes an existing value in the hash map
template <typename K, typename V>
void HashMap<K, V>::delete_value(const K &keyVal)
{
    size_t aux = hash_function(keyVal);
    size_t i;
    LSL<Node<K, V>> *auxList;
    long pos = is_colide(hash_function(keyVal));

    if (pos != -1){
        auxList = &m_buckets[pos].getValues();

        for (i = 0; i < auxList->size(); ++i)
            if ((*auxList)[i].getKey() == keyVal) {
                auxList->erase(i);
                break;
            }
        if (auxList->empty())
            m_buckets.erase(pos);
        else if (auxList->size() == i)
            cout << "There is not such value" << endl;
    }
    else
        cout << "There is not such value" << endl;
    cout << m_buckets.size() << endl;
}

// Removes every value stored in the hash map
template <typename K, typename V>
void HashMap<K, V>::clear()
{ m_buckets.clear(); }

template <typename K, typename V>
size_t HashMap<K, V>::hash_function(K val)
{
    stringstream ss;
    ss << val;
    string aux = ss.str();
    return string_to_size_t(aux) % m_mod;
}

// Returns a value stored in the hash map
// using a key as the way to find it
template <typename K, typename V>
V *HashMap<K, V>::operator[](K index)
{
    LSL<Node<K, V>> *auxList;
    Node<K, V> nodeTmp;
    long posNode;
    size_t hashValue = hash_function(index);
    long posBucket = is_colide(hashValue);
    V *v = nullptr;

    nodeTmp.setKey(index);
    if (posBucket != -1) {
        auxList = &m_buckets[posBucket].getValues();
        posNode = binary_search(*auxList, nodeTmp);
        if (posNode != -1)
            v = (*auxList)[posNode].getValue();
    }
    return v;
}

/////////////////////////
//// EXTRA FUNCTIONS ////
//// DEFINITIONS     ////
/////////////////////////
size_t string_to_size_t(string str)
{
    size_t sum = 0;
    for (size_t i = 0; i < str.length(); ++i)
        sum += (size_t)str[i];
    return sum + (size_t)str.length();
}

template <typename T>
long binary_search(LSL<T> &list, T data)
{
    int l = 0;
    int r = int(list.size() - 1);
    while (l <= r) {
        int m = (l + r) / 2;
        if (data == list[m])
            return m;
        else if (data < list[m])
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

#endif //HASHMAP_H