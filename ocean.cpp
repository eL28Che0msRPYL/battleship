#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;
#include "ships.h"
#include "ocean.h"

int Ocean::totalShips=0;

//edit only between these lines ------v
Ocean::~Ocean(){
//Next you will implement Ocean’s destructor. This destructor will go through the 2D vector of ships and delete all of the ships to free up the memory. 
//When you use new in a class it is good practice to do this to avoid memory leaks. Be careful, a ship might take up more than one position in the grid, but it is still only one ship and so should only be deleted once.
     for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            ships[i][j] = NULL;
            //delete ships[i][j];
        }
    } 
    //ships.clear()
    //delete ships[0][1];
    //delete ships[0][2];
    //delete ships;


    //delete all ships (including emptySeas)
    //no couts!
}

Ship::~Ship(){
    //cout destroyed safely
    cout << "destroyed safely" << endl;
}

Battleship::~Battleship(){
    cout << getShipType();
}

Cruiser::~Cruiser(){
    //cout getShipType
    cout << getShipType();
}

Destroyer::~Destroyer(){
    //cout getShipType
    cout << getShipType();
}

Submarine::~Submarine(){
    //cout getShipType
    cout << getShipType();
}

EmptySea::~EmptySea(){
    //cout getShipType
    cout << getShipType();
}
//edit only between these lines ------^

Ocean::Ocean(){
    srand(time(0));
    for (int i=0; i<SIDES; i++){
        vector<Ship*> tempVector;
        for (int j=0; j<SIDES; j++){
            tempVector.push_back(new EmptySea());
        }
        ships.push_back(tempVector);
    }

    shotsFired=0;
    hitCount=0;
    shipsSunk=0;
}

int Ocean::getRando(int max){
    return rand()%max;
}

void Ocean::placeOneShipRandomly(Ship* ship){
    int i,j;
    bool horiz;
    do{
        i=getRando();
        j=getRando();
        horiz=getRando(2);
    } while (!ship->okToPlaceShipAt(i,j,horiz,*this));
    // clear out the emptySeas
    if (horiz){
        for (int x=j; x<j+ship->getLength(); x++){
            delete ships[i][x];
            ships[i][x]=NULL;
            //cout<<i<<" "<<x<<endl;
        }
    } else {
        for (int y=i; y<i+ship->getLength(); y++){
            delete ships[y][j];
            ships[y][j]=NULL;
            //cout<<y<<" "<<j<<endl;
        }
    }
    ship->placeShipAt(i,j,horiz,*this);
    totalShips++;
}

void Ocean::placeAllShipsRandomly(){
    placeOneShipRandomly(new Battleship());
    placeOneShipRandomly(new Cruiser());
    placeOneShipRandomly(new Cruiser());
    placeOneShipRandomly(new Destroyer());
    placeOneShipRandomly(new Destroyer());
    placeOneShipRandomly(new Destroyer());
    placeOneShipRandomly(new Submarine());
    placeOneShipRandomly(new Submarine());
    placeOneShipRandomly(new Submarine());
    placeOneShipRandomly(new Submarine());
}

bool Ocean::isOccupied(int row, int column){
    return (ships[row][column]->getShipType()!="empty");
}

bool Ocean::shootAt(int row, int col){
    shotsFired++;
    if (ships[row][col]->isSunk()){
        return false;
    }
    if (ships[row][col]->shootAt(row,col)){
        hitCount++;
        if (ships[row][col]->isSunk()){
            shipsSunk++;
        }
        return true;
    } else {
        return false;
    }
}

int Ocean::getShotsFired(){return shotsFired;}
int Ocean::getHitCount(){return hitCount;}
int Ocean::getShipsSunk(){return shipsSunk;}

bool Ocean::isGameOver(){
    return (shipsSunk==totalShips);
}

void Ocean::print(){
    for (int i=-1; i<SIDES; i++){
        for (int j=-1; j<SIDES; j++){
            if (i==-1 && j==-1){
                cout<<" ";
            } else if (i==-1){
                cout<<j;
            } else if (j==-1){
                cout<<i;
            } else {
                string output=ships[i][j]->toString();
                if (output=="S"){//ship is not sunk
                    if (ships[i][j]->wasHit(i,j)){//true){//testing
                        cout<<output;
                    } else {
                        cout<<".";
                    }
                }
                else {
                    cout<<output;
                }
            }
        }
        cout<<endl;
    }
}

bool Ship::okToPlaceShipAt(int row, int column, bool horiz, const Ocean& ocean){
    if (horiz){
        if ((column+length)>SIDES){
            return false;
        }
    } else {
        if ((row+length)>SIDES){
            return false;
        }
    }
    for (int i=-1; i<length+1; i++){
        int x,y;
        int x1,y1;
        int x2,y2;
        if (horiz){
            y=row; y1=row; y2=row;
            x=column+i; x1=column+i; x2=column+i;
            if (x<0 || x>=SIDES)
                continue;
            if (row-1>=0){
                y1=row-1;
            }
            if (row+1<SIDES){
                y2=row+1;
            }
        } else {
            y=row+i; y1=row+i; y2=row+i;
            if (y<0 || y>=SIDES)
                continue;
            x=column; x1=column; x2=column;
            if (column-1>=0){
                x1=column-1;
            }
            if (column+1<SIDES){
                x2=column+1;
            }

        }
        if ((ocean.ships[y][x]->getShipType()!="empty") ||
            (ocean.ships[y1][x1]->getShipType()!="empty") ||
            (ocean.ships[y2][x2]->getShipType()!="empty")) {
            return false;
        }
    }
    return true;
}

void Ship::placeShipAt(int row, int column, bool horiz, Ocean& ocean){
    if (ocean.ships[row][column]!=NULL &&
        !okToPlaceShipAt(row,column,horiz,ocean))
        return;
    bowRow=row;
    bowColumn=column;
    horizontal=horiz;
    for (int i=0; i<length; i++){
        if (horizontal){
            ocean.ships[row][column+i]=this;
        } else {
            ocean.ships[row+i][column]=this;
        }
    }
}
