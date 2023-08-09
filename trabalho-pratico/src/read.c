#include "read.h"
//username; name; gender; birth_date; account_creation; pay_method; account_status

// Description:

// This function checks if a given string is a valid date in the format dd/mm/yyyy. It returns 1 if the string is not a valid date and 0 if it is a valid date.

static int test_date(char*date){
    if (strlen(date) != 10) {
        return 1;
    }
    if (date[0] < '0' || date[0] > '9' || date[1] < '0' || date[1] > '9') {
        return 1;
    }
    if (date[2] != '/') {
        return 1;
    }
    if (date[3] < '0' || date[3] > '9' || date[4] < '0' || date[4] > '9') {
        return 1;
    }
    if (date[5] != '/') {
        return 1;
    }
    if (date[6] < '0' || date[6] > '9' || date[7] < '0' || date[7] > '9' || date[8] < '0' || date[8] > '9' || date[9] < '0' || date[9] > '9') {
        return 1;
    }
    // Convert the day and month to integers
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');

    // Check that the day is between 1 and 31
    if (day < 1 || day > 31) {
        return 1;
    }

    // Check that the month is between 1 and 12
    if (month < 1 || month > 12) {
        return 1;
    }

    return 0;
}

// Description:

// This function checks if a given string is one of the three car classes (premium, green, or basic). The function converts the string to lower case and returns 0 if the string matches any of the car classes, and 1 otherwise.

static int test_car_class(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
    if (strcmp(str, "premium") == 0) {
        return 0;
    }
    if (strcmp(str, "green") == 0) {
        return 0;
    }
    if (strcmp(str, "basic") == 0) {
        return 0;
    }
    return 1;
}

// Description:

// This function checks if a given string is one of the two account statuses (active or inactive). The function converts the string to lower case and returns 0 if the string matches any of the account statuses, and 1 otherwise.

static int test_account_status(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
    if (strcmp(str,"active") == 0) {
        return 0;
    }
    if (strcmp(str,"inactive") == 0) {
        return 0;
    }
    return 1;
}

// Description:

// This function checks if a given string is a positive integer representing distance. It returns 0 if the string is a positive integer and 1 otherwise.

static int test_distance(char* str) {
    if (str[0] == '\0') {
        return 1;
    }
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 1;
        }
    }
    int num = atoi(str);
    if (num > 0) {
        return 0;
    } else {
        return 1;
    }
}

// Description:

// This  function checks if a given string is a positive number (integer or float). It returns 0 if the string is a positive number and 1 otherwise.

static int test_intordouble(char* str) {
    if (str[0] == '\0') {
        return 1;
    }
    if (strlen(str)>3){
        return 1;
    }
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]) && str[i] != '.') {
            return 1;
        }
    }

    int found_decimal = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '.') {
            found_decimal++;
            if (found_decimal > 1) {
                return 1;
            }
        }
    }
    double num = atof(str);
    if (num > 0) {
        return 0;
    } else {
        return 1;
    }
}
//id, name, gender, license_plate, city;
//id; name, birth_date; gender; car_class; license_plate; city; account_creation; account_status

// Description:

// This function checks if a line of a csv file is valid, according to the specified number of fields, required fields, and the number of required fields. The function returns 1 if the line is invalid and 0 if it is valid.

int test_line(char* line, int num_fields, int* required_fields, int num_required_fields) {
    if (line[0] == '\0' || line[0] ==';') {
        return 1;
    }
    int num_semicolons = 0;
    int num_empty_fields = 0;
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == ';') {
            num_semicolons++;
            if (line[i-1] == ';' || line[i+1] == ';') {
                num_empty_fields++;
            }
        }
    }
    if (num_semicolons == num_fields-1 && num_empty_fields == 0) {
        char* fields[num_fields];
        char* field = strtok(line, ";");
        int field_index = 0;
        while (field != NULL) {
            fields[field_index] = field;
            field = strtok(NULL, ";");
            field_index++;
        }
        for (int i = 0; i < num_required_fields; i++) {
            if (strlen(fields[required_fields[i]]) == 0) {
                return 1;
            }
        }
        return 0;
    } else {
        return 1;
    }
}

// ========================= Read_users ======================

// Description:

// This  function checks if a city exists in the citythatexists array. If it does not exist, the function adds it to the array.

static void is_in_array(char**citythatexists,int *size,int*howmany,char*city){

    if ((*size) == (*howmany)){
    (*size) +=10;
     citythatexists = (char **)realloc(citythatexists, (*size)*sizeof(char*));
    }

for (int i = 0; i < (*howmany); i++){
    if(strcmp(citythatexists[i],city)==0) return;
}
citythatexists[(*howmany)] = strdup(city);
(*howmany)+=1;

}

// Description:

// This function takes a single line from a CSV file as input, parses it to extract the individual fields and creates a Users object from the extracted data.

static Users lineToUsers(char *buffer) {
//username; name; gender; birth_date; account_creation; pay_method; account_status
char *temp = strdup(buffer);
int required_fields[4] = {0,1,2,5};
if (test_line(buffer,7,required_fields,4) == 1){free(temp);return NULL;}
    Users new = initUsers();
    if (new == NULL){free(new);return NULL;}
    char *username = strsep(&temp ,";");
    char *name = strsep(&temp ,";");
    char *gender = strsep(&temp ,";");
    char *birth_date = strsep(&temp ,";");
    if (test_date(birth_date)==1){free(username);free_user2(new);return NULL;}
    char *account_creation = strsep(&temp ,";");
    if (test_date(account_creation)==1){free(username);free_user2(new);return NULL;}
    char *pay_method = strsep(&temp ,";");
    char * account_status = strsep(&temp ,"\n");
    if (test_account_status(account_status)==1){free(username);free_user2(new);return NULL;}


    u_setUsername (new, username);
    u_setName(new,name);
    u_setGender(new, gender);
    u_setBirthDate(new, birth_date);
    u_setAccount_creation (new, account_creation);
    u_setAccount_status (new, account_status );
    free(username);
    
    return new;
}

// users.csv

// Description:

// This function reads the content of a CSV file that contains information about users. The function creates a Users_Collection object and fills it with Users objects, which are extracted from each line of the CSV file.

Users_Collection readUsers(char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("Erro ao abrir ficheiro -> %s\n", filepath);
        return NULL;
    }
    size_t max_size; //alterar se for preciso dependendo do tamanho
    Users_Collection ucoll = initUColl();
    char *line = malloc(sizeof(char) * max_size);
    //username, name, gender, pay_method;
    while (getline(&line, &max_size, fp) != -1) {
            Users new = lineToUsers(line);
            if(new == NULL) continue;
             inserUser(ucoll,new);
         
           
    }
    fclose(fp);
    free(line);
    return ucoll;
}

// ========================= Read_drivers ======================

// Description:

// This function takes a single line from a CSV file as input, parses it to extract the individual fields and creates a Drivers object from the extracted data.

static Drivers lineToDrivers(char *buffer) {
//id; name, birth_date; gender; car_class; license_plate; city; account_creation; account_status
char *temp = strdup(buffer);
int required_fields[5] = {0,1,3,5,6};
if (test_line(buffer,9,required_fields,5) == 1){free(temp);return NULL;}
    
    Drivers new = initDrivers();
    if (new == NULL){free(new);return NULL;}
    char *id = strsep(&temp,";");
    char *name = strsep(&temp,";");
    char *birth_date = strsep(&temp,";");
    if (test_date(birth_date)==1){free(id);free_driver2(new);return NULL;}
    char *gender= strsep(&temp,";");
    char *car_class = strsep(&temp,";");
    if (test_car_class(car_class)==1){free(id);free_driver2(new);return NULL;}
    char *license_plate= strsep(&temp,";");
    char *city = strsep(&temp,";");
    char *account_creation = strsep(&temp,";");
    if (test_date(account_creation)==1){free(id);free_driver2(new);return NULL;}
    char *account_status = strsep(&temp,"\n");
    if (test_account_status(account_status)==1){free(id);free_driver2(new);return NULL;}
    


    d_setId (new,id);
    d_setName (new,name);
    d_setBirth_date (new,birth_date);
    d_setGender (new,gender);
    d_setCar_class (new,car_class);
    d_setAccount_creation (new,account_creation);
    d_setAccount_status (new,account_status);
    free(id);
    return new;
}

// drivers.csv

// Description:

// This function reads the content of a CSV file that contains information about drivers. The function creates a Drivers_Collection object and fills it with Drivers objects, which are extracted from each line of the CSV file.

Drivers_Collection readDrivers(char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("Erro ao abrir ficheiro -> %s\n", filepath);
        return NULL;
    }
    size_t max_size; //alterar se for preciso dependendo do tamanho
    Drivers_Collection dcoll = initDColl();
    char *line = malloc(sizeof(char) * max_size);
    while (getline(&line, &max_size, fp) != -1) {
            Drivers new = lineToDrivers(line);
            if(new==NULL) continue;
            inserDrivers(dcoll,new);  
         
    }
    fclose(fp);
    free(line);
    return dcoll;
}
// ========================= Read_rides ======================

// Description:

// This function is called for each line of the file to convert the line of text into a Rides data structure.

static Rides lineToRides(char *buffer,char *scus,char *scdr) {
    //"id;date;driver;user;city;distance;score_user;score_driver;tip;comment"
    //id;date;driver;user;city;distance;score_user;score_driver;tip;comment
char *temp = strdup(buffer);
int required_fields[4] = {0,2,3,4};
if (test_line(buffer,10,required_fields,4) == 1){free(temp);return NULL;}
    Rides new = initRides();
    if (new == NULL){free(new);return NULL;}
   
    char *id = strsep(&temp,";");
    char *date = strsep(&temp,";");
    if (test_date(date)==1){free(id);free(new);return NULL;}
    char *driver = strsep(&temp,";");
    char *user = strsep(&temp,";");
    char *city = strsep(&temp,";");
    char *distance = strsep(&temp,";");
    if (test_distance(distance) == 1 ) {free(id);free(new);return NULL;}
    char *score_user = strsep(&temp,";");
    if (test_distance(score_user) == 1 ) {free(id);free(new);return NULL;}
    char *score_driver = strsep(&temp,";");
    if (test_distance(score_driver) == 1 ) {free(id);free(new);return NULL;}
    char *tip = strsep(&temp,";");
    if (test_intordouble(tip) == 1 ) {free(id);free(new);return NULL;}
    char *comment = strsep(&temp,"\n");


    r_setId(new, id);
    r_setDate(new,date);
    r_setDriver(new, driver);
    r_setUser(new, user);
    r_setCity(new, city);
    r_setDistance(new, distance);
    strcpy(scus,score_user);
    strcpy(scdr,score_driver);
    r_setTip(new,tip);
    free(id);
    return new;
}

// rides.csv

// Description:

// This function reads the rides from the file specified in filepath. If the file cannot be opened, it returns NULL. 
// The function reads each line of the file and calls the lineToRides function to convert the line into a Rides data structure. The function then updates the users and drivers collections by calling u_add_ride and d_add_ride. 
// Finally, the function inserts the new ride into the rides collection using inserRide and adds the city of the ride to the citythatexists array.

Rides_Collection readRides(char *filepath, Drivers_Collection dcoll,Users_Collection ucoll,char**citythatexists,int *size,int*howmany) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("Erro ao abrir ficheiro -> %s\n", filepath);
        return NULL;
    }
    size_t max_size; //alterar se for preciso dependendo do tamanho
    Rides_Collection rcoll = initRColl();
    char *line = malloc(sizeof(char) * max_size);
    char * p;
    char *scus = malloc(sizeof(char) * 3);
    char *scdr = malloc(sizeof(char) * 3);
    while (getline(&line, &max_size, fp)!= -1) {
         
            Rides new = lineToRides(line,scus,scdr);
            
            if(new==NULL) continue;
            char * aux = r_getUser(new);
            char * aux2 = r_getDriver(new);
            int dist = r_getDistance(new);
            double inc =strtod(scus,&p);
            double inc2 =strtod(scdr,&p);
            double tip =r_getTip(new);
            Users u = look_up_users(ucoll,aux);
            Drivers d = look_up_drivers(dcoll,aux2);


            char *car_class =d_getCar_class(d);
            char *car_class2 =d_getCar_class(d);
            char *data = r_getDate(new);
            u_add_ride(u,inc,car_class,dist,tip,data);
            char *city = r_getCity(new);
            d_add_ride(d,inc2,car_class2,dist,tip,data,city);
           
	
           inserRide(rcoll,new);
           is_in_array(citythatexists,size,howmany,city);
           free(city);
           free (aux);
           free (data); 
           free(car_class);
           free(car_class2);
           free (aux2);
    }
    free(line);
    free(scus);
    free(scdr);
    fclose(fp);
    return rcoll;
}