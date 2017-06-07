double calibrate_start(Adafruit_LSM303_Accel_Unified accel) {
  reverse(32000);
  return get_phi(accel, 10, 10000);
}

double calibrate_end(Adafruit_LSM303_Accel_Unified accel) {
  forward(32000);
  return get_phi(accel, 10, 10000);
}
