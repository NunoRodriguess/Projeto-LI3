#include "interperter.h"

// Description:

// This function compare Files and returns an integer which is 0 if the contents of the two files are equal, or 1 if they are not and if the files could not be opened.

static int compareFiles(char *cp1, char *cp2) {
    FILE *fp1, *fp2;
    char *line1 = NULL, *line2 = NULL;
    size_t len1 = 0, len2 = 0;
    ssize_t read1, read2;
    int ret = 0;

    fp1 = fopen(cp1, "r");
    fp2 = fopen(cp2, "r");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error: Could not open one of the files.\n");
        return 1;
    }

    read1 = getline(&line1, &len1, fp1);
    read2 = getline(&line2, &len2, fp2);

    // check if both files are empty
    if(read1 <= 0 && read2 <= 0) 
    {
        ret = 0;
    }
    else
    {
        do {
            if (read1 != read2 || strcmp(line1, line2) != 0) {
                ret = 1;
                break;
            }
            read1 = getline(&line1, &len1, fp1);
            read2 = getline(&line2, &len2, fp2);
        } while (read1 >= 0 && read2 >= 0);
    }
    fclose(fp1);
    fclose(fp2);
    free(line1);
    free(line2);
    return ret;
}

// Description

// This function opens a file and writes the result of the query to the file. The query depends on the first character of input. 
// If the first character is '1', q1 function will be called, if the first character is '2', q2 function will be called, and so on. The function will close the file and return.

static void start_querie(char *input,Model m,int x){

    FILE *fptr;
    char str1[128] ="Resultados/command";
    char str2[50] ="_output.txt";
    char str3[128];
    sprintf(str3, "%d",x);
    strcat(str1,str3);
    strcat(str1,str2);
fptr = fopen(str1, "w");

    if (input == NULL) return;
    if (input[0] =='1' ){
        q1(m,input,fptr);
        fclose(fptr);
        return;
    } 
    if (input[0] =='2' ){
        q2(m,input,fptr);
        fclose(fptr);
        return;
    } 
    if (input[0] =='3' ){
        q3(m,input,fptr);
        fclose(fptr);
        return;
    } 
    if (input[0] =='4' ){
        
        q4(m,input,fptr);
        fclose(fptr);
        return;
    }
    if (input[0] =='5' ){
        
        q5(m,input,fptr);
        fclose(fptr);
        return;
    }
    if (input[0] =='6' ){
        
        q6(m,input,fptr);
        fclose(fptr);
        return;
    }
    if (input[0] =='7' ){
        q7(m,input,fptr);
        fclose(fptr);
        return;
    }
    if (input[0] =='8' ){
        
        q8(m,input,fptr);
        fclose(fptr);
        return;
    } 
     if (input[0] =='9' ){
        
        q9(m,input,fptr);
        fclose(fptr);
        return;
    } 
    

fclose(fptr);

}

// Description

//  This function writes both the result of the query and the performance measurement of the query to different files. 
// The performance measurement is taken by measuring the execution time of the query. This function is used to test the performance of the queries.

static int start_querie_teste(char *input,Model m,int x){
    FILE *fptr,*fptr2;
    char str[128] ="output_teste/";
    char str1[128] ="command";
    char str2[50] ="_output.txt";
    char str3[128];
    sprintf(str3, "%d",x);
    strcat(str1,str3);
    strcat(str1,str2);
    strcat(str,str1);
    fptr = fopen(str, "w");
    clock_t start, end;
    double execution_time;

    if (input == NULL) return 0;
    if (input[0] =='1' ){
        start = clock();
        q1(m,input,fptr);
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        char str4[128]="performance_output/";
        strcat(str4,str1);
        fptr2 = fopen(str4, "w");
        fprintf(fptr2,"%.06f\n",execution_time);
        fclose(fptr);
        fclose(fptr2);
        char str5[128]="tests_1/";
        strcat(str5,str1);
        int flag = compareFiles(str,str5);
        fptr2 = fopen(str4, "a");
        if (flag == 0){
            fprintf(fptr2,"O ficheiro obeteve a output esperada\n");
        }
        else {
            fprintf(fptr2,"O ficheiro não obeteve a output esperada\n");
        }
        fclose(fptr2);
        return flag;
    } 
    if (input[0] =='2' ){
        start = clock();
        q2(m,input,fptr);
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        char str4[128]="performance_output/";
        strcat(str4,str1);
        fptr2 = fopen(str4, "w");
        fprintf(fptr2,"%6f\n",execution_time);
        fclose(fptr);
        char str5[128]="output_teste/";
        strcat(str5,str1);
        int flag = compareFiles(str,str5);
        if (flag == 0){
            fprintf(fptr2,"O ficheiro obeteve a output esperada\n");
        }
        else {
            fprintf(fptr2,"O ficheiro não obeteve a output esperada\n");
        }
        fclose(fptr2);
        return flag;
    } 
    if (input[0] =='3' ){
        start = clock();
        q3(m,input,fptr);
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        char str4[128]="performance_output/";
        strcat(str4,str1);
        fptr2 = fopen(str4, "w");
        fprintf(fptr2,"%.06f\n",execution_time);
        fclose(fptr);
        char str5[128]="tests_1/";
        strcat(str5,str1);
        int flag = compareFiles(str,str5);
        if (flag == 0){
            fprintf(fptr2,"O ficheiro obeteve a output esperada\n");
        }
        else {
            fprintf(fptr2,"O ficheiro não obeteve a output esperada\n");
        }
        fclose(fptr2);
        return flag;
    } 
    if (input[0] =='4' ){
        start = clock();
        q4(m,input,fptr);
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        char str4[128]="performance_output/";
        strcat(str4,str1);
        fptr2 = fopen(str4, "w");
        fprintf(fptr2,"%.06f\n",execution_time);
        fclose(fptr);
        char str5[128]="tests_1/";
        strcat(str5,str1);
        int flag = compareFiles(str,str5);
        if (flag == 0){
            fprintf(fptr2,"O ficheiro obeteve a output esperada\n");
        }
        else {
            fprintf(fptr2,"O ficheiro não obeteve a output esperada\n");
        }
        fclose(fptr2);
        
        return flag;
    }
    if (input[0] =='5' ){
        start = clock();
        q5(m,input,fptr);
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        char str4[128]="performance_output/";
        strcat(str4,str1);
        fptr2 = fopen(str4, "w");
        fprintf(fptr2,"%.06f\n",execution_time);
        fclose(fptr);
        char str5[128]="tests_1/";
        strcat(str5,str1);
        int flag = compareFiles(str,str5);
        if (flag == 0){
            fprintf(fptr2,"O ficheiro obeteve a output esperada\n");
        }
        else {
            fprintf(fptr2,"O ficheiro não obeteve a output esperada\n");
        }
        fclose(fptr2);
        
        return flag;
    }
    if (input[0] =='6' ){
        start = clock();
        q6(m,input,fptr);
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        char str4[128]="performance_output/";
        strcat(str4,str1);
        fptr2 = fopen(str4, "w");
        fprintf(fptr2,"%.06f\n",execution_time);
        fclose(fptr);
        char str5[128]="tests_1/";
        strcat(str5,str1);
        int flag = compareFiles(str,str5);
        if (flag == 0){
            fprintf(fptr2,"O ficheiro obeteve a output esperada\n");
        }
        else {
            fprintf(fptr2,"O ficheiro não obeteve a output esperada\n");
        }
        fclose(fptr2);
        
        return flag;
    }
    if (input[0] =='7' ){
        start = clock();
        q7(m,input,fptr);
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        char str4[128]="performance_output/";
        strcat(str4,str1);
        fptr2 = fopen(str4, "w");
        fprintf(fptr2,"%.06f\n",execution_time);
        fclose(fptr);
        char str5[128]="tests_1/";
        strcat(str5,str1);
        int flag = compareFiles(str,str5);
        if (flag == 0){
            fprintf(fptr2,"O ficheiro obeteve a output esperada\n");
        }
        else {
            fprintf(fptr2,"O ficheiro não obeteve a output esperada\n");
        }
        fclose(fptr2);
        
        return flag;
    }
    if (input[0] =='8' ){
        start = clock();
        q8(m,input,fptr);
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        char str4[128]="performance_output/";
        strcat(str4,str1);
        fptr2 = fopen(str4, "w");
        fprintf(fptr2,"%.06f\n",execution_time);
        fclose(fptr);
        char str5[128]="tests_1/";
        strcat(str5,str1);
        int flag = compareFiles(str,str5);
        if (flag == 0){
            fprintf(fptr2,"O ficheiro obeteve a output esperada\n");
        }
        else {
            fprintf(fptr2,"O ficheiro não obeteve a output esperada\n");
        }
        fclose(fptr2);
       
        return flag;
    } 
     if (input[0] =='9' ){
        start = clock();
        q9(m,input,fptr);
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        char str4[128]="performance_output/";
        strcat(str4,str1);
        fptr2 = fopen(str4, "w");
        fprintf(fptr2,"%0.6f\n",execution_time);
        fclose(fptr);
        char str5[128]="tests_1/";
        strcat(str5,str1);
        int flag = compareFiles(str,str5);
        if (flag == 0){
            fprintf(fptr2,"O ficheiro obeteve a output esperada\n");
        }
        else {
            fprintf(fptr2,"O ficheiro não obeteve a output esperada\n");
        }
        fclose(fptr2);
        
        return flag;
    } 

fclose(fptr);
}

void interpertador (char *dataset_input,char*inuput_file) {

char*l_users=g_build_path("/", dataset_input, "users.csv", NULL);
char*l_drivers=g_build_path("/", dataset_input, "drivers.csv", NULL);
char*l_rides=g_build_path("/", dataset_input, "rides.csv", NULL);


Model m =load_model(l_rides,l_drivers,l_users);
free(l_users);
free(l_drivers);
free(l_rides);
FILE *fp = fopen(inuput_file, "r");
size_t max_size = 128;
char *line = malloc(sizeof(char) * max_size);
int i = 1;
     while (getline(&line, &max_size, fp) > 0) {
        
        start_querie(line,m,i);
        i++;
    }
    free(line);
    fclose(fp);
    free_model(m);
}

void interpertador_teste(char *dataset_input,char*inuput_file) {

char*l_users=g_build_path("/", dataset_input, "users.csv", NULL);
char*l_drivers=g_build_path("/", dataset_input, "drivers.csv", NULL);
char*l_rides=g_build_path("/", dataset_input, "rides.csv", NULL);
clock_t start, end,end2,end3;
start = clock();
Model m =load_model(l_rides,l_drivers,l_users);
end = clock();
double load_time =((double)(end - start))/CLOCKS_PER_SEC;
free(l_users);
free(l_drivers);
free(l_rides);
FILE *fp = fopen(inuput_file, "r");
size_t max_size = 128;
char *line = malloc(sizeof(char) * max_size);
int i = 1;
int k = 0;
int b =k;
     while (getline(&line, &max_size, fp) > 0) {
     b = k;
        k += start_querie_teste(line,m,i);
        if ( b!=k) printf("%s\n",line);
        i++;
    }
    end2=clock();
    double q_time =((double)(end2 - start))/CLOCKS_PER_SEC-load_time;
    free(line);
    fclose(fp);
    free_model(m);
    end3=clock();
    double t_time =((double)(end3 - start))/CLOCKS_PER_SEC;
    char str_fname[100]="performance_output/overall.txt";
    FILE *fptr2 = fopen(str_fname, "w");
    fprintf(fptr2,"O tempo de load foi de:%.06fs\n",load_time);
    fprintf(fptr2,"O tempo das queries foi de:%.06fs\n",q_time);
    fprintf(fptr2,"O tempo total foi de:%.06fs\n",t_time);
    if (k == 0)fprintf(fptr2,"Todas as queries obtiveram o output esperado!\n");
    else fprintf(fptr2,"%d queries obtiveram o output errado!\n",k);
    fclose(fptr2);
}