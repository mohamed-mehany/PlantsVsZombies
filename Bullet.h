#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

class Bullet{
    public:
        float xO, zO;
        Bullet(float x, float z);
        void draw(float x, float z);
        void move();
};
