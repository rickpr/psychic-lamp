#include "data.h"
#define FORWARD 2000
#define REVERSE 1000
#define STOPPED 1520

int check_time() {
  return (2 * hour() + (minute() >= 30 ? 0.5 : 0)) - 11;
}

int seek_position(double angle, bool forward) {
}

