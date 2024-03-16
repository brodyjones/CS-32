//
//  History.hpp
//  cs32.proj1
//
//  Created by Brody Jones on 1/8/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#ifndef History_h
#define History_h

#include <stdio.h>
#include "globals.h"
#include <iostream>

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
  private:
    int m_rows;
    int m_cols;
    int m_grid[MAXROWS][MAXCOLS];
};

#endif /* History_h */
