#ifndef RoverCommands_h
#define RoverCommands_h

#define MAXCOMMANDLENGTH 15

// Behaviour for the robot when it receives a serial command:
// - act on the command
class RoverCommands
{
  public:

    enum COMMANDS {
      CMD_SPEED,
      CMD_FORWARD,
      CMD_BACKWARD,
      CMD_LEFT,
      CMD_RIGHT,
      CMD_SPINLEFT,
      CMD_SPINRIGHT,
      CMD_SPEEDLEFT,
      CMD_SPEEDRIGHT,
      CMD_SLIDELEFT,
      CMD_SLIDERIGHT,
      CMD_TURNAROUND,
      CMD_STOP,
      CMD_NAME,
      CMD_NOOP
    };

    struct CommandDef {
      char *commandStr;
      COMMANDS cmd;
    }; 
  
  RoverCommands();

  int execute(COMMANDS& cmd);
  int execCommand(char *commandStr);

  char *getName();
  int getSpeed();

private:
    char cmd[MAXCOMMANDLENGTH + 1];
    char buffer[MAXCOMMANDLENGTH + 1];
    char name[MAXCOMMANDLENGTH + 1];
    int speed;
    char *last;
    CommandDef defs[16];
  
    char *getNextToken();
    int getInt();

};

#endif
