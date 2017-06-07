void calibrate_start() {
  reverse(32000);
  // return atan(sqrt(x * x + y * y) / z);
}

void calibrate_end() {
  forward(32000);
}
