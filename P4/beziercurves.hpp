//
//  beziercurves.hpp
//  P4
//
//  Created by Raj Patel on 11/25/17.
//  Copyright © 2017 Raj Patel. All rights reserved.
//

#ifndef beziercurves_hpp
#define beziercurves_hpp

#include <stdio.h>
#include <vector>
#include "point.hpp"


class beziercurve
{
public:
    std::vector<point> bezierPoints;
    std::vector<point> actualBezierCurvePoints;
    int index;
    
    
    void deCasteljau(int resolution)
    {
        std::vector<point> BezierCurveCalcualted;
        point temppoint;
        float t;
        float increment;
        increment = 1/(float)resolution;
        if (!BezierCurveCalcualted.empty()) {
            BezierCurveCalcualted.clear();
        }
        if (!actualBezierCurvePoints.empty()) {
            actualBezierCurvePoints.clear();
        }
        
        
        BezierCurveCalcualted = bezierPoints;
        t = 0;
        for (int res = 0; res <= resolution; res++) {
            
            if (!BezierCurveCalcualted.empty()) {
                BezierCurveCalcualted.clear();
            }
            
            BezierCurveCalcualted = bezierPoints;
            
            for (int j =1; j < bezierPoints.size(); j++) {
                
                for (int k = 0; k < (bezierPoints.size() - j); k++) {
                    temppoint.x = (1-t)*BezierCurveCalcualted[k].x + t*BezierCurveCalcualted[k+1].x;
                    temppoint.y = (1-t)*BezierCurveCalcualted[k].y + t*BezierCurveCalcualted[k+1].y;
                    BezierCurveCalcualted[k] = temppoint;
                }
            }
            actualBezierCurvePoints.push_back(BezierCurveCalcualted[0]);
            t = t + increment;
        }
    }
    

    
    
    
    
};


#endif /* beziercurves_hpp */
