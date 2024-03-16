//
//  Game.hpp
//  cs32.proj1
//
//  Created by Brody Jones on 1/8/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include "Mesa.h"
#include "globals.h"
#include <iostream>


class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

        // Mutators
    void play();

  private:
    Mesa* m_mesa;
};

#endif /* Game_h */
