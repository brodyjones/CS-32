//
//  MatchMaker.h
//  cs32.proj4
//
//  Created by Brody Jones on 3/2/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "provided.h"
#include "RadixTree.h"

class MemberDatabase;

class AttributeTranslator;


class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    const MemberDatabase* m_db;
    const AttributeTranslator* m_at;
    RadixTree<int>* m_compatTree;
    std::vector<AttValPair>* m_vec;
    int* m_num;
};

#endif /* MatchMaker_h */
