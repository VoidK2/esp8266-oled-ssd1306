#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

String indate ="";
String val="";
//indate规定格式cpu?mem?time
//time规定格式%m%d%H%M
void setup(){
  Serial.begin(115200);
  // initialize with the I2C addr 0x3C (for the 128x64)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  test();
}
void loop(){
  uint8_t color=WHITE;
  while(Serial.available()>0){
    indate+=char(Serial.read());
    delay(2);
    if(Serial.available()<=0){
      Serial.println(indate);
    }
  }
  if(indate.length()>0){
    val=indate;

    display.clearDisplay();
    Serial.println("display:"+val);
    // Serial.println("width:"+display.width());
    // Serial.println("height:"+display.height());
    
    //cpu
    int cpuP=val.substring(0,2).toInt();
    display.drawRect(1,1,100,20,color);
    display.fillRect(1,1,cpuP,20,color%2);
    display.setTextSize(2);
    display.setTextColor(color);
    display.setCursor(102,1);
    display.println(val.substring(0,2));
    //mem
    int memP=val.substring(3,5).toInt();
    display.drawRect(1,25,100,20,color);
    display.fillRect(1,25,memP,20,color%2);
    display.setTextSize(2);
    display.setTextColor(color);
    display.setCursor(102,25);
    display.println(val.substring(3,5));
    //time
    display.setTextSize(2);
    display.setTextColor(color);
    display.setCursor(1,47);
    display.println(val.substring(6));
    //统一显示
    display.display();
    delay(200);
  }
  indate="";

}
void test(){
  display.drawPixel(10,20,WHITE);
  display.display();
  display.clearDisplay();
  delay(2000);
  display.drawRect(1,1,20,20,WHITE);
  display.display();
}
// Content-Type: text/html
// String stringOne = "Content-Type: text/html";
// if (stringOne.substring(19) == "html") {
//     Serial.println("It's an html file"); 
// } 
// if (stringOne.substring(14,18) == "text") {
//     Serial.println("It's a text-based file"); 
// }
//display.write("a"); 写字符
//display.drawPixel 写像素
//display.println("aaaa"); 写字符串
// display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
// display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
