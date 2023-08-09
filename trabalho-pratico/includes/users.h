#ifndef TRABALHO_PRATICO_USERS_H
#define TRABALHO_PRATICO_USERS_H


#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include "rides.h"
#include "stats.h"


#define USERS_MAX_LINE 1024

typedef struct user *Users;
typedef struct ucoll *Users_Collection;

Users initUsers();
Users_Collection initUColl();
void free_user(gpointer data);
void free_user2(Users u); 

// ============================ GETTERS ============================
// vai buscar valor que est\u00e1 numa ride (strdup para garantir encapsulamento)
// meter u_ atras disto
char *u_getUsername(Users u);
char *u_getName(Users u);
char *u_getGender(Users u);
char *u_getBirthDate(Users u);
char *u_getAccount_creation(Users u);
char *u_getPay_method(Users u);
char u_getAccount_status(Users u);
double *u_getScore(Users u);
double *u_getTotal(Users u);
double *u_getDistanceTotal(Users u);
int u_getNumRides(Users u);
// ============================ SETTERS ============================

void u_setUsername(Users u, char *username);
void u_setName(Users u, char *name);
void u_setGender(Users u, char *gender);
void u_setBirthDate (Users u, char *birth_date);
void u_setAccount_creation (Users u, char *account_creation);
void u_setPay_method (Users u, char *pay_method);
void u_setAccount_status (Users u, char *account_status);
// ============================ Misc ============================
void u_add_ride (Users u,double new_score,char*car_class,int distance,double tip,char*new_date); 
char ** u_give_array(Users_Collection ucoll,int *size);
int inserUser (Users_Collection ucoll , Users new);
Users look_up_users (Users_Collection ucoll,char* key);
void u_destroy (Users_Collection u);
void u_quickSort(char **arr, int low, int high,Users_Collection ucoll);

#endif //TRABALHO_PRATICO_USERS_H
