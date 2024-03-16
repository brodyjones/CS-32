//
//  AttributeTranslator.cpp
//  cs32.proj4
//
//  Created by Brody Jones on 3/2/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#include "AttributeTranslator.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "provided.h"
#include "RadixTree.h"



AttributeTranslator::AttributeTranslator(){
    
}
// nothing to initialize of destruct
AttributeTranslator::~AttributeTranslator(){
    
}

bool AttributeTranslator::Load(std::string filename){
    
    std::ifstream infile(filename);
    if (infile.is_open())
    { // access file and while its open
        std::string line;
        while(std::getline(infile, line)){ // while there are still input lines
            std::istringstream ss(line);
            std::string att1, val1, att2, val2, attval1;
            getline(ss, att1, ',');
            getline(ss, val1, ',');
            getline(ss, att2, ',');
            getline(ss, val2); // assign att val pairs to their appropriate spot
            attval1 = att1 + val1;
            AttValPair pair;
            pair.attribute = att2;
            pair.value = val2;
            vector<AttValPair>* ptr = m_tree.search(attval1); // search for first pai in the tree
            if(ptr == nullptr){
                vector<AttValPair> vec;
                vec.push_back(pair);
                m_tree.insert(attval1, vec); // if not in tree, create a new vector and add it to tree
            }
            else{
                bool dupli = false;
                for(int i = 0; i < ptr->size(); i++){
                    if((*ptr)[i] == pair){
                        dupli = true; // checks for duplicates within the vector
                    }
                }
                if(dupli == false){
                    ptr->push_back(pair); // adds pair to the vector
                }
            }
        }
    }
    return true;// chasnge this
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const{
    std::string attval1 = source.attribute + source.value;
    vector<AttValPair>* ptr = m_tree.search(attval1); // search for vector
    vector<AttValPair> v;
    if(ptr == nullptr){
        return v; // if no matching vector, return an empty one
    }
    return *ptr; // otherwise we return the appropriate vector
    
}
