#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

class Attacker{
    public:
        float xO, zO;
        int health;
        Attacker(float x, float z);
        int getHealth();
        void draw(float x, float z);
        void move();
        void hit();
};
