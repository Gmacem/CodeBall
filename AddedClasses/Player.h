#pragma once
#include "../model/Robot.h"
#include "../model/Action.h"
#include "Point.h"
#include "VectorF.h"

const double LONG_DIST_SPEED = 30;
const double MID_DIST_SPEED = 20;
const double SHORT_DIST_SPEED = 1;

const double LONG_DIST = 15;
const double MID_DIST = 2;
const double SHORT_DIST = 0;
const double JUMP_DIST = 5;

Point NextTickFrame(const Point & p, const VectorF & dir);

class Player
{
public:    
    Player () : _bot(nullptr) {}

    VectorF GetSpeedVector()
    {
        return VectorF(_bot->velocity_x, _bot->velocity_y, _bot->velocity_z);
    }
    
    Point GetPos()
    {
        return Point(_bot->x, _bot->y, _bot->z);
    }
    
    void GoToPoint (model::Action & action, const Point & p, double speed)
    {
        Point point(_bot->x, _bot->y, _bot->z);
        
        if (point == p)
            return;
        
        VectorF VectorFMove = VectorFToLength(VectorF(p.x(), p.y(), p.z()) - VectorF(point), speed);
        
        AddVectorToAction(action, VectorFMove);
    }    
    
    void GoToPointCaution(model::Action & action, const Point & p)
    {
        Point robotP(_bot->x, _bot->y, _bot->z);
        double dist = distance(robotP, p);
        if (dist >= LONG_DIST)
            GoToPoint(action, p, LONG_DIST_SPEED);
        else if (dist >= MID_DIST)
            GoToPoint(action, p, MID_DIST_SPEED);
        else
            GoToPoint(action, p, SHORT_DIST_SPEED);
    }    
    
    void Jump(model::Action & action, double speed)
    {
        action.jump_speed = speed;
    }
    
    bool HitInJump(const model::Ball & ball, model::Action & action)
    {
        Point ballP(ball.x, ball.y, ball.z);
        Point nextBallP = NextTickFrame(ballP, VectorF(ball.velocity_x, ball.velocity_y, ball.velocity_z));
        int bestSpeed = 0;
        double bestDist = INFINIUM;
        for (int speed = 1; speed <= ROBOT_MAX_JUMP_SPEED; ++speed)
        {
            VectorF vec = this->GetSpeedVector();
            vec.SetY(speed);
            Point curNextBotP = NextTickFrame(this->GetPos(), vec);
            double dist = distance(curNextBotP, nextBallP);
            if (dist <= JUMP_DIST && dist < bestDist)
            {
                bestSpeed = speed;
                bestDist = dist;
            }
        }
        if (bestSpeed != 0)
        {
            action.jump_speed = bestSpeed;
            return true;
        }
        return false;
    }
    
    
    void setRobot (model::Robot const & bot)
    {
        _bot = & bot;
    }
    
protected:
    model::Robot const * _bot;
};

Point NextTickFrame(const Point & p, const VectorF & dir)
{
    VectorF dirToNextPos = dir / TICKS_PER_SECOND;
    return p + dirToNextPos;
}
    
