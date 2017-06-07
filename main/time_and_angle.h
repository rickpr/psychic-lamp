#include "data.h"

int check_time() {
  return (2 * hour() + (minute() >= 30 ? 0.5 : 0)) - 11;
}

double vectors_to_phi(double x, double y, double z) {
  return atan(sqrt(x * x + y * y) / z);
}

double vectors_to_theta(double x, double y, double z) {
  return atan(y / x);
}

double vectors_to_rho(double x, double y, double z) {
  return sqrt(x * x + y * y + z * z);
}

int seek_position(double angle, bool forward) {
}

