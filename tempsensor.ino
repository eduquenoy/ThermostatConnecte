/**
  @file tempsensor.ino
  @brief Implémentation de la 
  @class TempSensor
  @brief Gestion du capteur de température
*/


TempSensor::TempSensor(byte pin){ //! Constructeur avec initialisation de la broche
  this->pin = pin; 
}

float TempSensor::getTemperature(){//! Renvoie la valeur de température (°C) enregistrée dans la variable membre
  
  return(this->temperature);
}

void TempSensor::temperatureMeasurement(){//! Effectue une mesure sur le capteur et l'enregistre dans la variable membre
  int a;
  float resistance, temperature;
  a=analogRead(pin);//Lecture de l'entrée analogique
  resistance=(float)(1023-a)*10000/a; //get the resistance of the sensor;
  this->temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;//convert to temperature via datasheet ;
}
byte TempSensor::getTemperature10(){//! Renvoie une valeur de température (°C) x10 pour faciliter la comparaison avec la consigne 
  
  return(byte(this->temperature * 10));
}

  