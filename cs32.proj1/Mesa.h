//
//  Mesa.hpp
//  cs32.proj1
//
//  Created by Brody Jones on 1/8/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef Mesa_h
#define Mesa_h

#include <stdio.h>
#include "globals.h"
#include "History.h"
#include <iostream>

class Player;
class Gark;

class Mesa
{
  public:
        // Constructor/destructor
    Mesa(int nRows, int nCols);
    ~Mesa();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     garkCount() const;
    int     numGarksAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    History& history();

        // Mutators
    bool   addGark(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackGarkAt(int r, int c, int dir);
    bool   moveGarks();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Gark*   m_garks[MAXGARKS];
    int     m_nGarks;
    History m_history;
};

#endif /* Mesa_h */
