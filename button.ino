/**
 @file button.ino
 @brief Implémentation des fonctions de gestion de bouton
*/



Button::Button(byte pin){ //!< Constructeur avec paramètre de broche
  this->pinNumber = pin;  //!< Initialisation de la broche
  pinMode(this->pinNumber,INPUT);
  this->state = false;
}

Button::Button(byte pin, bool state){//!< Constructeur avec paramètres de broche et d'état
  this->pinNumber = pin; 
  pinMode(this->pinNumber,INPUT);
  this->state = state;
}

bool Button::getState(){
  return(state);
}
void Button::setState(bool state){
  this->state = state;
}
