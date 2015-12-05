#include <bits/stdc++.h>
#include <GL/glut.h>
#include "Board.h"
using namespace std;
Board::Board(float x, float z) {
    memset(vis, 0, sizeof vis);
    memset(destr, 0, sizeof destr);
    xO = x;
    zO = z;
}
pair<float, float> Board::getCenter(int row, int col){
    float xC = xO + col - 0.5;
    float zC = zO + row - 0.5;
    return {xC, zC};
}
void Board::highlightCell(int row, int col){
    highlighted.push_back({row, col});
}
void Board::unHighlightCell(int row, int col){
    for(auto it = highlighted.begin(); it != highlighted.end();){
        if(it->first == row && it->second == col){
            it = highlighted.erase(it);
        }
        else
            ++it;
    }
}
bool Board::isFree(int row, int col){
    return !vis[row][col] && !destr[row][col];
}

bool Board::laneFree(int row){
    return !destr[row][1];
}

void Board::occupyCell(int row, int col){
    vis[row][col] = 1;
}
void Board::freeCell(int row, int col){
    vis[row][col] = 0;
}
void Board::destroyLane(int row){
    for(int i = 1; i <= 9; ++i){
        destroyed.push_back({row,i});
        destr[row][i] = 1;
    }
}
void Board::draw() {
	glColor3f(.3, .3, .3);
	glBegin(GL_LINE_LOOP);
		glVertex3f(xO, 0, zO);
		glVertex3f(xO + 9, 0, zO);
		glVertex3f(xO + 9, 0, zO + 5);
		glVertex3f(xO, 0, zO + 5);
	glEnd();

	glBegin(GL_LINES);
	for(int i = zO; i < zO + 5; ++i) {
		glColor3f(.3, .3, .6);
		glVertex3f(xO, 0, i);
		glVertex3f(xO + 9, 0, i);
	}
	for(int i = xO; i < xO + 9; ++i){
		glColor3f(.3,.3,.6);
		glVertex3f(i, 0, zO);
		glVertex3f(i, 0, zO + 5);
	}
	glEnd();

    for(auto it: highlighted){
        pair<float, float> c = getCenter(it.first, it.second);
        glPushMatrix();
            glColor3f(1,1,0);
            glTranslated(c.first, 0, c.second); // big cube at (0.5, 0.5, 0.5)
            glScaled(1, 0.05, 1);
            glutSolidCube(1);
        glPopMatrix();
    }
    for(auto it: destroyed){
        pair<float, float> c = getCenter(it.first, it.second);
        glPushMatrix();
            glColor3f(0,0,0);
            glTranslated(c.first, 0, c.second); // big cube at (0.5, 0.5, 0.5)
            glScaled(1, 0.05, 1);
            glutSolidCube(1);
        glPopMatrix();
    }
}
