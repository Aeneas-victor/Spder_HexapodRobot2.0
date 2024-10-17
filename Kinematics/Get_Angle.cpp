#include<stdio.h>
#include <math.h>
#include "Action.h"
#include "stm32f4xx.h"                  // Device header
#include "common.h"
#include "string.h"
#include "Delay.h"
#include "Serial.h"
#include "RobotServoController.h"
#include "Get_Angle.h"
#include "OLED.h"
#define MY_PI 3.14159
float get_angle1(float x,float y,float z)
{
	double angle;
	angle=atan2(y,x);
	return angle;
}

float get_angle2(float x,float y,float z)
{
	float data= CROTCH-sqrt(pow(x,2)+pow(y,2)) ; 
	float a = (pow(LEG,2.f)-pow(FOOT,2.f)+pow(data,2.f)+pow(z,2.f) )/(2*LEG*sqrt( pow(data,2.f) +pow(z,2.f)));
	float b = z/data;
	float angle = acos(a)-atan(b);
	return angle;
}

float get_angle3(float x,float y,float z)
{
	float data= CROTCH-sqrt(pow(x,2)+pow(y,2)) ; 
	float a = (pow(LEG,2.f)-pow(FOOT,2.f)+pow(data,2.f)+pow(z,2.f) )/(2*LEG*sqrt( pow(data,2.f) +pow(z,2.f)));
	float b = (pow(FOOT,2.f)-pow(LEG,2.f)+pow(data,2.f)+pow(z,2.f) )/(2*FOOT*sqrt( pow(data,2.f) +pow(z,2.f)));
	
	float angle=-acos(a)-acos(b);
	
	return angle;
}
 
 
//正运动学结算 
float get_x(float angle1,float angle2,float angle3)
{
	return cos(angle1)*( CROTCH+FOOT*cos(angle2+angle3)+LEG*cos(angle2) );
}
 
float get_y(float angle1,float angle2,float angle3)
{
	return sin(angle1)*(CROTCH+FOOT*cos(angle2+angle3)+LEG*cos(angle2));
}
 
float get_z(float angle1,float angle2,float angle3)
{
	return FOOT*sin(angle2+angle3)+LEG*sin(angle2);
}
 
void test(void)
{
	uint16_t Angle1,Angle2,Angle3;
	Angle1=get_angle1(100,100,-80)*500/MY_PI;
	Angle2=get_angle2(100,100,-80)*500/MY_PI;
	Angle3=get_angle3(100,100,-80)*500/MY_PI;
	MoveServo(front_Right_joint,Robot_Posture_Begin[15]+Angle1,200);
	MoveServo(front_Right_leg,Robot_Posture_Begin[16]+Angle2,200);
	MoveServo(front_Right_foot,Robot_Posture_Begin[17]+Angle3,200);
	OLED_ShowNum(1,1,Angle1,8);
	OLED_ShowNum(2,1,Angle2,8);
	OLED_ShowNum(3,1,Angle3,8);
	
}
