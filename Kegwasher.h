

struct kegs {
  bool keg1;
  bool keg2;
  bool keg3;
  bool keg4;
};

struct memoryMap {
  byte upper_temp; // 0-255 Degrees C
  byte range_temp; // 0-255 Degrees C
  byte min_wash_temp; // 0-255 Degrees C
  unsigned int min_air_press; // 0-65535 kPa
  unsigned int max_air_press; // 0-65535 kPa
  unsigned int min_co2_press; // 0-65535 kPa
  unsigned int max_co2_press; // 0-65535 kPa
  unsigned int min_water_press; // 0-65535 kPa
  unsigned int max_water_press; // 0-65535 kPa
};

struct pressureData {
  unsigned int water;
  unsigned int air;
  unsigned int co2;
};