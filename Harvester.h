// Prevents the toriverse header file being included more than once
#ifndef HARVESTER_h
#define HARVESTER_h

#include "Toriverse.h"
#include <string>

using namespace std;

class Toriverse;

class Harvester {

public:

  // Constructors and destructors
  Harvester();
  Harvester(char* filename);
  ~Harvester();

  // Setters ...
  void setXPos(int val) {xPos = val;}
  void setYPos(int val) {yPos = val;}
  void setEnergy(int val) {Energy += val;}
  void setScore(int val) {Score = val;}
  void setStatus(bool val) {HStatus = val;}
  void setFate(string fate) {HFate = fate;}

  // Getters ...

  int getXPos() const {return xPos;}
  int getYPos() const {return yPos;}
  int getXMom() {return xMom;}
  int getYMom() {return yMom;}
  int getEnergy() {return Energy;}
  int getScore() {return Score;}
  string getFate() {return HFate;}
  bool getStatus() {return HStatus;}

  // Command function
  void HarvesterCMD(Toriverse& T, char cmd);
  int xPos;
  int yPos;
  int xMom;
  int yMom;

protected:


  int Energy;
  int Score;
  bool HStatus;
  string HFate;

};

#endif
