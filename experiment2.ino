#include <M5Core2.h>

#define IN_PIN_0 19
#define OUT_PIN_0 27

bool state = false;
bool output0 = LOW;
String serial_data = "";

void monitor_serial_port(String data){
 M5.Lcd.fillRect(205, 52, 115, 18, WHITE);
 M5.Lcd.setTextFont(2);
 M5.Lcd.setCursor(210, 53);
 M5.Lcd.setTextColor(BLACK);
 M5.Lcd.print(data);
 Serial.println(data);
}


void setup(){
 M5.begin();
 Serial.begin(9600);
 Serial2.begin(9600);


 pinMode(IN_PIN_0, INPUT_PULLUP);

 pinMode(OUT_PIN_0, OUTPUT);
 digitalWrite(OUT_PIN_0, LOW);

 M5.Lcd.fillScreen(BLACK);
 M5.Lcd.setTextSize(1);
 M5.Lcd.setTextFont(4);

 M5.Lcd.drawFastHLine(0, 0, 320, WHITE);
 M5.Lcd.fillRect(0, 1, 320, 27, 0x098a);
 M5.Lcd.drawFastHLine(0, 29, 320, WHITE);
 M5.Lcd.setTextColor(WHITE);
 M5.Lcd.drawCentreString("Enjoy M5Stack ", 120, 4, 4);
 M5.Lcd.drawRightString("T220G054", 300, 2, 2);
 M5.Lcd.drawRightString("Kaneko Yuna", 310, 14, 2);

 M5.Lcd.drawFastVLine(202, 29, 43, WHITE);
 M5.Lcd.drawFastHLine(0, 72, 320, WHITE);
 M5.Lcd.drawCircle(10, 51, 9, WHITE);

 M5.Lcd.setTextFont(2);
 M5.Lcd.setCursor(212, 34);
 M5.Lcd.print("SERIAL MONITOR");
 M5.Lcd.fillRect(205, 52, 115, 18, WHITE);


 M5.Lcd.setTextFont(2);
 M5.Lcd.setCursor(225, 221);
 M5.Lcd.print("ON/OFF");
}

void loop(){
 M5.update();

 if (M5.BtnC.isPressed()){
  M5.Lcd.fillRect(218, 217, 64, 21, BLUE);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextFont(2);
  M5.Lcd.setCursor(225, 221);
  M5.Lcd.print("ON/OFF");
 }else{
  M5.Lcd.fillRect(218, 217, 64, 21, BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextFont(2);
  M5.Lcd.setCursor(225, 221);
  M5.Lcd.print("ON/OFF");
 }

 if((M5.BtnC.isPressed() == true || digitalRead(IN_PIN_0) == LOW) && state == false) {
  state = true;
  output0 = !output0;
  digitalWrite(OUT_PIN_0, output0);
}
 if(M5.BtnC.isReleased() == true && digitalRead(IN_PIN_0) == HIGH) {
  state = false;
}

if (Serial.available()) {
  serial_data = Serial.readStringUntil('\n');
  monitor_serial_port(serial_data);
}

if (Serial2.available()){
  serial_data = Serial2.readStringUntil('\n');
  monitor_serial_port(serial_data);

}


 M5.Lcd.setTextFont(4);
 M5.Lcd.setCursor(26, 42);
 if (output0 == LOW){
  M5.Lcd.setTextColor(CYAN, BLACK);
  M5.Lcd.printf("OUTPUT : OFF");
  M5.Lcd.fillCircle(10, 51, 8, BLACK);
} else {
  M5.Lcd.setTextColor(ORANGE, BLACK);
  M5.Lcd.printf("OUTPUT : ON");
  M5.Lcd.fillCircle(10, 51, 8, ORANGE);
}
delay(100);
}
