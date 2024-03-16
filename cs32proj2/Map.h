//
//  Map.hpp
//  cs32proj2
//
//  Created by Brody Jones on 1/20/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <stdio.h>
#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
  public:
    Map();
    ~Map();
    Map(const Map& old);
    Map& operator=(const Map& old);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
  private:
    struct Node
    {
        KeyType k;
        ValueType v;
        Node *next;
        Node *prev;
    };
    Node *head;
    Node *tail;
    int m_n;
};

bool merge(const Map& m1, const Map& m2, Map& result);

void reassign(const Map& m, Map& result);

#endif /* Map_h */
