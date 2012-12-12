
#include "Toriverse.h"
#include "Harvester.h"
#include <iostream>

using namespace std;

int main(){
  cout << "Welcome Player...to the Toriverse!" << endl;
  Toriverse testTori("2dmap.map");
  Harvester testHarvey("2dmap.map");

  cout << testHarvey.modH(-2,5) << endl;
  cout << testHarvey.modH(2,5) << endl;

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
  
  
  








