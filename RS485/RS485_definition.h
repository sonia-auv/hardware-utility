//###################################################
//              SLAVE DEFINITION
//###################################################

#define SLAVE_powersupply0 49
#define SLAVE_powersupply1 50
#define SLAVE_powersupply2 51
#define SLAVE_powersupply3 52
#define SLAVE_killMission 32
#define SLAVE_ESC_PWM 16
#define SLAVE_ESC_1 17
#define SLAVE_ESC_2 18
#define SLAVE_ESC_3 19
#define SLAVE_ESC_4 20
#define SLAVE_ESC_5 21
#define SLAVE_ESC_6 22
#define SLAVE_ESC_7 23
#define SLAVE_ESC_8 24
#define SLAVE_IO_CTR 64

//###################################################
//              CMD DEFINITION
//###################################################

// les define de la kill mission switch
#define CMD_MISSION 0
#define CMD_KILL 1

// les define du powersupply
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

// define de ESC
#define CMD_ESC_power 0

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