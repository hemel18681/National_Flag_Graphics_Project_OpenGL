#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>

GLfloat ya = 50,xa = 10;
int yFlag = 1, xFlag = 1;

void Animate(){
    if(ya>-50 && yFlag==1) ya-=0.2;
    if(ya<=-50 && yFlag==1) yFlag=0;
    if(ya<50 && yFlag==0) ya+=0.2;
    if(ya>=50 && yFlag==0) yFlag=1;

    if(xa>-10 && xFlag==1) xa-=0.2;
    if(xa<=-10 && xFlag==1) xFlag=0;
    if(xa<10 && xFlag==0) xa+=0.2;
    if(xa>=10 && xFlag==0) xFlag=1;

     glutPostRedisplay();
}

void Draw(){
    GLfloat x[4],y[4];
    GLfloat xt[200],yt[200],t;
    glClear(GL_COLOR_BUFFER_BIT);
    int i;
    x[0] = 100; x[1] = 200; x[2] = 200; x[3] = 300-xa;
    y[0] = 450; y[1] = 450+ya; y[2] = 450-ya; y[3] = 450;

    for(i=0,t=0;t<=1;i++,t+=0.01){
        xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*t*t*(1-t)*x[2] + t*t*t*x[3];
        yt[i] = pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*t*t*(1-t)*y[2] + t*t*t*y[3];
    }
    glPointSize(3);
    glBegin(GL_POINTS);
        for(i=0;i<200;i++) { glVertex2i(xt[i],yt[i]); }
    glEnd();
    glFlush();
}

void MyInit(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
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
