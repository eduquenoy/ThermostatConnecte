/**
 * @file Thermostat_v0.ino
 * @brief Programme principal
 *
 * @version Version 0
 *
 * @mainpage Gestion d'un thermostat connecté pour chaudière fioul
 *
 *  \~french @details  
  - \~french Il s'agit de réaliser, à l'aide d'un Arduino Uno Wifi Rev2, un thermostat pour chaudière avec connexion internet.
  - \~french La première phase du projet ressemble à une "preuve de concept" (_proof of concept_ ou POC) : mise en place des éléments (boutons, lcd, led simulant le relai de la chaudière, liaison internet par Wifi, ...) 
  
  \~english @details 
  - \~english Using an Arduino Uno Wifi Rev2, the aim is to create a boiler thermostat with an internet connection. 
  -  \~english The first phase of the project resembles a “proof of concept” (POC): setting up the components (buttons, lcd, led simulating the boiler relay, internet connection via Wifi, etc.). 
  \~

 * @todo 
 * - gestion et affichage de l'heure
 * - connexion internet
 * - programmation des phases allumage/extinction de la chaudière
 *
 * @subsection documentation Documentation
 * - Test LCD. Documentation : https://gcworks.fr/tutoriel/arduino/AfficheurLCDRGB.html 

 * @author Eric DUQUENOY
 * @date 15 mars 2025.
 *
 * @copyright  <a property="dct:title" rel="cc:attributionURL" href="https://eric.duquenoy.org">Thermostat connecté avec Arduino</a> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://eric.duquenoy.org">Eric DUQUENOY</a> is licensed under <a href="https://creativecommons.org/licenses/by-nc/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC BY-NC 4.0<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/nc.svg?ref=chooser-v1" alt=""></a> 
 
 */

#include "inclusions.h"          //! L'ensemble des constantes et inclusions de bibliothèques
#define TIMER1_INTERVAL_MS 5000  //! Intervalle de temps la mesure de température par interruption

/** 
 * Objets utilisés 
*/
LcdScreen ecranLCD;                      //!< Gestion de l'écran
Button button1(PIN_BUTTONS, false);      //!< Gestion bouton 1 (en mode interruptif)
Button button2(PIN_BUTTONS + 1, false);  //!< Gestion bouton 2 (en mode interruptif)
TempSensor temperature(PIN_SENSOR);      //!< Gestion capteur température
SetPoint setpoint;                       //!< Gestion consigne
Control regulation(PIN_LED, false);      //!< Régulation de la "chaudière" (une LED pour le moment). Initialisation à 0 de la partie opérative et de sa broche

/***  ***/
unsigned long lightOn;

/*** ***/


void setup() {         //! Initialisations diverses
  Serial.begin(9600);  //! Lancement console
  Serial.println("Démarrage");

  /*! Gestion des interruptions des boutons */
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTONS), ISR1, FALLING);      /*! Gestion du bouton 1 par interruption */
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTONS + 1), ISR2, FALLING);  //! Gestion du bouton 2 par interruption

  // Lancement du timer (mesures de température à intervalles réguliers)
  ITimer1.init();
  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1)) {
    Serial.println("Starting  ITimer1 OK, millis() = " + String(millis()));
  } else {
    Serial.println("Can't set ITimer1. Select another freq. or timer");
  }

  //Initialisation de l'écran LCD
  ecranLCD.begin(16, 2, INITIAL_LIGHT);  //Initialise l'écran LCD (2 lignes de 16 caractères)

  pinMode(PIN_LED, OUTPUT);


  ecranLCD.setCursor(0, 0);
  ecranLCD.print("Demarrage !");

  temperature.temperatureMeasurement();  //Une première mesure pour ne pas démarrer à zéro !
  delay(200);
}

void loop() {
  if (millis() > LIGHT_ON_DURATION + lightOn) { ecranLCD.switchOff(); }  //Délai extinction écran

  /*** Etat des boutons ***/

  //Les deux boutons en même temps (à voir...)
  //if(button1.getState() && button2.getState()){Serial.println("Coup double !!!");}

  //Bouton 1
  if (button1.getState()) {
    if (ecranLCD.getState()) {  //Si l'écran est déjà allumé, on fait l'action
      setpoint.setValueIncrease(5);
    } else {
      ecranLCD.switchOn();  //Allumer l'écran
    }
    lightOn = millis();       //Réinitialiser la temporisation d'allumage de l'écran
    button1.setState(false);  //Réinitialiser le bouton
  }

  //Bouton2
  if (button2.getState()) {
    if (ecranLCD.getState()) {
      setpoint.setValueDecrease(5);
    } else {
      ecranLCD.switchOn();  //Allumer l'écran
    }
    lightOn = millis();       //Réinitialiser la temporisation d'allumage de l'écran
    button2.setState(false);  //Réinitialiser le bouton
  }

  /*** Lecture température et affichage ***/

  ecranLCD.setCursor(0, 0);
  ecranLCD.print("Consigne : ");
  ecranLCD.print(float(setpoint.getValue() / 10.0), 1);
  ecranLCD.write((unsigned char)0);

  ecranLCD.setCursor(0, 1);
  ecranLCD.print("Temp. : ");
  ecranLCD.print(temperature.getTemperature(), 1);
  ecranLCD.write((unsigned char)0);

  /*** Régulation ***/
  regulation.comparison(temperature.getTemperature10(), setpoint.getValue());
  regulation.order();

  delay(500);

  ecranLCD.clear();
}

void TimerHandler1() {
  //Effectuer une mesure de temperature
  temperature.temperatureMeasurement();
}

void ISR1() {

  //noInterrupts();
  button1.setState(true);  //On mémorise l'état du bouton
  //for(int i=0;i<10;i++){delayMicroseconds(16383);}//Anti-rebonds
  //interrupts();
}
void ISR2() {

  //noInterrupts();
  button2.setState(true);
  //for(int i=0;i<10;i++){delayMicroseconds(16383);}
  //interrupts();
}
