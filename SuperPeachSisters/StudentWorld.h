#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"

#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    bool isSolid(int x, int y);
    Actor* findSolid(int x, int y);
    Actor* findPeach();
    void bonkOverlap(int x, int y);
    bool damageOverlap(int x, int y);
    int getPeachX();
    int getPeachY();
    void bonkPeach();
    void damagePeach();
    bool peachOverlap(int x, int y);
    void eraseDead();
    void beatLevel();
    void beatGame();
    void addActor(Actor* actor);
private:
    std::vector<Actor*> m_actors;
    Actor* m_peach;
    //int m_level;
    bool m_beatLevel;
    bool m_won;
};

#endif // STUDENTWORLD_H_
