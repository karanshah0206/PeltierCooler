

// count and print the number of found devices on tft 

void tftFoundDevices() {
   
  tft.setCursor(0,0);
  tft.fillScreen(ST7735_BLACK);
  // locate devices on the 1-wire bus
  tft.println("Locating devices");
  tft.print("Found ");
  tft.print(sensors.getDeviceCount(), DEC);
  tft.println(" devices.");

}


// initialize tft, black screen and landscape

void initTft() {

  // set tft_cs as putput
  pinMode(tft_cs, OUTPUT);

  // If your TFT's plastic wrap has a Black Tab, use the following:
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  // landscape
  tft.setRotation(3);
  // display is black
  tft.invertDisplay(false);

}


// write static text on tft

void writeStaticText() {

  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0,0);

  tft.print("Blue  :");
  tft.setCursor(90,0);
  tft.println("C");

  // sensor brown
  tft.print("Brown :");
  tft.setCursor(90,8);
  tft.println("C");

  // sensor water
  tft.print("Water :");
  tft.setCursor(90,16);
  tft.println("C");

}


// if the time has changed, print the current time on tft

void tftPrintTime() {
  static time_t tLast;
  
  t = now();
  if (t != tLast) {
    tLast = t;
    
    dateStringGenerator();
    
    tft.fillRect(0, 32, 126, 7, ST7735_BLACK);
    tft.setCursor(0,32);
    tft.println(dateString);
  }
} 


// print the currect temperatur values on tft
// but befor: print old time in black color, to vanisch the old data

void tftPrintTemp() {

  // sensor blue
  tft.setCursor(45,0);
  tft.setTextColor(ST7735_BLACK);
  tft.print(oldInputData.tempBlue);
  tft.setCursor(45,0);
  tft.setTextColor(ST7735_WHITE);
  tft.print(inputData.tempBlue);

  // sensor brown
  tft.setCursor(45,8);
  tft.setTextColor(ST7735_BLACK);
  tft.print(oldInputData.tempBrown);
  tft.setCursor(45,8);
  tft.setTextColor(ST7735_WHITE);
  tft.print(inputData.tempBrown);

  // sensor water
  tft.setCursor(45,16);
  tft.setTextColor(ST7735_BLACK);
  tft.print(oldInputData.tempWater);
  tft.setCursor(45,16);
  tft.setTextColor(ST7735_WHITE);
  tft.println(inputData.tempWater);

}
 
 
// print not found temperature sensors

void errorTempSensors(boolean errorBlue, boolean errorBrown, boolean errorWater) {
 tft.setCursor(0,24);
 if(errorBlue) tft.println("No blue termometer");
 if(errorBrown) tft.println("No brown termometer");
 if(errorWater) tft.println("No water termometer");

}


// in case data file coudn't be opened

void errorTempData() {
  tft.setCursor(0,48);
  tft.println("Error opening tempData.txt");
}


// print information about initialization of the sd-card

void tftPrintSDInfo(boolean errorInitSD) {
  
  tft.println("Initializing SD card...");
  
  if (errorInitSD) {
    tft.println("initialization failed!");
    while(true);
    return;
  }
  
  tft.println("initialization done.");
}
