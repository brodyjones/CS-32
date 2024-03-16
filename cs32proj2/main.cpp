//
//  main.cpp
//  cs32proj2
//
//  Created by Brody Jones on 1/20/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "Map.h"
#include <string>

using namespace std;

int main()
{
    Map mm;
    mm.insert("Little Ricky", 3.206); //regular inserts
    mm.insert("Ethel", 3.538);
    mm.insert("Ricky", 3.350);
    mm.insert("Lucy", 2.956);
    mm.insertOrUpdate("Ethel", 7.56); //updates because “Ethel” already in map
    mm.insert("Fred", 2.956);
    mm.insert("Lucy", 2.956); // failed insert
    assert(!mm.erase("Jess")); // failed erase, “Jess” not in map
    assert(mm.size() == 5);  // duplicate "Lucy" was not added and "Ethel" was updated
    mm.erase("Fred"); // successful erase
    assert(mm.empty() == false); //checks that map is not empty
    assert(mm.size() == 4); // successfully deleted a node
    assert(mm.contains("Little Ricky"));
    assert(mm.contains("Ethel"));
    assert(mm.contains("Lucy"));
    assert(mm.contains("Ricky"));
    assert(mm.contains("Fred") == false); // checks "Fred" is the only one missing
    KeyType k;
    ValueType v;
    assert(mm.get("Ricky", v) && v == 3.350); // successfully returns the value of “Ricky”
    assert(!mm.get("Fred", v) && v == 3.350); // failed get call
    assert(mm.get(0, k, v) && k == "Ethel" && v == 7.56); // gets "Ethel" is the least of the keys
    assert(!mm.get(4, k, v)); // failed get call, i out of bounds
    assert(!mm.get(-15, k, v)); // failed get call, i is negative
    assert(mm.get(3, k, v) && k == "Ricky" && v == 3.350); // gets largest key in Map
    
    Map mm2;
    mm2.insert("cheeto", 77.7);
    mm2.insert("dorito", 100.5);
    mm2.insert("sticky", 3.7);
    
    mm.swap(mm2); // successful swap
    assert(mm.size() == 3); // mm is now that size that mm2 previouly was
    assert(mm.contains("cheeto")); // mm contains what mm2 used to
    assert(mm2.size() == 4); // mm2 is now that size that mm previouly was
    assert(mm2.contains("Lucy")); // mm2 contains what mm used to
    mm.swap(mm2); // swap back
    
    Map mm3 = mm; // successful copy constructor
    
    assert(mm3.size() == 4); // check that is copied correctly
    mm3.erase("Little Ricky"); // erase from mm3 and not mm
    assert(!mm3.contains("Little Ricky"));// checks that mm and mm3 are seperate maps
    assert(mm.contains("Little Ricky")); //^^^
    
    mm3 = mm; //successful assignment operator
    assert(mm3.contains("Little Ricky")); // mm3 is again a copy of mm
    mm3.insert("Jess", -17.6); // insert to mm3 and not mm
    assert(mm3.contains("Jess")); //checks that mm and mm3 are seperate maps
    assert(!mm.contains("Jess")); //^^^
    
    Map mm4;
    merge(mm, mm2, mm4); // merge two maps with no overlapping keys
    cout << mm4.size() << endl; // size is the combined sized of both maps
    
    Map mm5;
    mm5.insert("a", 4.55); // insert so mm5 is not empty when we rearrange
    
    reassign(mm4, mm5); // successful reassign
    cout << mm5.size() << endl; // makes sure that mm5 was cleared before mm4 was reassigned
    for(int i = 0; i < mm5.size(); i++){
        mm5.get(i, k, v);
        cout << k << "  " << v << endl;
    } // shows that all the values are shifted
    
    cout << mm4.size() << endl;
    for(int i = 0; i < mm4.size(); i++){
        mm4.get(i, k, v);
        cout << k << "  " << v << endl;
    }// shows what the original values were before reassign
    
    reassign(mm4, mm4); // aliasing of the reassign function
    cout << mm4.size() << endl;
    for(int i = 0; i < mm4.size(); i++){
        mm4.get(i, k, v);
        cout << k << "  " << v << endl;
    } // still properly shifts the values
    
    Map m;
    assert(m.empty()); // checks empty function
    assert(m.size() == 0); // checks inital size is right
    assert(m.insert("a", 1.0)); // proper insert
    assert(!m.insert("a", 2.0)); // failed insert
    Map m2(m); // copy constructor
    assert(m2.size() == 1); // is a succesful copy of m
    assert(m2.contains("a")); // ^^^
    assert(!m2.erase("b")); // failed erase call
    assert(m2.erase("a")); // successful erase call
    m2.insertOrUpdate("abc", 123); // inserts becauze "abc" isn't already in m2
    m = m2; // successful assignment operator
    m = m; //assignment operator works with aliasing too
    assert(m.contains("abc")); // checks that m is not erased after aliasing
    m.insert("a", 1); // fill m and m2
    m.insert("b", 2); // ^^^
    m.insert("c", 3); // ^^^
    m2.insert("d", 4);// ^^^
    m2.insert("e", 5);// ^^^
    m2.insert("f", 6);// ^^^
    Map m3;
    m3.insert("ghhg", 7887); // m3 isnt empty before the merge
    assert(merge(m, m2, m3));
    assert(m3.size() == 7); // merge where they share key "abc" but the values match
    assert(m.update("abc", 124));
    assert(!merge(m, m2, m3)); // merge where they share the key "abc" but the values are different, so neither "abc" node is in map and merge returns false
    assert(m3.size() == 6); // "abc" is not in map
    Map m4;
    m4.insert("99", 99);
    reassign(m3, m4); // successful reassign
    cout << m4.size() << endl;
    for(int i = 0; i < m4.size(); i++){
        m4.get(i, k, v);
        cout << k << "  " << v << endl;
    } // check values are reassigned
    
    reassign(m4, m4); // aliased reassign
    cout << m4.size() << endl;
    for(int i = 0; i < m4.size(); i++){
        m4.get(i, k, v);
        cout << k << "  " << v << endl;
    } // check values are reassigned
    
    m4.update("c", 6); // now some keys share the same value
    reassign(m4, m4); // "c" gets the value of 6 that "b" originally had and "d" gets the 6 that was orignally "c"
    cout << m4.size() << endl;
    for(int i = 0; i < m4.size(); i++){
        m4.get(i, k, v);
        cout << k << "  " << v << endl;
    }
    
    int s = m4.size();
    for(int i = 0; i < s; i++){
        m4.get(0, k, v);
        m4.erase(k);
    } // erase all of m4
    
    assert(m4.empty()); // empty still works after nodes are inserted and deleted
    reassign(m4, m); // reassignment of an empty map
    assert(m.empty()); // the previous reassignment made m empty
    Map m5;
    m5.insert("hi", 990);
    merge(m, m4, m5); // merge of two empty maps
    assert(m5.empty()); // results in an empty map, even if m5 was not orioginally empty
    
    cout << "good job friend" << endl;
}
