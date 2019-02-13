#pragma once
#include "Player.h"
#include "Line.h"
#include "Point.h"
#include "VectorF.h"

const Point ENEMY_GOAL = Point(0, 0, DEPTH / 2);
const double DIST_TO_BALL = 2;
class Forward : public Player
{
public:
    Forward () : Player() {}
    
    void LeadBallToEnemy(const model::Ball & ball, model::Action & action)
    {
        Point ballP(ball.x, 0, ball.z);
        Line l(ENEMY_GOAL, ballP);
        VectorF shift = l.directionVector().ToLength(DIST_TO_BALL);
        Point p1 = ballP + shift;
        Point p2 = ballP - shift;
        if (distance(p1, ENEMY_GOAL) < distance(p2, ENEMY_GOAL))
            this->GoToPoint(action, p2, 50);
        else
            this->GoToPoint(action, p1, 50);
    }
};

