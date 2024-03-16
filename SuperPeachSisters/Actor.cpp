#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int startX, int startY, int dir, int depth, double size, StudentWorld* world, bool blocking, bool damagable)
: GraphObject(imageID, startX, startY, dir, depth, size), m_alive(true), m_world(world), m_blockingObject(blocking), m_damageable(damagable) {}

Actor::~Actor(){
    m_world = nullptr;
}

bool Actor::isAlive(){
    return m_alive;
}

StudentWorld* Actor::getWorld(){
    return m_world;
}

bool Actor::isBlockingObject(){
    return m_blockingObject;
}

bool Actor::isDamageable(){
    return m_damageable;
}

void Actor::bonk(){
    return;
}

void Actor::damage(){
    return;
}

void Actor::setAlive(bool alive){
    m_alive = alive;
}

void Actor::setFlower(){
    return;
}

void Actor::setMushroom(){
    return;
}

void Actor::setStar(){
    return;
}

bool Actor::hasFlower(){
    return false;
}

bool Actor::hasMushroom(){
    return false;
}

bool Actor::hasStar(){
    return false;
}

/////////////////////////////////////////////////////////////////////  SOLID IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////
Solid::Solid(int imageID, int startX, int startY, StudentWorld* world)
: Actor(imageID, startX, startY, 0, 2, 1.0, world, true, false) {}

Solid::~Solid(){
    
}

void Solid::doSomething(){
    //change this
    return;
}



/////////////////////////////////////////////////////////////////////  PIPE IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Pipe::Pipe(int startX, int startY, StudentWorld* world)
: Solid(IID_PIPE, startX, startY, world) {}

Pipe::~Pipe(){
    
}

/////////////////////////////////////////////////////////////////////  BLOCK IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////


Block::Block(int startX, int startY, StudentWorld* world, bool hasFlower, bool hasMushroom, bool hasStar)
: Solid(IID_BLOCK, startX, startY, world) {
    m_power = none;
    if(hasFlower){
        m_power = flower;
    }
    else if(hasMushroom){
        m_power = mushroom;
    }
    else if(hasStar){
        m_power = star;
    }
}

Block::~Block(){
    
}

void Block::doSomething(){
    //change this
    return;
}

void Block::bonk(){
    switch(m_power)
    {
        case none:{
            getWorld()->playSound(SOUND_PLAYER_BONK);
            break;
        }
        case flower:{//makes a new flower object and adds it to student world
            getWorld()->playSound(SOUND_POWERUP_APPEARS);
            Actor* actor = new Flower(getX(), getY()+8, getWorld());
            getWorld()->addActor(actor);
            m_power = none;
            break;
        }
        case mushroom:{//makes a new mushroom object and adds it to student world
            getWorld()->playSound(SOUND_POWERUP_APPEARS);
            Actor* actor = new Mushroom(getX(), getY()+8, getWorld());
            getWorld()->addActor(actor);
            m_power = none;
            break;
        }
        case star:{//makes a new star object and adds it to student world
            getWorld()->playSound(SOUND_POWERUP_APPEARS);
            Actor* actor = new Star(getX(), getY()+8, getWorld());
            getWorld()->addActor(actor);
            m_power = none;
            break;
        }
    }
    
}

/////////////////////////////////////////////////////////////////////  ENEMY IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Enemy::Enemy(int imageID, int startX, int startY, int dir, StudentWorld* world)
: Actor(imageID, startX, startY, dir, 0, 1.0, world, false, true) {}

Enemy::~Enemy(){
    
}

void Enemy::bonk(){
    getWorld()->playSound(SOUND_PLAYER_KICK);
    damage();
}

void Enemy::damage(){
    getWorld()->increaseScore(100);
    setAlive(false);
    die();
}

void Enemy::die(){
    return;
}
/////////////////////////////////////////////////////////////////////  ENEMY IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////
BasicEnemy::BasicEnemy(int imageID, int startX, int startY, int dir, StudentWorld* world)
: Enemy(imageID, startX, startY, dir, world) {}

BasicEnemy::~BasicEnemy(){
    
}


void BasicEnemy::doSomething(){
    if(!isAlive()){
        return;
    }//return if dead
    
    //attempt to bonk peach

    if(getWorld()->peachOverlap(getX(), getY())){
        getWorld()->bonkPeach();;
        return;
    }
    
    // default movement mechanics
    int newX, newY;
    if(getDirection() == 0){
        newX = getX() + 1;
        newY = getY();
    }
    else{
        newX = getX() - 1;
        newY = getY();
    }
    if(getWorld()->findSolid(newX, newY) != nullptr or
       getWorld()->findSolid(newX + SPRITE_WIDTH - 1, newY) != nullptr or
       getWorld()->findSolid(newX, newY + SPRITE_HEIGHT - 1) != nullptr or
       getWorld()->findSolid(newX + SPRITE_WIDTH - 1, newY + SPRITE_HEIGHT - 1) != nullptr){
        // If there is a blocking object, flip direction
        if(getDirection() == 0){
            setDirection(180);
        }
        else{
            setDirection(0);
        }
    }
    
    if(getWorld()->findSolid(newX, newY-1) == nullptr or
       getWorld()->findSolid(newX + SPRITE_WIDTH - 1, newY-1) == nullptr){
        //If about to walk off a platfom, flip direction
        if(getDirection() == 0){
            setDirection(180);
        }
        else{
            setDirection(0);
        }
    }
    
    if(getWorld()->findSolid(newX, newY) != nullptr or
    getWorld()->findSolid(newX + SPRITE_WIDTH - 1, newY) != nullptr or
    getWorld()->findSolid(newX, newY + SPRITE_HEIGHT - 1) != nullptr or
    getWorld()->findSolid(newX + SPRITE_WIDTH - 1, newY + SPRITE_HEIGHT - 1) != nullptr){
        // if there is a blocking object then return
        return;
    }
    else{
        //otherwise move to new coords
        moveTo(newX, newY);
    }
}

/////////////////////////////////////////////////////////////////////  GOOMBA IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Goomba::Goomba(int startX, int startY, int dir, StudentWorld* world)
: BasicEnemy(IID_GOOMBA, startX, startY, dir, world) {}

Goomba::~Goomba(){
    
}


/////////////////////////////////////////////////////////////////////  KOOPA IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Koopa::Koopa(int startX, int startY, int dir, StudentWorld* world)
: BasicEnemy(IID_KOOPA, startX, startY, dir, world) {}

Koopa::~Koopa(){
    
}

void Koopa::die(){
    //make a new shell
    Actor* a = new Shell(getX(), getY(), getDirection(), getWorld());
    getWorld()->addActor(a);
}



/////////////////////////////////////////////////////////////////////  PIRANHA IMPLEMENTATIONS  ///////////////////////////////////////// ////////////////////////////////////////////

Piranha::Piranha(int startX, int startY, int dir, StudentWorld* world)
: Enemy(IID_PIRANHA, startX, startY, dir, world), m_firingDelay(0) {}

Piranha::~Piranha(){
    
}

bool Piranha::hasDelay(){
    if(m_firingDelay > 0){
        return true;
    }
    else{
        return false;
    }
}

void Piranha::doSomething(){
    if(!isAlive()){
        return;
    }
    increaseAnimationNumber();
    
    // if piranha overlaps peach, bonk her
    if(getWorld()->peachOverlap(getX(), getY())){
        getWorld()->bonkPeach();
        return;
    }
    
    
    int peachY =getWorld()->getPeachY();
    int peachX =getWorld()->getPeachX();
    if(peachY >= getY() - (SPRITE_HEIGHT*1.5) and peachY <= getY() + (SPRITE_HEIGHT*1.5)){
        if(peachX >= getX()){//if peach is on similar y level to piranha
            setDirection(0);
        }
        else{
            setDirection(180); // face peach
        }
        
        if(hasDelay()){ // decrement firing delay and return
            m_firingDelay--;
            return;
        }
        int dist = abs(peachX - getX());
        if(dist < 8*SPRITE_WIDTH){ // if within 8 blocks
            Actor* actor = new PiranhaFireball(getX(), getY(), getDirection(), getWorld());
            getWorld()->addActor(actor); // add fireball to student world
            getWorld()->playSound(SOUND_PLAYER_FIRE);
            m_firingDelay = 40;//set new firing delay
        }
    }
    else{
        return;
    }
    
    
}
/////////////////////////////////////////////////////////////////////  GOAL IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////
Goal::Goal(int imageID, int startX, int startY, StudentWorld* world)
: Actor(imageID, startX, startY, 0, 1, 1, world, false, false) {}

void Goal::doSomething(){
    if(!isAlive()){
        return;
    }
    
    if(getWorld()->peachOverlap(getX(), getY())){
        getWorld()->increaseScore(1000);
        setAlive(false);
        setNextLevel();
        //tell world to go to next level
    }
}

Goal::~Goal(){
    
}

/////////////////////////////////////////////////////////////////////  FLAG IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Flag::Flag(int startX, int startY, StudentWorld* world)
: Goal(IID_FLAG, startX, startY, world) {}

void Flag::setNextLevel(){
    getWorld()->beatLevel(); // indicate that we are moving to the next level
}

Flag::~Flag(){
    
}

/////////////////////////////////////////////////////////////////////  MARIO IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Mario::Mario(int startX, int startY, StudentWorld* world)
: Goal(IID_MARIO, startX, startY, world) {}

void Mario::setNextLevel(){
    getWorld()->beatGame(); // indicate that peach beat the game
}

Mario::~Mario(){
    
}

/////////////////////////////////////////////////////////////////////  POWERUP IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

PowerUp::PowerUp(int imageID, int startX, int startY, StudentWorld* world)
: Actor(imageID, startX, startY, 0, 1, 1, world, false, false) {}

void PowerUp::doSomething(){
    if(!isAlive()){
        return;
    }
    if(getWorld()->peachOverlap(getX(), getY())){
        affectPeach(); // if overlapping peach then affect her
        return;
    }
    
    if(!getWorld()->isSolid(getX(), getY()-2) and
       !getWorld()->isSolid(getX()+SPRITE_WIDTH-1, getY()-2)){
        moveTo(getX(), getY()-2); // fall if there is nothing below blocking
    }
    int newX;
    int newY = getY();
    if(getDirection() == 0){
        newX = getX()+2;
    }
    else{
        newX = getX()-2; // set target coords
    }
    if(getWorld()->isSolid(newX, newY) or
       getWorld()->isSolid(newX + SPRITE_WIDTH - 1, newY) or
       getWorld()->isSolid(newX, newY + SPRITE_HEIGHT - 1) or
       getWorld()->isSolid(newX + SPRITE_WIDTH - 1, newY + SPRITE_HEIGHT - 1)){
        // If there is a blocking object, flip direction
        if(getDirection() == 0){
            setDirection(180);
            return;
        }
        else{
            setDirection(0);
            return;
        }
    }
    else{
        moveTo(newX, newY); // if no blocking object then move to new coords
    }
}

PowerUp::~PowerUp(){
    
}

/////////////////////////////////////////////////////////////////////  FLOWER IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Flower::Flower(int startX, int startY, StudentWorld* world)
: PowerUp(IID_FLOWER, startX, startY, world) {}

void Flower::affectPeach(){
    getWorld()->increaseScore(50);
    getWorld()->findPeach()->setFlower(); // give peach points and flower power then disappear
    setAlive(false);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
}

Flower::~Flower(){
    
}

/////////////////////////////////////////////////////////////////////  Mushroom IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Mushroom::Mushroom(int startX, int startY, StudentWorld* world)
: PowerUp(IID_MUSHROOM, startX, startY, world) {}

void Mushroom::affectPeach(){
    getWorld()->increaseScore(75);
    getWorld()->findPeach()->setMushroom(); // give peach points and jump power then disappear
    setAlive(false);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
}

Mushroom::~Mushroom(){
    
}


/////////////////////////////////////////////////////////////////////  STAR IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Star::Star(int startX, int startY, StudentWorld* world)
: PowerUp(IID_STAR, startX, startY, world) {}

void Star::affectPeach(){
    getWorld()->increaseScore(100);
    getWorld()->findPeach()->setStar();// give peach points and star power then disappear
    setAlive(false);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
}

Star::~Star(){
    
}

/////////////////////////////////////////////////////////////////////  PROJECTLIE IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Projectile::Projectile(int imageID, int startX, int startY, int dir, StudentWorld* world)
: Actor(imageID, startX, startY, dir, 1, 1, world, false, false) {}

Projectile::~Projectile(){
    
}

void Projectile::doSomething(){
    if(!isAlive()){
        return;
    }
    
    //If there isanactor for it to damage, peach or enemy accordingly, damage it
    damageSomething();
    
    //if nothing is preventing it frommoving down then it should fall 2 pixels
    if(!getWorld()->isSolid(getX(), getY()-2) and
       !getWorld()->isSolid(getX()+SPRITE_WIDTH-1, getY()-2)){
        moveTo(getX(), getY()-2);
    }
    int newX;
    int newY = getY();
    if(getDirection() == 0){
        newX = getX()+2;
    }
    else{
        newX = getX()-2;
    }
    if(getWorld()->isSolid(newX, newY) or
       getWorld()->isSolid(newX + SPRITE_WIDTH - 1, newY) or
       getWorld()->isSolid(newX, newY + SPRITE_HEIGHT - 1) or
       getWorld()->isSolid(newX + SPRITE_WIDTH - 1, newY + SPRITE_HEIGHT - 1)){
        // If there is a blocking object, disappear
        setAlive(false);
        return;
    }
    else{
        moveTo(newX, newY); // if no blocking object then move
    }
}

/////////////////////////////////////////////////////////////////////  PIRANHA FIREBALL IMPLEMENTATIONS  ///////////////////////////////////////////////////////////////

PiranhaFireball::PiranhaFireball(int startX, int startY, int dir, StudentWorld* world)
: Projectile(IID_PIRANHA_FIRE, startX, startY, dir, world) {}

PiranhaFireball::~PiranhaFireball(){
    
}

void PiranhaFireball::damageSomething(){
    if(getWorld()->peachOverlap(getX(), getY())){
        getWorld()->damagePeach();
        setAlive(false); // pirahna fireballs affect and damage peach only
        // if they hit peach then damage her and disappear
    }
}

/////////////////////////////////////////////////////////////////////  PEACH FIREBALL IMPLEMENTATIONS  ///////////////////////////////////////////////////////////////

PeachFireball::PeachFireball(int startX, int startY, int dir, StudentWorld* world)
: Projectile(IID_PEACH_FIRE, startX, startY, dir, world) {}

PeachFireball::~PeachFireball(){
    
}

void PeachFireball::damageSomething(){
    if(getWorld()->damageOverlap(getX(), getY())){ // damage any actors that it overlaps, then die
        setAlive(false);
    }
}

/////////////////////////////////////////////////////////////////////  SHELL IMPLEMENTATIONS  ///////////////////////////////////////////////////////////////

Shell::Shell(int startX, int startY, int dir, StudentWorld* world)
: Projectile(IID_SHELL, startX, startY, dir, world) {}

Shell::~Shell(){
    
}

void Shell::damageSomething(){
    
    if(getWorld()->damageOverlap(getX(), getY())){ //damage any actors that it overlaps, then die
        setAlive(false);
    }
     
}


/////////////////////////////////////////////////////////////////////  PEACH IMPLEMENTATIONS  /////////////////////////////////////////////////////////////////////////////////////

Peach::Peach(int startX, int startY, StudentWorld* world)
: Actor(IID_PEACH, startX, startY, 0, 0, 1.0, world, false, true), m_hp(1), m_remainingJump(0), m_hasJump(false), m_hasFlower(false), m_tempInvincibility(0), m_invincibility(0), m_shootRecharge(0){
}

Peach::~Peach(){
    
}

void Peach::setFlower(){
    m_hasFlower = true; // give peach flower
    m_hp = 2;
}

void Peach::setMushroom(){
    m_hasJump = true; // give peach mushroom
    m_hp = 2;
}

void Peach::setStar(){
    m_invincibility = 150; // set invicibility
}
bool Peach::hasFlower(){
    return m_hasFlower;
}

bool Peach::hasMushroom(){
    return m_hasJump;
}

bool Peach::hasStar(){
    if(m_invincibility > 0){
        return true;
    }
    else{
        return false;
    }
}

void Peach::bonk(){
    // if peach isnt invincible
    if(m_invincibility > 0 or m_tempInvincibility > 0){
        return; // if peach is invincible then do nothing
    }
    
    m_hp--; // losesome hp
    m_tempInvincibility = 10; //give peach temp invincibility
    m_hasJump = false;
    m_hasFlower = false; // remove powers
    if(m_hp >= 1){
        getWorld()->playSound(SOUND_PLAYER_HURT);
    }
    else{
        setAlive(false); // if hp hits 0 then peach dies
        
    }
}

void Peach::damage(){
    bonk(); // does the same as bonk
}

void Peach::doSomething(){
    
    if(!isAlive()){
        return;
    } // die if alive
    
    if(m_invincibility > 0){
        m_invincibility--;
    }
    
    if(m_tempInvincibility > 0){
        m_tempInvincibility--;
    }
    if(m_shootRecharge > 0){
        m_shootRecharge--;
    } // decrement invincibility and shoot recharge
    
    if(m_invincibility > 0){
        getWorld()->bonkOverlap(getX(), getY());
    } // bonk any actors when invincible
    
    //detect input, and movement
    if(m_remainingJump > 0){
        int jumpX = getX();
        int jumpY = getY()+4;

        if(getWorld()->findSolid(jumpX, jumpY + SPRITE_HEIGHT - 1) != nullptr or
           getWorld()->findSolid(jumpX+SPRITE_WIDTH-1, jumpY + SPRITE_HEIGHT - 1) != nullptr){
            if(getWorld()->findSolid(jumpX, jumpY + SPRITE_HEIGHT - 1) != nullptr){
                getWorld()->findSolid(jumpX, jumpY + SPRITE_HEIGHT - 1)->bonk();
            } // if still has jump and object above, bonk it
            else{
                getWorld()->findSolid(jumpX+SPRITE_WIDTH-1, jumpY + SPRITE_HEIGHT - 1)->bonk();
            }
            m_remainingJump = 0;
        }
        else{
            moveTo(jumpX, jumpY);
            m_remainingJump--;
        } // move up
    }
    else{
        if(getWorld()->findSolid(getX(), getY()-4) == nullptr and
           getWorld()->findSolid(getX() + SPRITE_WIDTH-1, getY()-4) == nullptr){
            moveTo(getX(), getY()-4);
        } // if no jump remaining and no blocking object below, fall down
    }
    
    int ch;
    int newX, newY;
    if (getWorld()->getKey(ch)){ // get key press
        switch (ch)
        {
            case KEY_PRESS_LEFT:
                setDirection(180);
                newX = getX()-4;
                newY = getY();
                if(getWorld()->findSolid(newX, newY) != nullptr){
                    getWorld()->findSolid(newX, newY)->bonk();
                    break;
                }
                if(getWorld()->findSolid(newX, newY+SPRITE_HEIGHT-1) != nullptr){
                    getWorld()->findSolid(newX, newY+SPRITE_HEIGHT-1)->bonk();
                    break;
                } //if moving left and there is a block, bonk item to the left
                else{
                    moveTo(newX, newY);
                    break; // otherwise move left
                }
            case KEY_PRESS_RIGHT:
                setDirection(0);
                newX = getX()+4;
                newY = getY();
                if(getWorld()->findSolid(newX+SPRITE_WIDTH-1, newY) != nullptr){
                    getWorld()->findSolid(newX+SPRITE_WIDTH-1, newY)->bonk();
                    break;
                }
                if(getWorld()->findSolid(newX+SPRITE_WIDTH-1, newY+SPRITE_HEIGHT-1) != nullptr){
                    getWorld()->findSolid(newX+SPRITE_WIDTH-1, newY+SPRITE_HEIGHT-1)->bonk();
                    break; // bonk blocking object to the right if there is one
                }
                else{
                    moveTo(newX, newY);
                    break; // otherwise move there
                }
            case KEY_PRESS_UP:
                if(getWorld()->findSolid(getX(), getY() - 1) != nullptr or
                   getWorld()->findSolid(getX() + SPRITE_WIDTH-1, getY() - 1) != nullptr){
                    // if there is a solid below peach
                    if(m_hasJump){ // give peach a jump depending on her work
                        m_remainingJump = 12;
                    }
                    else{
                        m_remainingJump = 8;
                    }
                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                }
                break;
            case KEY_PRESS_SPACE:
                if(!m_hasFlower){
                    break; // do nothing if no flower or if still recharging
                }
                if(m_shootRecharge > 0){
                    break;
                }
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                Actor* actor = new PeachFireball(getX(), getY(), getDirection(), getWorld());
                getWorld()->addActor(actor); //add a new fireball
                m_shootRecharge = 8; // and add a shoot delay
        }
    }
    
    return;
}

