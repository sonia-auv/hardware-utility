//###################################################
//              SLAVE DEFINITION
//###################################################

#define SLAVE_BACKPLANE 0
#define SLAVE_IO 1
#define SLAVE_KILLMISSION 2
#define SLAVE_STATE_SCREEN 7

//###################################################
//              CMD DEFINITION
//###################################################

// define kill mission switch
#define CMD_MISSION 0
#define CMD_KILL 1

// define backplane

#define CMD_VOLTAGE 0
#define CMD_CURRENT 1
#define CMD_READ_MOTOR 2
#define CMD_ACT_MOTOR 3
#define CMD_PWM 4

// define IO CONTROL
#define CMD_IO_TEMP  0
#define CMD_IO_DROPPER_ACTION  1
#define CMD_IO_TORPEDO_ACTION  2
#define CMD_IO_ARM_ACTION 3

//###################################################
//              DATA DEFINITION
//###################################################

#define DATA_IO_DROPPER_PORT 0
#define DATA_IO_DROPPER_STARBOARD 1

#define DATA_IO_TORPEDO_PORT 0
#define DATA_IO_TORPEDO_STARBOARD 1

#define DATA_IO_ARM_CLOSE 0
#define DATA_IO_ARM_OPEN 1