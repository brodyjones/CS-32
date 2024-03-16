//
//  MemberDatabase.cpp
//  cs32.proj4
//
//  Created by Brody Jones on 3/2/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#include "MemberDatabase.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"

MemberDatabase::MemberDatabase(){
    
}

MemberDatabase::~MemberDatabase(){
    std::set<PersonProfile*>::iterator it = m_people.begin();
    while(it != m_people.end()){
        if(*it != nullptr){
            delete (*it);
        }
        it++;
    } // deletes all dynamically allocated PersonProfiles
}

bool MemberDatabase::LoadDatabase(std::string filename){
    
    std::ifstream infile(filename);
    if (infile.is_open())
    {
        std::string line, name, email, att, val, attval;
        int numPairs;
        while(std::getline(infile, name)){
            std::getline(infile, email); // get name and email
            PersonProfile* p = new PersonProfile(name, email); // make new person
            PersonProfile** pt = emailToPerson.search(email);
            if(pt != nullptr){ // if duplicate email
                return false; // return
            }
            std::getline(infile, line);
            istringstream ss(line);
            ss >> numPairs; // for the listed number of pairs
            for(int i = 0; i < numPairs; i++){
                std::getline(infile, line);
                istringstream iss(line);
                std::getline(iss, att, ',');
                std::getline(iss, val); // get att val pairs
                attval = att + val;
                AttValPair av(att, val);
                p->AddAttValPair(av); // add pairs to our person
                std::vector<std::string>* ptr = attToEmail.search(attval);
                if(ptr == nullptr){
                    std::vector<std::string> a;
                    std::set<std::string> s;
                    a.push_back(email);
                    s.insert(email); // add all of our stuff
                    m_sets.insert(attval, s);
                    attToEmail.insert(attval, a);
                }
                else{
                    std::set<std::string>* pt = m_sets.search(attval); // searching with set is faster
                    std::set<std::string>::iterator it = pt->find(email);
                    if(it == pt->end()){ // checks for duplicates wothin existing vector and sert
                        pt->insert(email);
                        ptr->push_back(email);
                    }
                }
            }
            m_people.insert(p); // add person pointer to tree and set
            emailToPerson.insert(email, p);
            std::getline(infile, line); // gets blank line

        }
    }
    
    return true; // returns false if it found a repeat email, else returns true
    
    
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const{
    std::string av = input.attribute + input.value;
    std::vector<std::string>* ptr = attToEmail.search(av);
    if(ptr == nullptr){
        std::vector<std::string> temp; // returns an empty vector if none found
        return temp;
    }
    return (*ptr); // otherwise returns vector of emails
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const{
    PersonProfile** ptr = emailToPerson.search(email);
    if(ptr == nullptr){
        return nullptr; // returns nullptr if no matching email
    }
    else{
        const PersonProfile* p = *ptr;
        return p; // returns person profile if there is one
    }
}
