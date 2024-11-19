#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;
#include "ships.h"
#include "ocean.h"

Ship::Ship(){
    bowRow=0;
    bowColumn=0;
    length=0;
    horizontal=false;
    hit = new bool[4];
    for (int i=0; i<4; i++){
        hit[i]=false;
    }
}

Ship::Ship(int len):Ship(){
    length=len;
}

Ship::Ship(const Ship& ship){
    bowRow=ship.bowRow;
    bowColumn=ship.bowColumn;
    length=ship.length;
    horizontal=ship.horizontal;
    hit = new bool[4];
    for (int i=0; i<4; i++){
        hit[i]=ship.hit[i];
    }
}

int Ship::getLength(){return length;}
int Ship::getBowRow(){return bowRow;}
int Ship::getBowColumn(){return bowColumn;}
bool Ship::isHorizontal(){return horizontal;}
void Ship::setBowRow(int row){bowRow=row;}
void Ship::setBowColumn(int column){bowColumn=column;}
void Ship::setHorizontal(bool horiz){horizontal=horiz;}

bool Ship::shootAt(int row, int col){
    int i;
    if (length==1){
        i=0;
    } else if (horizontal){
        i=col-bowColumn;
    } else {
        i=row-bowRow;
    }
    hit[i]=true;
    /*
    cout<<getShipType()<<endl;
    cout<<i<<endl;
    for (int i=0; i<4; i++){
        if (hit[i]){
            cout<<"T";
        }else{
            cout<<"F";
        }
    }
    cout<<endl;
    */
    if (getShipType()=="empty"){
        return false;
    } else {
        return true;
    }
}

bool Ship::isSunk(){
    if (getShipType()=="empty"){
        return false;
    }
    for (int i=0; i<length; i++){
        if (!hit[i]){
            return false;
        }
    }
    return true;
}

bool Ship::wasHit(int row, int col){
    int i;
    if (getShipType()=="empty"){
        return false;
    } else if (horizontal){
        i=col-bowColumn;
        return (bowRow==row && i<length && i>=0 && hit[i]);
    } else {
        i=row-bowRow;
        return (bowColumn==col && i<length && i>=0 && hit[i]);
    }
}
string Ship::toString(){
    if (isSunk()){
        return "x";
    } else {
        return "S";
    }
}

Battleship::Battleship():Ship(4){}

string Battleship::getShipType(){
    return "battleship";
}

Cruiser::Cruiser():Ship(3){}

string Cruiser::getShipType(){
    return "cruiser";
}


Destroyer::Destroyer():Ship(2){}

string Destroyer::getShipType(){
    return "destroyer";
}

Submarine::Submarine():Ship(1){}

string Submarine::getShipType(){
    return "submarine";
}


EmptySea::EmptySea():Ship(1){//cout<<"created"<<endl;
}

string EmptySea::toString(){
    if (hit[0]){
        return "-";
    } else {
        return ".";
    }
}

string EmptySea::getShipType(){
    return "empty";
}
