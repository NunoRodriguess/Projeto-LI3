#ifndef TRABALHO_PRATICO_MODEL_H
#define TRABALHO_PRATICO_MODEL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rides.h"
#include "users.h"
#include "drivers.h"
#include "read.h"
#include "stats.h"
#include "table.h"

typedef struct model *Model;
typedef struct q4 *Q4;
typedef struct q7* Q7;

Model initModel();
Model load_model(char *ridesc,char*driversc,char*usersc);
void free_model(Model m); 
void free_string_array(char **strings, int size);
void q1 (Model m,char*buffer,FILE *fptr);
void q2 (Model m,char*buffer,FILE *fptr);
void q3 (Model m,char*buffer,FILE *fptr);
void q4 (Model m,char*buffer,FILE *fptr);
void q5 (Model m,char*buffer,FILE *fptr);
void q6 (Model m,char*buffer,FILE *fptr);
void q7 (Model m,char*buffer,FILE *fptr);
void q8 (Model m,char*buffer,FILE *fptr);
void q9 (Model m,char*buffer,FILE *fptr);
Table q1_interativa (Model m,char*arg);
Table q2_interativa (Model m,char*arg);
Table q3_interativa (Model m,char*arg);
Table q4_interativa (Model m,char*arg);
Table q5_interativa (Model m,char*arg,char*arg2);
Table q6_interativa (Model m,char*arg,char*arg2,char*arg3);
Table q7_interativa (Model m,char*arg,char*arg2);
Table q8_interativa (Model m,char*arg,char*arg2);
Table q9_interativa (Model m,char*arg,char*arg2);



#endif //TRABALHO_PRATICO_MODEL_H