#ifndef TRABALHO_PRATICO_DRIVERS_H
#define TRABALHO_PRATICO_DRIVERS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "stats.h"



#define DRIVERS_MAX_LINE 1024



typedef struct driver *Drivers;
typedef struct dcoll *Drivers_Collection;
typedef struct LinkedList *City;
Drivers_Collection initDColl();
City createNode();
void free_driver(gpointer data);
void free_driver2(Drivers d);

Drivers initDrivers();

// ============================ GETTERS ============================
char *d_getId(Drivers r);
char *d_getName(Drivers r);
char *d_getBirth_date(Drivers r);
char *d_getGender(Drivers r);
char *d_getCar_class(Drivers r);
char *d_getLicense_plate(Drivers r);
char *d_getCity(Drivers r);
char *d_getAccount_creation(Drivers r);
char d_getAccount_status(Drivers r);
double *d_getScore(Drivers d);
double *d_getTotal(Drivers d);
int d_getNumRides(Drivers d);
char *d_getLast_Ride(Drivers r);
double c_getScore(Drivers d,char*cityC);
double c_getNumRides(Drivers d,char*cityC);

// ============================ SETTERS ============================

void d_setId (Drivers d, char *id);
void d_setName (Drivers d, char *name);
void d_setBirth_date (Drivers d, char *birth_date);
void d_setGender (Drivers d, char *gender);
void d_setCar_class (Drivers d, char *car_class);
void d_setLicense_plate (Drivers d, char *license_plate);
void d_setCity (Drivers d, char *city);
void d_setAccount_creation (Drivers d, char *account_creation);
void d_setAccount_status (Drivers d, char *account_status);
// ============================ MISC ============================
int Isnull_id(Drivers d);
int inserDrivers(Drivers_Collection dcoll, Drivers new);
void d_add_ride (Drivers d,double new_score,char*car_class,int distance,double tip,char*new_date,char*city);
City addNode(City head, double value,char*cityy);
void incNode(Drivers d,char *city,double score);
Drivers look_up_drivers (Drivers_Collection dcoll,char* key);
void d_destroy (Drivers_Collection d);
char **d_give_array(Drivers_Collection dcoll,int *size);
void d_quickSort(char **arr, int low, int high,Drivers_Collection dcoll);
void c_insertionSort(char** array,int n,Drivers_Collection dcoll,char *city);
void c_quickSort(char **arr, int low, int high,Drivers_Collection dcoll,char *city);
#endif // TRABALHO_PRATICO_DRIVERS_H
