/*
 * Simple glut demo that can be used as a template for
 * other projects by Garrett Aldrich
 */


#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//other includes
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <math.h>
#include <fstream>
#include <vector>
#include <stack>          // std::stack
#include <algorithm>
#include "bspcurves.hpp"
#include "beziercurves.hpp"
//#include "triangles.hpp"
using namespace std;
int resol;


int curvetypemove;
int curvenummove;
int pointnummove;
bool pointmoved = false;
bool addthatpointbspline = false;
bool addthatpointbeziers = false;
bool addanewbezcurve = false;
bool addanewbspcurve = false;


/****set in main()****/
//the number of pixels in the grid
int grid_width;
int grid_height;

//the size of pixels sets the inital window height and width
//don't make the pixels too large or the screen size will be larger than
//your display size
float pixel_size;


bool moving = false;
/*Window information*/
int win_height;
int win_width;

vector<point> ObjectPts;
vector<vector<point> > ObjectTotalPts;
vector< vector<point> > PolygonOutlines;
vector< vector<point> > ClippedPolygonOutlines;
//vector<point> outlines;

point temppoint0;
point temppoint1;

void drawapoint(point start,int color);

fstream polyfile;
int howmanyObjects;
int howmanyedges;
int howManyPoints;
string start;
string middle;
string ending;
string blankline;
string polyx;
string polyy;
string polyz;

int winxy;
int winxz;
int winyz;


string fileName;
string intialpoint;
string finalpoint;
float F_light;
float K_light;


vector<point> bezierPoints;
vector<point> bsplinePoints;

vector<beziercurve> BezierCurves;
vector<bspcurve> BSplineCurves;


void draw_curves_save_file();
void saveFile();
void deCasteljau(int resolution);
void init();
void idle();
void display();
void draw_pix(int x, int y);
void reshape(int width, int height);
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void check();
void draw_lines(point start, point end, int color);
void theMenu();

void openFile();

bool juststarted = true;
int polynumba;
int pointnumber;
int mainw;
void menucases(int whichcase);
void rightClickMenu();






int main(int argc, char **argv)
{
      openFile();
    while (true) {
        cout << "Please enter the resolution you would like to render (how many points to use to draw the curves) (int) "<< endl;
        while(!(cin >> resol)) {
            cout << "Incorrect input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
//    openFile(0);
//    openFile(1);
//    openFile(2);
    
    
    //cout << ObjectTotalPts[0][0].x;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    /*initialize variables, allocate memory, create buffers, etc. */
    //create window of size (win_width x win_height
    win_width = 800;
    win_height = 800;
    glutInitWindowSize(win_width,win_height);
    glutInitWindowPosition(0, 0);
    //windown title is "glut demo"
     mainw = glutCreateWindow("glut demo");
    glClearColor(0, 0, 0, 1);
    glutDisplayFunc(display); //rendering calls here
    rightClickMenu();
    glutIdleFunc(idle);       //Function called while program is sitting "idle"
    glutKeyboardFunc(key);    //Keyboard events
    glutMouseFunc(mouse);     //mouse button events
    glutMotionFunc(motion);   //mouse movement events
    glutReshapeFunc(reshape);
    
 
    
    
    
    
    //start glut event loop
    glutMainLoop();
    return 0;
}





/*initialize gl stufff*/
void init()
{
    //set clear color (Default background to white)
    glClearColor(1.0,1.0,1.0,1.0);
    //checks for OpenGL errors
    check();
}

//called repeatedly when glut isn't doing anything else
void idle()
{
    //redraw the scene over and over again
    
    glutPostRedisplay();
}

//this is where we render the screen
void display()
{
    //clears the screen
    glClear(GL_COLOR_BUFFER_BIT);
    
   
    //clears the opengl Modelview transformation matrix
    glLoadIdentity();
    //theMenu();
    //theMenu();
    draw_curves_save_file();
    
    
    
    
    
    
    
    int resol;
    

    glFlush();  // Render now
    glutPostRedisplay();

}



void drawapoint(point start,int color){
    
    float startx=(start.x/(win_width/2))-1;
    float starty=(start.y/(win_height/2))-1;
    
    
    int r =1;
    int g =1;
    int b =1;
    
    //0 black
    //1 Beziers (blue)
    //2 Bpline (red)
    if (color == 0) {
        r = 0;
        g = 0;
        b = 0;
    }
    else if (color ==1)
    {
        r = .6;
        g = 1;
        b = 1;
    }
    else if (color ==2)
    {
        r = 1;
        g = 0;
        b = 0;
    }
    
    glLineWidth(2.0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(r,g,b);
    glVertex2f(startx,starty);
    glEnd();
    
    
}





void draw_lines(point start, point end, int color){
    
    float startx=(start.x/(win_width/2))-1;
    float starty=(start.y/(win_height/2))-1;

    float endx=(end.x/(win_width/2))-1;
    float endy=(end.y/(win_height/2))-1;
    
    int r =1;
    int g =1;
    int b =1;
    
    //0 black
    //1 Beziers (blue)
    //2 Bpline (red)
    if (color == 0) {
        r = 1;
        g = 1;
        b = 1;
    }
    else if (color ==1)
    {
        r = .6;
        g = 1;
        b = 1;
    }
    else if (color ==2)
    {
        r = 1;
        g = 0;
        b = 0;
    }
    
    glLineWidth(2.0);
    
    glBegin(GL_LINES);
        glColor3f(r,g,b);
        glVertex2f(startx,starty);
        glVertex2f(endx,endy);
    glEnd();
   
    
}

/*Gets called when display size changes, including initial craetion of the display*/
void reshape(int width, int height)
{
    /*set up projection matrix to define the view port*/
    //update the ne window width and height
    win_width = width;
    win_height = height;
    
    //creates a rendering area across the window
//    glViewport(0,0,width,height);
//    // up an orthogonal projection matrix so that
//    // the pixel space is mapped to the grid space
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0,grid_width,0,grid_height,-10,10);
//
//    //clear the modelview matrix
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    //set pixel size based on width, if the aspect ratio
//    //changes this hack won't work as well
//    pixel_size = width/(float)grid_width;
    
    //set pixel size relative to the grid cell size
    
    glViewport(0, 0, width, height);
    //glutReshapeWindow(width,height);
    glutPostRedisplay();
   
    //check for opengl errors
    check();
}






//checks for any opengl errors in the previous calls and
//outputs if they are present
void check()
{
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        printf("GLERROR: There was an error %s\n",gluErrorString(err) );
        exit(1);
    }
}





void openFile()
{
    int curvetype;
    int orda;
    bspcurve tempbspcurve;
    beziercurve tempbeziercurve;
    vector<point> tempdeboorpts;
    vector<point> tempbezierpts;
    while (true) {
        cout<< "What is the name of the file with the objects you woud like to load (with extension)?";
        getline(cin, fileName);
        polyfile.open (fileName, ios::in);
        if (polyfile.is_open())
        {
            polyfile >> howmanyObjects;
            //cout << howmanypolygons<< endl;
            
            for (int i = 0; i < howmanyObjects; i++) {
                
                getline(polyfile,blankline , '\n');
                
                polyfile >> curvetype;
                
                
                if (curvetype == 0) {
                    
                    //Beziers
                    polyfile >> howManyPoints;
                    polyfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    //cout << howmanyedges << endl;
                    for (int j = 0; j < howManyPoints ; j++) {
                        
                        getline(polyfile, polyx, ' ');
                        getline(polyfile, polyy, '\n');
                        temppoint0.x = stof(polyx);
                        temppoint0.y = stof(polyy);
                        
                        tempbezierpts.push_back(temppoint0);
                        
                    }
                    tempbeziercurve.index = i;
                    tempbeziercurve.bezierPoints = tempbezierpts;
                    BezierCurves.push_back(tempbeziercurve);
                    
                    tempbeziercurve.bezierPoints.clear();
                    tempbezierpts.clear();
                    
                }
                else if (curvetype == 1)
                {
                    
                    //boor
                    polyfile >> howManyPoints;
                    polyfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    polyfile >> orda;
                    polyfile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    //cout << howmanyedges << endl;
                    for (int j = 0; j < howManyPoints ; j++) {
                        
                        getline(polyfile, polyx, ' ');
                        getline(polyfile, polyy, '\n');
                        temppoint0.x = stof(polyx);
                        temppoint0.y = stof(polyy);
                        
                        tempdeboorpts.push_back(temppoint0);
                        
                    }
                    tempbspcurve.index = i;
                    tempbspcurve.deBoorPoints = tempdeboorpts;
                    tempbspcurve.theorder = orda;
                    BSplineCurves.push_back(tempbspcurve);
                    
                    tempbspcurve.deBoorPoints.clear();
                    tempdeboorpts.clear();
                    
                    
                    
                }
                
                
                
            }
            
            
        }
        else
        {
            cout << "file not found. try again" << endl;
            continue;
        }
        polyfile.close();
        break;
    }
    
}

void saveFile()
{
    int curvetype;
    int orda;
    bspcurve tempbspcurve;
    beziercurve tempbeziercurve;
    vector<point> tempdeboorpts;
    vector<point> tempbezierpts;
    while (true) {
         polyfile.open (fileName, ios::out | ios::trunc);
        if (polyfile.is_open())
        {
            polyfile << BSplineCurves.size() + BezierCurves.size() << '\n';
            //polyfile >> howmanyObjects;
            //cout << howmanypolygons<< endl;
            //getline(polyfile,blankline , '\n');
            
            for (int c = 0; c < BezierCurves.size(); c++) {
                polyfile << endl;
                polyfile << 0 << '\n';
                polyfile << BezierCurves[c].bezierPoints.size() << '\n';
                
                for (int p = 0; p < BezierCurves[c].bezierPoints.size() ; p++) {
                    polyfile << BezierCurves[c].bezierPoints[p].x;
                    polyfile << ' ' ;
                    polyfile << BezierCurves[c].bezierPoints[p].y;
                    polyfile << '\n' ;
                }
 
            }
            
            
            for (int c = 0; c < BSplineCurves.size(); c++) {
                polyfile << endl;
                polyfile << 1 << '\n';
                polyfile << BSplineCurves[c].deBoorPoints.size() << '\n';
                polyfile << BSplineCurves[c].theorder << '\n';
                for (int p = 0; p < BSplineCurves[c].deBoorPoints.size() ; p++) {
                    polyfile << BSplineCurves[c].deBoorPoints[p].x;
                    polyfile << ' ' ;
                    polyfile << BSplineCurves[c].deBoorPoints[p].y;
                    polyfile << '\n' ;
                }
                
            }
            

            
            
        }
        else
        {
            cout << "file not found. try again" << endl;
            continue;
        }
        polyfile.close();
        break;
    }
    
}


void mouse(int button, int state, int x, int y)
{
    bool trybeziers = false;
    
    //print the pixel location, and the grid location
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int xx;
        int yy;
        beziercurve tempbeziercurve;
        bspcurve tempbspcurve;
        //vector<point> tempbezierpts;
        point tempnew;
        
        //printf ("MOUSE AT PIXEL: %d %d\n",x,win_height-y);
        xx = x;
        yy = win_height-y;
        
        if (addanewbezcurve == true || addanewbspcurve == true) {
            
            if (addanewbezcurve == true) {
                tempnew.x = xx;
                tempnew.y = yy;
                tempbeziercurve.bezierPoints.push_back(tempnew);
                BezierCurves.push_back(tempbeziercurve);
                tempbeziercurve.bezierPoints.clear();
                addanewbspcurve = false;
                addanewbezcurve = false;
            }
            else if (addanewbspcurve == true) {
                tempnew.x = xx;
                tempnew.y = yy;
                tempbspcurve.deBoorPoints.push_back(tempnew);
                tempbspcurve.theorder = 3;
                BSplineCurves.push_back(tempbspcurve);
                tempbspcurve.deBoorPoints.clear();
                
                addanewbspcurve = false;
                addanewbezcurve = false;
            }
            
            
        }
        else
        {
            for (int i = 0; i < BSplineCurves.size(); i++) {
                if (!BSplineCurves[i].deBoorPoints.empty())
                {
                    for (int j = 0; j < BSplineCurves[i].deBoorPoints.size(); j++) {
                        if (xx-BSplineCurves[i].deBoorPoints[j].x >= -10 && xx-BSplineCurves[i].deBoorPoints[j].x <= 10 && yy-BSplineCurves[i].deBoorPoints[j].y  >= -10 &&yy-BSplineCurves[i].deBoorPoints[j].y <= 10)
                        {
                            //printf ("Actual Point: %f %f\n",BSplineCurves[i].deBoorPoints[j].x,BSplineCurves[i].deBoorPoints[j].y);
                            trybeziers = false;
                            moving = true;
                            pointmoved = true;
                            curvetypemove = 1;
                            curvenummove = i;
                            pointnummove = j;
                            
                            
                        }
                        else
                        {
                            if (moving == false) {
                                trybeziers = true;
                                pointmoved = false;
                            }
                            if (addthatpointbspline == true)
                            {
                                point temppoint;
                                temppoint.x = xx;
                                temppoint.y = yy;
                                
                                if (temppoint.x <   BSplineCurves[curvenummove].deBoorPoints[pointnummove].x ) {
                                    BSplineCurves[curvenummove].deBoorPoints.insert(BSplineCurves[curvenummove].deBoorPoints.begin()+pointnummove+1, temppoint);
                                }
                                else
                                {
                                    BSplineCurves[curvenummove].deBoorPoints.insert(BSplineCurves[curvenummove].deBoorPoints.begin()+pointnummove, temppoint);
                                }
                                glutPostRedisplay();
                                addthatpointbspline = false;
                            }
                            
                        }
                        
                        
                    }
                }
                
            }
            
            if (trybeziers == true) {
                for (int i = 0; i < BezierCurves.size(); i++) {
                    if (!BezierCurves[i].bezierPoints.empty())
                    {
                        for (int j = 0; j < BezierCurves[i].bezierPoints.size(); j++) {
                            if (xx-BezierCurves[i].bezierPoints[j].x >= -10 && xx-BezierCurves[i].bezierPoints[j].x <= 10 && yy-BezierCurves[i].bezierPoints[j].y  >= -10 &&yy-BezierCurves[i].bezierPoints[j].y <= 10)
                            {
                                //printf ("Actual Point: %f %f\n",BezierCurves[i].bezierPoints[j].x,BezierCurves[i].bezierPoints[j].y);
                                pointmoved = true;
                                moving = true;
                                curvetypemove = 0;
                                curvenummove = i;
                                pointnummove = j;
                                
                                
                            }
                            else
                            {
                                if (moving == false) {
                                    trybeziers = true;
                                    pointmoved = false;
                                }
                                if (addthatpointbeziers == true)
                                {
                                    point temppoint;
                                    temppoint.x = xx;
                                    temppoint.y = yy;
                                    if (temppoint.x <  BezierCurves[curvenummove].bezierPoints[pointnummove].x ) {
                                        BezierCurves[curvenummove].bezierPoints.insert(BezierCurves[curvenummove].bezierPoints.begin()+pointnummove+1, temppoint);
                                    }
                                    else
                                    {
                                        BezierCurves[curvenummove].bezierPoints.insert(BezierCurves[curvenummove].bezierPoints.begin()+pointnummove, temppoint);
                                    }
                                    glutPostRedisplay();
                                    addthatpointbeziers = false;
                                }
                            }
                            
                            
                        }
                    }
                    
                }
            }
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    }
    
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        //printf ("MOUSE AT PIXEL Final: %d %d\n",x,800-y);
        
        if (pointmoved == true) {
            if (curvetypemove == 1) {
                BSplineCurves[curvenummove].deBoorPoints[pointnummove].x = x;
                BSplineCurves[curvenummove].deBoorPoints[pointnummove].y = win_height-y;
                moving = false;
            }
            
            if (curvetypemove == 0) {
                BezierCurves[curvenummove].bezierPoints[pointnummove].x = x;
                BezierCurves[curvenummove].bezierPoints[pointnummove].y = win_height-y;
                moving = false;
            }
            
            
            pointmoved = false;
            
        }
        
        
        
        
        
        
    }
    
//
    glutPostRedisplay();
}

//gets called when the curser moves accross the scene
void motion(int x, int y)
{
    int xx = x;
    int yy = win_height- y;
//    cout << "AT: " << xx << " " << yy << endl;

    if (moving == true ) {
        if (curvetypemove == 0) {
            BezierCurves[curvenummove].bezierPoints[pointnummove].x = xx;
            BezierCurves[curvenummove].bezierPoints[pointnummove].y = yy;
            //draw_curves_save_file();
            glutPostRedisplay();
        }
        if (curvetypemove == 1) {
            BSplineCurves[curvenummove].deBoorPoints[pointnummove].x = xx;
            BSplineCurves[curvenummove].deBoorPoints[pointnummove].y = yy;
            //draw_curves_save_file();
            glutPostRedisplay();
        }
    }
    //redraw the scene after mouse movement
    
}

void draw_curves_save_file()
{
 
 
 for (int i = 0; i < BezierCurves.size(); i++) {
     if (!BezierCurves[i].bezierPoints.empty())
     {
         BezierCurves[i].deCasteljau(resol);
         
     }
     
 }
 
 
 for (int i = 0; i < BezierCurves.size(); i++) {
     if (!BezierCurves[i].bezierPoints.empty())
     {
         for (int j = 0; j < BezierCurves[i].bezierPoints.size()-1; j++) {
             draw_lines(BezierCurves[i].bezierPoints[j], BezierCurves[i].bezierPoints[j+1], 1);
         }
     }
     
 }
 
 for (int i = 0; i < BezierCurves.size(); i++) {
     if (!BezierCurves[i].actualBezierCurvePoints.empty())
     {
         for (int j = 0; j < BezierCurves[i].actualBezierCurvePoints.size()-1; j++) {
             draw_lines(BezierCurves[i].actualBezierCurvePoints[j], BezierCurves[i].actualBezierCurvePoints[j+1],0);
         }
     }
     
 }
 
 
 
 
 
 
 
 for (int i = 0; i < BSplineCurves.size(); i++) {
     if (!BSplineCurves[i].deBoorPoints.empty())
     {
         BSplineCurves[i].deBoor(resol);
         
     }
     
 }
 
 
 for (int i = 0; i < BSplineCurves.size(); i++) {
     if (!BSplineCurves[i].deBoorPoints.empty())
     {
         for (int j = 0; j < BSplineCurves[i].deBoorPoints.size()-1; j++) {
             draw_lines(BSplineCurves[i].deBoorPoints[j], BSplineCurves[i].deBoorPoints[j+1], 2);
         }
     }
     
 }
 
 for (int i = 0; i < BSplineCurves.size(); i++) {
     if (!BSplineCurves[i].actualBsplineCurvePoints.empty())
     {
         for (int j = 0; j < BSplineCurves[i].actualBsplineCurvePoints.size()-1; j++) {
             draw_lines(BSplineCurves[i].actualBsplineCurvePoints[j], BSplineCurves[i].actualBsplineCurvePoints[j+1],0);
         }
     }
     
 }
    
for (int i = 0; i < BSplineCurves.size(); i++) {
        if (!BSplineCurves[i].deBoorPoints.empty())
        {
            for (int j = 0; j < BSplineCurves[i].deBoorPoints.size(); j++) {
                drawapoint(BSplineCurves[i].deBoorPoints[j],2);
            }
        }
        
    }
    
    for (int i = 0; i < BezierCurves.size(); i++) {
        if (!BezierCurves[i].bezierPoints.empty())
        {
            for (int j = 0; j < BezierCurves[i].bezierPoints.size(); j++) {
                drawapoint(BezierCurves[i].bezierPoints[j],1);
            }
        }
        
    }
    
    
    
    
    
}


//gets called when a key is pressed on the keyboard
void key(unsigned char ch, int x, int y)
{
    
    int xx;
    int yy;
    xx = x;
    yy = win_height-y;
    bool acurvept = false;
    bool trybeziers = false;
    
    for (int i = 0; i < BSplineCurves.size(); i++) {
        if (!BSplineCurves[i].deBoorPoints.empty())
        {
            for (int j = 0; j < BSplineCurves[i].deBoorPoints.size(); j++) {
                if (xx-BSplineCurves[i].deBoorPoints[j].x >= -10 && xx-BSplineCurves[i].deBoorPoints[j].x <= 10 && yy-BSplineCurves[i].deBoorPoints[j].y  >= -10 &&yy-BSplineCurves[i].deBoorPoints[j].y <= 10)
                {
                    //printf ("Actual Point: %f %f\n",BSplineCurves[i].deBoorPoints[j].x,BSplineCurves[i].deBoorPoints[j].y);
                    acurvept = true;
                    curvetypemove = 1;
                    curvenummove = i;
                    pointnummove = j;
                    break;
                    
                    
                }
                else
                {
                    acurvept = false;
                    trybeziers = true;
                    
                }
                
                
            }
            
            if (acurvept == true) {
                trybeziers = false;
                break;
            }
        }
        
    }
    
    if (trybeziers == true) {
        for (int i = 0; i < BezierCurves.size(); i++) {
            if (!BezierCurves[i].bezierPoints.empty())
            {
                for (int j = 0; j < BezierCurves[i].bezierPoints.size(); j++) {
                    if (xx-BezierCurves[i].bezierPoints[j].x >= -10 && xx-BezierCurves[i].bezierPoints[j].x <= 10 && yy-BezierCurves[i].bezierPoints[j].y  >= -10 &&yy-BezierCurves[i].bezierPoints[j].y <= 10)
                    {
                        //printf ("Actual Point: %f %f\n",BezierCurves[i].bezierPoints[j].x,BezierCurves[i].bezierPoints[j].y);
                        acurvept = true;
                        curvetypemove = 0;
                        curvenummove = i;
                        pointnummove = j;
                        trybeziers = false;
                        break;
                    }
                    else
                    {
                        acurvept = false;
                    }
                    
                    
                }
                if (acurvept == true) {
                    break;
                }
            }
            
        }
    }
    
    //prints out which key the user hit
    //printf("User hit the \"%c\" key and curve type %d and curve number %d \n and point %d",ch,curvetypemove,curvenummove,pointnummove );
    
    if (ch == 'd') {
        if (curvetypemove == 0 && acurvept == true) {
            BezierCurves[curvenummove].bezierPoints.erase(BezierCurves[curvenummove].bezierPoints.begin()+pointnummove);
            if (BezierCurves[curvenummove].bezierPoints.empty()) {
                BezierCurves.erase(BezierCurves.begin()+curvenummove);
            }
            
            
        }
        if (curvetypemove == 1 && acurvept == true) {
            BSplineCurves[curvenummove].deBoorPoints.erase(BSplineCurves[curvenummove].deBoorPoints.begin()+pointnummove);
            
            if (BSplineCurves[curvenummove].deBoorPoints.empty()) {
                BSplineCurves.erase(BSplineCurves.begin()+curvenummove);
            }
            
            
        }
        
    }
    
    if (ch == 'a') {
        
        if (curvetypemove == 0 && acurvept == true) {
            cout << "move cursor to the position where you would like to add a point and click" << endl;
            cout << endl;
            addthatpointbeziers = true;
            addthatpointbspline = false;
        }
        if (curvetypemove == 1 && acurvept == true) {
            cout << "move cursor to the position where you would like to add a point and click" << endl;
            cout << endl;
            addthatpointbspline = true;
            addthatpointbeziers = false;
        }
        
        
        
        
        
    }
    
    
    if (ch == 'o') {
       
        
        if (curvetypemove == 1 && acurvept == true) {
            cout << endl;
            cout << "Current order: "  << BSplineCurves[curvenummove].theorder << " please change according to the change you made" << endl;
            
            
            
            
            while (true) {
                cout << "Enter New order: " << endl;
                
                while(!(cin >> pointnumber)) {
                    cout << "Incorrect input. Please try again.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (pointnumber > BSplineCurves[curvenummove].deBoorPoints.size() || pointnumber < 1)
                {
                    cout << "Index number out of range, please select between order 1 and " << BSplineCurves[curvenummove].deBoorPoints.size()-1 << endl;
                    continue;
                }
                else{
                    BSplineCurves[curvenummove].theorder = pointnumber;
                    break;
                }
            }
            
        }
        
        
        
    }
    
    if (ch == 'r') {
        
        
        while (true) {
            cout << "Please enter the resolution you would like to render (how many points to use to draw the curves) (int) "<< endl;
            while(!(cin >> resol)) {
                cout << "Incorrect input. Please try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        
        
    }
    
    if (ch == 's') {
        
        if (!BSplineCurves.empty() || !BezierCurves.empty()) {
            cout << "CHANGES SAVED" << endl << endl;
            saveFile();
        }
        
    }
    
    if (ch == 'z') {
        
        addanewbezcurve = true;
        addanewbspcurve = false;
        cout << "Please click where you would like to add the first point of the curve" << endl;
        cout << endl;
        
    }
    
    if (ch == 'x') {
        
        cout << "BYE :) " << endl;
        exit(0);
        
    }
    
    if (ch == 'l') {
        
        addanewbezcurve = false;
        addanewbspcurve = true;
        cout << "Please click where you would like to add the first point of the curve (note: The Order of this curve will be set to 3, please change accordingly)" << endl;
        cout << endl;
        
    }
    
    
    
            
    
    //redraw the scene after keyboard input
    glutPostRedisplay();
}

void menucases(int whichcase) {
    switch (whichcase) {
        case 0:
            if (!BSplineCurves.empty() || !BezierCurves.empty()) {
                cout << "CHANGES SAVED" << endl << endl;
                saveFile();
            }
            break;
        case 1:
            addanewbezcurve = true;
            addanewbspcurve = false;
            cout << "Please click where you would like to add the first point of the curve" << endl;
            cout << endl;
            break;
        case 2:
            addanewbezcurve = false;
            addanewbspcurve = true;
            cout << "Please click where you would like to add the first point of the curve (note: The Order of this curve will be set to 3, please change accordingly)" << endl;
            cout << endl;
            break;
        case 3:
            while (true) {
                cout << "Please enter the resolution you would like to render (how many points to use to draw the curves) (int) "<< endl;
                while(!(cin >> resol)) {
                    cout << "Incorrect input. Please try again.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            break;
        case 4:
            exit(0);
        default:
            break;
    }
}

void rightClickMenu() {
    int rcmenu;
    
    rcmenu = glutCreateMenu(menucases);
    glutAddMenuEntry("Save Changes", 0);
    glutAddMenuEntry("Add New Bezier Curve Point", 1);
    glutAddMenuEntry("Add New BSpline Curve Point", 2);
    glutAddMenuEntry("Change Resolution", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

