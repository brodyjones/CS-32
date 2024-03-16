//
//  Player.hpp
//  cs32.proj1
//
//  Created by Brody Jones on 1/8/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <iostream>

class Mesa;

class Player
{
  public:
        // Constructor
    Player(Mesa *mp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

        // Mutators
    void   stand();
    void   moveOrAttack(int dir);
    void   setDead();

  private:
    Mesa* m_mesa;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

#endif /* Player_h */
