//
//  MemberDatabase.h
//  cs32.proj4
//
//  Created by Brody Jones on 3/2/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"


class MemberDatabase
{
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    RadixTree<std::vector<std::string>> attToEmail;
    RadixTree<PersonProfile*> emailToPerson;
    std::set<PersonProfile*> m_people;
    RadixTree<std::set<std::string>>  m_sets;
};

#endif /* MemberDatabase_h */
