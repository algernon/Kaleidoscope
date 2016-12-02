#include "Keyboardio-Commander.h"

static const char *requiredGreeting;
static const char *greeting;
static const char *complaint;
static bool seenGreet;

static auto OK = "OK ";
static auto ERROR = "ERROR ";

static char command[COMMAND_SIZE];

static struct {
    String command;
    Commander_::CommandHandler handler;
} commands[MAX_COMMANDS];

Commander_::Commander_(void) {
}

void
Commander_::setup (const char *requiredGreeting_, const char *greeting_, const char *complaint_) {
    requiredGreeting = requiredGreeting_;
    greeting = greeting_;
    complaint = complaint_;

    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect.
    }

    registerCommand("hello", this->helloCommand);
    loop_hook_add(this->loopHook);
}

void
Commander_::setup(void) {
    setup("keyboard my, old friend",
          "You've come to talk with me again",
          "You forgot to greet me properly. How rude.");
}

void
Commander_::loopHook(void) {
    if (! Serial.available())
        return;

    if (! readCommand()) {
        Serial.print(ERROR);
        Serial.println(1);
        Serial.println(F("Incomplete command received, or timed out."));
        return;
    }

    if (! seenGreet) {
        Serial.print(ERROR);
        Serial.println(1);
        Serial.println(complaint);
        return;
    }

    if (! processCommand()) {
        Serial.print(ERROR);
        Serial.println(1);
        Serial.print(F("Unknown command: "));
        Serial.println(command);
        return;
    }
}

bool
Commander_::readCommand(void) {
    bool fullCommand = false;
    uint8_t i = 0;

    memset(command, 0, COMMAND_SIZE);

    do {
        int b = readChar();
        if ((char)b == '\r')
            continue;
        if ((char)b == ' ' || (char)b == '\t' || (char)b == '\n') {
            fullCommand = true;
            break;
        }

        command[i++] = (char)b;
    } while (i < COMMAND_SIZE - 1);

    return fullCommand;
}

bool
Commander_::processCommand(void) {
    for (uint8_t i = 0; i < MAX_COMMANDS; i++) {
        if (commands[i].command == NULL)
            break;

        if (commands[i].command.equals(command)) {
            (*(commands[i].handler))();
            return true;
        }
    }

    return false;
}

void
Commander_::registerCommand(String command, CommandHandler handler) {
    for (uint8_t i = 0; i < MAX_COMMANDS; i++) {
        if (commands[i].command == NULL) {
            commands[i].command = command;
            commands[i].handler = handler;
            return;
        }
    }
}

void
Commander_::helloCommand(void) {
    uint8_t i = 0;
    bool okGreeting = true;

    if (!Serial.find((char *)requiredGreeting))
        okGreeting = false;
    else if (!isEOL(readChar()))
        okGreeting = false;

    if (!okGreeting) {
        consumeUntilEOL();
        Serial.print(ERROR);
        Serial.println(1);
        Serial.println(complaint);
    }

    seenGreet = true;
    Serial.print(OK);
    Serial.println(1);
    Serial.println(greeting);
}

void
Commander_::consumeUntilEOL(void) {
    while (!isEOL(readChar())) {
    }
}

char
Commander_::readChar(void) {
    char b;
    Serial.readBytes(&b, 1);
    return b;
}

bool
Commander_::isEOL(char b) {
    return (b == '\n');
}

Commander_ Commander;
