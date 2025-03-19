/** @file lcdScreen.ino 

  @brief Cette classe s'appuie sur la bibliothèque rgb_lcd.
Elle tente de simplifier la gestion de l'afficheur.

******************************/


LcdScreen::LcdScreen() : rgb_lcd(){}

void LcdScreen::begin(byte column, byte row, byte light){
  rgb_lcd::begin(column,row);
  setRGB(light, light, light);
  currentLight = light;
  createChar(0, degree);
}
void LcdScreen::switchOn(){ //! Allume le rétro-éclairage
  setBackLight(INITIAL_LIGHT);
  currentLight = INITIAL_LIGHT;
  state = true;
}
void LcdScreen::switchOff(){//! Eteint le rétro-éclairage
  setBackLight(REST_LIGHT);
  currentLight = REST_LIGHT;
  state = false;
}

void LcdScreen::setBackLight(byte light){//! Fixe l'intensité du rétro-éclairage (lumière blanche, pas de couleur dominante)
  setRGB(light, light, light);
  currentLight = light;
}
bool LcdScreen::getState(){//! Indique si le rétro-éclairage est allumé ou non
  return(state);
}
