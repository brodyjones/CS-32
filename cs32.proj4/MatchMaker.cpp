//
//  MatchMaker.cpp
//  cs32.proj4
//
//  Created by Brody Jones on 3/2/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#include "MatchMaker.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "provided.h"
#include "RadixTree.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    m_db = &mdb;
    m_at = &at;
    m_compatTree = new RadixTree<int>;
    m_vec = new std::vector<AttValPair>;
    m_num = new int;
    //assign all of our pointers
}
MatchMaker::~MatchMaker(){
    delete m_compatTree;
    delete m_vec;
    delete m_num; // delete dynamically allocated items
}
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const{
    const PersonProfile* p;
    p = m_db->GetMemberByEmail(email); // assigns the pointer to given person
    AttValPair av;
    for(int i = 0; i < p->GetNumAttValPairs(); i++){ // for each pair
        if(p->GetAttVal(i, av)){
            std::vector<AttValPair> compatible = m_at->FindCompatibleAttValPairs(av);
            //find compatible attval pairs
            for(int k = 0; k < compatible.size(); k++){
                std::string attval = compatible[k].attribute + compatible[k].value;
                int* ptr = m_compatTree->search(attval); // checks for duplicates
                if(ptr == nullptr){ // if val isnt already in tree
                    m_compatTree->insert(attval, *m_num);
                    m_vec->push_back(compatible[k]); // add pair to tree and vector
                    (*m_num)++;
                }
            }
        }
    }
    std::vector<std::vector<std::string>> emailList;
    RadixTree<int> combatibleCount;
    std::vector<EmailCount> emails;
    int loc = 0;
    for(int j = 0; j < m_vec->size(); j++){ // for each compatible attribute
        std::vector<std::string> tempV = m_db->FindMatchingMembers((*m_vec)[j]);
        //find members who have the trait
        emailList.push_back(tempV); // push these people into a list
        for(int i = 0; i < tempV.size(); i++){ // for each person in the list
            int* ptr = combatibleCount.search(tempV[i]);
            if(ptr == nullptr){ // if not in counting tree
                combatibleCount.insert(tempV[i], loc); // insert
                EmailCount e(tempV[i], 1);
                emails.push_back(e); // add to vector
                loc++;
            }
            else{
                emails[*ptr].count++; // if they are in tree, just increment their count
            }
        }
    }
    

    
    
    std::vector<EmailCount> finalEmails;
    for(int j = 20; j >= 0; j--){
        for(int i = 0; i < emails.size(); i++){
            if(emails[i].email == email){
                i++;
                continue;
            }
            if(emails[i].count >= threshold + j){ // for every person that is above the threshold
                finalEmails.push_back(emails[i]); // add them to final list
                emails[i].count = -1; // so we dont readd it
            }
        }
    }
    
    return finalEmails;
}
