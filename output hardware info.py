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
