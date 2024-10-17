#ifndef __GET_ANGLE_H__
#define __GET_ANGLE_H__


#ifdef __cplusplus
extern "C"{
#endif 
	
#define CROTCH 45
#define LEG 75
#define FOOT 140
float get_angle1(float x,float y, float z);
float get_angle2(float x,float y,float z);
float get_angle(float x,float y, float z);
float get_x(float angle1,float angle2,float angle3);
float get_y(float angle1,float angle2,float angle3);
float get_z(float angle1,float angle2,float angle3);

void test(void);
	
	
#ifdef __cplusplus
}
#endif

#endif
