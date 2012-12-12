// Prevents the toriverse header file being included more than once
#ifndef TORIVERSE_h
#define TORIVERSE_h

#include "Harvester.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Harvester;

class Toriverse {

public:

  // Constructors and destructors
  Toriverse();
  Toriverse(char* filename);
  ~Toriverse();

  void Interaction(Harvester& Harvey);
  
  // Setters...
  void setObject(string Obj, int xPos, int yPos){Map[xPos][yPos] = Obj;}
  void timeStep(){
    lifeTime--;
    cout << "Lifetime is: " << lifeTime << endl;
  }

  //  Getters ...

  //char getObject(int xPos, int yPos); 
  int getXDim() const {return xDim;}
  int getYDim() const {return yDim;}
  int getLifeTime() {return lifeTime;}
  int getEnergyDensity() {return energyDensity;}
  int getStatus() {return status;}
  int getNSLocks() {return nSLocks;}
  int getWHolePos(int letter, int a, int b){
    return WHoles[letter][a][b];
  }
    
  
  
  string getObject(int xPos, int yPos) {
  return Map[xPos][yPos];
  }

protected:

  int xDim;
  int yDim;
  int lifeTime;
  int energyDensity;
  int status;
  int nSLocks;
  std::vector<std::vector<std::string> >  Map;
  std::vector<std::vector<std::vector<int> > > WHoles;


};

#endif
