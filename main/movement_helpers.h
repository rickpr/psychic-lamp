//#include <Servo.h>
#define FORWARD 1000
#define REVERSE 2000
#define STOPPED 1520

Servo myservo;
void stop() {
  myservo.writeMicroseconds(STOPPED);
}

void forward(long long int microseconds) {
  myservo.writeMicroseconds(FORWARD);
  delay(microseconds);
  stop();
}

void reverse(long long int microseconds) {
  myservo.writeMicroseconds(REVERSE);
  delay(microseconds);
  stop();
}
