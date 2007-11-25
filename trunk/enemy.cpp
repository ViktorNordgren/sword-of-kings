/*
* Enemy.cpp
*/

#include "enemy.h"


/*
* Class Enemy
*/

Enemy::Enemy()
{
    
}

/*
* This constuctor can be used to specify all values of a character
*/
Enemy::Enemy(string n, int hitpoints, double att, double def, int lev, string text, string id) : Character(n, hitpoints, att, def, lev, text)
{
    enemyID = id;
}

/*
* This constructor will set some values based on the level specified
*/
Enemy::Enemy(string n, int lev, string text, string id) : Character(n, lev, text)
{
    enemyID = id;
}

/*
* Getters
*/
string Enemy::getEnemyID()
{
    return enemyID;
}

/*
* Setters
*/
void Enemy::setEnemyID(string id)
{
    enemyID = id;
}
