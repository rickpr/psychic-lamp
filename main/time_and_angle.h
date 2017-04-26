#include "data.h"
int check_time(int current_increment) {
  float decimal_now = hour() + minute() / 60;
  return decimal_now - half_hours[current_increment] > 0.25 ? 0 : 1;
}
