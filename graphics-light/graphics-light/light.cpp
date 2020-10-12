/*
 * HW #5 - Lighting
 *
 *  Light in a 3D Scene
 *     - Jack 'O Lantern with Candle & Light
 *
 *  Mahalia Evans
 *
 */
//--------------------------
#include <_stdio.h>
#include <stdlib.h>
// #include <OpenGL/gl.h>
// #include <GLUT/glut.h>
#include <math.h>
#include <malloc/malloc.h>
//--------------------------
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//--------------------------
double rot; // Rotation Angle
//---------DISPLAY----------
void display()
{
   glClear(GL_COLOR_BUFFER_BIT);           // Clear screen

   glBegin(GL_POLYGON);      // Draw triangle
//    glVertex2f( 0.0, 0.5);
//    glVertex2f( 0.5,-0.5);
//    glVertex2f(-0.5,-0.5);
   glEnd();
   
   glFlush();                              // Make scene visible
}
//-----------KEYS-----------
void keys(unsigned char key, int x, int y)
{
  if (key == 'Esc')                        // Esc key - Exit the window
      exit(0);

  if (key == GLUT_KEY_RIGHT)               // Right arrow - increase rotation by 5 degree
      rot += 5;

  else if (key == GLUT_KEY_LEFT)           // Left arrow - decrease rotation by 5 degree
      rot -= 5;

   glutPostRedisplay();                    // Request display update
}
//-----------MAIN-----------
int main(int argc,char* argv[])
{
   glutInit(&argc,argv);                   // Initialize GLUT
   
   glutCreateWindow("Jack 'O Lantern");    // Create window

   glClearColor(184.0f/255.0f, 213.0f/255.0f, 238.0f/255.0f, 1.0f);  // Set Background Color
   
   glutDisplayFunc(display);               // Register function used to display scene

   glutKeyboardFunc(keys);                   // Set Window's keys callback
   
   glutMainLoop();                         // Pass control to GLUT for events
   
   return 0;                               // Return to OS
}











//______________________________________________________________________________________________________

// double pi=3.14159; // Pi

// double *store_sphere_triangle(double *current_ptr, double radius, double x1, double y1, double z1,
//                                                 double x2, double y2, double z2,
//                                                 double x3, double y3, double z3,
//                                                 double r, double g, double b) {
//     current_ptr[0] = x1;
//     current_ptr[1] = y1;
//     current_ptr[2] = z1;
//     current_ptr[3] = x1 / radius;
//     current_ptr[4] = y1 / radius;
//     current_ptr[5] = z1 / radius;
//     current_ptr[9] = x2;
//     current_ptr[4] = y2;
//     current_ptr[5] = z2;
//     current_ptr[3] = x1 / radius;
//     current_ptr[4] = y1 / radius;
//     current_ptr[5] = z1 / radius;
//     current_ptr[6] = x1;
//     current_ptr[1] = y1;
//     current_ptr[2] = z1;
//     current_ptr[3] = x1 / radius;
//     current_ptr[4] = y1 / radius;
//     current_ptr[5] = z1 / radius;
//     current_ptr[6] = r;
//     current_ptr[7] = g;
//     current_ptr[8] = b;

//  }

//  void sphere_render;

// //==================================SUN=======================================
// //----------------------------------------------------------------------------
// double *sphere_init(int *count, double radius) {

//     int num = 100;
//     //Size of Array
//     int num_doubles = 2 * num * num;
//     int size_of_vertex = sizeof(double) * (3 + 3 + 3); //Color + Vertex + Normal
//     double *sphere_buffer = (double *) malloc(num_doubles * size_of_vertex);
//     double *current_ptr = sphere_buffer;

//     double theta_arc_length = pi / (num);
//     double phi_arc_length = 2 * pi / (num);
//     for (int j = 0; j < num; ++j) {
//         for (int i = 0; i < num; ++i) {
//             double theta1 = theta_arc_length * i;
//             double theta2 = theta_arc_length * (i + 1);

//             double phi1 = phi_arc_length * j;
//             double phi2 = phi_arc_length * (j + 1);

//             double x1 = radius * sin(theta1) * cos(phi1);
//             double y1 = radius * sin(theta1) * sin(phi1);
//             double z1 = radius * cos(theta1);

//             double x2 = radius * sin(theta2) * cos(phi1);
//             double y2 = radius * sin(theta2) * sin(phi1);
//             double z2 = radius * cos(theta2);

//             double x3 = radius * sin(theta2) * cos(phi2);
//             double y3 = radius * sin(theta2) * sin(phi2);
//             double z3 = radius * cos(theta2);

//             double x4 = radius * sin(theta1) * cos(phi2);
//             double y4 = radius * sin(theta1) * sin(phi2);
//             double z4 = radius * cos(theta1);

//             // Quad
//             // glBegin(GL_LINE_LOOP);
//             // glVertex3f(x1, y1, z1);
//             // glVertex3f(x2, y2, z2);
//             // glVertex3f(x3, y3, z3);
//             // glVertex3f(x4, y4, z4);
//             // glEnd();

//             // Triangles
//             current_ptr = store_sphere_triangle(current_ptr, x1, y1, z1, x2, y2, z2, x3 y3, z3, r, g, b);

//             //Store Sphere Triangle =(x1, y1, z1 .. z3 .. z4)
//         }
//     }
//     //  End
//     glEnd();
//     //  Undo Transformations
//     glPopMatrix();
//}
