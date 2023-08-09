#include "users.h"



// colecao users
struct ucoll {
    GHashTable *table;
};

// uma entrada users 
struct user {
    char *username;
    char *name;
    char *gender;
    char *birth_date;
    char *account_creation;
    char account_status;
    char *last_ride_date;
    double *score;
    double *distance_total;
    double *total_gasto;
    int*num_rides;
};

// ============================  INITS  ============================

// Description:

// This function frees all dynamically allocated memory for a user struct

void free_user(gpointer data) {
    struct user *u = (struct user *) data;
    free(u->username);
    free(u->name);
    free(u->gender);
    free(u->birth_date);
    free(u->account_creation);
    free(u->last_ride_date);
    free(u->score);
    free(u->distance_total);
    free(u->total_gasto);
    free(u->num_rides);
   
    free(u);
}

// Description:

// This function frees all dynamically allocated memory for a user struct that is passed in as a Users type.

void free_user2(Users u) {
    free(u->last_ride_date);
    free(u->score);
    free(u->distance_total);
    free(u->total_gasto);
    free(u->num_rides);
   
    free(u);
}

// Description:

// This function creates a new Users_Collection struct and initializes it by allocating memory for it

Users_Collection initUColl() {
    Users_Collection ucoll = (Users_Collection) malloc(sizeof(struct ucoll));
    ucoll->table = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, free_user); //funcao glib
    // criar free_rides...
    return ucoll;
}

// Description:

// This function creates a new user struct and initializes it by allocating memory for its fields, setting the last ride date to "00/00/0000", initializing all other fields to 0, and returning a pointer to the newly created user struct.

Users initUsers() {

    Users r = (Users) malloc(sizeof(struct user));
    r->score = malloc(sizeof(double));
    r->total_gasto = malloc(sizeof(double));
    r->distance_total = malloc(sizeof(double));
    r->num_rides = malloc(sizeof(int));
    r->last_ride_date = malloc (sizeof(10));
    r->last_ride_date=strdup("00/00/0000");
    *(r->score) = 0.0;
    *(r->total_gasto) = 0.0;
    *(r->distance_total) = 0.0;
    *(r->num_rides)=0;
    return r;
    
}
// ============================ GETTERS ============================
// vai buscar valor que est\u00e1 numa user (strdup para garantir encapsulamento)
// meter u_ atras disto


char *u_getUsername(Users u) {
    return strdup(u->username);
}

char *u_getName(Users u) {
    return strdup(u->name);
}

char *u_getGender(Users u) {
    return strdup(u->gender);
}

char *u_getBirthDate(Users u) {
    return strdup(u->birth_date);
}

char *u_getAccount_creation(Users u) {
    return strdup(u->account_creation);
}

char u_getAccount_status(Users u) {
    return u->account_status;
}

char *u_getlastRide(Users u) {
    return strdup(u->last_ride_date);
}

double *u_getScore(Users u) {
    return u->score;
}

double *u_getTotal(Users u) {
    return u->total_gasto;
}

double *u_getDistanceTotal(Users u) {
    return u->distance_total;
}

int u_getNumRides(Users u) {
    return *(u->num_rides);
}
//username; name; gender; birth_date; account_creation; pay_method; account_status

// ============================ SETTERS ============================

void u_setUsername(Users u, char *username) {
    u->username = strdup(username);
    
}
void u_setName(Users u, char *name) {
    u->name = strdup(name);
}
void u_setGender(Users u, char *gender) {
    u->gender = strdup(gender);
}
void u_setBirthDate (Users u, char *birth_date) {
    u->birth_date = strdup(birth_date);
}
void u_setAccount_creation (Users u, char *account_creation) {
    u->account_creation = strdup(account_creation);
}
void u_setAccount_status (Users u, char *account_status) {
    if (strcmp(account_status,"inactive")==0){
    u->account_status = 1;
    }
    else {
    u->account_status = 0;
    }
}

// Description:

// This function updates the user struct passed in as an argument by adding new ride information such as score, total distance traveled, total spent, and last ride date.

void u_add_ride (Users u,double new_score,char*car_class,int distance,double tip,char*new_date){

    *(u->score) += new_score;
    *(u->num_rides)+=1;
    char *p;
    *(u->total_gasto) += get_preco(car_class,distance)+tip;
    *(u->distance_total) += (double)distance; 
    if (u->last_ride_date==NULL){
        
        u->last_ride_date = strdup(new_date);
        return;
    }
   if (more_recent(new_date, u->last_ride_date) == 0){
        char *nd = strdup(new_date);
        free(u->last_ride_date);
        u->last_ride_date = nd;
        return;
    }

}

// Description:

// This function returns an array of the keys of the hash table in the Users_Collection struct passed in as an argument and sets the size of the array to *size

char **u_give_array(Users_Collection ucoll,int *size){

return (char**) g_hash_table_get_keys_as_array (ucoll->table,size);

}

//Description:

// This function inserts a Users struct into the hash table in the Users_Collection struct passed in as an argument using the username as the key.

int inserUser (Users_Collection ucoll, Users new){

  return g_hash_table_insert (ucoll->table,new->username,new);

}

// Description:

// This  function returns the user struct in the hash table in the Users_Collection struct passed in as an argument that corresponds to the key passed in as an argument.

Users look_up_users (Users_Collection ucoll,char* key){

   Users r = g_hash_table_lookup(ucoll->table,key);

return r;

}

// Description:

// This function destroys the hash table in the Users_Collection struct passed in as an argument and frees the memory for the Users_Collection struct.

void u_destroy (Users_Collection u){

g_hash_table_destroy (u->table);
free(u);
}


// Description:

// This function takes last element as pivot, places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot */

static int partition(char **arr, int low, int high,Users_Collection ucoll)
{
    Users u1,u2;
    u1 = look_up_users(ucoll,arr[high]);
    double pivot = *(u1->distance_total); // pivot
    double e; 
    int i = (low - 1); // Index of smaller element and indicates
                       // the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        u2 = look_up_users(ucoll,arr[j]);
        e = *(u2->distance_total);
        
        if (e >= pivot){
            if (e==pivot){
            int date = more_recent(u1->last_ride_date,u2->last_ride_date);
            if (date==0){
               continue; 
            }
            if (date == 2){
            		char *us1= u_getUsername(u1);
            		char *us2= u_getUsername(u2);
            		int temp  = strcmp(us1,us2);
            		free(us1);
            		free(us2);
                   
                     if (temp < 0){continue;}
                


            }
            }
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1],&arr[high]);
    return (i + 1);
}
  
// Description:

// The main function that implements QuickSort arr[] --> Array to be sorted, low --> Starting index, high --> Ending index */

void u_quickSort(char **arr, int low, int high,Users_Collection ucoll)
{
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr,low,high,ucoll);
  
        // Separately sort elements before
        // partition and after partition
        u_quickSort(arr, low, pi - 1,ucoll);
        u_quickSort(arr, pi + 1, high,ucoll);
    }
}