//
//  PersonProfile.cpp
//  cs32.proj4
//
//  Created by Brody Jones on 3/2/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#include "PersonProfile.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "RadixTree.h"

PersonProfile::PersonProfile(std::string name, std::string email)
: m_name(name), m_email(email), m_num(0) {}


std::string PersonProfile::GetName() const{
    return m_name;// initializes name
}

std::string PersonProfile::GetEmail() const{
    return m_email; // initializes email
}

PersonProfile::~PersonProfile(){
    // defaul destructor should work fine here
}

void PersonProfile::AddAttValPair(const AttValPair& attval){
    std::string av = attval.attribute + attval.value;
    int* ptr = m_tree.search(av); // search for pair in tree
    if(ptr == nullptr){ // if it is not already in the tree
        m_tree.insert(av, m_num);
        m_vec.push_back(attval); // intert to tree and vector
        m_num++;
    }
    else{
        return;
    }
}

int PersonProfile::GetNumAttValPairs() const{
    return m_num;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
    if(attribute_num < 0 or attribute_num >= m_num){
        return false; // checks bounds
    }
    attval = m_vec[attribute_num]; // return pair thats at given index
    return true;
}
