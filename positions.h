#ifndef POSITIONS_H
#define POSITIONS_H

class Positions
{
public:
    Positions();

    void plot2T();
    void picked(int nObj, char color);// calculate [face] and [boxes] to rotate
    void rotateCounterClockWise();// rotating 4 boxes from picked [face]
    void rotateClockWise();
    char getFace();
    void getBoxes(int *boxes);// get 4 boxes from picked face
    void F(); // rotate boxes from FRONT face in table
    void _F();
    void B();
    void _B();
    void L();
    void _L();
    void R();
    void _R();
    void T();
    void _T();
    void D();
    void _D();

private:
    char tableSolved[6][8] = {  {'F','F','-','-','F','F','-','-'},
                                {'R','-','-','R','R','-','R','-'},
                                {'T','T','T','T','-','-','-','-'},
                                {'-','L','L','-','-','L','-','L'},
                                {'-','-','-','-','D','D','D','D'},
                                {'-','-','B','B','-','-','B','B'}   };

    char table[6][8] = {{'F','F','-','-','F','F','-','-'},
                        {'R','-','-','R','R','-','R','-'},
                        {'T','T','T','T','-','-','-','-'},
                        {'-','L','L','-','-','L','-','L'},
                        {'-','-','-','-','D','D','D','D'},
                        {'-','-','B','B','-','-','B','B'}   };
    char face;  // ['F'..'D'] this face was picked
    int boxes[4];// [1..8] these boxes placed in picked face. Fill this array in pick
    int nObj;   // [1..8] this box was picked
};

#endif // POSITIONS_H
