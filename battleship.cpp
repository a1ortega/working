//
//  battleship.cpp
//  battle_ship_1
//
//  Created by Evan Waxman on 4/8/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#ifndef map_h
#define map_h

#include "battleship.h"
using namespace std;

int main() {
    map player1ships;
    map player2ships;
    map player1guesses;
    map player2guesses;

    Player player1;
    Player player2;

    int sizeArray[5] = {2, 3, 3, 4, 5};

    for(int i=1; i<6; i++) {
        player1.createShip(i, sizeArray[i-1], &player1ships);
        printMap(&player1ships, &player1guesses);
    }

    for(int i=1; i<6; i++) {
        player2.createShip(i, sizeArray[i-1], &player2ships);
        printMap(&player2ships, &player2guesses);
    }

/*
    Ship ship1(1,"D5", 5, "right");
    placeShip(&ship1, &player1ships, '1');
    printMap(&player1ships, &player1guesses);
 */
    return 0;
}

  ////////////////////
 /// PLAYER CLASS ///
////////////////////

Ship* Player::createShip(int shipNumber, int length, map* map) {
    cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: D7): "<< endl;
    string position;
    cin >> position;

    while(position.length() > 2 || position.length() < 2) {
        cout << "Incorrect Coordinate Input" << endl;

        cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: D7): "<< endl;
        cin >> position;
    }

    //Coordinate check

    cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
    string orientation;
    cin >> orientation;

    while(orientation != "right" && orientation != "left" && orientation != "up" && orientation != "down") {
        cout << "Incorrect Orientation Input" << endl;

        cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
        cin >> orientation;
    }

    while(intersectionCheck(position, orientation, length, map) || boundaryCheck(position, orientation, length)){
        cout << "Incorrect Placement" << endl;

        cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: D7): "<< endl;
        cin >> position;

        while(position.length() > 2 || position.length() < 2) {
            cout << "Incorrect Coordinate Input" << endl;

            cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: D7): "<< endl;
            cin >> position;
        }

        //Coordinate check

        cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
        cin >> orientation;

        while(orientation != "right" && orientation != "left" && orientation != "up" && orientation != "down") {
            cout << "Incorrect Orientation Input" << endl;

            cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
            cin >> orientation;
        }

    }

    Ship* ship = new Ship(shipNumber, position, length, orientation);
    placeShip(ship, map, shipNumber);

    return ship;
}

bool boundaryCheck(string position, string orientation, int length) {
    int coordinate[2];
    char column, row;

    column = position.at(0);
    row = position.at(1);

    coordinate[1] = toupper(column) - 0x41;   // First argument must be a char A-J. Subtract
    // 0x41 to get int value for array indexing.
    // Refer to ASCII table.
    coordinate[0] = row - 0x30;    // Second argument must be a char 1-10. Subtract
    // 0x31 to get int value for array indexing.
    // Refer to ASCII table.


    if(orientation == "left")
    {
        if ((coordinate[1] - length) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(orientation == "right")
    {
        if ((coordinate[1] + length) > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(orientation == "up")
    {
        if ((coordinate[0] - length) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(orientation == "down")
    {
        if ((coordinate[0] + length) > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }else {
        return true;
    }
}

bool intersectionCheck(string position, string orientation, int length, map *map) {
    int coordinate[2];
    char column, row;

    column = position.at(0);
    row = position.at(1);

    coordinate[1] = toupper(column) - 0x41;   // First argument must be a char A-J. Subtract
    // 0x41 to get int value for array indexing.
    // Refer to ASCII table.
    coordinate[0] = row - 0x30;    // Second argument must be a char 1-10. Subtract
    // 0x31 to get int value for array indexing.
    // Refer to ASCII table.

    for(int i=0; i<length; i++) {
        if(map->mapArray[coordinate[0]][coordinate[1]] != '~') {
            return true;
        }
        coordinate[1]++;
    }
    return false;
}

int Player::getGuessX() {
    cout << "Enter your guess for the x coordinate: " << endl;
    int x;
    cin >> x;

    return x;
}

int Player::getGuessY() {

    cout << "Enter your guess for the y coordinate: " << endl;
    int y;
    cin >> y;

    return y;
}

string Player::getName() {

    cout << "Enter your name: " << endl;
    string name;
    cin >> name;

    return name;
}

  ////////////////////
 ///   MAP CLASS  ///
////////////////////

// Constructor for map object
map::map() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mapArray[i][j] = '~';       // Default map element value is ~
        }
    }
}

// Checks if coordinate was already guessed
bool map::guessCheck(int coordinate[]) {
    if(mapArray[coordinate[0]][coordinate[1]] == 'X' || mapArray[coordinate[0]][coordinate[1]] == 'O') {    // Only other values for guess map
        return 1;
    }else {
        return 0;
    }
}

// Checks if ship was hit
bool map::hitCheck(map *guessMap, int coordinate[2]) {
    if(mapArray[coordinate[0]][coordinate[1]] == '~'){
        guessMap->mapArray[coordinate[0]][coordinate[1]] = 'O';     // Update guess map
        return 0;
    }else {
        guessMap->mapArray[coordinate[0]][coordinate[1]] = 'X';     // Update guess map
        return 1;
    }
}

// Print mapArray of map
void printMap(map *player1ships, map *player1guesses) {
    cout << "   ------P1 Ships-----  -----P1 Guess------" << endl;
    cout << "   A B C D E F G H I J  A B C D E F G H I J" << endl;

    char row_count = '0';
    for (int i = 0; i < player1guesses->size; i++) {
        cout << row_count << "  ";
        for (int j = 0; j < player1guesses->size; j++) {
            cout << player1ships->mapArray[i][j] << " " ;
        }
        cout << " ";
        for(int j=0; j< player1guesses->size; j++){
            cout << player1guesses->mapArray[i][j]<< " ";
        }
        cout << endl;
        row_count++;
    }
}

void placeShip(Ship *ship, map *shipMap, char counter) {
    int coordinate[2];
    for(int i=0; i<ship->length; i++) {
        coordinate[1] = toupper(ship->chunk[i].at(0)) - 0x41;   // First argument must be a char A-J. Subtract
                                                                // 0x41 to get int value for array indexing.
                                                                // Refer to ASCII table.
        coordinate[0] = ship->chunk[i].at(1) - 0x30;    // Second argument must be a char 1-10. Subtract
                                                        // 0x31 to get int value for array indexing.
                                                        // Refer to ASCII table.
        shipMap->mapArray[coordinate[0]][coordinate[1]] = counter + 0x30;
    }
}

  ////////////////////
 ///  SHIP CLASS  ///
////////////////////

Ship::Ship(int shipNumber, string position, int l, string orientation)
{
    //Sets the length and initial chunk variable (first position) equal to the respective parameters
    length = l;
    chunk[0] = position;

    //Condition of if the orientation of the ship is to be up
    if(orientation.compare("up") == 0)
    {
      //Increments the ship upwards
      char number = position.at(1);
      for(int i = 1; i < length; i++)
      {
        number--;
        chunk[i] = string(1,position.at(0)) + number;
      }
    }

    //Condition of if the orientation of the ship is to be down
    if(orientation.compare("down") == 0)
    {
      //Increments the ship downwards
      char number = position.at(1);
      for(int i = 1; i < length; i++)
      {
        number++;
        chunk[i] = string(1,position.at(0)) + number;
      }
    }

    //Condition of if the orientation of the ship is to be right
    if(orientation.compare("right") == 0)
    {
      //Increments the ship to the right
      char number = position.at(0);
      for(int i = 1; i < length; i++)
      {
        number++;
        chunk[i] = number + string(1,position.at(1));
      }
    }

    //Condition of if the orientation of the ship is to be left
    if(orientation.compare("left") == 0)
    {
      //Increments the ship to the left
      char number = position.at(0);
      for(int i = 1; i < length; i++)
      {
        number--;
        chunk[i] = number + string(1,position.at(1));
      }
    }

    //Fills the health array with values equal to the corresponding ship nuber
    for(int i = 0; i < length; i++)
    {
      health[i] = shipNumber;
    }
}

//Method that attempts to shoot a ship at a given coordinate
bool Ship::shoot(string coord)
{
    //Searches through the all of the ship coordinates of the class
    for(int i = 0; i < length; i++)
    {
      //Compares the coordinates that are being shot with those of where the ship is located
      if(coord.compare(chunk[i]) && health[i] != 0)
      {
        //Health of ship at that point is set to 0 (essentially a dead variable)
        health[i] = 0;
        return true;
      }
    }
    return false;
}

//Statement to see if the ship is still alive
bool Ship::isAlive()
{
    //Sets a count variable
    int count = 0;
    for(int i = 0; i < length; i++)
    {
      //Compounds the count variable based on the values of the health index at that point
      count += health[i];
    }

    //After all of the compounding, if the count variable is equal to 0, the ship is confirmed to not be alive
    if(count == 0)
      return false;

    //It's alive
    else
      return true;
}

#endif
