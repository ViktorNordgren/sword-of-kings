/*
* Enemy.cpp
*/

#include "enemy.h"


/*
* Class Enemy
*/


/*
* This constuctor can be used to specify all values of a character
*/
Enemy::Enemy(string n, int hitpoints, double att, double def, int lev, string text, EnemyType enemType) : Character(n, hitpoints, att, def, lev, text)
{
    enemyType = enemType;
}

/*
* This constructor will set some values based on the level specified
*/
Enemy::Enemy(string n, int lev, string text, EnemyType enemType) : Character(n, lev, text)
{
    enemyType = enemType;
}

/*
* Getters
*/
EnemyType Enemy::getEnemyType()
{
    return enemyType;
}

/*
* Setters
*/
void Enemy::setEnemyType(EnemyType enemType)
{
    enemyType = enemType;
}
