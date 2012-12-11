// Prevents the toriverse header file being included more than once
#ifndef HARVESTER_h
#define HARVESTER_h

#include <string>

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

  // Getters ...

  int getXPos() const {return xPos;}
  int getYPos() const {return yPos;}
  int getXMom() {return xMom;}
  int getYMom() {return yMom;}
  int getEnergy() {return Energy;}
  int getScore() {return Score;}
  bool getStatus() {return HStatus;}

  // Command function
  void Command(char cmd);

protected:

  int xPos;
  int yPos;
  int xMom;
  int yMom;
  int Energy;
  int Score;
  bool HStatus;

};

#endif
