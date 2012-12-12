#include "Toriverse.h"
#include "Harvester.h"
#include <iostream>

using namespace std;

int main( int argc, char** argv ){
  //start with ./'name' 'mapname'
  cout << "Welcome Player...to the Toriverse!" << endl;
  
  Toriverse testTori(argv[1]);
  Harvester testHarvey(argv[1]);int main( int argc, char** argv ){

  while(testHarvey.getStatus()){
    char cmd;
    cout << "Please Enter your Command: " << endl;
    cin >> cmd;
    testHarvey.HarvesterCMD(testTori, cmd);
    testTori.Interaction(testHarvey);

    cout <<"XPos is: " <<  testHarvey.getXPos() << endl;
    cout <<"YPos is: " <<  testHarvey.getYPos() << endl;
    cout <<"XMom is: " <<  testHarvey.getXMom() << endl;
    cout <<"YMom is: " <<  testHarvey.getYMom() << endl;
    cout <<"Energy is: " << testHarvey.getEnergy() << endl;
  }

  cout << testHarvey.getFate() << endl;
  cout << "Your Score is: " << testHarvey.getScore() << endl;
  return 0;
}
  
  
  








