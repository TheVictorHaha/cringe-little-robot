#include <math.h>

class motor {
  public:
    int positionOffset;
    int port;

    motor(int port_, int positionOffset_){
      port = port_;
      positionOffset = positionOffset_;
    }

    void setSpeed(double speed){

    }

    double SPEED_COEFFECIENT = 1;
    void update(double angleReading, double angleInput, double inputSpeed, double throttle){
      double currAngle = angleReading + positionOffset;
      currAngle = fmod(currAngle, 360.0);
      double reading = currAngle - angleInput + (currAngle - angleInput < 0 ? 360 : 0);
      double modifier = reading < 180 ? 1 : -1;
      setSpeed(throttle + modifier * inputSpeed * SPEED_COEFFECIENT);
    }
};

double fwdAngle = 0;

void setup() {
  // put your setup code here, to run once:
  fwdAngle = 0;
}

int TRANSLATION_X_PIN;
int TRANSLATION_Y_PIN;
int THROTTLE_PIN;
int ANCHOR_CHANGE_PIN;

void loop() {
  // put your main code here, to run repeatedly:
  updateSensors();
  updateDeltaTime();
  takeInput(analogRead(TRANSLATION_X_PIN), analogRead(TRANSLATION_Y_PIN), analogRead(THROTTLE_PIN), analogRead(ANCHOR_CHANGE_PIN));
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

motor leftMotor(1, -90);
motor rightMotor(2, 90);

void takeInput(double translationX, double translationY, double throttle, double anchorChange){
  changeFwdAngle(anchorChange);

  double angle;
  if(translationX != 0){
    angle = atan(translationY / translationX) + (translationX < 0 ? 180 : 0);
  } else {
    angle = translationY > 0 ? 0 : 180;
  }

  angle += fwdAngle;
  if(angle < 0) angle += 360;


  //Change input coming from square of possible x and y into circle of possible velocities
  double translationSpeed = translationY > translationX ? translationY : translationX;

  leftMotor.update(gyroAngle, angle, translationSpeed, throttle);
  rightMotor.update(gyroAngle, angle, translationSpeed, throttle);

}


