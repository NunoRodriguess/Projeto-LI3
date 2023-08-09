#ifndef TRABALHO_PRATICO_RIDES_H
#define TRABALHO_PRATICO_RIDES_H

#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include "stats.h"


#define RIDES_MAX_LINE 1024

typedef struct ride *Rides;
typedef struct rcoll *Rides_Collection;

Rides initRides();
Rides_Collection initRColl();
void free_ride(gpointer data);

// ============================ GETTERS ============================
// vai buscar valor que est\u00e1 numa ride (strdup para garantir encapsulamento)
// meter r_ atras disto

char *r_getId(Rides r);
char *r_getDate(Rides r);
char *r_getDriver(Rides r);
char *r_getUser(Rides r);
char *r_getCity(Rides r);
int r_getDistance(Rides r);
char *r_getScore_user(Rides r);
char *r_getScore_driver(Rides r);
double r_getTip(Rides r);
char *r_getComment(Rides r);

// ============================ SETTERS ============================

void r_setId(Rides r, char *id);
void r_setDate(Rides r, char *date);
void r_setDriver(Rides r, char *driver);
void r_setUser(Rides r, char *user);
void r_setCity(Rides r, char *city);
void r_setDistance(Rides r, char *distance);
void r_setScore_user(Rides r, char *score_user);
void r_setScore_driver(Rides r, char *score_driver);
void r_setTip(Rides r, char *tip);
void r_setComment(Rides r, char *comment);

// ============================ MISC ============================

int inserRide(Rides_Collection rcoll, Rides new);
void free_scores(Rides rides);
void r_destroy (Rides_Collection r);
char **r_give_array(Rides_Collection rcoll,int *size);
Rides look_up_rides (Rides_Collection rcoll,char* key);
void insertionSort2(char** array,int n,Rides_Collection rcoll);
void r_quickSort(char **arr, int low, int high,Rides_Collection rcoll);
#endif //TRABALHO_PRATICO_RIDES_H
