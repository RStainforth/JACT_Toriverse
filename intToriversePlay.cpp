#include "Toriverse.h"
#include "Harvester.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

class string;
using namespace std;

int main( int argc, char** argv ){
  //start with ./'name' 'mapname'
  cout << "Welcome Player...to the Toriverse!" << endl;
  vector<char> cmdVec;
  
  char str[80];
  strcpy (str,argv[1]);
  strcat (str,".map");
  puts (str);
  Toriverse testTori(str);
  Harvester testHarvey(str);

  while(testHarvey.getStatus()){
    char cmd;
    cout << "Please Enter your Command: " << endl;
    cin >> cmd;
    testHarvey.HarvesterCMD(testTori, cmd);
    testTori.Interaction(testHarvey);
    cmdVec.push_back(cmd);

    for (int i = testTori.getYDim()-1; i >= 0; i--){
      for (int j = 0; j < testTori.getXDim()-1; j++){
  if (i == testHarvey.getYPos() && j == testHarvey.getXPos()){
	  cout << "X";
	}
	else{
	  cout << testTori.getObject(j,i);
	}
      }
      cout << endl;
    }
    cout <<"XPos is: " <<  testHarvey.getXPos() << endl;
    cout <<"YPos is: " <<  testHarvey.getYPos() << endl;
    cout <<"XMom is: " <<  testHarvey.getXMom() << endl;
    cout <<"YMom is: " <<  testHarvey.getYMom() << endl;
    cout <<"Energy is: " << testHarvey.getEnergy() << endl;
  }

  cout << "Your fate is: " << testHarvey.getFate() << endl;
  cout << "Your Score is: " << testHarvey.getScore() << endl;
  char str1[80];
  strcpy(str1,argv[1]);
  strcat(str1,"_PATH.hpg");
  puts (str1);
  ofstream outfile (str1);
  for (int k =0; k < cmdVec.size(); k++){
    cout << cmdVec[k];
    outfile << cmdVec[k];
  }
  outfile.close();
  cout << endl;
  return 0;
}
