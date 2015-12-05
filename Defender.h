#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

class Defender{
    public:
        long long timer;
        int type;
        float xO, zO;
        Defender(float x, float z, int type);
        void draw(float x, float z);
        bool fire();
};
