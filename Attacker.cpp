#include <bits/stdc++.h>
#include <GL/glut.h>
#include "Attacker.h"

using namespace std;

Attacker::Attacker(float x, float z){
    health = 3;
    xO = x;
    zO = z;
}
int Attacker::getHealth(){
    return health;
}
void Attacker::move(){
    xO -= 0.02;
}
void Attacker::hit(){
    health -= 1;
}

void Attacker::draw(float x, float z){
    float b = 0;
    switch(health){
        case 2:
            b = -0.2;
            break;
        case 1:
            b = -0.4;
            break;
        case 0:
            b = -0.6;
            break;
    }
    glPushMatrix();
        glTranslated(xO + x - 4, 0.15, zO + z - 0.45);
		glPushMatrix();
            glColor3f(.3,.3,.6 + b);
			glTranslated(3.8, 0, 0.8); // cylinder at (0,0,1)
			GLUquadricObj * qobj;
			qobj = gluNewQuadric();
			gluQuadricDrawStyle(qobj,GLU_FILL);
			gluCylinder(qobj, 0.15, 0.15, 0.2, 8, 8);
			glPushMatrix();
			glTranslated(0, 0, 0.2); // cylinder at (0,0,1)
			gluDisk(qobj, 0, 0.15, 50, 50);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
            glColor3f(.3,.3,.6 + b);
			glTranslated(4.2, 0, 0.8); // cylinder at (0,0,1)
			GLUquadricObj * qobj2;
			qobj2 = gluNewQuadric();
			gluQuadricDrawStyle(qobj2,GLU_FILL);
			gluCylinder(qobj2, 0.15, 0.15, 0.2, 8, 8);
			glPushMatrix();
			glTranslated(0, 0, 0.2); // cylinder at (0,0,1)
			gluDisk(qobj2, 0, 0.15, 50, 50);
			glPopMatrix();

		glPopMatrix();
		glPushMatrix();
            glColor3f(.3,.3,.6 + b);
			glTranslated(4.2, 0, 0); // cylinder at (0,0,1)
			GLUquadricObj * qobj3;
			qobj3 = gluNewQuadric();
			gluQuadricDrawStyle(qobj3,GLU_FILL);
			gluCylinder(qobj3, 0.15, 0.15, 0.2, 8, 8);
			glPushMatrix();
			gluDisk(qobj3, 0, 0.15, 50, 50);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
            glColor3f(.3,.3,.6 + b);
			glTranslated(3.8, 0, 0); // cylinder at (0,0,1)
			GLUquadricObj * qobj4;
			qobj4 = gluNewQuadric();
			gluQuadricDrawStyle(qobj4,GLU_FILL);
			gluCylinder(qobj4, 0.15, 0.15, 0.2, 8, 8);
			glPushMatrix();
			gluDisk(qobj4, 0, 0.15, 50, 50);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslated(4, 1.1, 0.5); // dodecahedron at (1,0,0)
			glScaled(0.15, 0.15, 0.15);
			glColor3f(0,1,.0);
			glutSolidDodecahedron();
		glPopMatrix();

		glPushMatrix();
			glColor3f(.3,.3,.6 + b);
			glTranslated(4, 0.5, 0.5); // big cube at (0.5, 0.5, 0.5)
			glutSolidCube(0.8);
		glPopMatrix();
		glPushMatrix();
			glTranslated(3.6,0.5,0.25);
			glRotatef(-90,0,1,0);
			glutSolidCone(0.1, 0.3, 10, 8);
		glPopMatrix();
		glPushMatrix();
			glTranslated(3.6,0.5,0.45);
			glRotatef(-90,0,1,0);
			glutSolidCone(0.1, 0.3, 10, 8);
		glPopMatrix();
		glPushMatrix();
			glTranslated(3.6,0.5,0.65);
			glRotatef(-90,0,1,0);
			glutSolidCone(0.1, 0.3, 10, 8);
		glPopMatrix();

	glPopMatrix();
}
