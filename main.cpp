#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::cin;
#include "ships.h"
#include "ocean.h"

int main(){
    //create an ocean
    Ocean game01;
    cout << "ocean created" << endl;

    //place all ships randomly
    game01.placeAllShipsRandomly();
    cout << "placed ships" << endl;

    //while not done
    while(game01.isGameOver() == false){
        //ask user for i and j
        int iIn;
        int jIn;
        cout << "Enter i :";
        cin >> iIn;
        cout << endl;
        cout << "Enter j :";
        cin >> jIn;
        cout << endl;

        //shoot at ship
        game01.shootAt(iIn, jIn);
        //report results of shot
        if (game01.isOccupied(iIn, jIn) == false){
            cout << "Miss" << endl;    
        }
        else if(game01.isOccupied(iIn, jIn) == true){
        cout << "Hit" << endl;
        };
        //print ocean
        game01.print();
    //repeat
    };

    
    //end of game message

    return 0;
}
