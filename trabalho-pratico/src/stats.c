#include "stats.h"


// Description:

// This function takes two strings representing dates in the format "dd/mm/yyyy" and returns 0 if the first date is more recent than the second date, 1 if the second date is more recent than the first date, and 2 if the dates are equal.

int more_recent(char *dt1, char *dt2) {
 
    char *data1 = strdup(dt1);
    char *data2 = strdup(dt2);
    int y1, y2, m1, m2, d1, d2;
    char *d1c = strsep(&data1, "/");
    char *m1c = strsep(&data1, "/");
    char *y1c = strsep(&data1, "/");
    d1 = atoi(d1c);
    m1 = atoi(m1c);
    y1 = atoi(y1c);

    char *d2c = strsep(&data2, "/");
    char *m2c = strsep(&data2, "/");
    char *y2c = strsep(&data2, "\n");
    d2 = atoi(d2c);
    m2 = atoi(m2c);
    y2 = atoi(y2c);

    free(d1c);
    free(d2c);
    free(data1);
    free(data2);

    if (y1>y2) return 0;
    if (y1<y2) return 1;

    if (m1>m2) return 0;
    if (m1<m2) return 1;

    if (d1>d2) return 0;
    if (d1==d2) return 2;
    if (d1<d2) return 1;

    return 0; // return 0 se 1 mais nova 2 . 2 se iguais 
}

// Description:

// This function takes a string car_class and an integer distance and returns the price for the given car class and distance traveled. The function returns 3.25 + 0.62 * distance for the "basic" car class, 4.00 + 0.79 * distance for the "green" car class, and 5.20 + 0.94 * distance for the "premium" car class.

double get_preco (char *car_class,int distance){

char * p;
double d =(double) distance;
char *basic ="basic";
char *green = "green";
char *premium = "premium";
 if (strcmp(basic,car_class)==0){

       return (3.25 +0.62*d);
        
    }
    if (strcmp(green,car_class)==0){

       
        return (4.00 + 0.79*d);
    }
    if (strcmp(premium,car_class)==0){

       
        return (5.20 + 0.94*d);
    }

}

// Description:

// This function takes two pointers to pointers to char and swaps the values stored at those addresses.

 void swap(char **s1, char **s2) {
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

// Description:

// This function takes an integer n and returns a string representation of the integer.

char* int_to_string(int n) {
    
    int num_digits = 0;
    int n_copy = n;
    while (n_copy > 0) {
        num_digits++;
        n_copy /= 10;
    }

    
    char* str = malloc(num_digits + 1);
    if (str == NULL) {
        return NULL;
    }

    sprintf(str, "%d", n);

    return str;
}

// Description:

// This function takes a pointer to a string and an integer shiftLength and shifts the string to the left by shiftLength characters.

void shiftLeft (char *string,int shiftLength){

int i,size=strlen(string);
if(shiftLength >= size){
    memset(string,'\0',size);
    return;
}

for (i=0; i < size-shiftLength; i++){
    string[i] = string[i + shiftLength];
    string[i + shiftLength] = '\0';
    if ( string[i] == '\n') string[i] = '\0';
}

}

// Description:

// This function takes a string and returns 1 if the string consists only of digits, and 0 otherwise.

int isUsername (char string[]){

    int r = 1;
    
   for (int i = 0;string[i]!='\0';i++){

        if (isdigit(string[i])== 0){

            r=0;
        }
   }
return r;
}

// Description:

// This function takes three integers representing the birth date, birth month, and birth year and returns the age in years.

int age(int birth_date, int birth_month, int birth_year) {
    int present_date = 9;
    int present_month = 10;
    int present_year = 2022;
    int temp = birth_date;
    birth_date = birth_year;
    birth_year = temp;
   int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if (birth_date > present_date) {
      present_date = present_date + month[birth_month - 1];
      present_month = present_month - 1;
   }
   if (birth_month > present_month) {
      present_year = present_year - 1;
      present_month = present_month + 12;
   }
   int final_date = present_date - birth_date;
   int final_month = present_month - birth_month;
   int final_year = present_year - birth_year;

   return final_year;
}

// Description:

// This function takes a variable number of char pointers and frees the memory dynamically allocated to each of the pointers.

void free_key_array(char**array,int size){

    for (int i = 0; i < size; i++) {
    free(array[i]);
    }
free(array);
}