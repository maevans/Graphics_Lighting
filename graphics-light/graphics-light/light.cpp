/*
 * HW #5 - Lighting
 *
 *  Light in a 3D Scene
 *     - Jack 'O Lantern with Candle & Light
 *
 *  Mahalia Evans - FALL 2020
 *   Time - 72hrs
 */
//--------------------------
#include <_stdio.h>
#include <stdlib.h>
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
double rot;  // Rotation Angle
int angle=0; // Azimuth of view angle
int elev=0;  // Elevation of view angle
int flashlight=1; // Light It Up! | light_flash
int candle=1; // Light It Up! | light_candle
int modeL=0; // Lighting Mode
double pi=3.1415926535; // PI
//----Directional-Light-----
struct Lighting{
    int ambient   =  30;  // Lighting (%)
    int diffuse   =  60;
    int emission  =   0;
    int specular  =   0;
};
//---------ROTATION---------
struct Rotation{
    double rotAngle;
    double rotX;
    double rotY;
    double rotZ;
};

// Store Triangles Needed for Sphere
    // Update Current Ptr & Index
 double *store_sphere_triangle(double *current_ptr, double radius, double x1, double y1, double z1,
                                                 double x2, double y2, double z2,
                                                 double x3, double y3, double z3,
                                                 double r, double g, double b) {
     current_ptr[0] = x1;
     current_ptr[1] = y1;
     current_ptr[2] = z1;

     current_ptr[3] = x1 / radius;
     current_ptr[4] = y1 / radius;
     current_ptr[5] = z1 / radius;

     current_ptr[6] = x2;
     current_ptr[7] = y2;
     current_ptr[8] = z2;

     current_ptr[9] = x2 / radius;
     current_ptr[10] = y2 / radius;
     current_ptr[11] = z2 / radius;

     current_ptr[12] = x3;
     current_ptr[13] = y3;
     current_ptr[14] = z3;

     current_ptr[15] = x3 / radius;
     current_ptr[16] = y3 / radius;
     current_ptr[17] = z3 / radius;

     current_ptr[18] = r;
     current_ptr[19] = g;
     current_ptr[20] = b;

     //Call Strore Sphere - Find Triangles to remove

 };

    //Fetch Array of ptrs
void sphere_render(double *current_ptr, double x, double y, double z) {
    for(int i = 0; i < LEN.current_ptr; i++ ) {
          //glvertex3f -> Cnt ptr & Vertices
             // Triangles
          glBegin(GL_TRIANGLES);
             glVertex3f(current_ptr[0], current_ptr[1], current_ptr[2]); // Vertices
             glNormal3f(current_ptr[3], current_ptr[4], current_ptr[5]); // Normal
             
             glVertex3f(current_ptr[6], current_ptr[7], current_ptr[8]);
             glNormal3f(current_ptr[9], current_ptr[10], current_ptr[11]);
             
             glVertex3f(current_ptr[12], current_ptr[13], current_ptr[14]);
             glNormal3f(current_ptr[15], current_ptr[16], current_ptr[17]);
          glEnd();
          
      }
    //double current ptr
  };


 double *sphere_init(int *count, double radius) {
                    
     glPushMatrix();                                            //  Transformation

     int num = 100;                                             //  Size of Array
     
     int num_doubles = 2 * num * num;
     
     int size_of_vertex = sizeof(double) * (3 + 3 + 3);         //  Color + Vertex + Normal
     
     double *sphere_buffer = (double *) malloc(num_doubles * size_of_vertex);
     double *current_ptr = sphere_buffer;

     double theta_arc_length = pi / (num);
     double phi_arc_length = 2 * pi / (num);
     
     //  Begin
     glBegin(GL_TRIANGLES);
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

             // Triangles
             current_ptr = store_sphere_triangle(current_ptr, x1, y1, z1, x2, y2, z2, x3 y3, z3, r, g, b);
         }
     }
     //  End
     glEnd();
     //  Undo Transformations
     glPopMatrix();
}

//---------CYLINDER---------
//--------------------------
//_________STEMS x 2________
//        ________        //
//       /   /   /        //
//      /   /   /         //
//      |   |   |         //
//      |   |   |         //
//      |   |   |         //
//--------------------------
// COLOR = 128, 128, 0 // OLIVE
// * ADD Shine + Lines (Texture)

static void cylinder (double radius, double height, int num,
                      double xPos, double yPos, double zPos, Rotation rot){
    //  Transformation
    glPushMatrix();
    //  Translation Double
    glTranslated(xPos,yPos,zPos); //TranslateD = Double, F = float
    // Rotation Double
    glRotated(rot.rotAngle,rot.rotX,rot.rotY,rot.rotZ); // Stem Rotation
    
    // Pumpkin Stem - Top & Bottom
    
    //Determine pt of A
        double a1_z = radius;
        double a1_x = 0;
        double a1_y = 0;
        double a1_h = height;

        glBegin(GL_TRIANGLES);
        for (int i = 0; num - 2; i++){
        
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

            // Triangles - Bottom & Top
            glVertex3f(a1_x, a1_y, a1_z);
            glVertex3f(x1, yLow, z1);
            glVertex3f(x2, yLow, z2);
            glVertex3f(a1_x, a1_h, a1_z);
            glVertex3f(x1, yHigh, z1);
            glVertex3f(x2, yHigh, z2);
        }
    glEnd();
    
    //  Undo transformations
    glPopMatrix();
}


//====================================================================
//-------FLASHLIGHT---------
/* Follow Light With Mouse */
/* Change Color on Key pressed */  // Yellow/White, Purple, Green

//---------CANDLE-----------
/* Change Color on Key pressed */  // Yellow, Green, Purple
//====================================================================


//----------PRINT-----------
void Text(char const *string) {
    char const *s; //string

    for (s = string; *s != '\0'; s++) {
        
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s); // Text Font & String
    }
}
//---------DISPLAY----------
void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear Screen & Depth Buffers
    
   glEnable(GL_DEPTH_TEST);                             // Enable Depth (Z)
    
   glLoadIdentity();                                    // Undo Prev Tranformations

    // --- Draw Pumpkin ---
    
    // ---  Draw Stems  ---
    
    
    //--------------------------
    // --- LIGHTS ---
    switch (modeL){                                     // Switch Light Colors
        
        case 0:
            //Flashlight - White/Yellow
            
            //Candle - Yellow/Light Orange
            
            break;
            
        case 1:
            //Flashlight - Purple
            
            //Candle - Green
            
            break;
            
        case 2:
            //Flashlight - Green
            
            //Candle - Purple
            
            break;
    }
    
    // Display Key Info
    glColor3f(0,0,0);           // Black Text Color
    
    glWindowPos2i(0,580);       // Top Left Corner
    Text("Exit - Esc");
    
    glWindowPos2i(0,540);       // New Line - glRasterPos2i(5,5);
    Text("0 - Reset");
    
    glWindowPos2i(0,500);
    Text("<- - Left");
    
    glWindowPos2i(0,460);
    Text("-> - Right");
    
    glWindowPos2i(0,420);
    Text("1 - Light On/Off");
    
    glWindowPos2i(0,380);
    Text("2 - Change Color");
   
   glFlush();                              // Make scene visible || Render the scene

   glutSwapBuffers();                      // Make the rendered scene visible
}
//---------RESHAPE----------
void reshape(int width,int height)
{
   // double ratio = (height > 0) ? (double)width/height : 1; //  Ratio of the width to the height of the window
    
    // ORTHO vs. PERSP
   
   glViewport(0,0, width,height);                          // Set the viewport to the entire window
 
   glLoadIdentity();                                       // Undo previous transformations
}
//-----------KEYS-----------
void keys(unsigned char key, int x, int y)
{
  if (key == 27)                           // Esc key - Exit the window
      exit(0);
  
  else if (key == '0')                     // 0 - Reset
     angle = elev = 0;

  else if (key == GLUT_KEY_RIGHT)          // Right arrow - increase by 5 degree
      rot += 5;

  else if (key == GLUT_KEY_LEFT)           // Left arrow - decrease by 5 degree
      rot -= 5;
    
  else if (key == '1')                     // 1 - Turn Flashlight On/Off
     flashlight = 1 - flashlight;
  
  else if (key == '2')                     // 2 - Change Color 1/3
    modeL = (modeL + 1);                        /// mode = (mode+1)%10;
     //light = mode(1);
     //light = mode(2);
     //light = mode(3);
    
   glutPostRedisplay();                    // Redisplay normal plane
}
//-----------MAIN-----------
int main(int argc,char* argv[])
{
   glutInit(&argc,argv);                   // Initialize GLUT
   
   glutCreateWindow("Jack 'O Lantern");    // Create window
    
   glClearColor(85.0f/255.0f, 107.0f/255.0f, 47.0f/255.0f, 1.0f);       // Set Background Color - Dark Olive Green
     
   //glClearColor(0.0f, 100.0f/255.0f, 0.0f, 1.0f);                     // Set Background Color - Dark Green

   //glClearColor(184.0f/255.0f, 213.0f/255.0f, 238.0f/255.0f, 1.0f);   // Set Background Color - Light Blue
   
   glutDisplayFunc(display);               // Register function used to display scene

   glutKeyboardFunc(keys);                 // Set Window's keys callback
   
   glutMainLoop();                         // Enters the GLUT event processing loop
   
   return 0;                               // Return to OS
}




//_____________________________________________________________________________________________________


//-------ICOSAHEDRON--------
//--------------------------
//______PUMPKIN + FACE______
//                        //
//        /_\ /_\         //
//          /_\           //
//      /\/\/\/\/\        //
//      \/\/\/\/\/        //
//--------------------------
// COLOR = 210, 105, 30 // CHOCOLATE // OUTSIDE
// COLOR = 205, 133, 63 // PERU      // INSIDE

// * ADD Shine + Lines (Texture)

/*
 * Coordinates = x, y, z
 * s = Size
 * angle => rotate about an axis (x/y/z)
 */
//void drawIco (float x, float y, float z,   // VBO (Vertex Buffer Object)
//              float s, float angle) {
//
//    // (A) Vertex Index & Constant
//
//    const int N = 60;
//
//    const unsigned char index[] =
//       {
//           0, 14, 10,    0, 14, 1,    1, 15, 14,    1, 15, 2,    2, 16, 15,    2, 16, 3,    3, 17, 16,    3, 17, 4,    4, 11, 17,
//          10, 14, 12,   12, 14, 18,   14, 18, 15,   15, 18, 19,  15, 16, 19,   16, 19, 20,  16, 17, 20,   17, 21, 20,  17, 11, 21,  11, 13, 21,
//           12, 18, 5,    5, 18, 6,     6, 18, 19,    19, 6, 7,    7, 19, 20,    20, 7, 8,    8, 20, 21,    21, 8, 9,   9, 21, 13,
//
//       };
    
    // (A) Vertex Coordiantes
    
    // smooth icosahedron has 14 non-shared (0 to 13) and
    // 8 shared vertices (14 to 21) (total 22 vertices)
    //-----------------------------
    //   00  01  02  03  04      //
    //   /\  /\  /\  /\  /\      //
    //  /  \/  \/  \/  \/  \     //
    // 10--14--15--16--17--11    //
    //  \  /\  /\  /\  /\  /\    //
    //   \/  \/  \/  \/  \/  \   //
    //  12--18--19--20--21--13   //
    //    \  /\  /\  /\  /\  /   //
    //     \/  \/  \/  \/  \/    //
    //     05  06  07  08  09    //
    //-----------------------------
        // TOP/BOTTOM - 2 vertices
            //         *         //
            //       /   \       //
            //       \   /       //
            //         *         //
        //-------------------------
        // SIDE - 10 vertices, 36 deg apart
    
        /// Multidimensional Array
        /// Calculate Product & Cross Product
        /// Ex.  cp[0] = y1 * z2 - z1 * y2;
           /// cp[1] = z1 * x2 - x1 * z2;
           /// cp[2] = x1 * y2 - y1 * x2;
        /// Normal = cp / length
    
    
    // (A) Vertex Colors
    
    // (B) Define Vertices & Colors
        // * glVertexPointer();
        // * glColorPointer();
    
        // * glEnableClientState(GL_VERTEX_ARRAY);
        // * glEnableClientState(GL_COLOR_ARRAY);
    
    // (B) Draw Pumpkin
//    glPushMatrix();
//
//    glTranslatef(x, y, z);       // Translate
//
//    glScalef(s, s, s);           // Size
//
//    glRotatef(angle, 1, 0, 0);
//    //glRotatef(angle, 0, 0, 1); // Z axis
//
//    glDrawElements(GL_TRIANGLES, N, GL_UNSIGNED_BYTE, index);
//
//    glPopMatrix();
    
    // (C) Disable Vertex Array & Color Array
        // * glDisableClientState(GL_VERTEX_ARRAY);
        // * glDisableClientState(GL_COLOR_ARRAY);
//}
