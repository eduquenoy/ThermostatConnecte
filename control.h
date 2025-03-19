/**
* @file control.h
* 
* @brief Régulation de température 
* @details 
  - Le système reçoit la consigne, la température mesurée et l'écart max (hystérésis)
*/

#ifndef __CONTROL_H__
#define __CONTROL_H__

#define HYSTERESIS 5 //Hysteresis = 0,5°


class Control{
public:
  Control(byte,bool);//Constructeur
  void comparison(byte , byte );
  void order();
  bool setState(bool);//Fixe l'état de la partie opérative
  bool getState();//Renvoie l'état de la partie opérative
private:
  bool item;
  byte pin;
};

#endif