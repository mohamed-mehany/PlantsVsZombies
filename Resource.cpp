#include <bits/stdc++.h>
#include <GL/glut.h>
#include "Resource.h"
using namespace std;

Resource::Resource(float x, float z){
    xO = x;
    zO = z;
	timer = 0;
}
void Resource::draw(float x, float z, float rotAng){
	glPushMatrix();
		glTranslated(xO + x, 0, zO + z);
		glRotatef(rotAng, 0,1,0);
		glPushMatrix();
			glTranslated(-0.01, 1.2, 0); // dodecahedron at (1,0,0)
			glScaled(0.15, 0.15, 0.15);
			glColor3f(0,1,.0);
			glutSolidDodecahedron();
		glPopMatrix();
		for(float i = 0 ; i < 25; i += 0.05){
			glPushMatrix();
				glRotatef(50.0f*i, 0,1,0);
				glTranslated(5*0.02,i*0.04,0);
				glColor3f(.3,.3,.6);
				glutSolidSphere(0.05, 10, 10);
			glPopMatrix();
		}
	glPopMatrix();
}
