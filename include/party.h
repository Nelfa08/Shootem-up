#ifndef __PARTY__
#define __PARTY__

#include "struct.h"

Party *init_party();
double normal_delay(double mean);
int free_party(Party *party);
int write_scoreboard(Party *party);
int read_scoreboard(Party *party);
int print_scoreboard(Party *party);

#endif