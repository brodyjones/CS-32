//
//  RadixTree.h
//  cs32.proj4
//
//  Created by Brody Jones on 3/2/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef RadixTree_h
#define RadixTree_h

#include <map>
#include <string>
using namespace std;
template <typename ValueType>
class RadixTree
{
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
private:
    std::map<std::string, ValueType>* m_map; // had to use std::map
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree(){
    m_map = new std::map<std::string, ValueType>; // allocated new map
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree(){
    delete m_map; // deletes map
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value){
    ValueType v = value;
    (*m_map)[key] = v; // inserts value into map
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{
    typename std::map<std::string,ValueType>::iterator it;
    it = m_map->find(key); // search for key in map
    if(it == m_map->end()){
        return nullptr; // if not found return nullptr
    }
    ValueType* vptr = &(it->second);
    return vptr; // otherweise return a pointer to the valuetype
}


#endif /* RadixTree_h */
