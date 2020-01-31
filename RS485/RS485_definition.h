//###################################################
//              SLAVE DEFINITION
//###################################################

#define SLAVE_powersupply0 0
#define SLAVE_powersupply1 1
#define SLAVE_powersupply2 2
#define SLAVE_powersupply3 3
#define SLAVE_killMission 4
#define SLAVE_ESC 5
#define SLAVE_IO_CTR 6
#define SLAVE_STATE_SCREEN 7

//###################################################
//              CMD DEFINITION
//###################################################

// define kill mission switch
#define CMD_MISSION 0
#define CMD_KILL 1

// define powersupply
#define CMD_PS_V16_1 0
#define CMD_PS_V16_2 1
#define CMD_PS_V12 2

#define CMD_PS_C16_1 3
#define CMD_PS_C16_2 4
#define CMD_PS_C12 5

#define CMD_PS_temperature 6
#define CMD_PS_VBatt 7

#define CMD_PS_ACT_12V 8
#define CMD_PS_ACT_16V_1 9
#define CMD_PS_ACT_16V_2 10

#define CMD_PS_CHECK_12V 11
#define CMD_PS_CHECK_16V_1 12
#define CMD_PS_CHECK_16V_2 13

// define ESC
#define CMD_ESC_MOTOR_1 0
#define CMD_ESC_MOTOR_2 1
#define CMD_ESC_MOTOR_3 2
#define CMD_ESC_MOTOR_4 3
#define CMD_ESC_MOTOR_5 4
#define CMD_ESC_MOTOR_6 5
#define CMD_ESC_MOTOR_7 6
#define CMD_ESC_MOTOR_8 7

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