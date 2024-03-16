#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <iostream>
#include <sstream>
using namespace std;


GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{

}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    m_peach = nullptr;
    m_beatLevel = false;
    m_won = false;
    
    //building level name
    ostringstream oss;
    oss << "level";
    oss.fill('0');
    oss << setw(2) << getLevel();
    oss << ".txt";
    Level currLevel(assetPath());
    currLevel.loadLevel(oss.str());
    if(currLevel.loadLevel(oss.str()) != currLevel.load_success){
        return GWSTATUS_LEVEL_ERROR; // level error is not a good file
    }
    int x;
    int y;
    for(x= 0; x < GRID_WIDTH; x++){
        for(y=0; y < GRID_HEIGHT; y++){ // increment through level file
            // for each symbol they add the appropriate actor to m_actors
            if(currLevel.getContentsOf(x, y) == currLevel.block){
                m_actors.push_back(nullptr);
                m_actors.back() = new Block(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, this, false, false, false);
            }
            if(currLevel.getContentsOf(x, y) == currLevel.flower_goodie_block){
                m_actors.push_back(nullptr);
                m_actors.back() = new Block(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, this, true, false, false);
            }
            if(currLevel.getContentsOf(x, y) == currLevel.mushroom_goodie_block){
                m_actors.push_back(nullptr);
                m_actors.back() = new Block(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, this, false, true, false);
            }
            if(currLevel.getContentsOf(x, y) == currLevel.star_goodie_block){
                m_actors.push_back(nullptr);
                m_actors.back() = new Block(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, this, false, false, true);
            }
            if(currLevel.getContentsOf(x, y) == currLevel.flag){
                m_actors.push_back(nullptr);
                m_actors.back() = new Flag(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, this);
            }
            
            if(currLevel.getContentsOf(x, y) == currLevel.mario){
                m_actors.push_back(nullptr);
                m_actors.back() = new Mario(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, this);
            }
            
            if(currLevel.getContentsOf(x, y) == currLevel.pipe){
                m_actors.push_back(nullptr);
                m_actors.back() = new Pipe(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, this);
            }
            if(currLevel.getContentsOf(x, y) == currLevel.goomba){
                m_actors.push_back(nullptr);
                int i = randInt(0, 1);
                if(i == 0){
                    m_actors.back() = new Goomba(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, 0, this);
                }
                else if(i == 1){
                    m_actors.back() = new Goomba(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, 180, this);
                }
            }
            if(currLevel.getContentsOf(x, y) == currLevel.koopa){
                m_actors.push_back(nullptr);
                int i = randInt(0, 1);
                if(i == 0){
                    m_actors.back() = new Koopa(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, 0, this);
                }
                else if(i == 1){
                    m_actors.back() = new Koopa(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, 180, this);
                }
            }
            if(currLevel.getContentsOf(x, y) == currLevel.piranha){
                m_actors.push_back(nullptr);
                int i = randInt(0, 1);
                if(i == 0){
                    m_actors.back() = new Piranha(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, 0, this);
                }
                else if(i == 1){
                    m_actors.back() = new Piranha(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, 180, this);
                }
            }
            
            // assign m_peach to a dynamically allocated peach
            if(currLevel.getContentsOf(x, y) == currLevel.peach){
                m_peach = new Peach(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, this);
            }
            
        }
    }
    return GWSTATUS_CONTINUE_GAME; // continue game
}

int StudentWorld::move()
{
    if(m_peach->isAlive()){
        m_peach->doSomething();
    }
    for(int i = 0; i < m_actors.size(); i++){
        if(m_actors[i]->isAlive()){
            m_actors[i]->doSomething();
        }
    }// for every alive actor, tell them to do something
    
    if(m_beatLevel == true){
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    } // if we reached flag, indicate we finished level
    
    if(m_won == true){
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    } // if peach reached mario, indicsate that we finished the game
    
    if(!m_peach->isAlive()){
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    } // if peach died, then indicate this a decrement lives
    
    eraseDead();// delete all actors that diesw during the tick
    
    ostringstream oss;
    oss << "Lives: " << getLives();
    oss.fill('0');
    oss << " Level: " << setw(2) << getLevel();
    oss << " Points: " << setw(6) << getScore();
    if(m_peach->hasStar()){
        oss << " StarPower!";
    }
    if(m_peach->hasFlower()){
        oss << " ShootPower!";
    }
    if(m_peach->hasMushroom()){
        oss << " JumpPower!";
    } // build the score using oss
    setGameStatText(oss.str()); // adjust the score
    
    
    return GWSTATUS_CONTINUE_GAME; //
}


void StudentWorld::cleanUp()
{
    while(!m_actors.empty()){
        if(m_actors.back() != nullptr){
            delete m_actors.back(); // delet every actor and clear out vector
        }
        m_actors.pop_back();
    }
    if(m_peach != nullptr){
        delete m_peach; // delete peach
        m_peach = nullptr;
    }
}




bool StudentWorld::isSolid(int x, int y){
    for(int i= 0; i < m_actors.size(); i++){
        if(m_actors[i] != nullptr and m_actors[i]->isBlockingObject()){
            if(x >= m_actors[i]->getX() and x <= m_actors[i]->getX() + SPRITE_WIDTH - 1){
                if(y >= m_actors[i]->getY() and y <= m_actors[i]->getY() + SPRITE_HEIGHT - 1){
                    return true; // return true if there is a solid object at coord
                }
            }
        }
    }
    return false;
}

Actor* StudentWorld::findSolid(int x, int y){
    for(int i= 0; i < m_actors.size(); i++){
        if(m_actors[i] != nullptr and m_actors[i]->isBlockingObject()){
            if(x >= m_actors[i]->getX() and x <= m_actors[i]->getX() + SPRITE_WIDTH - 1){
                if(y >= m_actors[i]->getY() and y <= m_actors[i]->getY() + SPRITE_HEIGHT - 1){
                    return m_actors[i];
                } // return a pointer to the solid object at coord
            }
        }
    }
    return nullptr; // else return nullptr
}


Actor* StudentWorld::findPeach(){
    return m_peach; //return pointer to peach
}



void StudentWorld::bonkOverlap(int x, int y){
    for(int i= 0; i < m_actors.size(); i++){
        if(m_actors[i] != nullptr and m_actors[i]->isDamageable()){
            if(m_actors[i]->getX()+SPRITE_WIDTH-1 > x and
               m_actors[i]->getX() < x+SPRITE_WIDTH-1 and
               m_actors[i]->getY()+SPRITE_HEIGHT-1 > y and
               m_actors[i]->getY() < y+SPRITE_HEIGHT-1){
                m_actors[i]->bonk(); // bonk any actor that overlaps an actor at coord
            }
        }
    }
    return;
}

bool StudentWorld::damageOverlap(int x, int y){
    bool temp = false;
    for(int i= 0; i < m_actors.size(); i++){
        if(m_actors[i] != nullptr and m_actors[i]->isDamageable()){
            if(m_actors[i]->getX()+SPRITE_WIDTH-1 > x and
               m_actors[i]->getX() < x+SPRITE_WIDTH-1 and
               m_actors[i]->getY()+SPRITE_HEIGHT-1 > y and
               m_actors[i]->getY() < y+SPRITE_HEIGHT-1){
                if(m_actors[i]->isAlive()){
                    m_actors[i]->damage();
                    temp = true; // damage any overlapping actor and return true if one was damaged
                }
            }
        }
    }
    return temp;
}

bool StudentWorld::peachOverlap(int x, int y){
    int peachX = m_peach->getX();
    int peachY = m_peach->getY();
    
    if(peachX + SPRITE_WIDTH - 1 > x and peachX < x + SPRITE_WIDTH-1 and
       peachY + SPRITE_HEIGHT - 1 > y and peachY < y + SPRITE_HEIGHT-1){
        return true; // return true iof peach overlaps actor at coord
    }
    else{
        return false;
    }
}


void StudentWorld::eraseDead(){
    std::vector<Actor*>::iterator it = m_actors.begin();
    for( ; it != m_actors.end(); ){
        if((*it)->isAlive()){
            it++;
        }
        else{
            delete *it;
            it = m_actors.erase(it); // erase any dead actors
        }
    }
}

void StudentWorld::bonkPeach(){
    m_peach->bonk();
}

void StudentWorld::damagePeach(){
    m_peach->damage();
}

int StudentWorld::getPeachX(){
    return m_peach->getX();
}

int StudentWorld::getPeachY(){
    return m_peach->getY();
}

void StudentWorld::beatLevel(){
    m_beatLevel = true;
}

void StudentWorld::beatGame(){
    m_won = true;
}

void StudentWorld::addActor(Actor* actor){
    m_actors.push_back(actor); // add actor to m_actors
}
