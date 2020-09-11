#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>


GLdouble ya = 50,xa = 10;
int yFlag = 1, xFlag = 1,Aniflag=0,p=0;

GLdouble r = 0.85, s = 0.00681817;
GLdouble pi = acos(-1);

GLfloat hold;



void Animate(){
    if(Aniflag==1){
        if(ya>-50 && yFlag==1) ya-=0.2;
        if(ya<=-50 && yFlag==1) yFlag=0;
        if(ya<50 && yFlag==0) ya+=0.2;
        if(ya>=50 && yFlag==0) yFlag=1;
        Sleep(0.5);
        if(xa>-10 && xFlag==1) xa-=0.2;
        if(xa<=-10 && xFlag==1) xFlag=0;
        Sleep(0.5);
        if(xa<10 && xFlag==0) xa+=0.2;
        if(xa>=10 && xFlag==0) xFlag=1;
        Sleep(0.5);

    }
     glutPostRedisplay();
}

void Draw(){
    GLfloat x[4],y1[4],y2[4];
    GLdouble xt[200],y1t[200],y2t[200],t;
    glClear(GL_COLOR_BUFFER_BIT);
    int i;
    x[0] = 100; x[1] = 200; x[2] = 200; x[3] = 300-xa;
    y1[0] = 450; y1[1] = 450+ya; y1[2] = 450-ya; y1[3] = 450;
    y2[0] = 350; y2[1] = 350+ya; y2[2] = 350-ya; y2[3] = 350;

    for(i=0,t=0;t<=1;i++,t+=0.01){
        xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*t*t*(1-t)*x[2] + t*t*t*x[3];
        y1t[i] = pow(1-t,3)*y1[0] + 3*t*pow(1-t,2)*y1[1] + 3*t*t*(1-t)*y1[2] + t*t*t*y1[3];
        y2t[i] = pow(1-t,3)*y2[0] + 3*t*pow(1-t,2)*y2[1] + 3*t*t*(1-t)*y2[2] + t*t*t*y2[3];

    }
    glColor3f(0,1,0);
    glPointSize(3);
    glBegin(GL_QUAD_STRIP);
        for(i=0;i<200;i++) {
                glVertex2d(xt[i],y1t[i]);
                glVertex2d(xt[i],y2t[i]);
        }
	glEnd();
	glColor3f(1,1,1);
    glRecti(90,460,100,50);
//    glEnd();
//
//    glColor3f(0.96, 0.16, 0.26);
//
//	glBegin(GL_POLYGON);
//        for (int i=0; i<100; i++) {
//            double theta = (2 * pi * i) / 100;
//            glVertex3f(r * cos(theta), r * sin(theta), 1.0);
//        }
//	glEnd();


    glFlush();
}

void Menu(int n){
    if(n==1) Aniflag = 1;
    else if(n==2) Aniflag = 0;
    else exit(0);
}

void MyInit(){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
    glutCreateMenu(Menu);
    glutAddMenuEntry("Start",1);
    glutAddMenuEntry("Stop",2);
    glutAddMenuEntry("Exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argC, char *argV[]){
    glutInit(&argC,argV);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Bangladesh National Flag");
    MyInit();
    glutDisplayFunc(Draw);
    glutIdleFunc(Animate);
    glutMainLoop();
    return 0;
}
