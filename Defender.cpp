#include <bits/stdc++.h>
#include <GL/glut.h>
#include "Defender.h"
using namespace std;

Defender::Defender(float x, float z, int typeC){
	type = typeC;
	timer = 0;
	xO = x;
    zO = z;
}
bool Defender::fire(){
	if(type == 0)
		return (timer % 50 == 0);
	else if(type == 1)
		return (timer % 10 == 0);
}
void Defender::draw(float x, float z){
	if(type == 0){
		glPushMatrix();
			glTranslated(xO + x - 1.1, 0, zO + z + 0.8);
			glPushMatrix();
				glColor3f(.3,.3,.6);
				glTranslated(1.1, 0.8, -0.8);
				glutSolidSphere(0.25, 10, 10);
			glPopMatrix();
			glPushMatrix();
				glColor3f(.3,.3,.6);
				glTranslated(1.1, 0.8, -0.75); // cylinder at (0,0,1)
				glRotatef(90, 1, 0, 0);
				GLUquadricObj * qobj;
				qobj = gluNewQuadric();
				gluQuadricDrawStyle(qobj,GLU_FILL);
				gluCylinder(qobj, 0.2, 0.2, 0.8, 8,8);
			glPopMatrix();

			glPushMatrix();
				glColor3f(.3,.3,.6);
				glTranslated(1.25, 0.8, -0.8);
				glRotatef(90, 0, 1, 0);
				GLUquadricObj * qobj2;
				qobj2 = gluNewQuadric();
				gluQuadricDrawStyle(qobj2,GLU_FILL);
				gluCylinder(qobj2, 0.2, 0.2, 0.4, 8,8);
			glPopMatrix();
		glPopMatrix();
	}
	else if(type == 1){
		glPushMatrix();
			glTranslated(xO + x - 1.1, 0, zO + z + 0.8);
			glPushMatrix();
				glColor3f(0,0.8,0);
				glTranslated(1.1, 0.8, -0.8);
				glutSolidSphere(0.25, 10, 10);
			glPopMatrix();
			/*glPushMatrix();
				glColor3f(0,0.8,0);
				glTranslated(1.1, 0.8, -0.75); // cylinder at (0,0,1)
				glRotatef(90, 1, 0, 0);
				GLUquadricObj * qobj;
				qobj = gluNewQuadric();
				gluQuadricDrawStyle(qobj,GLU_FILL);
				gluCylinder(qobj, 0.2, 0.2, 0.8, 8,8);
			glPopMatrix();*/

			glPushMatrix();
				glColor3f(0,0.8,0);
				glTranslated(1.25, 0.8, -0.8);
				glRotatef(90, 0, 1, 0);
				GLUquadricObj * qobj2;
				qobj2 = gluNewQuadric();
				gluQuadricDrawStyle(qobj2,GLU_FILL);
				gluCylinder(qobj2, 0.2, 0.2, 0.4, 8,8);
			glPopMatrix();
		glPopMatrix();
	}
}
