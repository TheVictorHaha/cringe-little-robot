#include <math.h>

double fwdAngle = 0;

void setup() {
  // put your setup code here, to run once:
  fwdAngle = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

}

void setSpeeds(double leftMotor, double rightMotor){

}

double deltaTime = 0;
double oldTime = 0;
void updateDeltaTime(){
  double currTime = millis();
  deltaTime = currTime - oldTime;
  oldTime = currTime;
}

double changeScaler = 1;
void changeFwdAngle(double changeRate){
  fwdAngle += changeRate * changeScaler * deltaTime;
}

double gyroAngle;
double angularSpeed;

void updateSensors(){
  double gyroOffset = 0;// work this into the angle calculation
  gyroAngle += gyroOffset;
}

void move(double targetAngle, double translationSpeed, double angularSpeed){

}

void takeInput(double translationX, double translationY, double throttle, double anchorChange){
  double angle = atan(translationY / translationX);

  //Change input coming from square of possible x and y into circle of possible velocities
  double translationSpeed = translationY > translationX ? translationY : translationX;

  double xSpeed = throttle;
  double ySpeed = throttle;
}

void pulseMotors(double translationPower, double spinPower, double targetAngle){
  double motor1Pos = 90;
  double motor2Pos = 270;
  motor1Pos += gyroAngle;
  motor2Pos += gyroAngle;
  
  double angleBound = 

}
