//
//  History.cpp
//  cs32.proj1
//
//  Created by Brody Jones on 1/8/22.
//  Copyright © 2022 Brody Jones. All rights reserved.
//

#include "History.h"
#include "globals.h"
#include <iostream>

using namespace std;


///////////////////////////////////////////////////////////////////////////
//  History implementations
///////////////////////////////////////////////////////////////////////////

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for(int i = 0; i < m_rows;i++){
        for(int j = 0; j < m_cols; j++){
            m_grid[i][j] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if(r < 1 or r > m_rows or c < 1 or c > m_cols){
        return false;
    }
    
    m_grid[r-1][c-1] += 1;
    return true;
}

void History::display() const
{
    char grid[MAXROWS][MAXCOLS];
    for(int i = 0; i < m_rows;i++){
        for(int j = 0; j < m_cols; j++){
            if(m_grid[i][j] > 0 and m_grid[i][j] < 26){
                grid[i][j] = 64 + m_grid[i][j];
            }
            else if(m_grid[i][j] == 0){
                grid[i][j] = '.';
            }
            else if(m_grid[i][j] >= 26){
                grid[i][j] = 'Z';
            }
        }
    }
    
    clearScreen();
    for(int i = 0; i < m_rows;i++){
        for(int j = 0; j < m_cols; j++){
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

