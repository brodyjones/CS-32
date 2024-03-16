//
//  PersonProfile.h
//  cs32.proj4
//
//  Created by Brody Jones on 3/2/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include <stdio.h>
#include <string>
#include <iostream>
#include "RadixTree.h"
#include <vector>
#include "provided.h"

    
class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    RadixTree<int> m_tree;
    std::vector<AttValPair> m_vec;
    int m_num;
    string m_name;
    string m_email;
};

#endif /* PersonProfile_h */
