#pragma once

#include <KeyboardioFirmware.h>

#define COMMAND_SIZE 64
#define MAX_COMMANDS 64

class Commander_ {
  public:
    Commander_(void);

    typedef void (*CommandHandler)(void);

    void setup(const char *requiredGreeting, const char *greeting, const char *complaint);
    void setup(void);
    void registerCommand(String command, CommandHandler handler);
  private:
    static void loopHook(void);
    static bool readCommand(void);
    static bool processCommand(void);

    static bool isEOL(char b);
    static char readChar(void);
    static void consumeUntilEOL(void);

    static void helloCommand(void);
};

extern Commander_ Commander;
