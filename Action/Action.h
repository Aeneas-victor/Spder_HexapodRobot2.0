/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : Action.h
  * @brief          : 动作组定义文件
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
#ifndef __ACTION_H__
#define __ACTION_H__
#include "common.h"


void Robot_Low_Action(void);
void _Move_Robot(uint8_t* Robot_Module,int16_t*Angle);
void Move_Advance(void);
void Move_Rotation(void);
#endif
