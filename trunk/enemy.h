/*
* Enemy.h
*/

#include "character.h"
#include "common_game.h"

class Enemy : public Character
{
    public:
        Enemy(string n, int hitpoints, double att, double def, int lev, string text, EnemyType enemType);
        Enemy(string n, int lev, string text, EnemyType enemType);
        //getters
        EnemyType getEnemyType();
        //setters
        void setEnemyType(EnemyType enemType);

    protected:
        EnemyType enemyType;
        
};

