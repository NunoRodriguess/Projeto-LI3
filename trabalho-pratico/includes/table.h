#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct table *Table;

void free_table(Table t);
Table init_table(int n, char *params);
void init_entries(Table t, int n);
void add_entry(Table t, char **params);

Table convert_table(Table t, int min, int max);

void show(Table t, FILE *fp);

int get_last(Table t);
int get_ncols(Table t);

#endif