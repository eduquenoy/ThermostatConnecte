/**
  @file control.ino 
  @brief Gestion de la régulation de température

  @class Control 
  @brief Gère la régulation en tout-ou-rien. L'état est stocké dans une variable membre. 
*/
Control::Control(byte pin,bool itemValue){
  this->item = itemValue;
  this->pin = pin;
}
void Control::order(){/** Lance ou arrête la partie opérative */
  if(item){
    digitalWrite(pin,HIGH);
  }
  else{
    digitalWrite(pin,LOW);  
  }
}
void Control::comparison(byte temperature, byte setpoint){//! Régulation avec une valeur d'hysteresis prédéfinie

  if(temperature < setpoint - HYSTERESIS){setState(true);}
  else{
    if(temperature > setpoint + HYSTERESIS){
      setState(false);}
    }
}
bool Control::setState(bool state){//! Fixe l'état du controle : marche/arrêt (tout-ou-rien)
  item = state;
  return(item);
}
bool Control::getState(){//! Renvoie l'état du controle
  return(item);
}
