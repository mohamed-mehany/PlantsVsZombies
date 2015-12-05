#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

class Resource{
    public:
        long long timer;
        float xO, zO;
        Resource(float x, float z);
        void draw(float x, float z, float rotAng);
};
