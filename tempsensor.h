/**
* @file tempsensor.h
* 
* @brief Mesure de la température
* @details 
  - on renvoie une valeur en °C
  - une variable menbre stocke la température
*/



#ifndef __TEMPSENSOR_H__
#define __TEMPSENSOR_H__

const int B=3975;                  //B value of the thermistor

class TempSensor {
public:
  TempSensor(byte);//Constructeur
  float getValue();//Renvoie la valeur de température en degrés °C (en faisant une mesure)
  float getTemperature(); //Renvoie la temperature (sans faire de mesure)
  void temperatureMeasurement(); //Effectue une mesure 
  byte getTemperature10();
private:
  byte pin;
  float temperature;
};


#endif