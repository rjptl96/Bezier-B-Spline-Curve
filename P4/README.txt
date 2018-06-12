Hello

This is the Project 4 by Raj Patel
ID:912204486

Instructions of Compilation and Before Use:

Compilation:
Please use the provided makefile. It is the same one provided with sample code. I just have it set to Linux. Please comment out line 4, and uncomment line 6 if you are running this on MACOS. This has been tested on CSIF via SSH. If the window for GLUT fails to launch, please use X11 forwarding by adding -X to the end of the ssh command when connecting to CSIF via SSH


When the makefile is run, p4 executable is created.
Before running, make sure the curves are in a text file (example included called curves.txt)



Curve file format example:
3 -------------------------Number of Curves
<Space> 
0 -------------------------Type of Curve (0 is Beziers, 1 is Bspline)
9 -------------------------Num of Points
98 261  ---------|
185 153 ---------|
290 164 ---------|
335 246 ---------|
378 312 ---------| ------- Points
371 379 ---------|
313 463 ---------|
197 483 ---------|
108 448 ---------|
<Space> 
1 --------------------------Type of Curve (Bspline)
8 --------------------------Number of Points
3 --------------------------The Order
747 609
695 592
730 439
659 579
652 443
542 463
554 587
503 593
<Space> 
1
9
3
502 99
636 51
492 157
559 303
477 479
465 359
432 131
390 281
370 199

-----------------------------------------------------------------------------------------

How to run: 

->Run with ./p4


How to use the program:

When the program starts, you will be presented with a Command line question that looks like:

What is the name of the file with the objects you would like to load (with extension)?

Please enter the name of the file that has the curves to be drawn/modified (if the file has an extension please enter it)

The if the file exists, you will be presented with:

"Please enter the resolution you would like to render (how many points to use to draw the curves) (int)"

-Here please enter the resolution in integer value. 

-----------------------------------------------------------------------------------------

Now the program will present you with the loaded curves: 

BLUE - Bezier Curves
RED  - B-Spline Curves

-----------------------------------------------------------------------------------------
Modifying Curves:

- the curves are fully interactive. You can drag any control point around and the curve will update interactively.


Deleting a point:

-To delete a control point, hover over it and hit the key 'd'


Adding a point:

- to add a point hover over a control point, the program will automatically figure out which curve you are to add a point to, and hit the key 'a'. Then move your cursor to the point where you would like to add a point and click it. It will add a point there and will connect the point to the rest of the curve. I have tried to make it so that it detects if you click to the left or right of the point you want to add, it might not always order the new point right. However, adding a point fully works


Changing the Order of a B-Spline Curve:

- To change the the order of a B-spline curve, hover your mouse over one of the control points in that curve (again, B-Spline is red) and hit 'o' on your keyboard. The console will ask you to enter the new order of that curve. Once you enter it, the scene will update automatically. 


-----------------------------------------------------------------------------------------
Right Click Menu:

- The program has a right click menu implemented. You can bring it up by right clicking on the Glut window. 

You will be Presented with these options: 

*Save Changes
*Add New Bezier Curve Point
*Add New BSpline Curve Point
*Change Resolution
*Exit


Save Changes: This will write the changes you have made to the curves to the file you loaded at the beginning of the program

Add New Bezier Curve Point: This lets you create a new Bezier Curve. When you click this, the console will tell you to click wherever you would like to place the first control point of the Bezier curve. Once you do so, you may press 'a' to continue adding more points to that new curve


Add New BSpline Curve Point: This lets you create a new Bspline Curve. When you click this, the console will tell you to click wherever you would like to place the first control point of the Bezier curve. Once you do so, you may press 'a' to continue adding more points to that new curve (note: the order of that curve will be set by default to 3, you may wish to change it to whatever you like by hovering over a point in the curve and pressing 'o')


*Change Resolution: This lets you change the resolution at which the curves are drawn. After selecting this, the console will prompt you to enter the new resolution. Please enter it in the console (int) and the scene shall update.

*Exit: exits the program. Make sure to save your changes before exiting as this option itself will not do so. 


NOTE: This menu may not work via SSH (the menu may not show up). If so I have implemented a back up.These are the keys that perform the same functions that the menu does :)

'S' - Save Changes
'Z' - Add New Bezier Curve Point
'L' - Add New BSpline Curve Point
'R' - Change Resolution
'X' - Exit


----------------------------------------------------------------------------------------

What Works What Doesn't: :)  

Everything is working. I think :P. One thing that could be awkward is adding points to an existing curve. For example if a curve is loaded from right to left. And you hover over a point and hit 'a' and click to the left of the hover point, it might accidentally connect the right point to the the new point. Just that. It still adds the point correctly and connects the curve fine. 



-Raj Patel


