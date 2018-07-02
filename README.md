# esp8266-oled-ssd1306

>替代任务管理器

下位机烧入的程序（对indate信息进行解析，显示）

```c
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
		
		
		int cpuP=(val.substring(0,1)-'0')*10+(val.substring(1,2)-'0');
		display.drawRect(1,1,100,20,color);
		display.fillRect(1,1,cpuP,20,color%2);
		display.setTextSize(2);
		display.setTextColor(color);
		display.setCursor(102,1);
		display.println(val.substring(0,2));
		//cpu

		int memP=(val.substring(3,4)-'0')*10+(val.substring(4,5)-'0');
		display.drawRect(1,25,100,20,color);
		display.fillRect(1,25,val.substring(3,5),20,color%2);
		display.setTextSize(2);
		display.setTextColor(color);
		display.setCursor(102,25);
		display.println(val.substring(3,5));
		//mem

		display.setTextSize(1);
		display.setTextColor(color);
		display.setCursor(1,47);
		display.println(val.substring(6));
		//time

		display.display();
		delay(200);
		//统一显示

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
/*Content-Type: text/html
String stringOne = "Content-Type: text/html";
if (stringOne.substring(19) == "html") {
    Serial.println("It's an html file"); 
} 
if (stringOne.substring(14,18) == "text") {
    Serial.println("It's a text-based file"); 
}
display.write("a"); 写字符
display.drawPixel 写像素
display.println("aaaa"); 写字符串
display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);*/
```

上位机调用python的若干个库

```py
#!/usr/bin/env python
# coding:utf-8
import serial
import time
import psutil

ser=serial.Serial("COM3",115200,timeout=1)

def GetMemorystate():
	phymem=psutil.virtual_memory()
	string=int(int(phymem.used/1024/1024)/int(phymem.total/1024/1024)*100)
	string=str(string)
	return (string)

def GetCPUstate():
	cpuP=psutil.cpu_percent(0.2,False)
	cpuP='%02d'%(cpuP)
	return (cpuP)
def GetTime():
	string=time.strftime('%m%d %H:%M',time.localtime(time.time()))
	return (string)

while (1):
	aimsP=str(GetCPUstate()+'?'+GetMemorystate()+'?'+GetTime())
	print ('上位机输出：',aimsP)
	aimsF=str.encode(aimsP)
	ser.write(aimsF)
	time.sleep(1)

```

最终效果
![img](https://upload.cc/i1/2018/07/02/8DHI1r.jpg)
