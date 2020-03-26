//###################################################
//              SLAVE DEFINITION
//###################################################

#define SLAVE_powersupply0 0x31
#define SLAVE_powersupply1 0x32
#define SLAVE_powersupply2 0x33
#define SLAVE_powersupply3 0x34
#define SLAVE_killMission 0x20
#define SLAVE_ESC 0x10
#define SLAVE_IO_CTR 0x40
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

#define CMD_PS_ACT_12V	0x10
#define CMD_PS_ACT_16V_1 0x11
#define CMD_PS_ACT_16V_2 0x12

#define CMD_PS_CHECK_12V	0x13
#define CMD_PS_CHECK_16V_1 0x14
#define CMD_PS_CHECK_16V_2 0x15

// define ESC
#define CMD_PWM  0x00

// define IO CONTROL
#define CMD_IO_TEMP  0
#define CMD_IO_DROP_PORT 0x01
#define CMD_IO_DROP_STARBOARD 0x02
#define CMD_IO_TORP_PORT 0x03
#define CMD_IO_TORP_STARBOARD 0x04
#define CMD_IO_ARM_OPEN 22
#define CMD_IO_ARM_CLOSE 23

//###################################################
//              DATA DEFINITION
//###################################################

#define DATA_IO_DROPPER_PORT 0
#define DATA_IO_DROPPER_STARBOARD 1

#define DATA_IO_TORPEDO_PORT 0
#define DATA_IO_TORPEDO_STARBOARD 1

#define DATA_IO_ARM_CLOSE 0
#define DATA_IO_ARM_OPEN 1