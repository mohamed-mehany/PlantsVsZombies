#include <bits/stdc++.h>
#include <GL/glut.h>
#include "Bullet.h"
using namespace std;

Bullet::Bullet(float x, float z){
    xO = x;
    zO = z;
}

void Bullet::move(){
    xO += 0.15;
}

void Bullet::draw(float x, float z){
	glPushMatrix();
		glTranslated(xO + x + 0.5, 0.8, zO + z);
		glPushMatrix();
            glColor3f(1,0,0);
            glutSolidSphere(0.20, 10, 10);
		glPopMatrix();
	glPopMatrix();
}
