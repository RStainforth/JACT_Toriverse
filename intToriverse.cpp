

#include "Toriverse.h"
#include <iostream>

using namespace std;

int main(){
  Toriverse testTori("toriverse_test.map");
  cout << "X Dim is: " << testTori.getXDim() << endl;
  cout << "Y Dim is: " << testTori.getYDim() << endl;
  cout << "LifeTime is: " << testTori.getLifeTime() << endl;
  cout << "Energy Density is: " << testTori.getEnergyDensity() << endl;
  cout << "Status is: " << testTori.getStatus() << endl;

  cout<< "Object at (0,0): " << testTori.getObject(0,0) << endl;
  for(int y=0;y<testTori.getYDim();y++){
    for(int x=0;x<testTori.getXDim();x++){
      cout<<testTori.getObject(x,testTori.getYDim()-y-1);
    }
    cout << endl;
  }
  
  //testTori.setObject("@",7,0);
  cout << "NEW UNIVERSE" << endl;

  for(int y=0;y<testTori.getYDim();y++){
    for(int x=0;x<testTori.getXDim();x++){
      cout<<testTori.getObject(x,testTori.getYDim()-y-1);
    }
    cout << endl;
  }

  cout << "Number of SubSpace Locks is: " << testTori.getNSLocks() << endl;
  cout << "Position of wormhole b is: " <<testTori.getWHolePos(1,0,0) << ","<< testTori.getWHolePos(1,0,1) << "||" << testTori.getWHolePos(1,1,0) << ","<< testTori.getWHolePos(1,1,1) << endl;
  return 0;
}
  








