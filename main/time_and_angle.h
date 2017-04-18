#include "data.h"
void update_time(int current_increment) {
  long now = DateTime.now();
  float decimal_now = numberOfHours(now) + numberOfMinutes(now) / 60;
  if(decimal_now - half_hours[current_increment] > 0.25)
    current_increment++;
}
