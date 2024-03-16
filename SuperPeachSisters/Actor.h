#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world, bool blocking, bool damageable);
    virtual ~Actor();
    virtual void doSomething()=0;
    virtual void bonk();
    virtual void damage();
    bool isAlive();
    StudentWorld* getWorld();
    bool isBlockingObject();
    bool isDamageable();
    void setAlive(bool alive);
    virtual void setFlower();
    virtual void setMushroom();
    virtual void setStar();
    virtual bool hasFlower();
    virtual bool hasStar();
    virtual bool hasMushroom();
private:
    StudentWorld* m_world;
    bool m_alive;
    bool m_blockingObject;
    bool m_damageable;
};

//////////////////////////////////////////////////////////////////////////////////   SOLID ACTORS     ////////////////////////////////////////////////////////////
class Solid: public Actor
{
public:
    Solid(int imageID, int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual ~Solid();
};

//enum Power {none, flower, mushroom, star};
class Block: public Solid
{
public:
    Block(int startX, int startY, StudentWorld* world, bool hasFlower, bool hasMushroom, bool hasStar);
    virtual ~Block();
    virtual void doSomething();
    virtual void bonk();
private:
    enum Power {none, flower, mushroom, star};
    Power m_power;
};

class Pipe: public Solid
{
public:
    Pipe(int startX, int startY, StudentWorld* world);
    virtual ~Pipe();
};

//////////////////////////////////////////////////////////////////////////////////   GOALS   ////////////////////////////////////////////////////////////

class Goal: public Actor
{
public:
    Goal(int imageID, int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual void setNextLevel()=0;
    virtual ~Goal();
};

class Flag: public Goal
{
public:
    Flag(int startX, int startY, StudentWorld* world);
    virtual void setNextLevel();
    virtual ~Flag();
};

class Mario: public Goal
{
public:
    Mario(int startX, int startY, StudentWorld* world);
    virtual void setNextLevel();
    virtual ~Mario();
};

//////////////////////////////////////////////////////////////////////////////////   POWERUPS   ////////////////////////////////////////////////////////////

class PowerUp: public Actor
{
public:
    PowerUp(int imageID, int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual void affectPeach()=0;
    virtual ~PowerUp();
};

class Flower: public PowerUp
{
public:
    Flower(int startX, int startY, StudentWorld* world);
    virtual void affectPeach();
    virtual ~Flower();
};

class Mushroom: public PowerUp
{
public:
    Mushroom(int startX, int startY, StudentWorld* world);
    virtual void affectPeach();
    virtual ~Mushroom();
};

class Star: public PowerUp
{
public:
    Star(int startX, int startY, StudentWorld* world);
    virtual void affectPeach();
    virtual ~Star();
};

//////////////////////////////////////////////////////////////////////////////////   ENEMIES   ////////////////////////////////////////////////////////////

class Enemy: public Actor
{
public:
    Enemy(int imageID, int startX, int startY, int dir, StudentWorld* world);
    virtual ~Enemy();
    virtual void bonk();
    virtual void damage();
    virtual void die();
};

class BasicEnemy: public Enemy
{
public:
    BasicEnemy(int imageID, int startX, int startY, int dir, StudentWorld* world);
    virtual ~BasicEnemy();
    virtual void doSomething();
};

class Goomba: public BasicEnemy
{
public:
    Goomba(int startX, int startY, int dir, StudentWorld* world);
    virtual ~Goomba();
};

class Koopa: public BasicEnemy
{
public:
    Koopa(int startX, int startY, int dir, StudentWorld* world);
    virtual ~Koopa();
    //virtual void doSomething();
    virtual void die();
};

class Piranha: public Enemy
{
public:
    Piranha(int startX, int startY, int dir, StudentWorld* world);
    virtual ~Piranha();
    virtual void doSomething();
    bool hasDelay();
private:
    int m_firingDelay;
};

//////////////////////////////////////////////////////////////////////////////////   PROJECTILES   ////////////////////////////////////////////////////////////

class Projectile: public Actor
{
public:
    Projectile(int imageID, int startX, int startY, int dir, StudentWorld* world);
    virtual void damageSomething()=0;
    virtual void doSomething();
    virtual ~Projectile();
};


class PiranhaFireball: public Projectile
{
public:
    PiranhaFireball( int startX, int startY, int dir, StudentWorld* world);
    virtual void damageSomething();
    virtual ~PiranhaFireball();
};

class PeachFireball: public Projectile
{
public:
    PeachFireball( int startX, int startY, int dir, StudentWorld* world);
    virtual void damageSomething();
    virtual ~PeachFireball();
};

class Shell: public Projectile
{
public:
    Shell( int startX, int startY, int dir, StudentWorld* world);
    virtual void damageSomething();
    virtual ~Shell();
};


//////////////////////////////////////////////////////////////////////////////////   PEACH   ////////////////////////////////////////////////////////////
class Peach: public Actor
{
public:
    Peach(int startX, int startY, StudentWorld* world);
    virtual ~Peach();
    virtual void doSomething();
    virtual void bonk();
    virtual void damage();
    virtual void setFlower();
    virtual void setMushroom();
    virtual void setStar();
    virtual bool hasFlower();
    virtual bool hasStar();
    virtual bool hasMushroom();
private:
    int m_hp;
    int m_remainingJump;
    bool m_hasJump;
    bool m_hasFlower;
    int m_invincibility;
    int m_tempInvincibility;
    int m_shootRecharge;
};


#endif // ACTOR_H_
