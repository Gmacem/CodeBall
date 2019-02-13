#include "MyStrategy.h"
#include <math.h>
#include <iomanip>
#include <iostream>
#include "AddedClasses/Forward.h"
#include "AddedClasses/Goalkeeper.h"
#include "AddedClasses/VectorF.h"
#include "AddedClasses/Point.h"

using namespace model;

MyStrategy::MyStrategy () { }

void MyStrategy::act (const Robot & me
        , const Rules & rules
        , const Game & game
        , Action & action) 
{
    static Forward forward;
    static Goalkeeper goalkeeper;
    if (me.id % 2 == 1)
    {
        forward.setRobot(me);
        //if (!forward.HitInJump(game.ball, action))
        forward.LeadBallToEnemy(game.ball, action);
    }
    else 
    {
        goalkeeper.setRobot(me);
        goalkeeper.PatrolGoal(game.ball, action);
    }
}
