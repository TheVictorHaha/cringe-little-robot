#include <math.h>

double anchorAngle = 0;

void setup() {
  // put your setup code here, to run once:
  anchorAngle = 0;
}


void loop() {
  // put your main code here, to run repeatedly:

}

void setSpeeds(double leftMotor, double rightMotor){

}

void changeAnchorAngle(){

}

double angle;
double angularSpeed;

void updateSensors(){

}

void move(double targetAngle, double translationSpeed, double angularSpeed){

}

void takeInput(double translationX, double translationY, double throttle, double anchorChange){
  double angle = tan(translationY / translationX);
  // double scaledX = translationX * sqrt(1 - translationY * translationY / 2);
  // double scaledY = translationY * sqrt(1 - translationX * translationX / 2);

  //DO THIS SOME OTHER TIME :)
  double small = sqrt(translationX * translationX + translationY * translationY);
  double large = small / translationY;
  double scaledY;

  double xSpeed = throttle;
  double ySpeed = throttle;
}

void pulseMotors(double translationPower, double spinPower, double targetAngle){
  double motor1Pos;
  double motor2Pos;
}

