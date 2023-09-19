#ifndef DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_INTERFACE_H_

typedef enum
{
	LEVEL_1_SPEED,
	LEVEL_2_SPEED,
	LEVEL_3_SPEED,
	LEVEL_4_SPEED,
	LEVEL_5_SPEED
}DC_MOTOR_speed_t;



void DC_MOTOR_voidSpeedControl(DC_MOTOR_speed_t speed);


#endif /* DC_MOTOR_INTERFACE_H_ */