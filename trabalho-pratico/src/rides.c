#include "rides.h"


// colecao rides
struct rcoll {
    GHashTable *table;
};

// uma entrada ride
struct ride {
    char *id;
    char *date;
    char *driver;
    char *user;
    char *city;
    int distance;
    double tip;
};

// ============================  INITS  ============================
Rides_Collection initRColl() {
    Rides_Collection rcoll = (Rides_Collection) malloc(sizeof(struct rcoll));
    rcoll->table = g_hash_table_new_full(g_str_hash, g_str_equal, NULL,free_ride); //funcao glib
    // criar free_rides...
    return rcoll;
}

void free_ride(gpointer data) {
    struct ride* r = (struct ride*) data;
    free(r->id);
    free(r->date);
    free(r->driver);
    free(r->user);
    free(r->city);
    free(r);
}
Rides initRides() {
    return (Rides) malloc(sizeof(struct ride));
}

// ============================ GETTERS ============================
// vai buscar valor que est\u00e1 numa ride (strdup para garantir encapsulamento)
// meter r_ atras disto

char *r_getId(Rides r) {
    return strdup(r->id);
}

char *r_getDate(Rides r) {
    return strdup(r->date);
}

char *r_getDriver(Rides r) {
    return strdup(r->driver);
}

char *r_getUser(Rides r) {
    return strdup(r->user);
}
char *r_getCity(Rides r) {
    return strdup(r->city);
}
int r_getDistance(Rides r) {
    return r->distance;
}
double r_getTip(Rides r) {
    return r->tip;
}



// ============================ SETTERS ============================

// Aqui n\u00e3o t\u00eam de ser Rides *r ?

void r_setId(Rides r, char *id) {
    r->id = strdup(id);
}

void r_setDate(Rides r, char *date) {
    r->date = strdup(date);
}

void r_setDriver(Rides r, char *driver) {
    r->driver = strdup(driver);
}

void r_setUser(Rides r, char *user) {
    r->user = strdup(user);
}
void r_setCity(Rides r, char *city) {
    r->city = strdup(city);
}
void r_setDistance(Rides r, char *distance) {
    r->distance = atoi(distance);
}
void r_setTip(Rides r, char *tip) {
    char *p;
    r->tip = strtod(tip,&p);
}

// Description:

// This function is used to insert a new ride into the Rides_Collection data structure.

int inserRide(Rides_Collection rcoll, Rides new){

   return g_hash_table_insert (rcoll->table,new->id,new);

}

// Description:

// This is a static function which takes a void pointer v as an argument. It does not perform any action and returns immediately.

static void free_table(void* v) {
    return;
}

// Description:

// This function is used to look up a ride in the Rides_Collection data structure using the ride id as the key.

Rides look_up_rides (Rides_Collection rcoll,char* key){

Rides r = g_hash_table_lookup(rcoll->table,key);

return r;

}

// Description:

// This function is used to get an array of ride ids from the Rides_Collection data structure.

char **r_give_array(Rides_Collection rcoll,int *size){

return (char**) g_hash_table_get_keys_as_array (rcoll->table,size);

}

// Description:

// This function is used to destroy the Rides_Collection data structure.

void r_destroy (Rides_Collection r){
g_hash_table_destroy(r->table);
free(r);
}


// A utility function to swap two elements

  
// Description:

// This function takes last element as pivot, places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot */

static int partition(char **arr, int low, int high,Rides_Collection rcoll)
{
    Rides r1,r2;
    char *p;
    r1 = look_up_rides(rcoll,arr[high]);
    int pivot = r_getDistance(r1); // pivot
    int e; 
    int i = (low - 1); // Index of smaller element and indicates
                       // the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        r2 = look_up_rides(rcoll,arr[j]);
        e = r_getDistance(r2);

        
        if (e >= pivot){
            if (e==pivot){
                char*date1 = r_getDate(r1);
            	char*date2 = r_getDate(r2);
            int date = more_recent(date1,date2);
            free(date1);
            free(date2);
            if (date==0){
               continue; 
            }
            if (date == 2){
            		char *id1= r_getId(r1);
            		char *id2= r_getId(r2);
            		int temp  = strcmp(id1,id2);
            		free(id1);
            		free(id2);
                   
                     if (temp > 0){continue;}
                


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

void r_quickSort(char **arr, int low, int high,Rides_Collection rcoll)
{
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr,low,high,rcoll);
  
        // Separately sort elements before
        // partition and after partition
        r_quickSort(arr, low, pi - 1,rcoll);
        r_quickSort(arr, pi + 1, high,rcoll);
    }
}