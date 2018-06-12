//
//  bspcurves.cpp
//  P4
//
//  Created by Raj Patel on 11/25/17.
//  Copyright © 2017 Raj Patel. All rights reserved.
//

#include "bspcurves.hpp"

//void bspcurve::wtfisgoinon()
//{
//    int res = 0;
//    float u = (float)theorder -1;
//    float increment;
//    increment = 1/res;
//    //Knot Vector (initially size k+n as required)
//    for (int i = 0; i < deBoorPoints.size() + theorder; i++) {
//        knotsvect.push_back(i);
//    }
//    
//    for (int i = 0; i < res*(theorder-1); i++) {
//        point tempPts[1000][1000];
//        for(int b = 0; b < deBoorPoints.size(); b++) {
//            tempPts[b][0].x = deBoorPoints[b].x;
//            tempPts[b][0].y = deBoorPoints[b].y;
//        }
//        
//        int I = 0;
//        for(int q = 0; q < knotsvect.size(); q++) {
//            if(u >= knotsvect[q] && u < knotsvect[q+1]) {
//                I = knotsvect[q];
//                break;
//            }
//        }
//        for(int j = 1; j <= theorder-1; j++) {
//            for(int c = (I - (theorder - 1)); c <= (I - j); c++) {
//                float top1 = knotsvect[c+theorder] - u;
//                float top2 = u - knotsvect[c+j];
//                float bot = knotsvect[c+theorder] - knotsvect[c+j];
//                tempPts[c][j].x = (top1/bot)*tempPts[c][j-1].x + (top2/bot)*tempPts[c+1][j-1].x;
//                tempPts[c][j].y = (top1/bot)*tempPts[c][j-1].y + (top2/bot)*tempPts[c+1][j-1].y;
//            }
//        }
//        actualBsplineCurvePoints.push_back(tempPts[I-theorder+1][theorder-1]);
//        u = u + increment;
//        
//    }
//}

