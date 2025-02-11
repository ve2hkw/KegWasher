#include "pinmap.h"
#include "Kegwasher.h"
#include <LiquidCrystal_PCF8574.h>
#include <Adafruit_ADS1X15.h>
#include <EEPROM.h>

Adafruit_ADS1115 ads;

void setup() {
  ads.begin();
  pinMode(CAUSTIC_LEVEL_SWITCH, INPUT);
  pinMode(ACID_LEVEL_SWITCH, INPUT);
  pinMode(KEG_SENSOR_1, INPUT);
  pinMode(KEG_SENSOR_2, INPUT);
  pinMode(KEG_SENSOR_3, INPUT);
  pinMode(KEG_SENSOR_4, INPUT);
  pinMode(CYCLE_START_BUTTON, INPUT);
  pinMode(HEATER_SWITCH, INPUT);


}

void loop() {
  

}

void wash() {

}

bool inputCheck(int input_number) { 
  if (digitalRead(input_number) == LOW){
    return true;
  }
  else {
    return false;
  }
} // end of input check

bool pressureCheck() {
  memoryMap memory = getEEPROMValues();
  pressureData current_pressure = pressureGet();
  bool water_good;
  bool air_good;
  bool co2_good;
  if (current_pressure.air > memory.min_air_press && current_pressure.air < memory.max_air_press){
    air_good = true;
  }
  else air_good = false;
  if (current_pressure.water > memory.min_water_press && current_pressure.water < memory.max_water_press){
    water_good = true;
  }
  else water_good = false;
  if (current_pressure.co2 > memory.min_co2_press && current_pressure.co2 < memory.max_co2_press){
    co2_good = true;
  }
  else co2_good = false;

  if (water_good && air_good && co2_good){
    return true;
  }
  else return false;
} //end of Pressure checking

pressureData pressureGet() {
  pressureData pressures;
  unsigned int water_raw, air_raw, co2_raw;
  water_raw = ads.readADC_SingleEnded(WATER_PRESSURE);
  air_raw   = ads.readADC_SingleEnded(AIR_PRESSURE);
  co2_raw   = ads.readADC_SingleEnded(CO2_PRESSURE);
  pressures.water = map(water_raw, 2666, 24000, 0, 690); // 690 kPa (100 PSI) sensor, output is .5v to 4.5v
  pressures.air = map(air_raw, 2666, 24000, 0, 1034); // 1034 kPa (150 PSI) sensor
  pressures.co2 = map(co2_raw, 2666, 24000, 0, 1034); // 1034 kPa (150 PSI) sensor
  return pressures;
} // end of pressure data retrieval

kegs numberOfKegsCheck() {
  kegs good_kegs;
  good_kegs.keg1 = inputCheck(KEG_SENSOR_1);
  good_kegs.keg2 = inputCheck(KEG_SENSOR_2);
  good_kegs.keg3 = inputCheck(KEG_SENSOR_3);
  good_kegs.keg4 = inputCheck(KEG_SENSOR_4);
  return good_kegs;
}

void resetEEPROMDefaults() {
  // Restore the values of the EEPROM memory to a default set
  // All temperatures are in C and all pressures are in kPa
  memoryMap memory;
  memory.upper_temp = 70;
  memory.range_temp = 5;
  memory.min_wash_temp = 60;
  memory.max_air_press = 350;
  memory.min_air_press = 250;
  memory.max_co2_press = 350;
  memory.min_co2_press = 250;
  memory.max_water_press = 350;
  memory.min_water_press = 200;

  EEPROM.put(0, memory);

}

memoryMap getEEPROMValues() {
  memoryMap memory;
  EEPROM.get(0, memory);
  return memory;
}

void emergencyPowerKill() {

}