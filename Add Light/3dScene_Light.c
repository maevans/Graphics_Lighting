//
//  main.c
//  SceneIn3D
//
//  Created by Mahalia Evans
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>


#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//===============================VARIABLES====================================
//----------------------------------------------------------------------------
int angle=0;          //  Azimuth of view angle
int elev=0;          //  Elevation of view angle
int mode=0;        //  Display
double z=0;     // Z variable
double w=1;     // W variable
double pi=3.14159; // Pi
int axes=0; // Axes

// Rotation
typedef struct {
    double rotAngle;
    double rotX;
    double rotY;
    double rotZ;
} Rotation;

//=================================TREE=======================================
//----------------------------------------------------------------------------
static void cylinder (double radius, double height, int num,
                      double xPos, double yPos, double zPos, Rotation rot){
    //  Transformation
    glPushMatrix();
    //  Translation Double
    glTranslated(xPos,yPos,zPos); //TranslateD = Double, F = float
    // Rotation Double
    glRotated(rot.rotAngle,rot.rotX,rot.rotY,rot.rotZ); // Tree Branch Rotation
    
    // Tree Trunk
    glBegin(GL_QUADS);
    // Angle in Radians
    for (int i = 0; i < num; i++){
        double angle1 = 2 * pi * i / num; // Num - sides of polygon for base or Vertex count
        double angle2 = 2 * pi * (i+1) / num;
        
        // Z axis
        double z1 = cos(angle1) * radius; // Radius of Cylinder
        double x1 = sin(angle1) * radius; // X Axis
        
        // Y Axis - Height
        double yLow = 0;
        double yHigh = height;
        
        double z2 = cos(angle2) * radius; // Radius of Cylinder
        double x2 = sin(angle2) * radius; // X Axis
        
        // Quad
        glVertex3f(x1,yLow,z1);
        glVertex3f(x2,yLow,z2);
        glVertex3f(x2,yHigh,z2);
        glVertex3f(x1,yHigh,z1);
        
    }
    //  End
    glEnd();
    //  Undo transformations
    glPopMatrix();
}

//==================================SUN=======================================
//----------------------------------------------------------------------------
static void sphere(double radius,
                   double xPos, double yPos, double zPos) {
    //  Transformation
    glPushMatrix();
    //  Translation
    glTranslated(xPos,yPos,zPos);
    int num = 320;
    double theta_arc_length = pi / (num);
    double phi_arc_length = 2 * pi / (num);
    for (int j = 0; j < num; ++j) {
        for (int i = 0; i < num; ++i) {
            double theta1 = theta_arc_length * i;
            double theta2 = theta_arc_length * (i + 1);

            double phi1 = phi_arc_length * j;
            double phi2 = phi_arc_length * (j + 1);

            double x1 = radius * sin(theta1) * cos(phi1);
            double y1 = radius * sin(theta1) * sin(phi1);
            double z1 = radius * cos(theta1);

            double x2 = radius * sin(theta2) * cos(phi1);
            double y2 = radius * sin(theta2) * sin(phi1);
            double z2 = radius * cos(theta2);

            double x3 = radius * sin(theta2) * cos(phi2);
            double y3 = radius * sin(theta2) * sin(phi2);
            double z3 = radius * cos(theta2);

            double x4 = radius * sin(theta1) * cos(phi2);
            double y4 = radius * sin(theta1) * sin(phi2);
            double z4 = radius * cos(theta1);

            // Quad
            glBegin(GL_LINE_LOOP);
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);
            glEnd();
        }
    }
    //  End
    glEnd();
    //  Undo Transformations
    glPopMatrix();
}

//=================================RAYS=======================================
//----------------------------------------------------------------------------
static void cone(double radius, double height, int num,
    double xPos, double yPos, double zPos, Rotation rot) {
    //  Transformation
    glPushMatrix();
    //  Translation
    glTranslated(xPos, yPos, zPos);

    glRotated(rot.rotAngle, rot.rotX, rot.rotY, rot.rotZ); // Ray Rotation

    // Sun Rays
    glBegin(GL_QUADS);

    for (int i = 0; i < num; i++) {
        double angle1 = 2 * pi * i / num;
        double angle2 = 2 * pi * (i + 1) / num;
        // Z axis
        double z1 = cos(angle1) * radius; // Radius of Cylinder
        double x1 = sin(angle1) * radius; // X Axis
        // Y Axis - Height
        double yLow = 0;
        double yHigh = height;

        double z2 = cos(angle2) * radius; // Radius of Cylinder
        double x2 = sin(angle2) * radius; // X Axis

        // Color
        //glColor3f(0,1,0);
        
        // Quad
        glVertex3f(x1, yLow, z1);
        glVertex3f(x2, yLow, z2);
        glVertex3f(0, yHigh, 0);
        glVertex3f(0, yHigh, 0);

    }
    //  End
    glEnd();
    //  Undo transformations
    glPopMatrix();
}

//===============================DISPLAY======================================
//----------------------------------------------------------------------------
void display()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();

    glRotatef(angle,1,0,0);
    glRotatef(elev,0,1,0);
    
    // -- Tree Rotations --
    Rotation rot = {0, 1, 0, 0}; // Trunk Rotation
    Rotation rot1 = {30, 0, 0, 92}; // Branch 1 Rotation
    Rotation rot2 = {30, 0, 0, 154}; // Branch 2 Rotation
    Rotation rot3 = {30, 0, 0, -88}; // Branch 3 Rotation
    Rotation rot4 = {30, 0, 0, -108}; // Branch 4 Rotation
    
    // --- TREE 1 ---
    
    // Trunk
    glColor3f(0.35,0.18,0.00);
    cylinder(0.3, 2, 250, -0.25, -1.5, 1.2, rot);
   
    // Branch 1
    glColor3f(0.59,0.27,0.00);
    cylinder(0.1, 0.6, 250, -0.4, 0, 1.07, rot1);
    
    // Branch 2
    glColor3f(0.59,0.22,0.00);
    cylinder(0.085, 0.5, 250, -0.38, -0.75, 1.06, rot2);
    
    // Branch 3
    glColor3f(0.59,0.22,0.00);
    cylinder(0.085, 0.3, 250, -0.11, 0.1, 1.03, rot3);
    
    // Branch 4
    glColor3f(0.59,0.27,0.00);
    cylinder(0.1, 0.6, 250, -0.1, -0.65, 1.07, rot4);
    
    // --- TREE 2 ---
   
    // Trunk
    glColor3f(0.35,0.18,0.00);
    cylinder(0.08, 1, 250, 0.35, -1.5, 0, rot);
   
    // Branch 1
    glColor3f(0.59,0.27,0.00);
    cylinder(0.05, 0.2, 250, 0.32, -0.8, -0.02, rot1);
    
    // Branch 2
    glColor3f(0.59,0.22,0.00);
    cylinder(0.0425, 0.25, 250, 0.38, -1.08, -0.018, rot2);
    
    // Branch 3
    glColor3f(0.59,0.22,0.00);
    cylinder(0.0425, 0.25, 250, 0.32, -1.1, -0.03, rot3);
    
    // Branch 4
    glColor3f(0.59,0.27,0.00);
    cylinder(0.05, 0.2, 250, 0.38, -0.65, -0.02, rot4);
    
    // --- SUN ---
    glColor3f(0.9,0.88,0.18);
    sphere(0.15, 0.6, 0.8, 0.2);
    
    // --- RAYS ---
    Rotation rot5 = {45, 0, -180, 0}; // Ray 4 Rotation
    Rotation rot6 = {45, 0, -280, 0}; // Ray 5 Rotation
    
    glColor3f(0.92, 0.84, 0.42);
    cone(0.08, 0.18, 250, 0.52, 0.88, 0.2, rot1); // Ray 1
    cone(0.08, 0.18, 250, 0.76, 0.78, 0.2, rot2); // Ray 2
    cone(0.08, 0.22, 250, 0.6, 0.82, 0.2, rot3); // Ray 3
    cone(0.08, 0.22, 250, 0.48, 0.68, 0.2, rot5); // Ray 4
    cone(0.08, 0.18, 250, 0.74, 0.66, 0.2, rot6); // Ray 5
    
    //  Draw axes
    glColor3f(1,1,1);
    double len = 4;
    if (axes)
    {
       glBegin(GL_LINES);
       glVertex3d(0.0,0.0,0.0);
       glVertex3d(len,0.0,0.0);
       glVertex3d(0.0,0.0,0.0);
       glVertex3d(0.0,len,0.0);
       glVertex3d(0.0,0.0,0.0);
       glVertex3d(0.0,0.0,len);
       glEnd();
       //  Position axes
       glRasterPos3d(len,0.0,0.0); // Position X
       glRasterPos3d(0.0,len,0.0); // Position Y
       glRasterPos3d(0.0,0.0,len); // Position Z
 
    }
    
    glFlush();

    glutSwapBuffers();
}

//===============================WINDOW=======================================
//----------------------------------------------------------------------------
void reshape(int width,int height)
{
   const double dim=2.5;

   double w2h = (height>0) ? (double)width/height : 1;

   glViewport(0,0, width,height);

   glMatrixMode(GL_PROJECTION);

   glLoadIdentity();
   
    //  Orthogonal projection
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);

   glMatrixMode(GL_MODELVIEW);

   glLoadIdentity();
}

//=================================KEYS=======================================
//----------------------------------------------------------------------------
void key(unsigned char ch,int x,int y)
{
    //  ESC to quit
   if (ch == 27)
      exit(0);

    //  Reset
   else if (ch == '0')
      angle = elev = 0;

    //  Toggle Axes
    else if (ch == 'a')
       axes = 1-axes;

    //  Increase
   else if (ch == '[')
   {
       z += 0.5;
   }

    //  Decrease
   else if (ch == ']')
   {
       z -= 0.5;
   }
   //  Redisplay the scene
   glutPostRedisplay();
}
//----------------------------------------------------------------------------
/*
 *  Change Angle UP, DOWN, LEFT, & RIGHT
 */
void arrows(int key,int x,int y)
{

   if (key == GLUT_KEY_DOWN) // Down
      angle += 5;

   else if (key == GLUT_KEY_UP) // Up
      angle -= 5;

   else if (key == GLUT_KEY_LEFT) // Left
      elev += 5;

   else if (key == GLUT_KEY_RIGHT) // Right
      elev -= 5;
    
   //  Redisplay the scene
   glutPostRedisplay();
}

//=================================MAIN=======================================
//----------------------------------------------------------------------------
int main(int argc,char* argv[])
{

   glutInit(&argc,argv);

   glutCreateWindow("Scene In 3D");

   glutDisplayFunc(display);

   glutKeyboardFunc(key);

    glutSpecialFunc(arrows);

   glutMainLoop();

   return 0;
}
//----------------------------------------------------------------------------
