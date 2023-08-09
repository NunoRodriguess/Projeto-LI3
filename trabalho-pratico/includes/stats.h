#ifndef TRABALHO_PRATICO_STATS_H
#define TRABALHO_PRATICO_STATS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <glib.h>


int more_recent(char *dt1, char *dt2);
double get_preco (char *car_class,int distance);
void swap(char **s1, char **s2);
char* int_to_string(int n);
void shiftLeft (char *string,int shiftLength);
int isUsername (char string[]);
int age(int birth_date, int birth_month, int birth_year);
void free_key_array(char**array,int size);

#endif // TRABALHO_PRATICO_STATS_H
