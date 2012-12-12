
#include "Toriverse.h"
#include "Harvester.h"
#include <iostream>

using namespace std;

int main(){
  cout << "Welcome Player...to the Toriverse!" << endl;
  Toriverse testTori("toriverse_01_01001.map");
  Harvester testHarvey("toriverse_01_01001.map");


  while(testHarvey.getStatus()){
    char cmd;
    cout << "Please Enter your Command: " << endl;
    cin >> cmd;
    testHarvey.HarvesterCMD(testTori, cmd);
    testTori.Interaction(testHarvey);
  }

  cout << testHarvey.getFate() << endl;
  cout << "Your Score is: " << testHarvey.getScore() << endl;
  return 0;
}
  
  
  








