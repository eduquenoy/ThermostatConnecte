


#ifndef __BUTTON_H__
#define __BUTTON_H__

/**
 @file button.h
 @brief \~french Gestion des boutons poussoirs \~english Push button processing \~
* \~french \class Button 
  \brief Gestion de boutons poussoirs. 
  \details 
  - Ils fonctionnent en mode interruptif, c'est donc l'interruption qui fixe l'état
  - deux constructeurs : 
   + l'un avec un paramètre : numéro de broche. L'état initial est fixé à zéro.
   + l'autre avec deux paramètres : numéro de broche et état initial
  - géré essentiellement en mode interruptif.
 
 \~english 
 @class Button 

 \brief Push-button management 

 \details 
 - essentially managed in interruptive mode.

\~
*/

class Button {
  public:
  Button(byte); //!< \~french constructeur avec parametre Pin
  Button(byte,bool); //!< \~french const. avec parametres Pin et état initial
  bool getState(); //!< \~french Renvoie l'état du bouton
  void setState(bool); //!< \~french Fixe l'état du bouton
  private:
  byte pinNumber; //!< Numéro de broche du bouton
  bool state; //!< Etat du bouton
};


#endif
