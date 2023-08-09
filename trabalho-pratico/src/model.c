#include "model.h"

struct q4 {

    double value;
    char *city;
    struct q4*next;
 };

struct model {
    Rides_Collection rides; //
    Drivers_Collection drivers; //
    char** keyArray_d; // 
    char** keyArray_d_2; // 
    char** keyArray_u;// 
    char** keyArray_r;// 
    int *r_size;// 
    int *d_size;// 
    int *d_size2;// 
    int *u_size;// 
    char *lastcity;// 
    char **starray; //
    Users_Collection users; //
    Q4 backuplist; //
    int starray_size; //
    int how_many_starray; //
    char isIn; //
};

// Description:

// This function creates an instance of the data model and initializes its members.

Model initModel() {
    Model m = malloc(sizeof(struct model));
    m->rides = NULL;
    m->drivers = NULL;
    m->users = NULL;
    m->keyArray_d=NULL;
    m->keyArray_u=NULL;
    m->keyArray_r=NULL;
    m->lastcity=NULL;
    m->backuplist = NULL;
    m->r_size = malloc(sizeof(int));
    m->d_size = malloc(sizeof(int));
    m->d_size2 = malloc(sizeof(int));
    m->u_size = malloc(sizeof(int));
    m->starray =(char **) malloc(10 * sizeof(char*));
    m->starray_size =10;
    m->how_many_starray = 0;
    m->isIn = 1;
    return m;
}

// Description:

// This function creates an instance of the data model, reads data from csv files, and initializes its members.

Model load_model(char *ridesc,char*driversc,char*usersc){

    Model m = initModel();
    if (!(ridesc && ridesc[0])) ridesc = "rides.csv";
    if (!(usersc && usersc[0])) usersc = "users.csv";
    if (!(driversc && driversc[0])) driversc= "drivers.csv";

    m->users=readUsers(usersc);
    m->drivers=readDrivers(driversc);
    m->rides=readRides(ridesc,m->drivers,m->users,m->starray,&m->starray_size,&m->how_many_starray);
    m->keyArray_d=d_give_array(m->drivers,m->d_size);
    m->keyArray_d_2=d_give_array(m->drivers,m->d_size2);
    d_quickSort(m->keyArray_d,0,*(m->d_size)-1,m->drivers);
    m->keyArray_u=u_give_array(m->users,m->u_size);
    u_quickSort(m->keyArray_u,0,*(m->u_size)-1,m->users);
    m->keyArray_r=r_give_array(m->rides,m->r_size); 
return m;
}


// Description:

// This function frees an array of strings.

 void free_string_array(char **strings, int size) {
    for (int i = 0; i < size; i++) {
        if (strings[i] != NULL)
            free(strings[i]);
    }
    free(strings);
}

// Description:

// This function frees all the memory used by the data model instance.

void free_model (Model m){
r_destroy(m->rides);
d_destroy(m->drivers);
u_destroy(m->users);
free(m->keyArray_r);
free(m->keyArray_d);
free(m->keyArray_d_2);
free(m->keyArray_u);
free_string_array(m->starray,m->starray_size);
free(m->r_size);
free(m->d_size);
free(m->d_size2);
free(m->u_size);
if (m->lastcity!=NULL) free(m->lastcity);
Q4 current = m->backuplist;
    Q4 temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->city);
        free(temp);
    }
free(m);
}

// Description:

// This function creates a new node.

static Q4 createNodeq4(){
    Q4 temp; 
    temp = (Q4)malloc(sizeof(struct q4)); 
    temp->next = NULL;
    return temp;
}

// Description:

// This function adds a new node.

static Q4 addNodeq4(Q4 head, double value,char*cityy){
    Q4 temp,p;// declare two nodes temp and p
    temp = createNodeq4();//createNode will return a new node with data = value and next pointing to NULL.
    temp->value = value; // add element's value to data part of node
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

// This function is checking if the city is present in a linked list of nodes.
// The function uses a loop to traverse the linked list, comparing each city in the nodes with the input city, and returning the value of the node if a match is found. 
// If the linked list is empty or if the city is not found in the list, the function returns -1.

double isNode(Q4 head,char*city){

    if(head == NULL){
       return -1;     //when linked list is empty
    }
    Q4 p = head;

    while (p!=NULL){

        if (strcmp(p->city,city)==0){
            return p->value;
        }
        p = p->next;
    }
    return -1;
}

// Description:

// List the summary of a profile registered in the service through its identifier, represented by <ID>.

void q1 (Model m,char*buffer,FILE *fptr) {

shiftLeft(buffer,2);

    if (isUsername(buffer)==0) {

       Users u =look_up_users(m->users,buffer);

        if (u==NULL) return;
        if(u_getAccount_status(u)==1) return;
        int num = u_getNumRides(u);
        double p;
        if (num == 0) {p = 0.0;}
        if (num != 0) {p = (*u_getScore(u))/(double) num;}
        double gasto = *u_getTotal(u);
        char *birth=u_getBirthDate(u);
        char *y =strsep(&birth,"/");
        int year = atoi(y);
      	int month = atoi(strsep(&birth,"/"));
      	int day = atoi(strsep(&birth,"/"));
        int idade =age(day,month,year);
        char * name_print = u_getName(u);
        char * gender_print = u_getGender(u);
       fprintf(fptr,"%s;%s;%d;%.3f;%d;%.3f\n",name_print,gender_print,idade,p,num,gasto);
       free (y);
       free(name_print);
       free(gender_print);
    }
     if (isUsername(buffer)==1) {

        Drivers d =look_up_drivers(m->drivers,buffer);
        int o =Isnull_id(d);
        if (o==0) {return;}
        if (d_getAccount_status(d)==1) return;
        int num = d_getNumRides(d);
        double p;
        if (num == 0) { p = 0.0;}
        if (num != 0) { p = (*d_getScore(d))/(double) num;}
        double gasto = *d_getTotal(d);
        char *birth=d_getBirth_date(d);
        char *y =strsep(&birth,"/");
        char * name_print = d_getName(d);
        char * gender_print = d_getGender(d);
        int year = atoi(y);
      	int month = atoi(strsep(&birth,"/"));
      	int day = atoi(strsep(&birth,"/"));
        int idade =age(day,month,year);
       fprintf(fptr,"%s;%s;%d;%.3f;%d;%.3f\n",name_print,gender_print,idade,p,num,gasto);
       free (y);
       free(name_print);
       free(gender_print);
    }


}

// Description:

// List the N drivers with the highest average rating. 
// In the event of a tie, the result shall be sorted so that drivers with the most recent trip appear first. Case there is a new tie, the driver id must be used to break the tie (in ascending order) 

void q2 (Model m,char*buffer,FILE *fptr) {
    shiftLeft(buffer,1);
    int N = atoi(buffer);
    int size;
    for (int i = 0; i<N && i<*(m->d_size);i++){
        Drivers d = look_up_drivers(m->drivers,m->keyArray_d[i]);
        if (d_getAccount_status(d)==1){
            N+=1;
            continue;
        }
        
        int num = d_getNumRides(d);
        
        double p;
        if (num == 0) { p = 0.0;}
        if (num != 0) { p = *(d_getScore(d))/(double) num;}
        char *name_print = d_getName(d);
        fprintf(fptr,"%s;%s;%.3f\n",m->keyArray_d[i],name_print,p);
        free(name_print);
    }
    
}

// Description

// List the N users with the greatest distance traveled. 
// In case of a tie, the result shall be sorted so that users with the most recent trip appear first. If there is new tie, the user's username must be used to break the tie (in ascending order)

void q3 (Model m,char*buffer,FILE *fptr) {
    shiftLeft(buffer,1);
    int N = atoi(buffer);
    int size;
    for (int i = 0; i<N && i <*(m->u_size);i++){
        Users u = look_up_users(m->users,m->keyArray_u[i]);
        if (u_getAccount_status(u)==1){
            N+=1;
            continue;
        }
        double p = *u_getDistanceTotal(u) ;
        char *name_print = u_getName(u);
        fprintf(fptr,"%s;%s;%.0f\n",m->keyArray_u[i],name_print,p);
        free(name_print);
    }
    
}

// Description:

// Average price of trips (not including tips) in a given city, represented by <city>.

void q4 (Model m,char*buffer,FILE *fptr) {
    shiftLeft(buffer,2);
    double preco_medio;
    preco_medio =isNode(m->backuplist,buffer);
    if (preco_medio == -1){
    int size;
    size = *(m->r_size);
    int numVia = 0;
    preco_medio = 0.0;
    for (int i = 0 ; i <size;i++){

        Rides r = look_up_rides (m->rides,m->keyArray_r[i]);
        char *c = r_getCity(r);
        if (strcmp (c,buffer) == 0){

                char *dKey = r_getDriver(r);
                Drivers d = look_up_drivers(m->drivers,dKey);
                free(dKey);

            numVia +=1; 
            char *car_classf = d_getCar_class(d);
            int car_distf =r_getDistance(r);
            preco_medio += get_preco(car_classf,car_distf);
            free(car_classf);
            

        }
        free(c);

    }
    if (numVia != 0){

        preco_medio = preco_medio / (double) numVia;
    }
    else {
        return;
    }
    fprintf(fptr,"%.03f\n",preco_medio);
    m->backuplist=addNodeq4(m->backuplist,preco_medio,buffer);
    }

    else {
    fprintf(fptr,"%.03f\n",preco_medio);
   
    }
}

// Description:

// Average price of trips (not including tips) in a given time interval, this being range represented by <date A> and <date B>.

void q5 (Model m,char*buffer,FILE *fptr) {
    shiftLeft(buffer,2);
    char *data1 = strdup(buffer);
    data1[10] = '\0';
    shiftLeft(buffer,10);
    char *data2 = strdup(buffer);
    int size;
    size = *(m->r_size);
    int numVia = 0;
    double preco_medio = 0.0;
    for (int i = 0 ; i <size;i++){

        Rides r = look_up_rides (m->rides,m->keyArray_r[i]);
        char *tempdata = r_getDate(r);
        int c1 =more_recent(tempdata,data1);
        if(c1==1) {
        
        	free(tempdata);
        	continue;
        	
        }
        char *tempdata2 = strdup(tempdata);
        int c2 =more_recent(tempdata2,data2); 
        
        if (c2==1 || c2==2 ){ // return 0 se 1 mais nova 2 . 2 se iguais 

                char *dKey = r_getDriver(r);
                Drivers d = look_up_drivers(m->drivers,dKey);
                free(dKey);
            numVia +=1; 
            char *car_classf = d_getCar_class(d);
            int car_distf = r_getDistance(r);
            preco_medio += get_preco(car_classf,car_distf);
            free(car_classf);
            
        }
        free(tempdata);
        free(tempdata2);

    }
    if (numVia == 0){
    free(data1);
    free(data2);
    return;
    }
    preco_medio = preco_medio / (double) numVia;
    fprintf(fptr,"%.03f\n",preco_medio);
   
    free(data1);
    free(data2);

}

// Description:

// Average distance traveled, in a given city, represented by <city>, in a given time interval, being this interval represented by <date A> and <date B>

void q6 (Model m,char*buffer,FILE *fptr) {
    shiftLeft(buffer,2);
    char *cityy = strsep(&buffer," ");
    int j;
for (j = 0; j<m->how_many_starray;j++){

    if (strcmp(m->starray[j],cityy)==0) break;
        
    
}
if ( j == m->how_many_starray ) {
        
        return;
    }
    char *data1 = strdup(buffer);
    data1[10] = '\0';
    shiftLeft(buffer,10);
    char *data2 = strdup(buffer);
    int size;
    size = *(m->r_size); 
    int numVia = 0;
    double dist_media = 0.0;
    char * p; 
    for (int i = 0 ; i <size;i++){

        Rides r = look_up_rides (m->rides,m->keyArray_r[i]);
        char *citycmp = r_getCity(r);
        if(strcmp (citycmp,cityy) != 0){
        	
        	free(citycmp);
		continue;        
        }
        char *tempdata = r_getDate(r);
        int c1 =more_recent(tempdata,data1);
        if (c1==1){
        	free(tempdata);
        	free(citycmp);
        	continue;
        	
        	
        }
        char *tempdata2 = strdup(tempdata); 
        int c2 =more_recent(tempdata2,data2); 
        
        if (c2==1 || c2==2 ){ // return 0 se 1 mais nova 2 . 2 se iguais 

                char *dKey = r_getDriver(r);
                Drivers d = look_up_drivers(m->drivers,dKey);
                free(dKey);

            numVia +=1; 
            
         
            double dob = (double) r_getDistance(r);
            dist_media += dob;

        }
        free(tempdata);
        free(tempdata2);
        free(citycmp);
    }
    free(data1);
    free(data2);
    if (numVia== 0){
    return;
    }
    dist_media = dist_media / (double) numVia;
    fprintf(fptr,"%.03f\n",dist_media);
}

// Description:

// Top N drivers in a given city, represented by <city> (in the rides.csv file), sorted by average driver rating. 
// In case of a tie, the result shall be sorted through the driver id, in descending order.

void q7 (Model m,char*buffer,FILE *fptr) {

shiftLeft(buffer,2);
char *n_string= strsep(&buffer," ");
int N = atoi(n_string);
char *city = strsep(&buffer,"\n");
int j;
for (j = 0; j<m->how_many_starray;j++){

    if (strcmp(m->starray[j],city)==0) break;
        
    
}
if ( j == m->how_many_starray ) return;
int size;
char *p;
size = *(m->d_size2);
if (m->isIn == 1){
    m->lastcity = strdup(city);
    c_quickSort(m->keyArray_d_2,0,size-1,m->drivers,city);
    m->isIn = 0;
}else {

	if (strcmp(m->lastcity,city)!=0){
	c_quickSort(m->keyArray_d_2,0,size-1,m->drivers,city);
   	}
   	
	free(m->lastcity);
    	m->lastcity = strdup(city);
}
    for (int i = 0 ; i<N;i++){

        Drivers d = look_up_drivers(m->drivers,m->keyArray_d_2[i]);
        if (d_getAccount_status(d)==1){
            N+=1;
       
            continue;
        }
            
            char * id =d_getId(d);
            char * nome =d_getName(d);
            double av_media =c_getScore(d,city) / (double) c_getNumRides(d,city);
            if (isnan(av_media)) {
    			N+=1;
    			free(id);
            		free(nome);
    			continue;
		}	

            fprintf(fptr,"%s;%s;%.03f\n",id,nome,av_media);
            free(id);
            free(nome);
        
    }




}


static int partition(char **arr, int low, int high,Rides_Collection rcoll, Drivers_Collection dcoll,Users_Collection ucoll)
{
    
    Drivers d1,d2;
    Rides r1,r2;
    Users u1,u2;
    r1 = look_up_rides(rcoll,arr[high]);
    char *id1 = r_getDriver(r1);
    d1 = look_up_drivers(dcoll,id1);
    free(id1);
    char * pivot = d_getAccount_creation(d1); // pivot account creation
    char *e=NULL; 
    int i = (low - 1); // Index of smaller element and indicates
                       // the right position of pivot found so far
    
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        r2 = look_up_rides(rcoll,arr[j]);
        char *id2 = r_getDriver(r2);
        d2 = look_up_drivers(dcoll,id2);
        e = d_getAccount_creation(d2);
        free(id2);
        int date = more_recent(pivot,e);
        if (date == 0 || date==2){
            if (date==2){
                char *us1 = r_getUser(r1);
                u1 = look_up_users(ucoll,us1);
                free(us1);
                char *us2 = r_getUser(r2);
                u2 =look_up_users(ucoll,us2);
                free(us2);

                char *date2 =u_getAccount_creation(u1);
                char *date3 =u_getAccount_creation(u2);
                int date_cmp = more_recent(date2,date3);
                free(date2);
                free(date3);
                if (date_cmp == 1){
                free(e);
                    continue;
                }
                if (date_cmp == 2){
                    
                    char *idv1= r_getId(r1);
            		char *idv2= r_getId(r2);
            		int temp  = strcmp(idv1,idv2);
            		free(idv1);
            		free(idv2);
                   
                     if (temp < 0){free(e);continue;}
                }
            }
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
        free(e);
    }
    free(pivot);
    swap(&arr[i + 1],&arr[high]);
    return (i + 1);
}

// Description:

// This function sorts the elements in the arr array between indices low and high by repeatedly partitioning the subarray and then recursively sorting the two sub-arrays on either side of the partition. 

void q8_quickSort(char **arr, int low, int high,Rides_Collection rcoll, Drivers_Collection dcoll,Users_Collection ucoll)
{
 
    if (low < high) {

        int pi = partition(arr,low,high,rcoll,dcoll,ucoll);
  
    
        q8_quickSort(arr, low, pi - 1,rcoll,dcoll,ucoll);
        q8_quickSort(arr, pi + 1, high,rcoll,dcoll,ucoll);
    }
}

// Description:

// List all trips in which the user and the driver are of the gender passed as a parameter, represented by <gender> and have profiles with X or more years, where X is represented by <X>

void q8 (Model m,char*buffer,FILE *fptr) {
shiftLeft(buffer,2);
char *gender= strsep(&buffer," ");
char *n_string = strsep(&buffer,"\n");
int how_old = atoi(n_string);

int size;
size = *(m->r_size);  
int count = 0;
char **secondKeyArray;
secondKeyArray = malloc(size * sizeof(char*));

for (int i = 0 ; i<size;i++){

    Rides temp = look_up_rides(m->rides,m->keyArray_r[i]);
        char *username = r_getUser(temp);
        char *driver = r_getDriver(temp);
        Users u = look_up_users(m->users,username);
        Drivers d = look_up_drivers(m->drivers,driver);
        free(username);
        free(driver);
        char *genderU = u_getGender(u); //
        char *genderD = d_getGender(d); //
        char *accountcreU = u_getAccount_creation(u);
        char *accountcreD = d_getAccount_creation(d);
        char *creUdc = strsep(&accountcreU,"/");
        char *creUmc = strsep(&accountcreU,"/");
        char *creUyc = strsep(&accountcreU,"/");
        char *creDdc = strsep(&accountcreD,"/");
        char *creDmc = strsep(&accountcreD,"/");
        char *creDyc = strsep(&accountcreD,"/");
        int creUd = atoi(creUdc);
        int creUm = atoi(creUmc);
        int creUy = atoi(creUyc);
        int creDd = atoi(creDdc);
        int creDm = atoi(creDmc);
        int creDy = atoi(creDyc);
        free(creUdc);
        free(creDdc); 
        int ageU = age(creUy,creUm,creUd); //
        int ageD = age(creDy,creDm,creDd); //
        free(accountcreU);
        free(accountcreD);
        
         if (strcmp(genderD,genderU) == 0 && strcmp(gender,genderD)==0 && d_getAccount_status(d)==0 && u_getAccount_status(u)==0 && ageU >= how_old && ageD >= how_old){ 
                secondKeyArray[count] = (m->keyArray_r[i]);
                count++;
                }
        free(genderD);
        free(genderU);
}
q8_quickSort(secondKeyArray,0,count-1,m->rides,m->drivers,m->users);
for (int i = 0 ; i<count;i++){
 Rides temp3 = look_up_rides(m->rides,secondKeyArray[i]);

        char *id_driver = r_getDriver(temp3);
        char *username_user = r_getUser(temp3);

        Drivers dp = look_up_drivers(m->drivers,id_driver);
        Users up = look_up_users(m->users,username_user);
        char * name_driver = d_getName(dp);
        char * name_user = u_getName(up);
        
        fprintf(fptr,"%s;%s;%s;%s\n",id_driver,name_driver,username_user,name_user);
        free(id_driver);
        free(username_user);
        free(name_driver);
        free(name_user);
}
free(secondKeyArray);


}

// Description:

// List the trips on which the passenger tipped, in the time interval (date A, date B), this interval being represented by the parameters <data A> and <data B>, sorted in order of distance traveled (in descending order). 
// In the event of a tie, the most recent trips must appear first. If ties persist, sort by trip id (in descending order).

void q9 (Model m,char*buffer,FILE *fptr) {
    shiftLeft(buffer,2);
    char *data1 = strdup(buffer);
    data1[10] = '\0';
    shiftLeft(buffer,10);
    char *data2 = strdup(buffer);
    int size;
    char *p;
    size = *(m->r_size);  
    int count = 0;
    char **secondKeyArray;
    secondKeyArray = malloc(size * sizeof(char*));
    for (int i = 0 ; i<size;i++){

        Rides temp = look_up_rides(m->rides,m->keyArray_r[i]);
            char *d1 = r_getDate(temp);
            char *d2 = strdup(d1);
            int c1 =more_recent(d1,data1); 
            int c2 =more_recent(d2,data2);
            free(d1);
            free(d2);
            double tip_r = r_getTip(temp);
            if (tip_r > 0.0 && ((c1==0 || c1 ==2) && (c2==1 || c2==2 )) ){ 
                secondKeyArray[count] = (m->keyArray_r[i]);
                count++;
                }
             



    }
r_quickSort(secondKeyArray,0,count-1,m->rides);
for (int i = 0 ; i<count;i++){

        Rides temp3 = look_up_rides(m->rides,secondKeyArray[i]);
        char *id_print = r_getId(temp3);
        char *date_print = r_getDate(temp3);
        int dist_print = r_getDistance(temp3);
        char *city_print = r_getCity(temp3);
        double tip_print_db = r_getTip(temp3);
        fprintf(fptr,"%s;%s;%d;%s;%.03f\n",id_print,date_print,dist_print,city_print,tip_print_db);
        free(id_print);
        free(date_print);
        free(city_print);

    }
free(secondKeyArray);
free(data1);
free(data2);
}

// Description:

// The function starts by creating a header for the table and initializing the table with 6 columns and the given header.
// The function then checks if the input argument arg is a username or not.
// If arg is a username, it looks up the user information using the look_up_users function. If the user is not found or the user's account status is 1 (inactive), the function returns an empty table.
// If the argument is not a username, the function does the same for a driver. 
// Finally, the function adds the parameters as an entry in the table and returns the table.

Table q1_interativa (Model m, char *arg) { 
    char *header =strdup("Nome Genero Idade ScoreMedio NumeroViagens Gasto");
    Table t = init_table(6, header);
    init_entries(t, 1);
    char **params = malloc(sizeof(char*) * 6); // 6 por causa do n\u00famero de colunas
    if (isUsername(arg)==0) {
        Users u =look_up_users(m->users,arg);
        if (u==NULL) return t;
        if(u_getAccount_status(u)==1) return t;
        int num = u_getNumRides(u);
        double p;
        if (num == 0) {p = 0.0;}
        if (num != 0) {p = (*u_getScore(u))/(double) num;}
        double gasto = *u_getTotal(u);
        char *birth=u_getBirthDate(u);
        char *y =strsep(&birth,"/");
        int year = atoi(y);
      	int month = atoi(strsep(&birth,"/"));
      	int day = atoi(strsep(&birth,"/"));
        int idade =age(day,month,year);
        char * name_print = u_getName(u);
        char * gender_print = u_getGender(u);
        //NOTE - isto \u00e9 um exemplo de como se muda as cenas para a tabela mas ainda est\u00e1 por testar
        //NOTE - ainda est\u00e1 por fazer isto no else
        params[0] = strdup(name_print);
        params[1] = strdup(gender_print);
        params[2] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[2], "%d", idade);
        params[3] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[3], "%.3f", p);
        params[4] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[4], "%d", num);
        params[5] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[5], "%.3f", gasto);
        add_entry(t, params);
              
        //fprintf(fptr,"%s;%s;%d;%.3f;%d;%.3f\n",name_print,gender_print,idade,p,num,gasto);
        free(y);
        free(name_print);
        free(gender_print);
        free(params);
 
    }
    else if (isUsername(arg)==1) {
        Drivers d =look_up_drivers(m->drivers,arg);
        int o =Isnull_id(d);
        if (o==0) {return t;}
        if (d_getAccount_status(d)==1) return t;
        int num = d_getNumRides(d);
        double p;
        if (num == 0) { p = 0.0;}
        if (num != 0) { p = (*d_getScore(d))/(double) num;}
        double gasto = *d_getTotal(d);
        char *birth=d_getBirth_date(d);
        char *y =strsep(&birth,"/");
        char * name_print = d_getName(d);
        char * gender_print = d_getGender(d);
        int year = atoi(y);
      	int month = atoi(strsep(&birth,"/"));
      	int day = atoi(strsep(&birth,"/"));
        int idade =age(day,month,year);
        
        //fprintf(fptr,"%s;%s;%d;%.3f;%d;%.3f\n",name_print,gender_print,idade,p,num,gasto);
         params[0] = strdup(name_print);
        params[1] = strdup(gender_print);
        params[2] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[2], "%d", idade);
        params[3] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[3], "%.3f", p);
        params[4] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[4], "%d", num);
        params[5] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[5], "%.3f", gasto);
        add_entry(t, params);
        free (y);
        free(name_print);
        free(gender_print);
        
    }
    return t;
}

// Description:

// This function creates and returns a table of drivers with their 'Id', 'Nome' and 'ScoreMédio'
// It initializes a table t with 3 columns and header 'Id Nome ScoreMedio' and then converts 'arg' to an integer in_en which is used as the number of entries for the table.
// It checks de driver's account status, tje average score (...) and finally adds the 'params' array as an entry to the table and returns the table 't'.

Table q2_interativa (Model m,char*arg) {
    char *header =strdup("Id Nome ScoreMedio");
    Table t = init_table(3, header);
    int in_en = atoi(arg);
    init_entries(t, in_en);
    char **params = malloc(sizeof(char*) * 3); // 3 por causa do n\u00famero de colunas

    int N = in_en;
    int size;
    for (int i = 0; i<N && i<*(m->d_size);i++){
        Drivers d = look_up_drivers(m->drivers,m->keyArray_d[i]);
        if (d_getAccount_status(d)==1){
            N+=1;
            continue;
        }
        
        int num = d_getNumRides(d);
        
        double p;
        if (num == 0) { p = 0.0;}
        if (num != 0) { p = *(d_getScore(d))/(double) num;}
        char *name_print = d_getName(d);
        // fprintf(fptr,"%s;%s;%.3f\n",m->keyArray_d[i],name_print,p);
        params[0] = strdup(m->keyArray_d[i]);
        params[1] = strdup(name_print);
        params[2] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[2], "%.3f", p);
        add_entry(t, params);
        free(name_print);
    }
    return t;
    
}

// Description:

// This function first creates a header for the table using the string "Username Nome ScoreMedio". Then, it creates a table using the "init_table" function with 3 columns and the given header.
// After that, the function initializes the entries in the table using the number of rows as the argument.
// Then,  for each user, if the user's account status is equal to 1, the loop continues to the next iteration. Otherwise, the function calculates the user's "ScoreMedio" as the user's total distance and adds a new row to the table with the user's username, name, and ScoreMedio.
// Returns the generated table.

Table q3_interativa (Model m,char*arg) {
    char *header =strdup("Username Nome ScoreMedio");
    Table t = init_table(3, header);
    int in_en = atoi(arg);
    init_entries(t, in_en);
    char **params = malloc(sizeof(char*) * 3); // 3 por causa do n\u00famero de colunas
    int N = in_en;
    int size;
    for (int i = 0; i<N && i <*(m->u_size);i++){
        Users u = look_up_users(m->users,m->keyArray_u[i]);
        if (u_getAccount_status(u)==1){
            N+=1;
            continue;
        }
        double p = *u_getDistanceTotal(u) ;
        char *name_print = u_getName(u);
       // fprintf(fptr,"%s;%s;%.0f\n",m->keyArray_u[i],name_print,p);
        params[0] = strdup(m->keyArray_u[i]);
        params[1] = strdup(name_print);
        params[2] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[2], "%.3f", p);
        add_entry(t, params);
        free(name_print);
    }
    return t;
}

// Description:

// This function starts by initializing a table with a single column, "PrecoMedio", for storing the result. It then initializes the entries in the table to 1.
// Next, the function checks if the average price for the given city has already been calculated or not.
// The average price is calculated by summing up the prices of all rides in the city and dividing by the number of rides. The result is then added to the table as the only entry.
// Finally, the function stores the result in the backup list of the Model object for future use and returns the table.

Table q4_interativa (Model m,char*arg) {
    char *header =strdup("PrecoMedio");
    Table t = init_table(1, header);
    init_entries(t,1);
    char **params = malloc(sizeof(char*) * 1); // 1 por causa do n\u00famero de colunas
    double preco_medio;
    char*buffer = arg;
    preco_medio =isNode(m->backuplist,buffer);
    if (preco_medio == -1){
    int size;
    size = *(m->r_size);
    int numVia = 0;
    preco_medio = 0.0;
    for (int i = 0 ; i <size;i++){

        Rides r = look_up_rides (m->rides,m->keyArray_r[i]);
        char *c = r_getCity(r);
        if (strcmp (c,buffer) == 0){

                char *dKey = r_getDriver(r);
                Drivers d = look_up_drivers(m->drivers,dKey);
                free(dKey);

            numVia +=1; 
            char *car_classf = d_getCar_class(d);
            int car_distf =r_getDistance(r);
            preco_medio += get_preco(car_classf,car_distf);
            free(car_classf);
            

        }
        free(c);

    }
    if (numVia != 0){

        preco_medio = preco_medio / (double) numVia;
    }
    else {
        return t;
    }
    //fprintf(fptr,"%.03f\n",preco_medio);
    m->backuplist=addNodeq4(m->backuplist,preco_medio,buffer);
     params[0] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[0], "%.3f", preco_medio);
    add_entry(t, params);
    return t;
    }

    else {
   //fprintf(fptr,"%.03f\n",preco_medio);
   params[0] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[0], "%.3f", preco_medio);
    add_entry(t, params);
    return t;
    }
}


// Description:

// The function initializes a table with one column named "PrecoMedio". It then loops through all the rides stored in the model and filters out rides that are outside the specified date range.
// For each valid ride, the function calculates the ride's price based on the car class and distance and adds it to the total. After looping through all the rides, the average price is calculated and stored as a string in the table's only row. 
// Returns the table

Table q5_interativa (Model m,char*arg,char*arg2) {
char *header =strdup("PrecoMedio");
    Table t = init_table(1, header);
    init_entries(t,1);
    char **params = malloc(sizeof(char*) * 1); // 1 por causa do n\u00famero de colunas
    char *data1 = strdup(arg);
    data1[10] = '\0';
    char *data2 = strdup(arg2);
    int size;
    size = *(m->r_size);
    int numVia = 0;
    double preco_medio = 0.0;
    for (int i = 0 ; i <size;i++){

        Rides r = look_up_rides (m->rides,m->keyArray_r[i]);
        char *tempdata = r_getDate(r);
        int c1 =more_recent(tempdata,data1);
        if(c1==1) {
        
        	free(tempdata);
        	continue;
        	
        }
        char *tempdata2 = strdup(tempdata);
        int c2 =more_recent(tempdata2,data2); 
        
        if (c2==1 || c2==2 ){ // return 0 se 1 mais nova 2 . 2 se iguais 

                char *dKey = r_getDriver(r);
                Drivers d = look_up_drivers(m->drivers,dKey);
                free(dKey);
            numVia +=1; 
            char *car_classf = d_getCar_class(d);
            int car_distf = r_getDistance(r);
            preco_medio += get_preco(car_classf,car_distf);
            free(car_classf);
            
        }
        free(tempdata);
        free(tempdata2);

    }
    if (numVia == 0){
    free(data1);
    free(data2);
    return t;
    }
    preco_medio = preco_medio / (double) numVia;
    params[0] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[0], "%.3f", preco_medio);
    add_entry(t, params);
    
    
    free(data1);
    free(data2);
    return t;

}

// Description:

// The function initializes a table with one header row with the value "DistanciaMedia" and a single entry.
// The function then performs a loop to find a city matching the string value of "arg" in the "starray" field of the input "Model" structure. If the city is not found in the starray, the function returns the table "t".
// Next, the function performs a loop to check each ride in the "rides" field of the input "Model" structure. If the city of the ride is not the same as the target city, or if the date of the ride is earlier than the string value of "arg2" or later than the string value of "arg3", the function moves on to the next ride.
// For each valid ride, the result is then stored in the "params" array and added as an entry to the table "t".
// Returns the table.

Table q6_interativa (Model m,char*arg,char*arg2,char*arg3) {
char *header =strdup("DistanciaMedia");
    Table t = init_table(1, header);
    init_entries(t,1);
    char **params = malloc(sizeof(char*) * 1); // 1 por causa do n\u00famero de colunas
    char *cityy = arg;
    int j;
for (j = 0; j<m->how_many_starray;j++){

    if (strcmp(m->starray[j],cityy)==0) break;
        
    
}
if ( j == m->how_many_starray ) {
        
        return t;
    }
    char *data1 = strdup(arg2);
    data1[10] = '\0';
    char *data2 = strdup(arg3);
    int size;
    size = *(m->r_size); 
    int numVia = 0;
    double dist_media = 0.0;
    char * p; 
    for (int i = 0 ; i <size;i++){

        Rides r = look_up_rides (m->rides,m->keyArray_r[i]);
        char *citycmp = r_getCity(r);
        if(strcmp (citycmp,cityy) != 0){
        	
        	free(citycmp);
		continue;        
        }
        char *tempdata = r_getDate(r);
        int c1 =more_recent(tempdata,data1);
        if (c1==1){
        	free(tempdata);
        	free(citycmp);
        	continue;
        	
        	
        }
        char *tempdata2 = strdup(tempdata); 
        int c2 =more_recent(tempdata2,data2); 
        
        if (c2==1 || c2==2 ){ // return 0 se 1 mais nova 2 . 2 se iguais 

                char *dKey = r_getDriver(r);
                Drivers d = look_up_drivers(m->drivers,dKey);
                free(dKey);

            numVia +=1; 
            
         
            double dob = (double) r_getDistance(r);
            dist_media += dob;

        }
        free(tempdata);
        free(tempdata2);
        free(citycmp);
    }
    free(data1);
    free(data2);
    if (numVia== 0){
    return t;
    }
    dist_media = dist_media / (double) numVia;
    params[0] = (char*) malloc(sizeof(char) * 10);
        sprintf(params[0], "%.3f", dist_media);
    add_entry(t, params);
}

// Description:

// The function initializes a table structure with three columns (Id, Nome, AvaliacaoMedia) and sets its header as the string "Id Nome AvaliacaoMedia".
// The function then converts the arg argument to an integer N, which represents the number of entries to be added to the table and the arg2 argument is a string city that represents a city name.
// If the driver's account is active, the function gets the driver's id, nome, and av_media, and adds the data to the table as a new entry. The function then frees the id and nome fields.
// Returns the table.

Table q7_interativa(Model m,char*arg,char*arg2) {
char *header =strdup("Id Nome AvaliacaoMedia");
    Table t = init_table(3, header);
    char **params = malloc(sizeof(char*) * 3); // 3 por causa do n\u00famero de colunas
char *n_string= arg;
int N = atoi(n_string);
init_entries(t,N);
char *city = arg2;
int j;
for (j = 0; j<m->how_many_starray;j++){

    if (strcmp(m->starray[j],city)==0) break;
        
    
}
if ( j == m->how_many_starray ) return t;
int size;
char *p;
size = *(m->d_size2);
if (m->isIn == 1){
    m->lastcity = strdup(city);
    c_quickSort(m->keyArray_d_2,0,size-1,m->drivers,city);
    m->isIn = 0;
}else {

	if (strcmp(m->lastcity,city)!=0){
	c_quickSort(m->keyArray_d_2,0,size-1,m->drivers,city);
   	}
   	
	free(m->lastcity);
    	m->lastcity = strdup(city);
}

    for (int i = 0 ; i<N;i++){

        Drivers d = look_up_drivers(m->drivers,m->keyArray_d_2[i]);
        if (d_getAccount_status(d)==1){
            N+=1;
            continue;
        }
            
            char * id =d_getId(d);
            char * nome =d_getName(d);
            double av_media =c_getScore(d,city) / (double) c_getNumRides(d,city);
            if (isnan(av_media)) {
    			N+=1;
    			free(id);
            		free(nome);
    			continue;
		}	
		
            
           
            params[0] = strdup(id);
            params[1] = strdup(nome);
            params[2] = (char*) malloc(sizeof(char) * 20);
            sprintf(params[2], "%.3f", av_media);
            add_entry(t,params);
            free(id);
            free(nome);
    }


 return t;

}

// Description:

// The function filters the data stored based on multiple criteria in the Model and returns a table with 4 columns: "Id", "NomeDriver", "Username", and "User".
// It loops through all the rides in the model, gets the information about the driver and user associated with each ride and stores the filtered rides in a new array named "secondKeyArray".
// Then, the function sorts this array, initializes the entries in the table and fills the table with the filtered information.
// Finally, it frees up the memory and returns the table.

Table q8_interativa (Model m,char*arg,char*arg2) {
char *header =strdup("Id NomeDriver Username User");
    Table t = init_table(4, header);
    char **params = malloc(sizeof(char*) * 4); // 4 por causa do n\u00famero de colunas
char *gender= arg;
int how_old = atoi(arg2);
int size;
size = *(m->r_size);  
int count = 0;
char **secondKeyArray;
secondKeyArray = malloc(size * sizeof(char*));

for (int i = 0 ; i<size;i++){

    Rides temp = look_up_rides(m->rides,m->keyArray_r[i]);
        char *username = r_getUser(temp);
        char *driver = r_getDriver(temp);
        Users u = look_up_users(m->users,username);
        Drivers d = look_up_drivers(m->drivers,driver);
        free(username);
        free(driver);
        char *genderU = u_getGender(u); //
        char *genderD = d_getGender(d); //
        char *accountcreU = u_getAccount_creation(u);
        char *accountcreD = d_getAccount_creation(d);
        char *creUdc = strsep(&accountcreU,"/");
        char *creUmc = strsep(&accountcreU,"/");
        char *creUyc = strsep(&accountcreU,"/");
        char *creDdc = strsep(&accountcreD,"/");
        char *creDmc = strsep(&accountcreD,"/");
        char *creDyc = strsep(&accountcreD,"/");
        int creUd = atoi(creUdc);
        int creUm = atoi(creUmc);
        int creUy = atoi(creUyc);
        int creDd = atoi(creDdc);
        int creDm = atoi(creDmc);
        int creDy = atoi(creDyc);
        free(creUdc);
        free(creDdc); 
        int ageU = age(creUy,creUm,creUd); //
        int ageD = age(creDy,creDm,creDd); //
        free(accountcreU);
        free(accountcreD);
        
         if (strcmp(genderD,genderU) == 0 && strcmp(gender,genderD)==0 && d_getAccount_status(d)==0 && u_getAccount_status(u)==0 && ageU >= how_old && ageD >= how_old){ 
                secondKeyArray[count] = (m->keyArray_r[i]);
                count++;
                }
        free(genderD);
        free(genderU);
}
q8_quickSort(secondKeyArray,0,count-1,m->rides,m->drivers,m->users);
init_entries(t,count);
for (int i = 0 ; i<count;i++){
 Rides temp3 = look_up_rides(m->rides,secondKeyArray[i]);

        char *id_driver = r_getDriver(temp3);
        char *username_user = r_getUser(temp3);

        Drivers dp = look_up_drivers(m->drivers,id_driver);
        Users up = look_up_users(m->users,username_user);
        char * name_driver = d_getName(dp);
        char * name_user = u_getName(up);
        
        //fprintf(fptr,"%s;%s;%s;%s\n",id_driver,name_driver,username_user,name_user);
            params[0] = strdup(id_driver);
            params[1] = strdup(name_driver);
            params[2] = strdup(username_user);
            params[3] = strdup(name_user);
            add_entry(t,params);
        free(id_driver);
        free(username_user);
        free(name_driver);
        free(name_user);
}
free(secondKeyArray);

return t;
}

// Description:

//
// It iterates through all the rides stored in the model "m" and filters the rides based on two conditions: the tip must be positive and the date of the ride must be between the two given dates (arg and arg2). If a ride meets the conditions, its key is added to an array of secondKeyArray.
// After filtering the rides, the function sorts the secondKeyArray by the rides stored in the model's hash table (m->rides). It then initializes the entries of the table based on the count of filtered rides.
// Finally, for each filtered ride, the function retrieves its information, converts it into the appropriate type, and adds it to the table as an entry.
// The function frees the allocated memory and returns the table

Table q9_interativa (Model m,char*arg,char*arg2) {
char *header =strdup("Id Data Distancia Cidade Gorjeta");
    Table t = init_table(5, header);
    char **params = malloc(sizeof(char*) * 5); // 5 por causa do n\u00famero de colunas
    char *data1 = arg;
    data1[10] = '\0';
    char *data2 = arg2;
    int size;
    char *p;
    size = *(m->r_size);  
    int count = 0;
    char **secondKeyArray;
    secondKeyArray = malloc(size * sizeof(char*));
    for (int i = 0 ; i<size;i++){

        Rides temp = look_up_rides(m->rides,m->keyArray_r[i]);
            char *d1 = r_getDate(temp);
            char *d2 = strdup(d1);
            int c1 =more_recent(d1,data1); 
            int c2 =more_recent(d2,data2);
            free(d1);
            free(d2);
            double tip_r = r_getTip(temp);
            if (tip_r > 0.0 && ((c1==0 || c1 ==2) && (c2==1 || c2==2 )) ){ 
                secondKeyArray[count] = (m->keyArray_r[i]);
                count++;
                }
             



    }
r_quickSort(secondKeyArray,0,count-1,m->rides);
init_entries(t,count);
for (int i = 0 ; i<count;i++){
        Rides temp3 = look_up_rides(m->rides,secondKeyArray[i]);
        char *id_print = r_getId(temp3);
        char *date_print = r_getDate(temp3);
        int dist_print = r_getDistance(temp3);
        char *city_print = r_getCity(temp3);
        double tip_print_db = r_getTip(temp3);
        params[0] = strdup(id_print);
            params[1] = strdup(date_print);
            params[2] = (char*) malloc(sizeof(char) * 10);
            sprintf(params[2], "%d",dist_print);
            params[3] = strdup(city_print);
            params[4] = (char*) malloc(sizeof(char) * 10);
            sprintf(params[4], "%.3f", tip_print_db);
            add_entry(t,params);
        free(id_print);
        free(date_print);
        free(city_print);

    }
free(secondKeyArray);
return t;
}