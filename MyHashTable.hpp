#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <functional>
using namespace std;

template <class K, class V>
class MyHashTable {
    public:
        //Constructor
        MyHashTable(size_t bucketCount = 20011) : mBuckets(bucketCount), mSize(0) {}

        //Destructor
        ~MyHashTable() = default;

        //Member functions
        void insert(const K& key, const V& value);
        V* find(const K& key);
        size_t size() const;
        size_t bucketCount() const;

    private:
        //data members
        vector<list<pair<K, V>>> mBuckets;
        size_t mSize;
        
        //private member functions
        size_t getBucketIndex(const K& key) const;
};

template <class K, class V>
void MyHashTable<K, V>::insert(const K &key, const V &value)
{
    size_t index = getBucketIndex(key);
    list<pair<K, V>>& bucket = this->mBuckets[index];

    bool isFound = false;

    for (typename list<pair<K, V>>::iterator it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            it->second = value;
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        bucket.emplace_back(key, value); //using the list to implement separate chaining
        ++this->mSize;
    }
}

template <class K, class V>
V* MyHashTable<K, V>::find(const K &key)
{
    size_t index = getBucketIndex(key);
    list<pair<K, V>>& bucket = this->mBuckets[index];

    for (typename list<pair<K, V>>::iterator it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            return &it->second;
        }
    }

    return nullptr;
}

template <class K, class V>
size_t MyHashTable<K, V>::size() const
{
    return this->mSize;
}

template <class K, class V>
size_t MyHashTable<K, V>::bucketCount() const
{
    return this->mBuckets.size();
}

template <class K, class V>
size_t MyHashTable<K, V>::getBucketIndex(const K &key) const
{
    size_t hashVal = hash<K>{}(key);

    return hashVal % this->mBuckets.size();                   //map to bucket
}
