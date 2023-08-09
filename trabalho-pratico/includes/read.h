#ifndef TRABALHO_PRATICO_READ_H
#define TRABALHO_PRATICO_READ_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "rides.h"
#include "users.h"
#include "drivers.h"


Rides_Collection readRides(char *filepath,Drivers_Collection dcoll,Users_Collection ucoll,char**citythatexists,int *size,int*howmany);
Users_Collection readUsers(char *filepath);
Drivers_Collection readDrivers(char *filepath);

#endif //TRABALHO_PRATICO_READ_H