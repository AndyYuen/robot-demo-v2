#include <string.h>
#include "RoverCommands.h"
#include "TurnSensor.h"
#include "RoverC.h"

// List of Remote Commands
//    static CommandDef RoverCommands::defs[] = {
//      { "forward",    CMD_FORWARD },
//      { "backward" ,  CMD_BACKWARD },
//      { "left",       CMD_LEFT },
//      { "right",      CMD_RIGHT },
//      { "spinLeft",   CMD_SPINLEFT },
//      { "spinRight",  CMD_SPINRIGHT },
//      { "speedLeft",  CMD_SPEEDLEFT },
//      { "speedRight", CMD_SPEEDRIGHT },
//      { "slideLeft",  CMD_SLIDELEFT },
//      { "slideRight", CMD_SLIDERIGHT },
//      { "turnAround", CMD_TURNAROUND },
//      { "stop",       CMD_STOP },
//      { "name",       CMD_NAME },
//      { "speed",      CMD_SPEED },
//      { NULL,         CMD_NOOP }
//    };
    
#define FIXED_SPEED 50
#define SLIDE_TIME  300

#define TURN_ANGLE  15  * 360 / 425
#define ONE_REV     360 * 360 / 425
#define HALF_REV    180 * 360 / 425
//#define TURN_ANGLE  15
//#define ONE_REV     360
//#define HALF_REV    180

  RoverCommands::RoverCommands() {
    speed = 60;
    cmd[0] = buffer[0] = 0;
    strcpy(name, "dummy");

    // init command definitions
    defs[0].commandStr = "forward";     defs[0].cmd = CMD_FORWARD;
    defs[1].commandStr = "backward";    defs[1].cmd = CMD_BACKWARD;
    defs[2].commandStr = "left";        defs[2].cmd = CMD_LEFT;
    defs[3].commandStr = "right";       defs[3].cmd = CMD_RIGHT;
    defs[4].commandStr = "spinLeft";    defs[4].cmd = CMD_SPINLEFT;
    defs[5].commandStr = "spinRight";   defs[5].cmd = CMD_SPINRIGHT;
    defs[6].commandStr = "speedLeft";   defs[6].cmd = CMD_SPEEDLEFT;
    defs[7].commandStr = "speedRight";  defs[7].cmd = CMD_SPEEDRIGHT;
    defs[8].commandStr = "slideLeft";   defs[8].cmd = CMD_SLIDELEFT;
    defs[9].commandStr = "slideRight";  defs[9].cmd = CMD_SLIDERIGHT;
    defs[10].commandStr = "turnAround"; defs[10].cmd = CMD_TURNAROUND;
    defs[11].commandStr = "stop";       defs[11].cmd = CMD_STOP;
    defs[12].commandStr = "name";       defs[12].cmd = CMD_NAME;
    defs[13].commandStr = "speed";      defs[13].cmd = CMD_SPEED;
    defs[14].commandStr = NULL;         defs[14].cmd = CMD_NOOP;
  }

  // lookup the command and execute it
  int RoverCommands::execCommand(char *commandStr) {
    int i = 0;
    while (defs[i].commandStr != NULL ) {
      strncpy(buffer, commandStr, MAXCOMMANDLENGTH);

      // Identify and execute the commandStr
      char *cmd = strtok_r(buffer, " ", &last); 
      if (strncmp(cmd, defs[i].commandStr, MAXCOMMANDLENGTH) == 0) {
        execute(defs[i].cmd);
        return 0;
      }
      i++;
    }
    return 1;
  }

  // Execute the robot movement commands
  int RoverCommands::execute(COMMANDS& cmd) {

    switch (cmd) {
      case CMD_SPEED:
        speed = getInt();
        break;
      case CMD_NAME:
        strncpy(name, getNextToken(), MAXCOMMANDLENGTH);
        break;
      case CMD_FORWARD:
        Move_forward(speed);
        break;
      case CMD_BACKWARD:
        Move_back(speed);
        break;
      case CMD_RIGHT:
      case CMD_SPEEDRIGHT:
        Move_turnleft(speed);
        TurnSensor::getInstance()->waitTillTurnedNumberOfDegreesLeft(TURN_ANGLE);
        Move_stop(speed);
        break;
      case CMD_LEFT:
      case CMD_SPEEDLEFT:
        Move_turnright(speed);
        TurnSensor::getInstance()->waitTillTurnedNumberOfDegreesRight(TURN_ANGLE);
        Move_stop(speed);
        break;
      case CMD_SPINRIGHT:
        Move_turnleft(speed);
        TurnSensor::getInstance()->waitTillTurnedNumberOfDegreesLeft(ONE_REV);
        Move_stop(speed);
        break;
      case CMD_SPINLEFT:
        Move_turnright(speed);
        TurnSensor::getInstance()->waitTillTurnedNumberOfDegreesRight(ONE_REV);
        Move_stop(speed);
        break;
//      case CMD_SPEEDLEFT:
//        Move_turnleft(speed);
//        TurnSensor::getInstance()->waitTillTurnedNumberOfDegreesLeft(TURN_ANGLE);
//        Move_stop(speed);
//        break;
//      case CMD_SPEEDRIGHT:
//        Move_turnright(speed);
//        TurnSensor::getInstance()->waitTillTurnedNumberOfDegreesRight(TURN_ANGLE);
//        Move_stop(speed);
//        break;
      case CMD_SLIDELEFT:
        Move_left(speed);
        delay(SLIDE_TIME);
        Move_stop(speed);
        break;
      case CMD_SLIDERIGHT:
        Move_right(speed);
        delay(SLIDE_TIME);
        Move_stop(speed);
        break;
      case CMD_TURNAROUND:
        Move_right(speed);
        TurnSensor::getInstance()->waitTillTurnedNumberOfDegreesRight(HALF_REV);
        Move_stop(speed);
        break;
      case CMD_STOP:
        Move_stop(speed);
        break;
      default:
        break;
    }
    return 0;
  }

  // retreive name specified in "name" command
  char *RoverCommands::getName() {
    return name;
  }

  // retreive the speed setting of movements
  int RoverCommands::getSpeed() {
    return speed;
  }

  // get next token in command string
  char *RoverCommands::getNextToken() {
    return strtok_r(NULL, " ", &last);
  }

  // convert next token in command string to an integer
  int RoverCommands::getInt() {
    int aNumber;
    char *arg;
    arg = getNextToken();
    if (arg != NULL) {
      aNumber = atoi(arg);    // Converts a char string to an integer
    }
    else {
      aNumber = 0;
    }
  
    return aNumber;
  }
