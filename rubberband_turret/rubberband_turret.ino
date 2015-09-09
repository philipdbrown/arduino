#include <Servo.h>
#include <Wire.h>
#include "nunchuck_funcs.h"

int loopCnt = 0;

Servo LR; //servo for Left-Right movement
Servo UD; //servo for Up-Down movement
Servo bang; //servo for shooting rubber bands

byte accX, accY, joyX, joyY, zbut, cbut;

void setup() {
  LR.attach(9);
  UD.attach(10);
  bang.attach(8);
  
  Serial.begin(19200);
  nunchuck_setpowerpins();
  nunchuck_init();
  Serial.print("WiiChuck: Let's Do This!!!\n");
  delay(100);
}

void loop() {
  if(loopCnt > 200) {
    loopCnt = 0;
    
    nunchuck_get_data();
    
    zbut = nunchuck_zbutton();
    cbut = nunchuck_cbutton();
    joyX = nunchuck_joyx();
    joyY = nunchuck_joyy();
    accX = nunchuck_accelx();
    accY = nunchuck_accely();
    
    
    /**
    *  RIGHT & LEFT
    **/
    //int horiz = map(joyX, 23, 230, 102, 78);
    int horiz = map(joyX, 23, 230, 50, 130);
    if (abs(horiz - 90) <= 2) {
      horiz = 90;
    }
    else if (horiz > 90) {
      horiz -= 2;
    }
    else if (horiz < 90) {
      horiz += 2;
    }
    Serial.print("\thoriz:  "); Serial.println(horiz,DEC);
    LR.write(horiz);
    
    
    /**
    * UP & DOWN
    **/
    int vert = map(joyY, 28, 231, 110, 70); //makes it so there is a small area in the middle where the joystick won't actuate anything (Y direction)
    if (abs(vert - 90) <= 2) {
      vert = 90;
    }
    else if (vert > 90) {
      vert -= 2;
    }
    else if (vert < 90) {
      vert += 2;
    }
    Serial.print("\tvert:  "); Serial.println(vert,DEC);
    UD.write(vert);
    
    /**
    * SHOOT
    **/
    int shoot = 90; //creates shooting servo value

    if ((zbut == 0) && (cbut != 0)) { 
      shoot = 60;
    }

    if ((cbut == 0) && (zbut != 0)) {
       shoot = 150;
    }
    Serial.print("\tshoot: "); Serial.println(shoot,DEC);
    bang.write(shoot);
  }
  loopCnt++;
}
