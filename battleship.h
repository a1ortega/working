#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

//int main();
class Ship {
public:
    int health[5];
    string chunk[5];
    int length;
    Ship(int shipNumber, string position, int l, string orientation);
    bool shoot(string coord);
    bool isAlive();
};

class map {
public:
    map();
    const static int size = 10;     // Size won't ever change
    char mapArray[size][size];
    void printMap(map *player1ships, map *player1guesses);
    bool hitCheck(map *guessMap, int coordinate[]);
    bool guessCheck(int coordinate[]);
    void placeShip(Ship *ship, map *shipMap, char counter);
};

class Player {
public:
    Ship* ship1;
    Ship* ship2;
    Ship* ship3;
    Ship* ship4;
    Ship* ship5;
    string name;
    int getGuessX();
    int getGuessY();
    string getName();
    Ship* createShip(int shipNumber, int length, map* map);

};

bool intersectionCheck(string position, string orientation, int length, map *map);
bool boundaryCheck(string position, string orientation, int length);
void printMap(map *player1ships, map *player1guesses);
void placeShip(Ship *ship, map *shipMap, char counter);
