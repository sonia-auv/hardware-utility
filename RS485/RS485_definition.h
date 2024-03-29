//###################################################
//              SLAVE DEFINITION
//###################################################

#define SLAVE_PSU0 0
#define SLAVE_PSU1 1
#define SLAVE_PSU2 2
#define SLAVE_PSU3 3
#define SLAVE_KILLMISSION 4
#define SLAVE_ESC 5
#define SLAVE_IO 6
#define SLAVE_STATE_SCREEN 7
#define SLAVE_PWR_MANAGEMENT 8

//###################################################
//              CMD DEFINITION
//###################################################

// define kill mission switch
#define CMD_MISSION 0
#define CMD_KILL 1

// define backplane/PSU
#define CMD_VOLTAGE 0
#define CMD_CURRENT 1
#define CMD_TEMPERATURE 2

// define backplane/ESC
#define CMD_READ_MOTOR 15
#define CMD_ACT_MOTOR 16
#define CMD_PWM 17

// define IO CONTROL
#define CMD_IO_TEMP  0
#define CMD_IO_DROPPER_ACTION  1
#define CMD_IO_TORPEDO_ACTION  2
#define CMD_IO_ARM_ACTION 3
#define CMD_IO_LEAK_SENSOR 4

// COMMON DEFINITION
#define CMD_IS_ALIVE 30

//###################################################
//              DATA DEFINITION
//###################################################

// define IO CONTROL

#define DATA_IO_DROPPER_PORT 0
#define DATA_IO_DROPPER_STARBOARD 1

#define DATA_IO_TORPEDO_PORT 0
#define DATA_IO_TORPEDO_STARBOARD 1

#define DATA_IO_ARM_CLOSE 0
#define DATA_IO_ARM_OPEN 1

#define DATA_IO_LEAK_SENSOR_DRY 0
#define DATA_IO_LEAK_SENSOR_LEAK 1
