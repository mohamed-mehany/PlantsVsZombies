#include <bits/stdc++.h>
#include <GL/glut.h>
#include "Attacker.h"
#include "Defender.h"
#include "Resource.h"
#include "Board.h"
#include "Bullet.h"

typedef pair<int, int> ii;
// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f,z = 5.0f, xCir = 0, yCir = 10, zCir = 8;
float rotAng;
int money = 40, destroyedLanes = 0, timer = 0, destroyedAttackers = 0;
int resourceCost = 10, defenderCost = 20, canonDefenderCost = 30;
bool paused = false, won = false, lost = false, cinematic = false;
vector<pair<ii, Defender> > defenders;
vector<pair<ii, Attacker> > attackers;
vector<pair<ii, Resource> >resources;
vector<pair<int, Bullet> > bullets;
Board b1(-4, -5);
bool rowPressed = false, colPressed = false;
int curRow = 0, curCol = 0;
float t = 0;
void checkAttackers(){
	for(auto it = attackers.begin(); it != attackers.end();){
		if(it->second.xO <= -4.5){
			b1.destroyLane(it->first.first);
			it = attackers.erase(it);
			destroyedLanes++;
		}
		else if(it->second.getHealth() <= 0){
			it = attackers.erase(it);
			destroyedAttackers++;
			money += 5;
		}
		else
			++it;
	}
}

bool checkCollisionBullet(pair<ii, Attacker> &att1, pair<int, Bullet> &bb1){
	return ((att1.first.first == bb1.first) && fabs(bb1.second.xO-att1.second.xO) <= 0.17);
}
bool checkCollisionDefender(pair<ii, Attacker> &att1, pair<ii, Defender> &def1){
	return (att1.first.first == def1.first.first) && (fabs(att1.second.xO-def1.second.xO) <= 0.8);
}
bool checkCollisionResource(pair<ii, Attacker> &att1, pair<ii, Resource> &res1){
	return (att1.first.first == res1.first.first) && (fabs(att1.second.xO-res1.second.xO) <= 0.8);
}

void output(float x, float z, string st)
{
	glRasterPos3f(x, 0, z);
	int len, i;
	len = (int) st.length();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
	}
}

void checkLanes(){
	for(int i = 1; i <= 5; ++i){
		if(!b1.laneFree(i)){
			for(auto it2 = attackers.begin(); it2 != attackers.end();){
				if(it2->first.first == i){
					it2 = attackers.erase(it2);
				}
				else{
					it2++;
				}
			}
			for(auto it2 = defenders.begin(); it2 != defenders.end();){
				if(it2->first.first == i){
					it2 = defenders.erase(it2);
				}
				else{
					it2++;
				}
			}
			for(auto it2 = resources.begin(); it2 != resources.end();){
				if(it2->first.first == i){
					it2 = resources.erase(it2);
				}
				else{
					it2++;
				}
			}
		}
	}

}
void drawPieces(){
	for(auto &it: attackers){
		for(auto it2 = bullets.begin(); it2 != bullets.end();){
			if(checkCollisionBullet(it, *it2)){
				it.second.hit();
				it2 = bullets.erase(it2);
			}
			else{
				it2++;
			}
		}
		for(auto it2 = defenders.begin(); it2 != defenders.end();){
			if(checkCollisionDefender(it, *it2)){
				it2 = defenders.erase(it2);
			}
			else{
				it2++;
			}
		}
		for(auto it2 = resources.begin(); it2 != resources.end();){
			if(checkCollisionResource(it, *it2)){
				it2 = resources.erase(it2);
			}
			else{
				it2++;
			}
		}
		it.second.draw(0, 0);
	}
	for(auto &it: defenders){
		it.second.draw(0, 0);
		it.second.timer++;
	}
	for(auto &it: resources){
		it.second.draw(0, 0, rotAng);
		it.second.timer++;
	}
	for(auto it = bullets.begin(); it != bullets.end();){
		if(it->second.xO <= -4.5 || it->second.xO >= 4.8){
			it = bullets.erase(it);
		}
		else it++;
	}
	for(auto it: bullets){
		it.second.draw(0, 0);
	}
}
void freeCamera(){
	glLoadIdentity();
	gluLookAt(x, 1.0f, z, x+lx, 1.0f, z+lz, 0.0f, 1.0f, 0.0f);
}

void displayText(){
	string moneyS = "Current Amount of resources:" + to_string(money);
	string costOfResouce = "It costs " + to_string(resourceCost) + " to build a resource gatherer.";
	string costOfDefender = "It costs " + to_string(defenderCost) + " to buy a defender and "
		+ to_string(canonDefenderCost) +" to buy a flying canon defender.";
	string killedSoFar = "You have killed so far " + to_string(destroyedAttackers);
	output(-6, -8.6, moneyS);
	output(-5.9, -8, costOfResouce);
	output(-5.85, -7.4, costOfDefender);
	output(-5.75, -6.8, killedSoFar);

	if(lost){
		string lostText = "Zombies Ate Your Brain!!!";
		output(0, 2.8, lostText);
	}
	else if(won){
		string wonText = "Congratulations!!! You Won";
		output(0, 2.8, wonText);
	}
}
void checkStatus(){
	if(destroyedLanes >= 3){
		lost = true;
	}
	if(destroyedAttackers >= 50){
		won = true;
	}
}
void cinematicView(){
	t += 0.01;
	xCir = 12.0*cos(t);
	zCir = 12.0*sin(t);
}
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//freeCamera();
	if(cinematic){
		cinematicView();
	}
	else
		xCir = 0.0, zCir = 8.0;
	//cout<<cinematic<<" "<<xCir<<" "<<yCir<<endl;
	glLoadIdentity();
	gluLookAt(xCir, yCir, zCir, 0, 0, 0, 0.0, 1.0, 0.0);
	b1.draw();
	checkStatus();
	drawPieces();
	checkAttackers();
	checkLanes();
	displayText();
	glFlush();
}
bool isRow(unsigned char key){
	return key >= '1' && key <= '5';
}
bool isCol(unsigned char key){
	return key >= '1' && key <= '9';
}

void deleteCell(int row, int col){
	for(auto it = defenders.begin(); it != defenders.end();){
		if(it->first.first == row && it->first.second == col){
			it = defenders.erase(it);
		}
		else
			++it;
	}
	for(auto it = resources.begin(); it != resources.end();){
		if(it->first.first == row && it->first.second == col){
			it = resources.erase(it);
		}
		else
			++it;
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	if(key == 'p')
		paused = !paused;
	if(paused || lost || won)
		return;
	if(key == 'v')
		cinematic = !cinematic;
	if(!rowPressed && isRow(key)){
		rowPressed = true;
		curRow = (int) key - '0';
	}
	else if(rowPressed && !colPressed && isCol(key)){
		colPressed = true;
		curCol = (int) key - '0';
	}
	if(rowPressed && colPressed){
		b1.highlightCell(curRow, curCol);
		pair<float, float> center = b1.getCenter(curRow, curCol);
		switch(key){
			case 'd':{
				if(b1.isFree(curRow, curCol) && money >= defenderCost){
					Defender def1(center.first, center.second, 0);
					defenders.push_back({{curRow, curCol},def1});
					b1.occupyCell(curRow, curCol);
					money -= defenderCost;
				}
				rowPressed = false;
				colPressed = false;
				b1.unHighlightCell(curRow, curCol);
				break;
			}
			case 'c':{
				if(!b1.isFree(curRow, curCol)){
					deleteCell(curRow, curCol);
					b1.freeCell(curRow, curCol);
				}
				rowPressed = false;
				colPressed = false;
				b1.unHighlightCell(curRow, curCol);
				break;
			}
			case 'r':{
				if(b1.isFree(curRow, curCol) && money >= resourceCost){
					Resource res1(center.first, center.second);
					resources.push_back({{curRow, curCol},res1});
					b1.occupyCell(curRow, curCol);
					money -= resourceCost;
				}
				rowPressed = false;
				colPressed = false;
				b1.unHighlightCell(curRow, curCol);
				break;
			}
			case 'n':{
				if(b1.isFree(curRow, curCol) && money >= canonDefenderCost){
					Defender def1(center.first, center.second, 1);
					defenders.push_back({{curRow, curCol},def1});
					b1.occupyCell(curRow, curCol);
					money -= canonDefenderCost;
				}
				rowPressed = false;
				colPressed = false;
				b1.unHighlightCell(curRow, curCol);
				break;
			}
			// case 'a':{
			// 	if(b1.isFree(curRow, curCol)){
			// 		Attacker at1(center.first, center.second);
			// 		attackers.push_back({{curRow, curCol},at1});
			// 	}
			// 	rowPressed = false;
			// 	colPressed = false;
			// 	b1.unHighlightCell(curRow, curCol);
			// 	break;
			// }
		}
	}
}
void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 0.1f;
	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}
void moveAttackers(){
	for(auto &it: attackers){
		it.second.move();
	}
}
void moveBullets(){
	for(auto &it: bullets){
		it.second.move();
	}
}
void defendersShoot(){
	for(auto &it: defenders){
		if(it.second.fire()){
			pair<float, float> c = b1.getCenter(it.first.first, it.first.second);
			Bullet bbb(c.first, c.second);
			bullets.push_back({it.first.first, bbb});
		}
	}
}
void gatherResources(){
	for(auto it: resources){
		if(it.second.timer % 50 == 0)
			money++;
	}
}
void spawnAttacker(){
	srand (time(NULL));
	int rowN = rand() % 5 + 1;
	int colN = 9;
	if(b1.laneFree(rowN)){
		pair<float, float> c = b1.getCenter(rowN, colN);
		Attacker at1(c.first, c.second);
		attackers.push_back({{rowN, colN},at1});
	}
}
void Anim(int val) {
	if(!paused && !won && !lost){
		rotAng += 3.0;
		timer++;
		if(timer % 200 == 0){
			spawnAttacker();
		}
		moveAttackers();
		gatherResources();
		defendersShoot();
		moveBullets();
		glutPostRedisplay();
	}
	glutTimerFunc(33, Anim, 0);
}
void initGL(){
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Plants Vs Zombies");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	initGL();
	glutDisplayFunc(Display);
	glutTimerFunc(0, Anim, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 300 / 300, 0.1f, 300.0f);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();
}
