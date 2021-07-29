#include "Adafruit_LC709203F.h"

Adafruit_LC709203F lc;

void setup() {
  /* **********************README********************************************************************
   *  The number in Serial.begin() is called "baud rate." It is a number you will need later to type into
   *   PLX DAQ software.
   ************************README**********************************************************************/
  Serial.begin(115200);
  delay(10);
  Serial.println("\nAdafruit LC709a203F demo");

  if (!lc.begin()) {
    Serial.println(F("Couldnt find Adafruit LC709203F?\nMake sure a battery is plugged in!"));
    while (1) delay(10);
  }
  Serial.println(F("Found LC709203F"));
  Serial.print("Version: 0x"); Serial.println(lc.getICversion(), HEX);
  
  /* **********************README********************************************************************
   *  With different battery, you will have to change the value of MAH
   *   eg: if you are using a 1200mAh battery, then change
   *   "LC709203F_APA_500MAH"  to "LC709203F_APA_1200MAH"
   *  You can normally find the value on the package that came with the battery or datasheet
   ************************README**********************************************************************/
  lc.setPackSize(LC709203F_APA_500MAH);

  lc.setAlarmVoltage(3.8);

  /* **********************README********************************************************************
   *  The next three line is for setting up the title in excel sheet
   *  
   *  CLEARDATA clears all previous data.
   *  
   *  Items after LABEL will be title for each column of your data. You can add whatever you want as long
   *   as you start the bracket with LABEL.However, Adafruit_LC709203F only can only detect voltage, 
   *   battery level, temperature of the batery pack if thermistor is available.
   *  
   *  RESETTIMER is for resetting timer since we have used the timer function.
   ************************README**********************************************************************/

  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time, Started Time, Battery Voltage, Battery Percentage");
  Serial.println("RESETTIMER");
}

void loop() {

    /* **********************README********************************************************************
    *   The next four line of code is to log data into excel sheet.
    *   
    *   Just like LABEL aforementioned, you have to start the bracket with DATA so that excel will know that
    *    you are about to log data in. TIME and TIMER are functions that came with PLX-DAQ, so they will be
    *    recognized even if they are in quotation marks. Notice how evey item in the first Serial.print() is 
    *    separated by a comma, that is how you do it if you want to add a new column of data. Also see how 
    *    Serial.print() and Serial.println are used differently. The use of  Serial.print() doesn't switch 
    *    to next line, whereas the use of Serial.println() switch to next line. Since battery level is the last
    *    column of data in a row, so we use Serial.println() to print lc.cellPercent() instead of Serial.print().
    *    
    *   So data logged into excel should look like:
    *   | time | timer | voltage | battery level (%)|
    *   | time | timer | voltage | battery level (%)|
    *   | time | timer | voltage | battery level (%)|
   ************************README**********************************************************************/
  Serial.print("DATA, TIME, TIMER,");
  Serial.print(lc.cellVoltage(), 3);
  Serial.print(",");
  Serial.println(lc.cellPercent(), 1);
 
  delay(2000);  // dont query too often!
  
}
