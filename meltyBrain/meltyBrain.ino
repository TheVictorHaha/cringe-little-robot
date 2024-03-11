#include <math.h>

bool test = true;

class motor {
  public:
    int positionOffset;
    int port;

    motor(int port_, int positionOffset_){
      port = port_;
      positionOffset = positionOffset_;
    }

    void setSpeed(double speed){
      //TBI
    }

    double SPEED_COEFFECIENT = 1;
    int update(double angleReading, double angleInput, double inputSpeed, double throttle){
      double currAngle = angleReading + positionOffset;
      currAngle = fmod(currAngle, 360.0);
      double reading = currAngle - angleInput + (currAngle - angleInput < 0 ? 360 : 0);
      double modifier = reading < 180 ? 1 : -1;
      int speed = throttle + modifier * inputSpeed * SPEED_COEFFECIENT;
      if(test){
        return speed;
      } else {
        setSpeed();
      }
    }
};

double fwdAngle = 0;

void setup() {
  // put your setup code here, to run once:
  fwdAngle = 0;
}

//needs values
int TRANSLATION_X_PIN;
int TRANSLATION_Y_PIN;
int THROTTLE_PIN;
int ANCHOR_CHANGE_PIN;

int inputY = 0;
int inputX = 0;
int simAngle = 0;
bool testPrint = false;
int testThrottle = 0;

char printBuffer[128];

void loop() {
  // put your main code here, to run repeatedly:
  updateSensors();
  updateDeltaTime();

  if(test){
    
    if(newData){
      switch(receivedChar){
        case 'u':
          inputY = 1;
          testThrottle = 1;
        break;

        case 'd':
          inputY = -1;
          testThrottle = 1;
        break;

        case 'l':
          inputX = -1;
          testThrottle = 1;
        break;

        case 'r':
          inputX = 1;
          testThrottle = 1;
        break;

        case 'x':
          inputX = 0;
          inputY = 0;
          testThrottle = 0;
        break;

        case '1':
          simAngle += 45;
        break;

        case '2':
          simAngle -= 45;
        break;

        case 'p':
          sprintf(printBuffer, "X: %d, Y: %d, ANGLE: %d\n", inputX, inputY, simAngle);
          Serial.print(printBuffer);
        break;

        case 'P':
          testPrint = !testPrint;
        break;
      }
      takeInput(inputX, inputY, testThrottle, 0);
    }
  } else {
    takeInput(analogRead(TRANSLATION_X_PIN), analogRead(TRANSLATION_Y_PIN), analogRead(THROTTLE_PIN), analogRead(ANCHOR_CHANGE_PIN));
  }
}

char receivedChar;
bool newData = false;
void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        newData = true;
    }
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
  //TBI
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

  int lSpeed = leftMotor.update(gyroAngle, angle, translationSpeed, throttle);
  int rSpeed = rightMotor.update(gyroAngle, angle, translationSpeed, throttle);
  if(test){
    if(testPrint){
      sprintf(printBuffer, "L: %d, R: %d\n", lSpeed, rSpeed);
      Serial.print(printBuffer);
    }
  }

}


