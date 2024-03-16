//
//  Map.cpp
//  cs32proj2
//
//  Created by Brody Jones on 1/20/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#include "Map.h"
#include <iostream>

using namespace std;

Map::Map()
{
    m_n = 0;
    head = nullptr;
    tail = nullptr;
    //creates an empty map with zero members
    //sets head and tail to nullptr
}

bool Map::empty() const
{
    if(m_n == 0){
        return true;
    }
    else{
        return false;
    }
    //returns true if there are zero members in map
}

int Map::size() const
{
    return m_n;
    //returns the size of the map
}

bool Map::insert(const KeyType& key, const ValueType& value)
{

    Node *r;
    r = head;
    while(r != nullptr){
        if(r->k == key){
            return false;
        }
        r = r->next;
    }
    //checks if key is already in map
    
    //adds to front
    Node *p;
    p = new Node;
    p->k = key;
    p->v = value;
    p->next = head;
    p->prev = nullptr;
    if(head == nullptr){//if there are no previous elements, we must attatch the tail too
        head = p;
        tail = p;
    }
    else{
        head = p;
        p->next->prev = p;//otherwise we just attatch the next node
    }
    m_n++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    if(head == nullptr){
        return false;//if the map is empty
    }
    Node *p;
    p = head;
    while(p != nullptr){
        if(p->k == key){//when p points at the node with the corresponding key
            p->v = value;//update the value
            return true;
        }
        p = p->next;
    }
    
    return false; // otherwise return false if key not found
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{

    if(update(key, value)){
        return true;
    }
    else{
        insert(key, value);
        return true;
    }
}

bool Map::erase(const KeyType& key)
{
    //CHANGE TO ACCOUNT FOR TAIL!!!!!
    if(head == nullptr){
        return false;//can't erase a node if there arent any
    }
    
    if(head->k == key){ //check if the first node needs to be erased
        Node *killMe = head;
        head = head->next;
        delete killMe;
        if(head == nullptr){
            tail = nullptr;
        }
        else{
            head->prev = nullptr; //deletes the first node and reassignes the head
        }
        m_n--;
        return true;
    }
    
    Node *p = head;
    while(p != nullptr){
        if(p->next != nullptr && p->next->k == key){
            break; //stops at the node above the one we want to delete
        }
        p = p->next;
    }
    if(p == nullptr){//key wasnt in list
        return false;
    }
    Node *kill = p->next;
    p->next = kill->next;
    if(kill->next != nullptr){
        kill->next->prev = p;//if our kill node is in the middle of the list
    }
    else{
        tail = p;//if out kill node is the last one
    }
    delete kill;
    m_n--; //adjusts m_n if a node is erased
    return true;
}

bool Map::contains(const KeyType& key) const
{
    Node *p;
    p = head;
    while(p != nullptr){
        if(p->k == key){
            return true; //increments through the map and returns true if key is found
        }
        p = p->next;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    if(contains(key) == false){
        return false; // returns false if map doesnt contain key
    }
    Node *p;
    p = head;
    while(p != nullptr){
        if(p->k == key){//when p points at the node with the corresponding key
            value = p->v;//set value equal to v
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if(i < 0){
        return false;
    }
    if(i >= m_n){
        return false;
    } // makes sure i is a valid number
    
    Node *p;
    p = head;
    while(p != nullptr){
        int count = 0; // increments through every node and counts how many nodes it is greater than
        Node *r;
        r = head;
        while(r != nullptr){
            if(r->k < p->k){
                count++;
            }
            r = r->next;
        }
        if(count == i){ // if the count is equal to i, then we set key and value accordingly
            key = p->k;
            value = p->v;
            return true;
        }
        p = p->next;
    }
    return true;
}

void Map::swap(Map& other)
{
    Node *temp;
    int tempSize;
    
    temp = head;
    head = other.head;//swaps head pointers
    other.head = temp;
    
    temp = tail;
    tail = other.tail;//swaps tail pointers
    other.tail = temp;
    
    tempSize = m_n;
    m_n = other.m_n;//swaps sizes
    other.m_n = tempSize;
}

//Destructor//////////////

Map::~Map()
{
    Node *p;
    Node *kill;
    p = head;
    while(p != nullptr){//increments through and delets each item
        kill = p;
        p = p->next;
        delete kill;
    }
    head = nullptr;
    tail = nullptr;
}

Map::Map(const Map& old)
{
    head = nullptr;
    tail = nullptr;
    
    Node *p;
    p = old.head;
    while(p != nullptr){ //increments through old and adds each node from old into new
        insert(p->k, p->v);
        p = p->next;
    }
}

Map& Map::operator=(const Map& old)
{
    if(head == old.head  && m_n == old.m_n){ // deals with aliasing
        return *this;
    }
    
    Node *p;
    Node *kill;
    p = head;
    while(p != nullptr){
        kill = p;
        p = p->next;
        delete kill;//clears out new map
    }
    m_n = 0;
    head = nullptr;
    tail = nullptr;
    
    Node *r;
    r = old.head;
    while(r != nullptr){
        insert(r->k, r->v); // build the new map from the old nodes
        r = r->next;
    }
    
    return *this;
}

bool merge(const Map& m1, const Map& m2, Map& result)
{
    KeyType k;
    ValueType v;
    int i = 0;
    
    result = m1;
    for(i = 0;i < m2.size(); i++){
        m2.get(i, k, v);
        result.insert(k, v);  // adds all nodes from m1 and m2 to result
    }
    
    KeyType k1;
    ValueType v1;
    KeyType k2;
    ValueType v2;
    bool valid = true;
    
    for(i = 0; i < m1.size(); i++){
        m1.get(i, k1, v1);
        for(int j = 0; j < m2.size(); j++){
            m2.get(j, k2, v2);
            if(k2 == k1){
                if(v2 != v1){
                    valid = false;
                    result.erase(k1); // checks that if any key appears in m1 and m2, that the values are equal, if they are not, we erase the node and return false
                }
            }
        }
    }
    
    return valid;
}

void reassign(const Map& m, Map& result)
{
    KeyType k;
    ValueType v;
    int i = 0;
    
    KeyType k1;
    ValueType v1;
    KeyType k2;
    ValueType v2;
    ValueType temp;
    bool equals = false;
    
    if(m.size() == result.size()){//checks if m and result are the same for aliasing
        equals = true;
        for(i = 0; i < m.size(); i++){
            m.get(i, k1, v1);
            result.get(i, k2, v2);
            if(k1 != k2 or v1 != v2){
                equals = false;
            }
        }
    }
    
    if(equals){  // deals with aliasing without deleting the result map
        if(m.size() == 0 or m.size() == 1){
            return;
        }
        m.get(0, k1, v1);
        temp = v1;
        for(i = 1; i < m.size(); i++){
            m.get(i-1, k1, v1);
            m.get(i, k2, v2);
            result.update(k2, temp);
            temp = v2;
        }
        m.get(0, k1, v1);
        result.update(k1, temp);
        return;
    }
    
    int s = result.size();
    for(i = 0; i < s; i++){
        result.get(0, k, v);
        result.erase(k);//clears out the original result map
    }
    
    if(m.size() == 0){ // returns an empty map if m is empty
        return;
    }
    
    if(m.size() == 1){// just inserts the one node in m
        m.get(0, k, v);
        result.insert(k, v);
    }
    
    
    for(i = 1; i < m.size(); i++){ // assigns every key to the value of the key before it
        m.get(i-1, k1, v1);
        m.get(i, k2, v2);
        result.insert(k2, v1);
    }
    
    m.get(0, k1, v1);
    result.insert(k1, v2); // sorts out the last node
    return;
}
