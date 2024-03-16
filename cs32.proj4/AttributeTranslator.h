//
//  AttributeTranslator.h
//  cs32.proj4
//
//  Created by Brody Jones on 3/2/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator
{
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    RadixTree<vector<AttValPair>> m_tree;
    
};

#endif /* AttributeTranslator_h */
