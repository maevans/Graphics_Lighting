/*
 * HW #5 - Lighting
 * HW #6 - Textures
 *
 *  Light & Texture in a 3D Scene
 *     - Three Pumpkins 
 *
 *  Mahalia Evans - FALL 2020
 *   Time - 42hrs
 */
//--------------------------
#define GL_SILENCE_DEPRECATION
#include "CSCIx229.h"
//--------------------------
/* GOALS
 * + Create Vines
 * + Shaders to create Face
 * + Add Grass Textures & Light
 * + Fix Light Colors on Pumpkins
 * + Add Candle light inside Pumpkins
 * + Fix Up/Down Arrows
 */
//---------------------------------------------------------
#define WIDTH 400
#define HEIGHT 400
double rot;                // Rotation Angle
int angle=0;               // Azimuth of view angle
int elev=0;                // Elevation of view angle
int light_flash=1;         // Light It Up! | Flashlight
//int light_candle=1;        // Light It Up! | Candle
int modeL=0;               // Lighting Mode
double pi=3.1415926535;    // PI
double *sphere_ptr = 0;    // Sphere - Allocate Vertices
int count_vert = 0;        // Count Vertices
int modeV = 0;             // Mode of View
double ratio = WIDTH/(double)HEIGHT; // Aspect Ratio
double world = 5.0;        // Dimensions
double field = 45;            // Field Of View
float view_ortho = 1;
float lightX = 0;          // Light Movement (1)
float light_dir = 1;       // Current Light Direction (1)
float lightX2 = 0;         // Light Movement (1)
float light_dir2 = -1;     // Current Light Direction (2)
int light_mov = 1;         // Start Light Move
unsigned int textImg[3];   // Texture Images
//---------------------------------------------------------
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
//----------SPHERE----------
//--------------------------
//______PUMPKIN + FACE______
//                        //
//        /_\ /_\         //
//          /_\           //
//      /\/\/\/\/\        //
//      \/\/\/\/\/        //
//--------------------------
//______Store Triangles Needed for Sphere______
double *store_sphere_triangle(double *current_ptr, double radius, double x1, double y1, double z1,
                                                                  double x2, double y2, double z2,
                                                                  double x3, double y3, double z3,
                                                                  double u1, double v1, double u2, double v2,
                                                                  double u3, double v3) {
     // Update Current Ptr & Index
     current_ptr[0] = x1; //Vert
     current_ptr[1] = y1;
     current_ptr[2] = z1;

     current_ptr[3] = x1 / radius; //Norm
     current_ptr[4] = y1 / radius;
     current_ptr[5] = z1 / radius;
        
     current_ptr[6] = u1; //TextCoords
     current_ptr[7] = v1;

     current_ptr[8] = x2;
     current_ptr[9] = y2;
     current_ptr[10] = z2;

     current_ptr[11] = x2 / radius;
     current_ptr[12] = y2 / radius;
     current_ptr[13] = z2 / radius;
    
     current_ptr[14] = u2;
     current_ptr[15] = v2;

     current_ptr[16] = x3;
     current_ptr[17] = y3;
     current_ptr[18] = z3;

     current_ptr[19] = x3 / radius;
     current_ptr[20] = y3 / radius;
     current_ptr[21] = z3 / radius;

     current_ptr[22] = u3;
     current_ptr[23] = v3;
    
    return current_ptr + 24;

     //Call Store Sphere - Find Triangles to REMOVE
     //return 0;

 };
//______Fetch Array of ptrs______
void sphere_render(double *current_ptr, int num_vertices) {
    
    // Enable Pumpkin Texture
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,textImg[0]);
    
    // Triangles
    glBegin(GL_TRIANGLES);
    
    for(int i = 0; i < num_vertices; i++ ) {
        
        glNormal3f(current_ptr[3], current_ptr[4], current_ptr[5]); // Normal
        glVertex3f(current_ptr[0], current_ptr[1], current_ptr[2]); // Vertices
        glTexCoord2f(current_ptr[6], current_ptr[7]);  // Texture Coordinates
        current_ptr = current_ptr + 8;  // Next Vertex -> current ptr
      }
    glEnd();
};
//______Initialize Sphere______
double *sphere_init(int *count, double radius) {

     int num = 10;  // Size of Array
     
     int num_vertices = 2 * 3 * num * num;  // Number of Vertices
     
     int size_of_vertex = sizeof(double) * (3 + 3 + 3);  // Color + Vertex + Normal
     
     double *sphere_buffer = (double *) malloc(num_vertices * size_of_vertex);
     double *current_ptr = sphere_buffer;

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
             
             double u1 = theta1 / pi;
             double v1 = phi1 / (2 * pi);

             double u2 = theta2 / pi;
             double v2 = phi1 / (2 * pi);

             double u3 = theta2 / pi;
             double v3 = phi2 / (2 * pi);
             
             // Triangles - Update Current Ptr
           current_ptr = store_sphere_triangle(current_ptr, radius, x1, y1, z1, x2, y2, z2, x3, y3, z3,
                                                 u1, v1, u2, v2, u3, v3);
             
             double x4 = radius * sin(theta1) * cos(phi2);
             double y4 = radius * sin(theta1) * sin(phi2);
             double z4 = radius * cos(theta1);

             // Triangles - Update Current Ptr
             current_ptr = store_sphere_triangle(current_ptr, radius, x1, y1, z1, x3, y3, z3, x4, y4, z4,
                                                   u1, v1, u2, v2, u3, v3);
             
         }
     }
    
    *count = num_vertices;  // Update Count of Vertices
    
    return sphere_buffer;   // Returns ptr to Sphere_Buffer
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
    
    // Enable Stem Texture
//    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,textImg[1]);
    
    // Pumpkin Stem - Sides
    glBegin(GL_TRIANGLES);
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
        
        // Coordinates
        double s1 = angle1 / (2 * pi);
        double s2 = angle2 / (2 * pi);
        
        // Triangles
        glNormal3f(x1, 0, z1);
        glVertex3f(x1,yLow,z1);  // 0, 1, 2
        glTexCoord2f(s1, 0);
        
        glNormal3f(x2, 0, z2);
        glVertex3f(x2,yLow,z2);
        glTexCoord2f(s2, 0);
        
        glNormal3f(x2, 0, z2);
        glVertex3f(x2,yHigh,z2);
        glTexCoord2f(s2, 1);
        
        glNormal3f(x1, 0, z1);  // 0, 2 , 3
        glVertex3f(x1,yLow,z1);
        glTexCoord2f(s1, 0);
        
        glNormal3f(x2, 0, z2);
        glVertex3f(x2,yHigh,z2);
        glTexCoord2f(s2, 1);
        
        glNormal3f(x1, 0, z1);
        glVertex3f(x1,yHigh,z1);
        glTexCoord2f(s1, 0);
        
        // Pumpkin Stem - Bottom & Top
        glNormal3f(0, -1, 0);
        glVertex3f(0, yLow, 0);
        glTexCoord2f(0, 0);
        
        glVertex3f(x1, yLow, z1);
        glTexCoord2f(s1, 0);
        
        glVertex3f(x2, yLow, z2);
        glTexCoord2f(s2, 1);
        
        glNormal3f(0, 1, 0);
        glVertex3f(0, yHigh, 0);
        glTexCoord2f(0, 0);
        
        glVertex3f(x1, yHigh, z1);
        glTexCoord2f(s1, 1);
        
        glVertex3f(x2, yHigh, z2);
        glTexCoord2f(s2, 1);
        
    }
    //  End
    glEnd();
    
    //  Undo transformations
    glPopMatrix();
}
//----------CUBE------------
//--------------------------
//_________FLOOR____________
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double angle)
{
//       glEnable(GL_TEXTURE_2D);
       glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
       glBindTexture(GL_TEXTURE_2D,textImg[2]);

       glPushMatrix();
//       glLoadIdentity();
       //  Offset, scale and rotate
       glTranslated(0,-1,0);
       glRotated(angle,0,1,0);
       glScaled(dx,dy,dz);
    
       //  Cube = 6 * 2 = 12 Triangles
        glBegin(GL_TRIANGLES);
             //Normal
            glNormal3f( 0, 0, 1);
            glVertex3f(-1, -1, -1); // Tri 1
//            glTexCoord2f(0,0);
    
            glVertex3f(-1, -1, 1);
//            glTexCoord2f(0,0);
    
            glVertex3f(-1, 1, -1);
//            glTexCoord2f(0,0);
    
    
            glNormal3f( 0, 0, 1);
            glVertex3f(1, 1, -1); // Tri 2
//            glTexCoord2f(0,0);
    
            glVertex3f(-1, -1, -1);
//            glTexCoord2f(0,0);
    
            glVertex3f(-1, 1, -1);
//            glTexCoord2f(0,0);
    
    
            glNormal3f( 0, 0,-1);
            glVertex3f(1, -1, 1); // Tri 3
//            glTexCoord2f(0,1);
    
            glVertex3f(-1, -1, -1);
//            glTexCoord2f(0,1);
    
            glVertex3f(1, -1, -1);
//            glTexCoord2f(0,1);
    
    
            glNormal3f( 0, 0,-1);
            glVertex3f(1, 1, -1); // Tri 4
//            glTexCoord2f(0,1);
    
            glVertex3f(1, -1, -1);
//            glTexCoord2f(0,1);
    
            glVertex3f(-1, -1, -1);
//            glTexCoord2f(0,1);
    
    
            glNormal3f(+1, 0, 0);
            glVertex3f(-1, -1, -1); // Tri 5
//            glTexCoord2f(1,1);
    
            glVertex3f(-1, 1, 1);
//            glTexCoord2f(1,1);
    
            glVertex3f(-1, 1, -1);
//            glTexCoord2f(1,1);
            
            glNormal3f(+1, 0, 0);
            glVertex3f(1, -1, 1); // Tri 6
//            glTexCoord2f(1,1);
    
            glVertex3f(-1, -1, 1);
//            glTexCoord2f(1,1);
    
            glVertex3f(-1, -1, -1);
//            glTexCoord2f(1,1);
    
    
            glNormal3f(-1, 0, 0);
            glVertex3f(-1, 1, 1); // Tri 7
//            glTexCoord2f(1,0);
    
            glVertex3f(-1, -1, 1);
//            glTexCoord2f(1,0);
    
            glVertex3f(1, -1, 1);
//            glTexCoord2f(1,0);
    
    
            glNormal3f(-1, 0, 0);
            glVertex3f(1, 1, 1); // Tri 8
//            glTexCoord2f(1,0);
    
            glVertex3f(1, -1, -1);
//            glTexCoord2f(1,0);
    
            glVertex3f(1, 1, -1);
//            glTexCoord2f(1,0);
    
    
            glNormal3f( 0,+1, 0);
            glVertex3f(1, -1, -1); // Tri 9
//            glTexCoord2f(1,2);
    
            glVertex3f(1, 1, 1);
//            glTexCoord2f(1,2);
    
            glVertex3f(1, -1, 1);
//            glTexCoord2f(1,2);
    
    
            glNormal3f( 0,+1, 0);
            glVertex3f(1, 1, 1); // Tri 10
//            glTexCoord2f(1,2);
    
            glVertex3f(1, 1, -1);
//            glTexCoord2f(1,2);
    
            glVertex3f(-1, 1, -1);
//            glTexCoord2f(1,2);
                
    
            glNormal3f( 0,-1, 0);
            glVertex3f(1, 1, 1); // Tri 11
//            glTexCoord2f(2,2);
    
            glVertex3f(-1, 1, -1);
//            glTexCoord2f(2,2);
    
            glVertex3f(-1, 1, 1);
//            glTexCoord2f(2,2);
    
    
            glNormal3f( 0,-1, 0);
            glVertex3f(1, 1, 1); // Tri 12
//            glTexCoord2f(2,2);
    
            glVertex3f(-1, 1, 1);
//            glTexCoord2f(2,2);
    
            glVertex3f(1, -1, 1);
//            glTexCoord2f(2,2);
    
       glEnd();
   //  Undo transofrmations
    glPopMatrix();
}
//--------ORTHO/PERS--------
void View() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (modeV){
        //printf("Field: %f \n",field);
       gluPerspective(field, ratio, world/4, 4*world);  //  Perspective - Angle, Aspect Ratio, Min, Max
    }
    else
       glOrtho(-ratio*world*view_ortho, +ratio*world*view_ortho, -ratio*world*view_ortho, +ratio*world*view_ortho, -10, +10);  //  Orthogonal projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//----------PRINT-----------
void Text(char const *string) {
    char const *s; //string
    for (s = string; *s != '\0'; s++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s); // Text Font & String
    }
}
//---------RESHAPE----------
void reshape(int width,int height)
{
    ratio = (double)width / (double)height;   // Aspect Ratio
    glViewport(0, 0, width, height);          // Set the viewport to the entire window
    View();                                   // ORTHO vs. PERS
}
//---------DISPLAY----------
void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear Screen & Depth Buffers
    
   glEnable(GL_DEPTH_TEST);                             // Enable Depth (Z)
    
   glLoadIdentity();                                    // Undo Prev Tranformations
    
    View();
    
    // --- CAMERA ---
    //--------------------------
    if (modeV)                                          //  Perspective - Eye View
     {
       gluLookAt(0,0,8, 0,0,0, 0,1,0);
       glTranslated(0, 0, 0);
       glRotatef(elev, 1, 0, 0);
       glRotatef(angle, 0, -1, 0);
     }
    else                                                //  Orthogonal - World View
     {
       glTranslated(1, 0, -4);
       gluLookAt(0,1,0, 1,0,-4, 0,4,0);
       glRotatef(elev, 1, 0, 0);
       glRotatef(angle, 0, 1, 0);
     }
    //--------------------------
    // --- LIGHTS ---
    if (light_flash){
        //--------------------------
        // --- LIGHT 1 ---
        GLfloat light_pos[4] = { lightX, 3, 0, 1 };          // Position - x, y, z, Directional(0) / Point(1) Light
        if (light_mov == 1){
            if (lightX > 5 && light_dir == 1){                   // Light forward
                lightX = lightX - 0.1;
                light_dir = -1;
                }
            else if (lightX < -5 && light_dir == -1) {           // Light back
                lightX = lightX + 0.1;
                light_dir = +1;
                }
            else {
                lightX = lightX + 0.1 * light_dir;
            }
        }
        //--------------------------
        // --- LIGHT 1 COLOR ---
        switch (modeL) {
            case 0: {
                GLfloat red[4] = {1, 0, 0, 1};
                glLightfv(GL_LIGHT1, GL_DIFFUSE, red);                               // Red Light
                break;
            }
                
            case 1: {
                GLfloat purple[4] = {30.0f/255.0f, 144.0f/255.0f, 255.0f, 1};          // Color - 30, 144, 255 - Purple
                glLightfv(GL_LIGHT1, GL_DIFFUSE, purple);                              // Purple Light
                break;
            }
                
            case 2: {
                GLfloat dark_purple[4] = {70.0f/255.0f, 130.0f/255.0f, 180.0f/255.0f, 1};   // Color - 70, 130, 180 - Dark Purple
                glLightfv(GL_LIGHT1, GL_DIFFUSE, dark_purple);                               // Purple Light
                break;
            }
        }
        //--------------------------
        // --- LIGHT 2 ---
        GLfloat light_pos2[4] = { lightX2, 3, 0, 1 };        // Position - x, y, z, Directional(0) / Point(1) Light
        if (light_mov == 1){
            if (lightX2 > 5 && light_dir2 == 1){                   // Light forward
                lightX2 = lightX2 - 0.1;
                light_dir2 = -1;
            }
            else if (lightX2 < -5 && light_dir2 == -1) {           // Light back
                lightX2 = lightX2 + 0.1;
                light_dir2 = +1;
                }
            else {
                lightX2 = lightX2 + 0.1 * light_dir2;
                }
            }
        //--------------------------
        // --- LIGHT 2 COLOR ---
        switch (modeL) {
            case 1: {
                GLfloat orange[4] = {244.0f/255.0f, 164.0f/255.0f, 96.0f/255.0f, 1};    // Color - 205, 133, 63 - Dark Orange
                glLightfv(GL_LIGHT1, GL_DIFFUSE, orange);                               // Orange Light - 244, 164, 96
                break;
            }

            case 2: {
                GLfloat blue[4] = {0.0f,0.0f,1.0f, 1};
                glLightfv(GL_LIGHT1, GL_DIFFUSE, blue);                              // Blue Light
                break;
            }

            case 0: {
                GLfloat green[4] = {0, 1, 0, 1};
                glLightfv(GL_LIGHT1, GL_DIFFUSE, green);                               // Green Light
                break;
            }
        }
        glEnable(GL_NORMALIZE);
        glEnable(GL_LIGHTING);
        
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);       // Light Position (1)
        glEnable(GL_LIGHT0);                                // Constant - Enables 1st Light
        
        glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);      // Light Position (2)
        glEnable(GL_LIGHT1);                                // Constant - Enables 2nd Light
        
        glEnable(GL_COLOR_MATERIAL);                        // Color Material
    }
    else {
        glDisable(GL_LIGHTING);
        }
    
    glColor3f(1,0,0);
    cube(0,-1,0, 4,0.3,-4, 45);
    //--------------------------
    // --- Draw Pumpkin 1 ---
    glColor3f(210.0f/255.0f, 105.0f/255.0f, 30.0f/255.0f);   // COLOR = 210, 105, 30 // CHOCOLATE
    sphere_render(sphere_ptr, count_vert);                   // Draw Sphere
    
    // ---  Draw Stem 1  ---
    Rotation rot = {30, 0, 0, 1};
    glColor3f(128.0f/255.0f, 128.0f/255.0f, 0.0f);          // COLOR = 128, 128, 0 // OLIVE
    cylinder(0.2, 1, 150, 0.2, 0.5, 0, rot);                // Draw Cylinder
    
    //--------------------------
    // --- Draw Pumpkin 2 ---
    glTranslated(1, -0.3, 2);
    glColor3f(210.0f/255.0f, 105.0f/255.0f, 30.0f/255.0f);   // COLOR = 210, 105, 30 // CHOCOLATE
    sphere_render(sphere_ptr, count_vert);                   // Draw Sphere
    
    // ---  Draw Stem 2  ---
    Rotation rot2 = {45, 0, 0, 1.5};
    glColor3f(128.0f/255.0f, 128.0f/255.0f, 0.0f);          // COLOR = 128, 128, 0 // OLIVE
    cylinder(0.2, 1, 150, 0.2, 0.5, 0, rot2);                // Draw Cylinder
    glTranslated(0.8, -0.5, 2);
    
    //--------------------------
    // --- Draw Pumpkin 3 ---
    glTranslated(-4, 0, -5);
    glColor3f(210.0f/255.0f, 105.0f/255.0f, 30.0f/255.0f);   // COLOR = 210, 105, 30 // CHOCOLATE
    sphere_render(sphere_ptr, count_vert/2);                   // Draw Sphere

    // ---  Draw Stem 3  ---
    Rotation rot3 = {-35, -2, 0, 0.5};
    glColor3f(128.0f/255.0f, 128.0f/255.0f, 0.0f);          // COLOR = 128, 128, 0 // OLIVE
    cylinder(0.2, 1, 150, 0.2, 0.5, 0, rot3);                // Draw Cylinder

    //--------------------------
    // --- Display Key Info ---
    glColor3f(0,0,1);
    
    glWindowPos2i(10,290);       // Bottom Left Corner
    Text("Esc - Exit");
    
    glWindowPos2i(10,250);
    Text("0 - Reset");
    
    glWindowPos2i(10,210);
    Text("v - View");
    
    glWindowPos2i(10,170);
    Text("1 - Light On/Off");
    
    glWindowPos2i(10,130);
    Text("2 - Change Color");
    
    glWindowPos2i(10,90);
    Text("3 - Stop/Start Light");
    
    glWindowPos2i(10,50);
    Text("4/5 - Zoom In/Out");
    
    glWindowPos2i(10,10);
    Text("Arrows - Up/Down, Left/Right");
   
   glFlush();                              // Make scene visible || Render the scene

   glutSwapBuffers();                      // Make the rendered scene visible
    
   glutPostRedisplay();                    // Redisplay Scene
}
//-----------KEYS-----------
void keys(unsigned char key, int x, int y)
{
  if (key == 27)                          // Esc key - Exit the window
      exit(0);
  
  else if (key == '0')                    // 0 - Reset
     angle = elev = 0;
    
  else if (key == 'v')                    // Switch View - Ortho vs. Pers
     modeV = 1 - modeV;
    
  else if (key == '5'){                    // Zoom Out
    field -= 5;
    view_ortho += 0.1;
  }
  else if (key == '4'){                    // Zoom In
    field += 5;
    view_ortho -= 0.1;
  }
    
  else if (key == '1')                    // 1 - Turn Flashlight On/Off
     light_flash = 1 - light_flash;
  
  else if (key == '2')                    // 2 - Change Color 1/3
    modeL = (modeL + 1)%3;
    
  else if (key == '3')                    // 3 - Stop/Start Light
     light_mov = -1 * light_mov;
    
   View();                                // Reset View
    
   glutPostRedisplay();                   // Redisplay normal plane
}
void arrows(int key, int x, int y) {
    
    if (key == GLUT_KEY_RIGHT)            // Right arrow - increase by 2 degree
        angle += 2;

    else if (key == GLUT_KEY_LEFT)        // Left arrow - decrease by 2 degree
        angle -= 2;
    
    else if (key == GLUT_KEY_UP)          // Up arrow - increase by 5 degree
        elev += 5;
    
    else if (key == GLUT_KEY_DOWN)        // Down arrow - decrease by 5 degree
        elev -= 5;
    
    View();                               // Reset View
    
    glutPostRedisplay();
}
//-----------MAIN-----------
int main(int argc,char* argv[])
{
   glutInit(&argc,argv);                                           // Initialize GLUT
    
   glutInitWindowSize(WIDTH,HEIGHT);                               // Initial Window Size
   
   glutCreateWindow("Jack 'O Lantern");                            // Create window
    
   glClearColor(51.0f/255.0f, 51.0f/255.0f, 0.0f, 1.0f);           // Set Background Color - Dark Olive Green
   
   sphere_ptr = sphere_init(&count_vert, 1);                       // Sphere Ptr
   
   glutDisplayFunc(display);                                       // Display Scene Func
    
   glutReshapeFunc(reshape);                                       // Reshape Window

   glutKeyboardFunc(keys);                                         // Set Window's keys callback
    
   glutSpecialFunc(arrows);                                        // Special keys
    
   textImg[0] = LoadTexBMP("pumpkin.bmp");                         // Load Texture Files
   textImg[1] = LoadTexBMP("stalk-green.bmp");
   textImg[2] = LoadTexBMP("grass.bmp");
        
   glutMainLoop();                                                 // Enters the GLUT event processing loop
   
   return 0;                                                       // Return to OS
}
//______________________________________________________________________________________________________________
