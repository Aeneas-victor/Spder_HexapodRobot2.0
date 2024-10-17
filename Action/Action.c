
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : Action.c
  * @brief          : 运动规则函数文件
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024-aeneas
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE BEGIN Header */

#include "stm32f4xx.h"                  // Device header
#include "common.h"
#include "string.h"
#include "Delay.h"
#include "Serial.h"
#include "RobotServoController.h"
#include "Action.h"

uint16_t SPEED=SPEED_HIGH;
uint16_t* Robot_Posture=Robot_Posture_Begin;
const uint8_t Robot_ModuleArray[18]=
{
	rear_Left_joint,rear_Left_leg,rear_Left_foot,
	middle_Left_joint,middle_Left_leg,middle_Left_foot,
	front_Left_joint,front_Left_leg,front_Left_foot,
	
	rear_Right_joint,rear_Right_leg,rear_Right_foot,
	middle_Right_joint,middle_Right_leg,middle_Right_foot,
	front_Right_joint,front_Right_leg,front_Right_foot
};

uint16_t Robot_Low_Start[18]=
{
	522,321,//1，2
	206,
	525,351,//4，5
	255,
	487,359,//7，8
	191,
	500,663,//10，11
	805,
	499,706,//13，14
	808,
	483,662,//16，17
	793
};
uint16_t Robot_Posture_Begin[18]={522,321,206,525,351,255,487,359,191,500,663,805,499,706,808,483,662,793};

uint8_t RobotjointArray[6]=//joint enum array
{
	rear_Left_joint,middle_Left_joint,front_Left_joint,
	rear_Right_joint,middle_Right_joint,front_Right_joint
};

int16_t Rotation_Param[6]=//rotation param
{
	80,80,80,80,80,80
};

uint8_t TriangleAdvanceLeft_Module[6]=//triangle advance left module
{
	rear_Left_joint,rear_Left_leg,middle_Right_joint,middle_Right_leg,front_Left_joint,front_Left_leg
};

uint8_t Left_rear_Move_Module[3]=//left rear move module 
{
	rear_Left_joint,middle_Right_joint,front_Left_joint
};

uint8_t Left_rear_LegMove_Module[3]=//left rear leg move module
{
	rear_Left_leg,middle_Right_leg,front_Left_leg
};

int16_t LRM_Param[3] ={80,-80,80 };
int16_t LFM_Param[3] ={-80,80,-80};
int16_t RRM_Param[3] ={-80,80,-80};
int16_t RFM_Param[3] ={80,-80,80};
int16_t Universal_Param[3]={0,0,0};
int16_t ALU_Param[6]=//advance left up param
{
	-30,-60,60,60,-30,-60
};

int16_t RLU_Param[6]=//rear left up param
{
	30,-60,-60,60,30,-60
};

int16_t ALD_Param[6]=//advance left down param
{
	60,0,-60,0,60,0
};

uint8_t TriangleAdvanceRight_Module[6]=//triangle advance right module
{
	rear_Right_joint,rear_Right_leg,middle_Left_joint,middle_Left_leg,front_Right_joint,front_Right_leg
};

uint8_t Right_rear_Move_Module[3]=//right rear move module
{
	rear_Right_joint,middle_Left_joint,front_Right_joint
};

uint8_t Right_rear_LegMove_Module[3]=//right rear leg move module 
{
	rear_Right_leg,middle_Left_leg,front_Right_leg
};

int16_t ARU_Param[6]=//advance right up param
{
	30,60,-60,-60,30,60
};

int16_t RRU_Param[6]=//rear right up param
{
	-30,60,60,-60,-30,60
};

int16_t ARD_Param[6]=//advance right down param
{
	-60,0,60,0,-60,0
};

/**
  * @brief  Robot_Low_Action
  * @param  void
  * @retval  none
  */

void Robot_Action(void)
{
	for(uint8_t i=0;i<18;i++)
	{
		MoveServo(i+1,Robot_Posture_Begin[i],SPEED);
	}
}

/**
  * @brief  move function
* @param  Robot_Module:零部件枚举数组
* @param  Angle:移动角度数组
* @param  AttitudeMode: 舵机姿态模式
* @param number:移动舵机个数
  * @retval  none
  */

void _Move_Robot(uint8_t* Robot_Module,uint16_t* AttitudeMode,int16_t*Angle,uint8_t number,uint16_t Time)
{
	for(uint8_t i=0;i<number;i++)
	{
		MoveServo(Robot_Module[i],(uint16_t)(AttitudeMode[Robot_Module[i]-1]+Angle[i]),Time);
	}
}

/**
  * @brief  Move advance code
  * @param  void
  * @retval  none
  */

void Move_Advance(void)
{	
	_Move_Robot(TriangleAdvanceLeft_Module,Robot_Posture,ALU_Param,6,SPEED);//left leg up
	Delay_Ms(SPEED+2);
	_Move_Robot(Right_rear_Move_Module,Robot_Posture,RRM_Param,3,SPEED);
	Delay_Ms(SPEED);
	_Move_Robot(Left_rear_LegMove_Module,Robot_Posture,Universal_Param,3,SPEED);
	_Move_Robot(TriangleAdvanceRight_Module,Robot_Posture,ARU_Param,6,SPEED);
	Delay_Ms(SPEED+2);
	_Move_Robot(Left_rear_Move_Module,Robot_Posture,LRM_Param,3,SPEED);
	Delay_Ms(SPEED);
	_Move_Robot(Right_rear_LegMove_Module,Robot_Posture,Universal_Param,3,SPEED);
	Delay_Ms(20);
}
/**
  * @brief  move Retreat function
  * @param  void
  * @retval  none
  */

void Move_Retreat(void)
{
	
	_Move_Robot(TriangleAdvanceLeft_Module,Robot_Posture,RLU_Param,6,SPEED);
	Delay_Ms(SPEED+2);
	_Move_Robot(Right_rear_Move_Module,Robot_Posture,RFM_Param,3,SPEED);
	Delay_Ms(SPEED);
	_Move_Robot(Left_rear_LegMove_Module,Robot_Posture,Universal_Param,3,SPEED);
	_Move_Robot(TriangleAdvanceRight_Module,Robot_Posture, RRU_Param,6,SPEED);
	Delay_Ms(SPEED+2);
	_Move_Robot(Left_rear_Move_Module,Robot_Posture, LFM_Param,3,SPEED);
	Delay_Ms(SPEED);
	_Move_Robot(Right_rear_LegMove_Module,Robot_Posture,Universal_Param,3,SPEED);
	Delay_Ms(20);
	
}

/**
  * @brief  move turn lrft function
  * @param  void
  * @retval  none
  */

void Move_Left_Turn(void)
{
	_Move_Robot(TriangleAdvanceLeft_Module,Robot_Posture,)
}

/**
  * @brief  move turn right function
  * @param  void
  * @retval  none
  */
void Move_Right_Turn(void)
{
	
}
/**
  * @brief  side move left
  * @param  void
  * @retval  none
  */
void Move_Side_Left(void)
{
	
}

/**
  * @brief  side move right
  * @param  void
  * @retval  none
  */
void Move_Side_Right(void)
{
	
}

/**
  * @brief  move rotation function
  * @param  void
  * @retval  none
  */
void Move_Rotation(void)
{
	_Move_Robot(RobotjointArray,Robot_Posture,Rotation_Param,6,200);
	Delay_Ms(202);
	for(uint8_t i=0;i<6;i++)
	{
		Rotation_Param[i]=-Rotation_Param[i];
	}
	Delay_Ms(200);
	_Move_Robot(RobotjointArray,Robot_Posture,Rotation_Param,6,200);
	Delay_Ms(202);
	for(uint8_t i=0;i<6;i++)
	{
		Rotation_Param[i]=-Rotation_Param[i];
	}
	Delay_Ms(200);
}
void Set_Posture_High(void){
	for(uint8_t i=1;i<19;i++)
	{
		if(i==2||i==5||i==3||i==6||i==8||i==9){Robot_Posture_Begin[i-1]=Robot_Low_Start[i-1]+180;}
		else if(i==11||i==12||i==14||i==15||i==17||i==18){Robot_Posture_Begin[i-1]=Robot_Low_Start[i-1]-180;}
		else continue;
	}
	Move_Stop();
	Delay_Ms(200);
}
void Set_Posture_Midium(void){
	for(uint8_t i=1;i<19;i++)
	{
		if(i==2||i==5||i==3||i==6||i==8||i==9){Robot_Posture_Begin[i-1]=Robot_Low_Start[i-1]+100;}
		else if(i==11||i==12||i==14||i==15||i==17||i==18){Robot_Posture_Begin[i-1]=Robot_Low_Start[i-1]-100;}
		else continue;
	}
	Move_Stop();
	Delay_Ms(200);
}
void Set_Posture_Low(void){
	for(uint8_t i=0;i<18;i++)
	{Robot_Posture_Begin[i]=Robot_Low_Start[i];}
	Move_Stop();Delay_Ms(200);
}		
void Set_Speed_High(void){SPEED=SPEED_HIGH;}
void Set_Speed_Midium(void){SPEED=SPEED_MIDIUM;}
void Set_Speed_Low(void){SPEED=SPEED_LOW;}
/**
  * @brief  move stop
  * @param  void
  * @retval none
  */
void Move_Stop(void)
{
	Delay_Ms(200);
	Robot_Action();
}














