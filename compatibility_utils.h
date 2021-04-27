#ifndef TICTACTOE_IN_C_COMPATIBILITY_UTILS_H
#define TICTACTOE_IN_C_COMPATIBILITY_UTILS_H

#include <stdbool.h>
#include <termios.h>

void enable_raw_mode();
void disable_raw_mode();
bool kbhit();

#endif //TICTACTOE_IN_C_COMPATIBILITY_UTILS_H
