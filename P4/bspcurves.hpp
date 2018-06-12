//
//  bspcurves.hpp
//  P4
//
//  Created by Raj Patel on 11/25/17.
//  Copyright © 2017 Raj Patel. All rights reserved.
//

#ifndef bspcurves_hpp
#define bspcurves_hpp

#include <stdio.h>
#include <vector>
#include "point.hpp"

class bspcurve
{
public:
    std::vector<point> deBoorPoints;
    std::vector<point> actualBsplineCurvePoints;
    std::vector<float> knotsvect;
    int index;
    int theorder;
    
    void deBoor(int resolution)
    {
        int theOrder = theorder;
        if (!actualBsplineCurvePoints.empty()) {
            actualBsplineCurvePoints.clear();
        }
        
        if (!knotsvect.empty()) {
            knotsvect.clear();
        }
        if (theOrder != 1) {
            float u = (float)theOrder -1;
            float increment;
            increment = 1/(float)resolution;
            for (int i = 0; i < deBoorPoints.size() + theOrder; i++) {
                knotsvect.push_back(i);
            }
            for (float i = u; i < knotsvect[deBoorPoints.size()]; i  = i + increment) {
                point deboorpts[50][50];
                for(int p = 0; p < deBoorPoints.size(); p++) {
                    deboorpts[p][0].x = deBoorPoints[p].x;
                    deboorpts[p][0].y = deBoorPoints[p].y;
                }
                int I = 0;
                for(int q = 0; q < knotsvect.size(); q++) {
                    if( u < knotsvect[q+1]&& u >= knotsvect[q] ) {
                        I = knotsvect[q];
                        break;
                    }
                }
                for(int j = 1; j <= theOrder-1; j++) {
                    for(int i = (I - (theOrder - 1)); i <= (I - j); i++) {
                        float nu1 = knotsvect[i+theOrder] - u;
                        float nu2 = u - knotsvect[i+j];
                        float den = knotsvect[i+theOrder] - knotsvect[i+j];
                        deboorpts[i][j].x = (nu1/den)*deboorpts[i][j-1].x + (nu2/den)*deboorpts[i+1][j-1].x;
                        deboorpts[i][j].y = (nu1/den)*deboorpts[i][j-1].y + (nu2/den)*deboorpts[i+1][j-1].y;
                    }
                }
                actualBsplineCurvePoints.push_back(deboorpts[I-theOrder+1][theOrder-1]);
                u = u + increment;
            }
        }
        //int res;
        
    }
    
    
    
    
};




#endif /* bspcurves_hpp */
