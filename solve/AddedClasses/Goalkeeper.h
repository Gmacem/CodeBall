#pragma once
#include "Player.h"
#include "Point.h"
#include "VectorF.h"
#include "../model/Action.h"
#include "Line.h"
#include "../model/Ball.h"

const Point GoalMid(0, ROBOT_RADIUS, -DEPTH / 2 + ROBOT_RADIUS);
const double SHIFT_DEPTH = 15;
const double SHIFT_WIDTH = 0;

std::vector<Point> path = {
		Point(-GOAL_WIDTH / 2 - SHIFT_WIDTH, 0, BOTTOM_RADIUS - DEPTH / 2),
		Point(-GOAL_WIDTH / 2 - SHIFT_WIDTH, 0, SHIFT_DEPTH - DEPTH / 2 ),
		Point(GOAL_WIDTH / 2 + SHIFT_WIDTH , 0, SHIFT_DEPTH - DEPTH / 2 ),
		Point(GOAL_WIDTH / 2 + SHIFT_WIDTH, 0,  BOTTOM_RADIUS - DEPTH / 2 ),};

class Goalkeeper : public Player
{
public:
    Goalkeeper () : Player() {}
    
    void GoToGoal (model::Action & action, double speed) 
    {
        this->GoToPoint(action, GoalMid, speed);
    }

    void PatrolGoal(const model::Ball & ball, model::Action & action)
    {
        Point ballP(ball.x, 0, ball.z);
        Line dir(ballP, VectorF(ball.velocity_x, 0, ball.velocity_z));
        Point bestPoint = path[0];
        double bestDist = distance(bestPoint, ballP);
        for (int i = 0; i + 1 < path.size(); ++i)
        {
            Line curLine(path[i], path[i + 1]);
            Point inter;
            if (LineIntersection(curLine, dir, inter))
            {
                double dist = distance(inter, ballP);
                if (!InSegment(path[i], path[i + 1], curLine, inter))
                {
                    dist = distance(path[i + 1], ballP);
                    inter = path[i + 1];
                    
                }
                if (dist < bestDist)
                {
                    bestDist = dist;
                    bestPoint = inter;
                }
            }
        }
        if (!this->HitInJump(ball, action))
            this->GoToPointCaution(action, bestPoint);
    }
};

