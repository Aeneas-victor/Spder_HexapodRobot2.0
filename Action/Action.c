
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

uint8_t RobotjointArray[6]=//joint enum array
{
	rear_Left_joint,middle_Left_joint,front_Left_joint,
	rear_Right_joint,middle_Right_joint,front_Right_joint
};

int16_t Rotation_Param[6];
uint8_t TriangleAdvanceLeft_Module[6]=
{
	rear_Left_joint,rear_Left_leg,middle_Right_joint,middle_Right_leg,front_Left_joint,front_Left_leg
};

int16_t ALU_Param[6]=
{
	-30,-60,60,60,-30,-60
};

int16_t ALD_Param[6]=
{
	60,0,-60,0,60,0
};

uint8_t TriangleAdvanceRight_Module[6]=
{
	rear_Right_joint,rear_Right_leg,middle_Left_joint,middle_Left_leg,front_Right_joint,front_Right_leg
};

int16_t ARU_Param[6]=
{
	30,60,-60,-60,30,60
};

int16_t ARD_Param[6]=
{
	-60,0,60,0,-60,0
};

/**
  * @brief  Robot_Low_Action
  * @param  void
  * @retval  none
  */

void Robot_Low_Action(void)
{
	for(uint8_t i=0;i<18;i++)
	{
		MoveServo(i+1,Robot_Low_Start[i],200);
	}
}

/**
  * @brief  move function
* @param  Robot_Module:零部件枚举数组
* @param  Angle:移动角度数组
* @param number:移动舵机个数
  * @retval  none
  */

void _Move_Robot(uint8_t* Robot_Module,int16_t*Angle)
{
	for(uint8_t i=0;i<6;i++)
	{
		MoveServo(Robot_Module[i],(uint16_t)(Robot_Low_Start[Robot_Module[i]-1]+Angle[i]),400);
	}
}

/**
  * @brief  Move advance code
  * @param  void
  * @retval  none
  */


void Move_Advance(void)
{
	_Move_Robot(TriangleAdvanceLeft_Module,ALU_Param);
	Delay_Ms(500);
	_Move_Robot(TriangleAdvanceLeft_Module,ALD_Param);
	Delay_Ms(300);
	_Move_Robot(TriangleAdvanceRight_Module,ARU_Param);
	Delay_Ms(500);
	_Move_Robot(TriangleAdvanceRight_Module,ARD_Param);
	Delay_Ms(300);
}

void Move_Rotation(void)
{
	for(uint8_t i=0;i<6;i++)
	{
		Rotation_Param[i]=40;
	}
	_Move_Robot(RobotjointArray,Rotation_Param);
}

