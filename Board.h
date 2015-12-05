#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

class Board{
    public:
        float xO, zO;
        bool vis[11][11], destr[11][11];
        vector<pair<int, int> > highlighted, destroyed;
        Board(float x, float z);
        void draw();
        pair<float, float> getCenter(int row, int col);
        void highlightCell(int row, int col);
        bool isFree(int row, int col);
        void occupyCell(int row, int col);
        void freeCell(int row, int col);
        void unHighlightCell(int row, int col);
        void destroyLane(int row);
        bool laneFree(int row);
};
