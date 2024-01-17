
//gcc -o interface interface.c -lglut -lGLU -lGL -lm -lpthread

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "head.h"

float objectX = 0.7;
float objectY = 0.7;
float speed = 0.01f;  // Adjust the speed as needed
float leftLimit = -0.4f;
float rightLimit = 0.5f;
float waitTime = 3500;  // Time to wait before moving down (in milliseconds)
int currentState = 0;  // 0: Move to left, 1: Wait, 2: Move down
float x_posTruck[3];
float y_posTruck[3];
float a_posTruck[3];
float b_posTruck[3];

float x_position=  0.85;
//float y_position=  0.9;
float x1_position= 0.7;

float x2_position=  -0.9;
float x3_position=  -0.5;
float x4_position=  -0.7;


float Bx_position=  0.85;
float Bx1_position= 0.7;

float red_chocolate= -0.65;
float white_milk = -0.5;
float yello_chips= -0.8;

float item1=  -0.77;
float item2=  -0.87;
float item3=  -0.67;
float item4=  -0.57;
float item5=  -0.47;

float Bx2_position=  -0.9;
float Bx3_position=  -0.5;
float Bx4_position=  -0.7;

//new
float x11_position = 0.9; // Initial x position of managerTeamA
float y1_position = 0.1;  // Initial y position of managerTeamA
//float speed = 0.01;       // Adjust the speed as needed
int moveState = 0;        // 0: Move left, 1: Move down

//void Run();
void Restart();
void display();
//void drawEMployee(float x, float y);
void drawManagerA();
void specialKeys(int key, int x, int y) ;
void timer(int value) ;

void circle(float x, float y);
void introscreen(float x, float y,char * ch);
void renderbitmap(float x, float y, void * font, char * string);
void rectangle(float x,float y,float a,float b);
void rectangle1(float x,float y,float a,float b);
void rectangle2(float x,float y,float a,float b);

float PI=3.1416;
void circle(float,float);
void rectangle(float x,float y,float a,float b);
void rectangle1(float x,float y,float a,float b);
void rectangle2(float x,float y,float a,float b);


void drawManager(float x, float y) {
    glColor3ub(139, 0, 139); // Purple color for the managerTeamA
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 0.1, y);
    glVertex2f(x + 0.1, y - 0.1);
    glVertex2f(x, y - 0.1);
    glEnd();
}
/*
void drawEMployee(float x, float y) {
    glColor3ub(255, 153, 153); // Purple color for the managerTeamA
        glBegin(GL_QUADS);
        glVertex2f(x_position, y_position);
        glVertex2f(x_position + 0.1, y_position);
        glVertex2f(x_position + 0.1, y_position-0.1);
        glVertex2f(x_position,y_position-0.1);
    glEnd();
}
*/

void drawManagerA() {
    glBegin(GL_QUADS);
	glBegin(GL_QUADS);
	glVertex2f(x1_position,0.7);
	glVertex2f(x1_position+0.1,0.7);	
	glVertex2f(x1_position+0.1,0.6);
	glVertex2f(x1_position,0.6);
	glEnd();
    glEnd();
}

void display2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply translation to move the object
    glTranslatef(objectX, objectY, 0.0f);

    // Draw the object
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
    drawManagerA();


    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            objectY += 0.1f;  // Move object up
            break;
        case GLUT_KEY_DOWN:
            objectY -= 0.1f;  // Move object down
            break;
        case GLUT_KEY_LEFT:
            objectX -= 0.1f;  // Move object left
            break;
        case GLUT_KEY_RIGHT:
            objectX += 0.1f;  // Move object right
            break;
    }

    // Ensure the object stays within the specified limits
    if (objectX < leftLimit) objectX = leftLimit;
    if (objectX > rightLimit) objectX = rightLimit;

    glutPostRedisplay();  // Request a redraw to reflect the changes
}


void timer(int value) {
    switch (currentState) {
        case 0:  // Move to left
            objectX -= speed;
            if (objectX < leftLimit) {
                objectX = leftLimit;
                currentState = 1;  // Change state to wait
                glutTimerFunc(waitTime, timer, 0);
            } else {
                glutTimerFunc(16, timer, 0);
            }
            break;
        case 1:  // Wait
            // Do nothing, just wait
            currentState = 2;  // Change state to move down
            glutTimerFunc(16, timer, 0);
            break;
        case 2:  // Move down
            objectY -= speed;
            if (objectY < -0.5) {
                objectY = -0.5;
                currentState = 0;  // Change state to move to left again
                glutTimerFunc(16, timer, 0);
            } else {
                glutTimerFunc(16, timer, 0);
            }
            break;
    }

    glutPostRedisplay();  // Request a redraw to reflect the changes
}

void introscreen(float x, float y,char * ch) {
  glColor3f(255, 255, 255);
  //glColor3ub(153,0,0);
  char buf[100] = {
    0
  };

  sprintf(buf,"%s",ch);
  renderbitmap(x,y, GLUT_BITMAP_8_BY_13, buf);

}
void renderbitmap(float x, float y, void * font, char * string) {
  char * c;
  glRasterPos2f(x, y);
  for (c = string;* c != '\0'; c++) {
    glutBitmapCharacter(font, * c);
  }     
}

void circle(float x, float y)
{

    int i;
    GLfloat radius;
    int triangleAmount =40;
    GLfloat twicePi = 2.0 * PI;
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(238, 139, 21);
        radius =0.05;

        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(
        x + (radius * cos(i *  twicePi / triangleAmount)),
        y + (radius * sin(i * twicePi / triangleAmount))
                  );
        }

    glEnd();

   
}

void rectangle(float x,float y,float a,float b){
	
  		
  //glColor3ub(100, 149, 237);  //blue
  glColor3ub(255,255,0); 	//yello 
  //glColor3ub(255, 0, 0);        //red
  glRectf(x-0.05,y,x+0.20,y+0.12);//x1,y1,x2,y2
  glEnd();
  circle(a, b);
  circle(a+0.15,b); 

	
}
void rectangle1(float x,float y,float a,float b){
 
  glColor3ub(255,255,0);
  glRectf(x+0.5,y,x+0.25,y+0.12);//x1,y1,x2,y2
  glEnd();
  circle(a, b);
  circle(a+0.15,b); 

}
void rectangle2(float x,float y,float a,float b){

  glColor3ub(100, 149, 237);
  glRectf(x+0.55,y,x+0.30,y+0.12);//x1,y1,x2,y2
  glEnd();
  circle(a+0.35,b);
  circle(a+0.50,b); 
}

int main2(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);  // Set the initial window size
    glutCreateWindow("OpenGL Move Object");

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Initialize the timer function
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}

int main(int argc, char *argv[]) {
	    
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(640, 640);
	//glutInitWindowPosition(1,0);
	glutCreateWindow("Supermarket Shelf Simulator");

	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Initialize the timer function
	glutTimerFunc(0, timer, 0);
        
	glutMainLoop();
	//while(1);
	 return 0;
}

void display()
{
	//glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.139f, 1.0f); // Using (0, 0, 139) values for dark blue
	//glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // Using (0, 0, 128) values for dark blue
	//glClearColor(65.0f / 255.0f, 105.0f / 255.0f, 225.0f / 255.0f, 1.0f);
	//glClearColor(0,0,0,0);
	
	//glClearColor(0.5f, 0.6f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
		
	glColor3ub(255,0,0);
	glBegin(GL_LINES);
	glVertex2f(-1.0,0.0);
	glVertex2f(7.0,0.0);
	glEnd();
	////************************************** NEW 
	

	
	////////*************************************
	
	introscreen(0.6, 0.85,"Team A");
	introscreen(0.6,-0.15,"Team B");

	
	introscreen(-0.9, 0.9,"STORAGE AREA");
		
	
	introscreen(-0.79, 0.80,"A");
	introscreen(-0.49, 0.80,"C");
	introscreen(-0.65, 0.80,"B");
	
        introscreen(0.08,0.2,"Carts ");
        introscreen(-0.9,0.25,"Customers");
	introscreen(-0.9,-0.46,"shelfs");
	//introscreen(0.2,-0.72,"T1: ");
	
	rectangle(x_posTruck[0],y_posTruck[0],a_posTruck[0],b_posTruck[0]);
	//rectangle1(x_posTruck[1],y_posTruck[1],a_posTruck[1],b_posTruck[1]);
	rectangle2(x_posTruck[2],y_posTruck[2],a_posTruck[2],b_posTruck[2]);

	
	/////////////////////////////////////////////////////////////
	// draw Storage Area 
        
        //left
	//glColor3ub(0,255,0);
	glColor3ub(153,0,0);
	glBegin(GL_LINES);
	glVertex2f(-0.85, 0.85);
	glVertex2f(-0.85, 0.45);
	glEnd();
	
	//right
	//glColor3ub(0,255,0);
	glColor3ub(153,0,0);
	glBegin(GL_LINES);
	glVertex2f(-0.40,0.85);
	glVertex2f(-0.40,0.45);
	glEnd();

        //top
	//glColor3ub(0,255,0);
	glColor3ub(153,0,0);
	glBegin(GL_LINES);
	glVertex2f(-0.40, 0.85);
	glVertex2f(-0.85, 0.85);
	glEnd();


	//batom 
	//glColor3ub(0,255,0);
	glColor3ub(153,0,0);
	glBegin(GL_LINES);
	glVertex2f(-0.40,0.45);
	glVertex2f(-0.85,0.45);
	glEnd();
	
	//line A
        //glColor3ub(0,255,0);
	glColor3ub(153,0,0);
	glBegin(GL_LINES);
	glVertex2f(-0.55,0.85);
	glVertex2f(-0.55,0.45);
	glEnd();
	//LINE B
	//glColor3ub(0,255,0);
	glColor3ub(153,0,0);
	glBegin(GL_LINES);
	glVertex2f(-0.70,0.85);
	glVertex2f(-0.70,0.45);
	glEnd();
	
	///////////////***********************
	//choclet read
	 glColor3ub(255, 0, 0);
	 glBegin(GL_QUADS);
	 glVertex2f(red_chocolate, 0.65);
	 glVertex2f(red_chocolate + 0.05, 0.65);
	 glVertex2f(red_chocolate + 0.05, 0.6);
	 glVertex2f(red_chocolate, 0.6);
         glEnd();
         
	 glColor3ub(255, 0, 0);
	 glBegin(GL_QUADS);
	 glVertex2f(red_chocolate, 0.75);
	 glVertex2f(red_chocolate + 0.05, 0.75);
	 glVertex2f(red_chocolate + 0.05, 0.7);
	 glVertex2f(red_chocolate, 0.7);
         glEnd();
         
         glColor3ub(255, 0, 0);
	 glBegin(GL_QUADS);
	 glVertex2f(red_chocolate, 0.55);
	 glVertex2f(red_chocolate + 0.05, 0.55);
	 glVertex2f(red_chocolate + 0.05, 0.5);
	 glVertex2f(red_chocolate, 0.5);
         glEnd();
         
         //item meilk 
         
         glColor3ub(204,255,204);
	 glBegin(GL_QUADS);
	 glVertex2f(white_milk, 0.65);
	 glVertex2f(white_milk + 0.05, 0.65);
	 glVertex2f(white_milk + 0.05, 0.6);
	 glVertex2f(white_milk, 0.6);
         glEnd();
         
	 glColor3ub(204,255,204);
	 glBegin(GL_QUADS);
	 glVertex2f(white_milk, 0.75);
	 glVertex2f(white_milk + 0.05, 0.75);
	 glVertex2f(white_milk + 0.05, 0.7);
	 glVertex2f(white_milk, 0.7);
         glEnd();
         
         glColor3ub(204,255,204);
	 glBegin(GL_QUADS);
	 glVertex2f(white_milk, 0.55);
	 glVertex2f(white_milk + 0.05, 0.55);
	 glVertex2f(white_milk + 0.05, 0.5);
	 glVertex2f(white_milk, 0.5);
         glEnd();
         
         //yello_chips
         
         glColor3ub(255,255,0);
	 glBegin(GL_QUADS);
	 glVertex2f(yello_chips, 0.65);
	 glVertex2f(yello_chips + 0.05, 0.65);
	 glVertex2f(yello_chips + 0.05, 0.6);
	 glVertex2f(yello_chips, 0.6);
         glEnd();
         
	 glColor3ub(255,255,0);
	 glBegin(GL_QUADS);
	 glVertex2f(yello_chips, 0.75);
	 glVertex2f(yello_chips + 0.05, 0.75);
	 glVertex2f(yello_chips + 0.05, 0.7);
	 glVertex2f(yello_chips, 0.7);
         glEnd();
         
         glColor3ub(255,255,0);
	 glBegin(GL_QUADS);
	 glVertex2f(yello_chips, 0.55);
	 glVertex2f(yello_chips + 0.05, 0.55);
	 glVertex2f(yello_chips + 0.05, 0.5);
	 glVertex2f(yello_chips, 0.5);
         glEnd();
         
         ///****************
         //items in shelfs
	glColor3ub(204,0,0);
	glBegin(GL_QUADS);
	glVertex2f(item1,0.-0.77);
	glVertex2f(item1+0.05,-0.77);	
	glVertex2f(item1+0.05,-0.72);
	glVertex2f(item1,-0.72);
	glEnd();
	
	glColor3ub(204,0,0);
	glBegin(GL_QUADS);
	glVertex2f(item2,-0.77);
	glVertex2f(item2+0.05,-0.77);	
	glVertex2f(item2+0.05,-0.72);
	glVertex2f(item2,-0.72);
	glEnd();
	
	glColor3ub(255,255,0);
	glBegin(GL_QUADS);
	glVertex2f(item3,-0.77);
	glVertex2f(item3+0.05,-0.77);	
	glVertex2f(item3+0.05,-0.72);
	glVertex2f(item3,-0.72);
	glEnd();
	
	glColor3ub(255,255,0);
	glBegin(GL_QUADS);
	glVertex2f(item4,-0.77);
	glVertex2f(item4+0.05,-0.77);	
	glVertex2f(item4+0.05,-0.72);
	glVertex2f(item4,-0.72);
	glEnd();
	
	glColor3ub(204,255,204);
	glBegin(GL_QUADS);
	glVertex2f(item5,-0.57);
	glVertex2f(item5+0.05,-0.57);	
	glVertex2f(item5+0.05,-0.52);
	glVertex2f(item5,-0.52);
	glEnd();
	
	glColor3ub(204,255,204);
	glBegin(GL_QUADS);
	glVertex2f(item5,-0.77);
	glVertex2f(item5+0.05,-0.77);	
	glVertex2f(item5+0.05,-0.72);
	glVertex2f(item5,-0.72);
	glEnd();
	
	
	
	///-----------------------------------------------------
	// team1
	glColor3ub(255, 153, 153);
        glBegin(GL_QUADS);
        glVertex2f(x_position, 0.9);
        glVertex2f(x_position + 0.1, 0.9);
        glVertex2f(x_position + 0.1, 0.8);
        glVertex2f(x_position, 0.8);
        glEnd();

	glColor3ub(255,153,153);
	glBegin(GL_QUADS);
	glVertex2f(x_position,0.7);
	glVertex2f(x_position+0.1,0.7);	
	glVertex2f(x_position+0.1,0.6);
	glVertex2f(x_position,0.6);
	glEnd();
	
	glColor3ub(255,153,153);
	glBegin(GL_QUADS);
	glVertex2f(x_position,0.5);
	glVertex2f(x_position+0.1,0.5);	
	glVertex2f(x_position+0.1,0.4);
	glVertex2f(x_position,0.4);
	glEnd();

	//manager tem1
	//glColor3ub(255,51,51);
	//glColor3ub(128, 0, 128);
/*	
	glColor3ub(139, 0, 139);
	//glColor3ub(255,51,255);
	glBegin(GL_QUADS);
	glVertex2f(x1_position,0.7);
	glVertex2f(x1_position+0.1,0.7);	
	glVertex2f(x1_position+0.1,0.6);
	glVertex2f(x1_position,0.6);
	glEnd();
 */
        
        //////
	glColor3ub(230,255,255);
	glBegin(GL_QUADS);
	glVertex2f(x2_position,0.2);
	glVertex2f(x2_position+0.1,0.2);	
	glVertex2f(x2_position+0.1,0.1);
	glVertex2f(x2_position,0.1);
	glEnd();
		
	glColor3ub(165, 42, 42);
	glBegin(GL_QUADS);
	glVertex2f(x3_position,0.2);
	glVertex2f(x3_position+0.1,0.2);	
	glVertex2f(x3_position+0.1,0.1);
	glVertex2f(x3_position,0.1);
	glEnd();
	

	glColor3ub(165, 42, 42);
	glBegin(GL_QUADS);
	glVertex2f(x4_position,0.2);
	glVertex2f(x4_position+0.1,0.2);	
	glVertex2f(x4_position+0.1,0.1);
	glVertex2f(x4_position,0.1);
	glEnd();
	

	//team2
	glColor3ub(0,255,0);
	glBegin(GL_QUADS);
	glVertex2f(Bx_position,-0.2);
	glVertex2f(Bx_position+0.1,-0.2);	
	glVertex2f(Bx_position+0.1,-0.1);
	glVertex2f(Bx_position,-0.1);
	glEnd();
	
	glColor3ub(0,255,0);
	glBegin(GL_QUADS);
	glVertex2f(Bx_position,-0.4);
	glVertex2f(Bx_position+0.1,-0.4);	
	glVertex2f(Bx_position+0.1,-0.3);
	glVertex2f(Bx_position,-0.3);
	glEnd();
	
	glColor3ub(0,255,0);
	glBegin(GL_QUADS);
	glVertex2f(Bx_position,-0.6);
	glVertex2f(Bx_position+0.1,-0.6);	
	glVertex2f(Bx_position+0.1,-0.5);
	glVertex2f(Bx_position,-0.5);
	glEnd();

	//team manager 2
	
        glColor3ub(0,39,0);
	//glColor3ub(0,153,0);
	glBegin(GL_QUADS);
	glVertex2f(Bx1_position,-0.4);
	glVertex2f(Bx1_position+0.1,-0.4);	
	glVertex2f(Bx1_position+0.1,-0.3);
	glVertex2f(Bx1_position,-0.3);
	glEnd();
	
	////////////////////////////////////////////////////////////
	glColor3ub(255,255,255);
	glBegin(GL_QUADS);
	glVertex2f(Bx2_position,-0.2);
	glVertex2f(Bx2_position+0.1,-0.2);	
	glVertex2f(Bx2_position+0.1,-0.1);
	glVertex2f(Bx2_position,-0.1);
	glEnd();



	glColor3ub(165,42,42);
	glBegin(GL_QUADS);
	glVertex2f(Bx3_position,-0.2);
	glVertex2f(Bx3_position+0.1,-0.2);	
	glVertex2f(Bx3_position+0.1,-0.1);
	glVertex2f(Bx3_position,-0.1);
	glEnd();


	glColor3ub(255,255,255);
	glBegin(GL_QUADS);
	glVertex2f(Bx4_position,-0.2);
	glVertex2f(Bx4_position+0.1,-0.2);	
	glVertex2f(Bx4_position+0.1,-0.1);
	glVertex2f(Bx4_position,-0.1);	
	glEnd();
	
	////////------------------------------------
	// line 1 Type C

	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.9,-0.5);
	glVertex2f(-0.4,-0.5);
	glEnd();


	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.9,-0.6);
	glVertex2f(-0.4,-0.6);
	glEnd();



	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.9,-0.5);
	glVertex2f(-0.9,-0.6);
	glEnd();


	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.4,-0.5);
	glVertex2f(-0.4,-0.6);
	glEnd();


	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.8,-0.5);
	glVertex2f(-0.8,-0.6);
	glEnd();


	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.7,-0.5);
	glVertex2f(-0.7,-0.6);
	glEnd();

	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.6,-0.5);
	glVertex2f(-0.6,-0.6);
	glEnd();

	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.5,-0.5);
	glVertex2f(-0.5,-0.6);
	glEnd();

	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.4,-0.5);
	glVertex2f(-0.4,-0.6);
	glEnd();




//line 2 Type C

	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.9,-0.7);
	glVertex2f(-0.4,-0.7);
	glEnd();


	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.9,-0.8);
	glVertex2f(-0.4,-0.8);
	glEnd();



	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.9,-0.7);
	glVertex2f(-0.9,-0.8);
	glEnd();


	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.4,-0.7);
	glVertex2f(-0.4,-0.8);
	glEnd();


	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.8,-0.7);
	glVertex2f(-0.8,-0.8);
	glEnd();


	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.7,-0.7);
	glVertex2f(-0.7,-0.8);
	glEnd();

	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.6,-0.7);
	glVertex2f(-0.6,-0.8);
	glEnd();

	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.5,-0.7);
	glVertex2f(-0.5,-0.8);
	glEnd();

	glColor3ub(255,255,0);
	glBegin(GL_LINES);
	glVertex2f(-0.4,-0.7);
	glVertex2f(-0.4,-0.8);
	glEnd();

// End Line TypeC
	// Draw managerTeamA
    // Draw the first object
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
    drawManager(objectX, objectY);


	glutSwapBuffers(); // Swap between double frame buffer
	glFlush(); // displayed on the screen
}
void drawObject(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, -0.1f);  // Bottom-left corner
    glVertex2f(0.1f, -0.1f);   // Bottom-right corner
    glVertex2f(0.1f, 0.1f);    // Top-right corner
    glVertex2f(-0.1f, 0.1f);   // Top-left corner
    glEnd();
    glPopMatrix();
}





