#ifndef OCEAN_H
#define OCEAN_H
//do not edit this file!
const int SIDES=10;//jim add
class Ocean{
private:
    int shotsFired;
    int hitCount;
    int shipsSunk;
    static int totalShips; //jim add
public:
    vector<vector<Ship*>> ships;
    Ocean();
    ~Ocean();
    int getRando(int max=SIDES); //jim add
    void placeOneShipRandomly(Ship* ship); //jim add
    void placeAllShipsRandomly();
    bool isOccupied(int row, int column);
    bool shootAt(int row, int column);
    int getShotsFired();
    int getHitCount();
    int getShipsSunk();
    bool isGameOver();
    void print();

};
#endif