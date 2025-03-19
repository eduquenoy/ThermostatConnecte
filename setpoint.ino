/** 
  @file setpoint.ino
  @brief Implémentation de la gestion de la consigne
  
  @details La consigne est exprimée en °Cx10 pour éviter d'utiliser un flottant. Comme elle est stocké sur un byte, elle ne peut être négative et la température de consigne n'excède pas 25,5 
  
  @class SetPoint
  @brief Gestion de la consigne
*/

SetPoint::SetPoint(){//! Constructeur avec valeur initiale prédéfinie
  this->setPointValue = INITIAL_SETPOINT;
}
SetPoint::SetPoint(byte value){//! Constructeur avec valeur initiale fournie à l'appel
  this->setPointValue = value;
}
byte SetPoint::getValue(){//! Renvoie la valeur de consigne
  return(setPointValue);
}
void SetPoint::setValue(byte value){//! Fixe la valeur de consigne
  this->setPointValue = value;
}

void SetPoint::setValueIncrease(byte value){//! Incrémente la consigne (quand on appuie sur le BP correspondant)
  if(this->setPointValue < MAX_SETPOINT - value){
      this->setPointValue += value;
  }
}
void SetPoint::setValueDecrease(byte value){//! Décrémente la consigne (quand on appuie sur le BP correspondant)
  if(this->setPointValue > MIN_SETPOINT + value ){
      this->setPointValue -= value;
  }
}