/**
* @file lcdscreen.h
* 
* @brief Gestion de l'afficheur LCD
* @details 
  - actuellement, on ne gère que le rétro-éclairage pas sa couleur
  - 
*/

#ifndef __LCDSCREEN_H__
#define __LCDSCREEN_H__

#include <Wire.h>
#include <rgb_lcd.h>

#define INITIAL_LIGHT 50
#define REST_LIGHT 0
#define ALERT_LIGHT 250
#define LIGHT_ON_DURATION 7000 //Durée (en milli-secondes) d'allumage de l'écran après appui sur bouton ou redémarrage

/**
* \~french \class LcdScreen 
  \brief Gestion de l'écran LCD. 
  \details 
 - Héritée de rgb_lcd, on y ajoute quelques fonctions simplificatrices :
  + setBackLight() qui permet de fixer l'intensité de la luminosité de l'afficheur (lumière blanche)
  + switchOn() et switchOff() qui permettent d'"eteindre" ou d'"allumer" l'éclairage de l'afficheur
 
 \~english 

 @class LcdScreen 

 \brief for LCD screen management. 

 \details 
 Inherited from rgb_lcd, we've added a few simplifying functions:
 - setBackLight(), which sets the brightness of the display (white light)
 - switchOn() and switchOff() to “turn off” or “turn on” display lighting
*/
class LcdScreen : public rgb_lcd {
  public:
  LcdScreen(); //constructor
  void begin(byte, byte, byte); //(nombre caractères, nombre lignes, rétro-éclairage)
  void setBackLight(byte);
  bool getState();
  void switchOn();//Allume l'éclairage
  void switchOff();
  private:
  bool state;//Etat d'allumage de l'écran
  byte currentLight;
  byte degree[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
  };

};
#endif