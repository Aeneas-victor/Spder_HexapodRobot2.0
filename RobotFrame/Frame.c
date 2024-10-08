/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : Frame.c
  * @brief          : 框架定义文件
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

#include "BlueSerial.h"
#include "Frame.h"
#include <string.h>
#include "Delay.h"
#include "Serial.h"
#include <stdio.h>
#include "RobotServoController.h"
#include "Action.h"
#include "OLED.h"

extern char Serial_RxPacket[100];//数据接收包
extern uint8_t Serial_RxFlag;//数据标志位
/**
  * @brief  HexapodRobot 初始化函数 包括模块的初始化函数
  * @param  Robot_Positure_Init   动作初始化函数，传入需要时初始化是表现得动作
  * @retval  none
  */
void HexapodRobot_Init(InitFunc Robot_Positure_Init)
{
	Delay_Init();
	Robot_Serial_Init();
	Robot_Positure_Init();
}
/**
  * @brief  框架入口函数
  * @param  none
  * @retval  none
  */
void FrameEntry()
{
	HexapodRobot_Init(Robot_Low_Action);
	while(1)
	{
		CtrlEntry(BluetoochMode);
	}
}
/**
  * @brief  控制模式入口函数
  * @param  传入控制的模式函数
  * @retval  none
  */
void CtrlEntry(CallBackFunc CtrlMode)
{
	CtrlMode();
}
/**
  * @brief  蓝牙模式
  * @param  none
  * @retval  none
  */
void BluetoochMode(void)
{
	Blue_Serial_Init();

	while(1)
	{
		if(Serial_RxFlag==1)
		{
			if(strcmp(Serial_RxPacket,"Forward_LowSpeed")==0)
			{
				 Move_Advance();
			}
			else if(strcmp(Serial_RxPacket,"Forward_LowSpeed")==0)
			{
				
			}
			else if(strcmp(Serial_RxPacket,"Back_LowSpeed")==0)
			{
				
			}
			else if(strcmp(Serial_RxPacket,"Back_HighSpeed")==0)
			{
				
			}
			else if(strcmp(Serial_RxPacket,"Rotation")==0)
			{
				
			}
			else{
				break;
				//返回上级目录，选择模式
			}
		}
	}
}
/**
  * @brief  步态选择函数
  * @param  none
  * @retval  none
  */
void SwitchGait()
{
	return;
}

