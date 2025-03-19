/**
* @file setpoint.h
* 
* @brief Gestion de la consigne
* @details 
  - la consigne est géré avec un byte plutôt qu'un float. La raison est d'économiser la mémoire. Pour obtenir une précision, on stocke la température de consigne multipliée par 10.
*/

#ifndef __SETPOINT_H__
#define __SETPOINT_H__

#define INITIAL_SETPOINT 200 //Température de consigne *10
#define MAX_SETPOINT 255
#define MIN_SETPOINT 0

class SetPoint { //Gestion de la consigne
public:
  SetPoint();//Constructeur
  SetPoint(byte);//Constructeur avec paramètre de valeur de consigne
  byte getValue();
  void setValue(byte);
  void setValueIncrease(byte);
  void setValueDecrease(byte);
private:
  byte setPointValue;
};


#endif