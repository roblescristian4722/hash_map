#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <iostream>
#include <sstream>
#include "lsl.h"
#define PRIMO 211
#define DEFAULT_MOD 13
using namespace std;

//// CLASS PROTOTYPES ////
template<typename K, typename V>
class Node;
template <typename K, typename V>
class Bucket;
template <typename K, typename V>
class HashMap;

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

    bool operator>(Node<K, V> &other)
    { return this->key > other.key; }

    bool operator==(Node<K, V> &other)
    { return this->key == other.key; }

    bool operator<(Node<K, V> &other)
    { return this->key < other.key; }

    friend class Bucket<K,V>;
    friend class HashMap<K, V>;
};

////////////////
//// BUCKET ////
////////////////
template <typename K, typename V>
class Bucket
{
private:
    LSL<Node<K, V>> m_nodes;
    bool m_visited;
public:
    Bucket() {}
    ~Bucket()
    { m_nodes.clear(); }

    size_t bucket_size()
    { return m_nodes.size(); }

    void append(const Node<K, V> &node)
    { m_nodes.push_back(node); }

    bool operator>(Bucket<K, V> &other)
    { return this->m_hashValue > other.m_hashValue; }

    bool operator<(Bucket<K, V> &other)
    { return this->m_hashValue < other.m_hashValue; }

    bool operator==(Bucket<K, V> &other)
    { return this->m_hashValue == other.m_hashValue; }

    friend class HashMap<K, V>;
};
//////////////////
//// HASH MAP ////
//////////////////
template <typename K, typename V>
class HashMap
{
private:
    Bucket<K, V>* m_buckets;
    size_t m_size;

public:
    HashMap();
    ~HashMap();

    struct Pair
    {
        K *key;
        V *value;
    };

    bool empty();
    bool colide(size_t hash);
    size_t size();

    void insert(const K &keyVal, const V &val);
    void delete_value(const K &keyVal);
    void clear();
    V *operator[](K index);
    size_t hash_function(K val);
    HashMap::Pair get_position(size_t index);
};

//////////////////////
//// HASH MAP     ////
//// DEFINITIONS  ////
//////////////////////

template <typename K, typename V>
HashMap<K, V>::HashMap()
{
    m_size = 0;
    m_buckets = new Bucket<K,V>[PRIMO];
}

template<typename K, typename V>
HashMap<K, V>::~HashMap()
{ clear(); }

// Returns true if empty
// and false otherwise
template <typename K, typename V>
bool HashMap<K, V>::empty()
{ return m_size }

// indicates wheter the hash value returned
// by hash_function already exists and if it does this
// method gives you it's exact position
template <typename K, typename V>
bool HashMap<K, V>::colide(size_t hash)
{
    if (empty())
        return false;
    if (!m_buckets[hash].m_visited)
        return false;
    return true;
}

// Returns the total size of the hash map (i.e. the
// summation of the size of every bucket in buckets list)
template <typename K, typename V>
size_t HashMap<K, V>::size()
{
    size_t sizeTotal = 0;
    for (size_t i = 0; i < PRIMO; ++i)
        if (m_buckets[i].m_visited)
            sizeTotal += m_buckets[i].bucket_size();
    return sizeTotal;
}

// Inserts a new node in the hash map
template <typename K, typename V>
void HashMap<K, V>::insert(const K &keyVal, const V &val)
{
    Node<K, V> nodeTmp(keyVal, val);
    Bucket<K, V> bucketTmp;
    bool hashColided;
    size_t hash;

    hash = hash_function(keyVal);
    m_buckets[hash].m_nodes.append(nodeTmp);
}

// Deletes an existing value in the hash map
template <typename K, typename V>
void HashMap<K, V>::delete_value(const K &keyVal)
{
    size_t aux = hash_function(keyVal);
    size_t i;
    LSL<Node<K, V>> *auxList;
    long pos = colide(hash_function(keyVal));

    if (pos != -1){
        auxList = &m_buckets[pos].m_nodes;

        for (i = 0; i < auxList->size(); ++i)
            if ((*auxList)[i].key == keyVal) {
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
}

// Removes every value stored in the hash map
template <typename K, typename V>
void HashMap<K, V>::clear()
{ m_buckets.clear(); }

// It gets the key's corresponding hash
// value using the PJW method
template <typename K, typename V>
size_t HashMap<K, V>::hash_function(K val)
{
    // The input turns into a stringstream value
    // and then turns into a string due to
    // possible numeric keys
    stringstream ss;
    char* pos;
    size_t hash = 0;
    size_t tmp;
    
    ss << val;
    string auxStr = ss.str();
    for (pos = auxStr; *pos != '\0'; ++pos){
        hash = (hash << 4) + (*pos);
        tmp = hash & 0xF0000000;
        if (tmp > 1){
            hash = hash ^ (tmp << 24);
            hash = hash ^tmp;
        }
    }
    return hash;
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
    long posBucket = colide(hashValue);
    V *v = nullptr;

    nodeTmp.key = index;
    if (posBucket != -1) {
        auxList = &m_buckets[posBucket].m_nodes;
        posNode = binary_search(*auxList, nodeTmp);
        if (posNode != -1)
            v = &(*auxList)[posNode].value;
    }
    return v;
}

#endif //HASHMAP_H