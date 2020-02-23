#ifndef REFERENCE_H
#define REFERENCE_H

// Only uncomment one of these at a time. It will
// control which motor controllers are used for the
// robot that this code is going on.
// #define COMP_BOT
#define PRACTICE_BOT

//////////////////////////////////////////////////////////////

#ifdef PRACTICE_BOT

#define TURRET          52   // Brake
#define SHOOTER_1       5   // Coast
#define SHOOTER_2       62   // Coast
#define DRIVE_LEFT_1    4  
#define DRIVE_LEFT_2    57
#define DRIVE_LEFT_3    55
#define DRIVE_RIGHT_1   54
#define DRIVE_RIGHT_2   56
#define DRIVE_RIGHT_3   59
#define COLOR_WHEEL     8    // Brake
#define TOWER_1         53   // Brake
#define TOWER_2         61   // Brake
#define HOPPER_LEFT     58   // Brake
#define HOPPER_RIGHT    60   // Brake
#define INTAKE          44   // Brake
#define CLIMB           1   // Brake

#endif // End of PRACTICE_BOT

/////////////////////////////////////////////////////////////

#ifdef COMP_BOT

#define TURRET          0   // Brake
#define SHOOTER_1       1   // Coast
#define SHOOTER_2       2   // Coast
#define DRIVE_LEFT_1    4
#define DRIVE_LEFT_2    5
#define DRIVE_LEFT_3    9
#define DRIVE_RIGHT_1   6
#define DRIVE_RIGHT_2   7
#define DRIVE_RIGHT_3   10
#define COLOR_WHEEL     8    // Brake
#define TOWER_1         11   // Brake
#define TOWER_2         12   // Brake
#define HOPPER_LEFT     62   // Brake
#define HOPPER_RIGHT    61   // Brake
#define INTAKE          44   // Brake
#define CLIMB           69   // Brake

#endif // End of COMP_BOT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

// This area should be sensor locations etc, that are common
// to both robots. 

#define GYRO            1
#define RATCHET_SERVO   0
#define IR_SENSOR       1

#endif