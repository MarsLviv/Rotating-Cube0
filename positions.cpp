#include "positions.h"
#include <QDebug>

Positions::Positions(){
}

void Positions::plot2T()
{
    for (int i = 0; i < 6; i++){
        QString str;
        for (int j = 0; j < 8; j++){
            str.append(table[i][j]);
            str.append(' ');
        }
        qDebug() << str;
    }
}

void Positions::picked(int nObj, char color){
    int row;        // get row's # from table
    switch (color) {
    case 'r': row = 0; break;
    case 'g': row = 1; break;
    case 'y': row = 2; break;
    case 'b': row = 3; break;
    case 'w': row = 4; break;
    case 'm': row = 5; break;
    default:
        qDebug() << "Trouble in Positions::picked function: switched to default";
        break;
    }
    face = table[row][nObj - 1];
    int n = 0;      // get all 4 boxes from picked face - to int array boxes[4]
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++)
            if (table[i][j] == face){
                boxes[n] = j + 1;
                n++;
            }
    //qDebug() << "PICK_face" <<face << " boxes:" << boxes[0] <<boxes[1] <<boxes [2] << boxes[3];
}

void Positions::rotateCounterClockWise(){   // use [face]
    if (face == 'F') F();
    if (face == 'B') B();
    if (face == 'L') L();
    if (face == 'R') R();
    if (face == 'T') T();
    if (face == 'D') D();
}

void Positions::rotateClockWise(){
    // use [face]
    if (face == 'F') _F();
    if (face == 'B') _B();
    if (face == 'L') _L();
    if (face == 'R') _R();
    if (face == 'T') _T();
    if (face == 'D') _D();
}

char Positions::getFace(){
    return face;
}

void Positions::getBoxes(int *boxes){
    //qDebug() << "getBoxes";
    boxes[0] = this->boxes[0]; boxes[1] = this->boxes[1];
    boxes[2] = this->boxes[2]; boxes[3] = this->boxes[3];
}

void Positions::F(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'R') { table[i][j] = 'T'; continue;}
                else if (table[i][j] == 'T') { table[i][j] = 'L'; continue;}
                else if (table[i][j] == 'L') { table[i][j] = 'D'; continue;}
                else if (table[i][j] == 'D') { table[i][j] = 'R'; continue;}
            }
        }
}

void Positions::_F(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'R') { table[i][j] = 'D'; continue;}
                else if (table[i][j] == 'D') { table[i][j] = 'L'; continue;}
                else if (table[i][j] == 'L') { table[i][j] = 'T'; continue;}
                else if (table[i][j] == 'T') { table[i][j] = 'R'; continue;}
            }
        }
}

void Positions::B(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'T') { table[i][j] = 'R'; continue;}
                else if (table[i][j] == 'R') { table[i][j] = 'D'; continue;}
                else if (table[i][j] == 'D') { table[i][j] = 'L'; continue;}
                else if (table[i][j] == 'L') { table[i][j] = 'T'; continue;}
            }
        }
}

void Positions::_B(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'T') { table[i][j] = 'L'; continue;}
                else if (table[i][j] == 'L') { table[i][j] = 'D'; continue;}
                else if (table[i][j] == 'D') { table[i][j] = 'R'; continue;}
                else if (table[i][j] == 'R') { table[i][j] = 'T'; continue;}
            }
        }
}

void Positions::L(){
for (int i = 0; i < 6; i++)
    for (int j = 0; j < 8; j++){
        if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
            if (table[i][j] == 'T') { table[i][j] = 'B'; continue;}
            else if (table[i][j] == 'B') { table[i][j] = 'D'; continue;}
            else if (table[i][j] == 'D') { table[i][j] = 'F'; continue;}
            else if (table[i][j] == 'F') { table[i][j] = 'T'; continue;}
        }
    }
}

void Positions::_L(){
for (int i = 0; i < 6; i++)
    for (int j = 0; j < 8; j++){
        if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
            if (table[i][j] == 'T') { table[i][j] = 'F'; continue;}
            else if (table[i][j] == 'F') { table[i][j] = 'D'; continue;}
            else if (table[i][j] == 'D') { table[i][j] = 'B'; continue;}
            else if (table[i][j] == 'B') { table[i][j] = 'T'; continue;}
        }
    }
}

void Positions::R(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'F') { table[i][j] = 'D'; continue;}
                else if (table[i][j] == 'D') { table[i][j] = 'B'; continue;}
                else if (table[i][j] == 'B') { table[i][j] = 'T'; continue;}
                else if (table[i][j] == 'T') { table[i][j] = 'F'; continue;}
            }
        }
}

void Positions::_R(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'F') { table[i][j] = 'T'; continue;}
                else if (table[i][j] == 'T') { table[i][j] = 'B'; continue;}
                else if (table[i][j] == 'B') { table[i][j] = 'D'; continue;}
                else if (table[i][j] == 'D') { table[i][j] = 'F'; continue;}
            }
        }
}

void Positions::T(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'F') { table[i][j] = 'R'; continue;}
                else if (table[i][j] == 'R') { table[i][j] = 'B'; continue;}
                else if (table[i][j] == 'B') { table[i][j] = 'L'; continue;}
                else if (table[i][j] == 'L') { table[i][j] = 'F'; continue;}
            }
        }
}

void Positions::_T(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'F') { table[i][j] = 'L'; continue;}
                else if (table[i][j] == 'L') { table[i][j] = 'B'; continue;}
                else if (table[i][j] == 'B') { table[i][j] = 'R'; continue;}
                else if (table[i][j] == 'R') { table[i][j] = 'F'; continue;}
            }
        }
}

void Positions::D(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'F') { table[i][j] = 'L'; continue;}
                else if (table[i][j] == 'L') { table[i][j] = 'B'; continue;}
                else if (table[i][j] == 'B') { table[i][j] = 'R'; continue;}
                else if (table[i][j] == 'R') { table[i][j] = 'F'; continue;}
            }
        }
}

void Positions::_D(){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 8; j++){
            if ( j == (boxes[0] - 1) || j == (boxes[1] - 1) || j == (boxes[2] - 1) || j == (boxes[3] - 1)){
                if (table[i][j] == 'F') { table[i][j] = 'R'; continue;}
                else if (table[i][j] == 'R') { table[i][j] = 'B'; continue;}
                else if (table[i][j] == 'B') { table[i][j] = 'L'; continue;}
                else if (table[i][j] == 'L') { table[i][j] = 'F'; continue;}
            }
        }
}
