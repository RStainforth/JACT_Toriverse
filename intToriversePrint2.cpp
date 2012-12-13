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
  cout << "\n\n";
  cout << "Welcome Player...to the Toriverse!" << endl;
  cout << endl;
  cout << "Map Loaded is: ";
  vector<char> cmdVec;
  
  char str[80];
  strcpy (str,argv[1]);
  strcat (str,".map");
  puts (str);
  Toriverse testTori(str);
  Harvester testHarvey(str);

  testTori.printMap();


  testHarvey.positionInMap(testTori);


  
  while(testHarvey.getStatus()){
    char cmd;
    cout << "\n" << endl;
    cout << "Please Enter your Command: " << endl;
    cin >> cmd;
    testHarvey.HarvesterCMD(testTori, cmd);
    cout << endl;
    testTori.Interaction(testHarvey);
    cout << endl;
    if (testHarvey.getStatus()){
      cmdVec.push_back(cmd);
      testHarvey.positionInMap(testTori);
      testHarvey.getCharacterH(testTori);
    }
  }
  cout << endl;
  cout << "END OF GAME" << endl;
  cout << endl;
  cout << "Your fate is: " << testHarvey.getFate() << endl;
  //cout <<"Energy is: " << testHarvey.getEnergy() << endl;
  //cout <<"LifeTime is: " << testTori.getLifeTime() << endl;
  cout << "Your Score is: " << testHarvey.getScore() << endl;

  char str1[80];
  strcpy(str1,argv[1]);
  strcat(str1,".hpg");
  //cout << endl;
  //cout << "Path written to: ";
  //puts (str1);

  if (testHarvey.getScore() != 0){
    cmdVec.push_back('e');
  	char str1[80];
  	strcpy(str1,argv[1]);
  	strcat(str1,".hpg");
  	cout << endl;
  	cout << "Successful path written to: ";
  	puts (str1);
  	ofstream outfile (str1);
  	for (int k =0; k < cmdVec.size(); k++){
    		outfile << cmdVec[k];
  	}
  	outfile.close();
  }
  cout << endl;
  cout << "Thank you for playing!" << endl;
  cout << endl;
  return 0;
}
