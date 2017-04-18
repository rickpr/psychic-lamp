#include "data.h"
int check_time(int current_increment) {
  long now = DateTime.now();
  float decimal_now = numberOfHours(now) + numberOfMinutes(now) / 60;
  return decimal_now - half_hours[current_increment] > 0.25 ? 0 : 1;
}
