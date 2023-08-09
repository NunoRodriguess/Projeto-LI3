#include "drivers.h"

// colecao drivers
struct dcoll {
    GHashTable *table;
};
// uma entrada drivers

struct LinkedList{
    int num_rides;
    double score;
    char *city;
    struct LinkedList *next;
 };

struct driver {
    char *id;
    char *name;
    char *birth_date;
    char *gender;
    char *car_class;
    char *account_creation;
    char account_status;
    char *last_ride_date;
    double *score;
    double *total_gasto;
    int*num_rides;
    City list;

};

// Description:

// This function frees memory associated with a driver struct by freeing memory of individual components and linked list of city structs.

void free_driver(gpointer data) {
    struct driver *d = (struct driver *) data;
    free(d->id);
    free(d->name);
    free(d->birth_date);
    free(d->gender);
    free(d->car_class);
    free(d->account_creation);
    free(d->last_ride_date);
    free(d->score);
    free(d->total_gasto);
    free(d->num_rides);
    City current = d->list;
    City temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->city);
        free(temp);
    }
    free(d);
}

// Description:

// This function frees memory associated with a driver struct by freeing memory of individual components.

void free_driver2(Drivers d) {

   free(d->last_ride_date);
   free(d->score);
   free(d->total_gasto);
   free(d->num_rides);
    free(d);
}

// Description:

// This function creates and initializes a driver collection struct, which uses a hash table from GLib library and sets a custom deallocation function free_driver to be called when a driver is removed from the hash table.

Drivers_Collection initDColl() {
    Drivers_Collection dcoll = (Drivers_Collection) malloc(sizeof(struct dcoll));
    dcoll->table = g_hash_table_new_full(g_str_hash, g_str_equal, NULL,free_driver); //funcao glib
    // criar free_rides...
    return dcoll;
}

// Description:

// This function creates a new city struct node with initialized values.

City createNode(){
    City temp; 
    temp = (City)malloc(sizeof(struct LinkedList));
    temp->city = NULL;
    temp->next = NULL;
    return temp;
}

// Description:

// This function adds a new city struct node to a linked list of city structs with the specified city name and score.

City addNode(City head, double value,char*cityy){
    City temp,p;// declare two nodes temp and p
    temp = createNode();//createNode will return a new node with data = value and next pointing to NULL.
    temp->score = value; // add element's value to data part of node
    temp->num_rides = 1;
    temp->city = strdup(cityy);
    if(head == NULL){
        head = temp;     //when linked list is empty
    }
    else{
        p  = head;//assign head to p 
        while(p->next != NULL){
            p = p->next;//traverse the list until p is the last node.The last node always points to NULL.
        }
        p->next = temp;//Point the previous last node to the new node created.
    }
    return head;
}

// Description:

// This function increments the score and number of rides of a city struct node in a linked list of city structs associated with a driver, or adds a new node to the linked list if the city does not exist yet.

void incNode(Drivers d,char *cityC,double new_score){
 if (d->list==NULL){
d->list = addNode(d->list,new_score,cityC);


}
else{
City p;
p =d->list;
while(p != NULL){
    if (strcmp(p->city,cityC)==0){
        break;
    }
    p = p->next;
  }

if (p!=NULL){
    
        p->score +=new_score;
        p->num_rides +=1;
    }
    else {

        d->list = addNode(d->list,new_score,cityC);
    }

}
}

// Description:

// This function retrieves the score of a city struct node in a linked list of city structs associated with a driver.

double c_getScore(Drivers d,char*cityC ){
    City p;
    p = d->list;
    while(p != NULL){
    if (strcmp(p->city,cityC)==0){
        break;
    }
    p = p->next;
  }
  if (p!=NULL){
       return p->score;
    }
    else {
     return 0.0;
    }
}

// Description:

// This function retrieves the number of rides of a city struct node in a linked list of city structs associated with a driver.

double c_getNumRides(Drivers d,char*cityC ){
    City p;
    p = d->list;
    while(p != NULL){
    if (strcmp(p->city,cityC)==0){
        break;
    }
    p = p->next;
  }
  if (p!=NULL){
       return p->num_rides;
    }
    else {
     return 0.0;
    }
}

// Description:

// This function creates and initializes a driver struct with initialized values.

Drivers initDrivers() {
 Drivers r = (Drivers) malloc(sizeof(struct driver));
    r->score = malloc(sizeof(double));
    r->total_gasto = malloc(sizeof(double));
    r->num_rides = malloc(sizeof(int));
    *(r->score) = 0.0;
    *(r->total_gasto) = 0.0;
    *(r->num_rides)=0;
    r->last_ride_date=strdup("00/00/0000");
    r->list = NULL;
    return r;
}

// ============================ GETTERS ============================
// vai buscar valor que est\u00e1 numa driver (strdup para garantir encapsulamento)
// meter d_ atras disto


char *d_getId(Drivers r) {
    return strdup(r->id);
}
char *d_getName(Drivers r) {
    return strdup(r->name);
}
char *d_getBirth_date(Drivers r) {
    return strdup(r->birth_date);
}

char *d_getGender(Drivers r) {
    return strdup(r->gender);
}

char *d_getCar_class(Drivers r) {
    return strdup(r->car_class);
}

char *d_getAccount_creation(Drivers r) {
    return strdup(r->account_creation);
}

char d_getAccount_status(Drivers r) {
    return r->account_status;
}

char *d_getLast_Ride(Drivers r) {
    return strdup(r->last_ride_date);
}

double *d_getScore(Drivers d) {
    return d->score;
}

double *d_getTotal(Drivers d) {
    return d->total_gasto;
}

int d_getNumRides(Drivers d) {
    return *(d->num_rides);
}

// ============================ SETTERS ============================

//id; name, birth_date; gender; car_class; license_plate; city; account_creation; account_status

void d_setId (Drivers d, char *id) {
    d->id = strdup(id);
}

void d_setName (Drivers d, char *name) {
    d->name = strdup(name);
}

void d_setBirth_date (Drivers d, char *birth_date) {
    d->birth_date = strdup(birth_date);
}

void d_setGender (Drivers d, char *gender) {
    d->gender = strdup(gender);
}

void d_setCar_class (Drivers d, char *car_class) {
    d->car_class = strdup(car_class);
}


void d_setAccount_creation (Drivers d, char *account_creation) {
    d->account_creation = strdup(account_creation);
}

void d_setAccount_status (Drivers d, char *account_status) {

    if (strcmp(account_status,"inactive")==0){
    d->account_status = 1;
    }
    else {
    d->account_status = 0;
    }
}

// Description:

// This function inserts a new driver into the "Drivers_Collection" data structure.
int inserDrivers(Drivers_Collection dcoll, Drivers new){

    return g_hash_table_insert (dcoll->table,new->id,new);

}

// Description:

// This function checks if the input string is a valid date or not. It returns the number of '/' characters in the input string. If there are not enough '/' characters, the function returns 0, indicating that the input string is not a date.
static int check_date(char*date){
int counter=0;
if (date == NULL) return 0 ; 

    for (int i = 0;date[i]!='\0';i++) {

        if (date[i]=='/') counter +=1;

    }


    return counter;



} // 0 se n\u00e3o for date

// Description:

// This function updates the information of a driver after a ride. It updates the driver's score, number of rides, total expenses, and last ride date

void d_add_ride (Drivers d,double new_score,char*car_class,int distance,double tip,char*new_date,char *city){

    *(d->score) += new_score;
    *(d->num_rides)+=1;
    incNode(d,city,new_score);
    *(d->total_gasto) += get_preco(car_class,distance) + tip;
    if (d->last_ride_date==NULL){
        
        d->last_ride_date = strdup(new_date);
        return;
    }
   if (more_recent(new_date, d->last_ride_date) == 0){
        char *nd = strdup(new_date);
        free(d->last_ride_date);
        d->last_ride_date = nd;
        return;
    }
   
}

// Description:

// This function looks up a driver in the "Drivers_Collection" data structure, given a key (ID). 

Drivers look_up_drivers (Drivers_Collection dcoll,char* key){

   Drivers r = g_hash_table_lookup(dcoll->table,key);

return r;

}

// Description:

// This function returns an array of strings containing the IDs of all drivers in the "Drivers_Collection" data structure. The size of the array is stored in the variable pointed to by "size".

char **d_give_array(Drivers_Collection dcoll,int *size){

return (char**) g_hash_table_get_keys_as_array (dcoll->table,size);

}

// Description:

// his function frees the memory of an object stored in a hash table.

static void free_table(void* v) {
    return;
}

// Description:

// This function destroys a "Drivers_Collection" data structure and frees the memory associated with it.
void d_destroy (Drivers_Collection d){

   g_hash_table_destroy(d->table);
free(d);
} 

// Description:

// This function takes last element as pivot, places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot 

static int partition(char **arr, int low, int high,Drivers_Collection dcoll)
{
    Drivers d1,d2;
    d1 = look_up_drivers(dcoll,arr[high]);
    double pivot = (*(d1->score)/(double) *(d1->num_rides)); // pivot
    double e; 
    int i = (low - 1); // Index of smaller element and indicates
                       // the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        d2 = look_up_drivers(dcoll,arr[j]);
        e = (*(d2->score)/(double) *(d2->num_rides));
        
        if (e >= pivot){
            if (e==pivot){
            int date = more_recent(d1->last_ride_date,d2->last_ride_date);
            if (date==0){
               continue; 
            }
            if (date == 2){
            		char *id1= d_getId(d1);
            		char *id2= d_getId(d2);
            		int temp  = strcmp(id1,id2);
            		free(id1);
            		free(id2);
                   
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

void d_quickSort(char **arr, int low, int high,Drivers_Collection dcoll)
{
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr,low,high,dcoll);
  
        // Separately sort elements before
        // partition and after partition
        d_quickSort(arr, low, pi - 1,dcoll);
        d_quickSort(arr, pi + 1, high,dcoll);
    }
}

// Description:

// This function selects a pivot from the elements in the array, rearranges the elements in such a way that elements less than the pivot come before it, while elements greater than the pivot come after it.
// At the end of the function, the pivot is placed in the correct position in the sorted array, and the index of the pivot is returned.

static int c_partition(char **arr, int low, int high,Drivers_Collection dcoll,char *city)
{
    Drivers d1,d2;
    d1 = look_up_drivers(dcoll,arr[high]);
    double pivot = c_getScore(d1,city) / (double) c_getNumRides(d1,city); // pivot
    double e; 
    int i = (low - 1); // Index of smaller element and indicates
                       // the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        d2 = look_up_drivers(dcoll,arr[j]);
        e = c_getScore(d2,city) / (double) c_getNumRides(d2,city);
        
        if (e >= pivot){
            if (e==pivot){
            
            		char *id1= d_getId(d1);
            		char *id2= d_getId(d2);
            		int temp  = strcmp(id1,id2);
            		free(id1);
            		free(id2);
                   
                     if (temp > 0){continue;}
                


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

void c_quickSort(char **arr, int low, int high,Drivers_Collection dcoll,char *city)
{
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = c_partition(arr,low,high,dcoll,city);
  
        // Separately sort elements before
        // partition and after partition
        c_quickSort(arr, low, pi - 1,dcoll,city);
        c_quickSort(arr, pi + 1, high,dcoll,city);
    }
}

// Description:

// This function checks if a Drivers object is null.

int Isnull_id(Drivers d){
    
    if (d == NULL ) return 0;
    else return 1;


}
  