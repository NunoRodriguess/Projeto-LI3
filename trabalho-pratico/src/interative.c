/**
 * @file interative.c
 * @brief Este ficheiro tem como fun\u00e7\u00e3o criar um interpretador 
 * de leitura e execu\u00e7\u00e3o de comandos.
 * 
 */
#include "interative.h"

#define LINE 128

#define COMMAND_DELS ";\n"

#define FUNCTION_DELS " (),;\n"


enum error {
    VALID,          // 0
    INVALID_INPUT,  // 1
    INVALID_VAR,    // 2
    INVALID_FUNC,   // 3
    INVALID_ARG,    // 4
    INVALID_COM     // 5
};

// Description:

// This function is a type definition for a custom error type 'ERROR' with different values

typedef enum error ERROR;
void print_error(ERROR erro) {
    switch (erro) {
        case INVALID_FUNC:
            printf("Invalid function\n");
            break;
        case INVALID_ARG:
            printf("Invalid argument\n");
            break;
        case INVALID_VAR:
            printf("Invalid variable\n");
            break;
        case INVALID_COM:
            printf("Invalid command\n");
            break;
        case INVALID_INPUT:
            printf("Invalid input\n");
            break;
        case VALID:
            printf("Done\n");
            break;
        default:
            return;
    }
}

// Description:

// This function clears the console screen

void clrscreen() {
    printf("\e[1;1H\e[2J");
}

// Description:

// This function print the respective guide on how to use the commands in the program

void print_format_guide() {
    printf("\n---------------------------------------- Guide to use commands properly ----------------------------------\n");
    printf("[Load Model]\n");
    printf("\tDescrição: iniciar ficheiros com os datasets que pretende\n");
    printf("\tUso: load <dataset rides> <dataset drivers> <dataset users>\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
}

// Description:

// This function print the respective guide on how to use queries in the program.

void print_query_guide() {
    printf("\n---------------------------------------------------------- Guide to use queries properly -----------------------------------------------------\n");
    printf("[Nota] - cada elemento entre < > corresponde a um argumento\n");

    printf("[Querie 1]\n");
    printf("\tDescription: Obter o resumo de um perfil registado no serviço (pode pertencer a um utilizador ou a um condutor)\n");
    printf("\tUsage example: <1> <ID do utilizador/condutor>\n");

    printf("[Querie 2]\n");
    printf("\tDescription: Obter os N condutores com maior avaliação media (viagem mais recente e id do condutor para desempate)\n");
    printf("\tUsage example: <2> <N>\n");

    printf("[Querie 3]\n");
    printf("\tDescription: Obter os N utilizadores com maior distancia viajada (viagem mais recente e username do utilizador para desempate)\n");
    printf("\tUsage example: <3> <N>\n");

    printf("[Querie 4]\n");
    printf("\tDescription: Obter o preço médio das viagens numa determinada cidade\n");
    printf("\tUsage example: <4> <cidade>\n");

    printf("[Querie 5]\n");
    printf("\tDescription: Obter o preço médio das viagens num determinado intervalo de tempo\n");
    printf("\tUsage example: <5> <data inicial> <data final>\n");

    printf("[Querie 6]\n");
    printf("\tDescription: Obter a distância média percorrida numa determinada cidade, num determinado intervalo de tempo\n");
    printf("\tUsage example: <6> <cidade> <data inicial> <data final>\n");
    ;
    printf("[Querie 7]\n");
    printf("\tDescription: Obter o top N condutores numa determinada cidade pela avaliação média na respetiva cidade\n");
    printf("\tUsage example: <7> <N> <cidade>\n");

    printf("[Querie 8]\n");
    printf("\tDescription: Obter as viagens em que o utilizador e o condutor são de X género e têm perfil registado com mais de X anos\n");
    printf("\tUsage example: <8> <género> <numero de anos>\n");

    printf("[Querie 9]\n");
    printf("\tDescription: Obter as viagens em que o passageiro deu gorjeta num determinado intervalo de tempo\n");
    printf("\tUsage example: <9> <data inicial> <data final>\n");

    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

// Description:

// Initializes the interpreter and prints "Welcome!" on the console.

void init_intrep() {
    printf("\nWelcome!\n");
}

// Description:

// Accepts a string as an argument and checks if it's equal to "exit", "quit" or "q". If true, it prints "Exiting..." on the console and returns 1, otherwise returns 0.

int is_exit(char* line) {
    if ((g_str_equal(line, "exit") || g_str_equal(line, "quit") || g_str_equal(line, "q"))) {
        printf("Exiting...\n");
        return 1;
    }
    return 0;
}

// Description:

// Prints a message on the console indicating the commands available to navigate through pages.

void print_paging_commands() {
    printf("\nn - next page || p - previous page || q - quit show interpreter || w - write in file\n");
}

// Description:

// This function is then called to display the results in the table format.

ERROR show_func(Table t) {
    Table page;

    int control = 0;
    int max_range = control + 12;
    clrscreen();

    int table_len = get_last(t);
    page = convert_table(t, control, control + 12);
    show(page, stdout);
    if (control + 12 > table_len) max_range = table_len - 1;
    
    printf("SHOWING LINES BETWEEN %d TO %d\n", control+1, max_range+1);
    printf("TOTAL LINES IN TABLE: %d\n", table_len);
    print_paging_commands();
    char key;
    while ((key = fgetc(stdin)) != 'q') {
        if(key == ' ' || key == '\n') continue;        
        clrscreen();
        if (key == 'n') {
            if ((control + 24) > table_len)
                control = table_len-12 < 0 ? 0 : table_len - 12;
            else
                control += 12;
        } else if (key == 'p') {
            if ((control - 12) < 0)
                control = 0;
            else
                control -= 12;
        } else if (key == 'w') {
            char file[20];
            printf("Insira o nome do ficheiro onde escrever: ");
            scanf("%s", file);
            char path[32] = "Resultados/";
            strcat(path, file);
            FILE *fp = fopen(path, "w");
            if (fp == NULL) {
                printf("Erro ao abrir ficheiro -> %s\n", file);
                continue;
            }
            show(t, fp);
            fclose(fp);
            clrscreen();
        } 
        else printf("[Error] Invalid key, try again\n\n");
        page = convert_table(t, control, control + 12);
        show(page, stdout);
        if (control + 12 >= table_len) max_range = table_len - 1;
        else max_range = control + 12;
        printf("\nSHOWING LINES BETWEEN %d TO %d\n", control+1, max_range+1);
        printf("TOTAL LINES IN TABLE: %d\n", table_len);
        print_paging_commands();
    }
    
    clrscreen();
    return VALID;
}

// Description:

// This function is used to determine which query to execute based on the input q value, and to parse the arguments required for each query. 
// The function also handles the error cases when the arguments are not provided correctly

ERROR call_function(int q, char *line, Model m) { 
    ERROR err = VALID;
    if (q == 1) {
        char *arg = strsep(&line, " \n");
        if (!arg || !arg[0]) return INVALID_ARG;

        Table t = q1_interativa(m, arg);
        err = show_func(t);
    }
    if (q == 2) {
        char *arg = strsep(&line, " \n");
        if (!arg || !arg[0]) return INVALID_ARG;

        Table t = q2_interativa(m, arg);
        err = show_func(t);
    }
    if (q == 3) {
        char *arg = strsep(&line, " \n");
        if (!arg || !arg[0]) return INVALID_ARG;
        
        Table t = q3_interativa(m, arg);
        err = show_func(t);
    }
    if (q == 4) {
        char *arg = strsep(&line, " \n");
        if (!arg || !arg[0]) return INVALID_ARG;
        
        Table t = q4_interativa(m, arg);
        err = show_func(t);
    }
    if (q == 5) {
        char *arg = strsep(&line, " ");
        char *arg2 = strsep(&line, " \n");
        if (!arg || !arg[0]) return INVALID_ARG;
        if (!arg2 || !arg2[0]) return INVALID_ARG;

        Table t = q5_interativa(m, arg, arg2);
        err = show_func(t);
    }
    if (q == 6) {
        char *arg = strsep(&line, " ");
        char *arg2 = strsep(&line, " ");
        char *arg3 = strsep(&line, " \n");
        if (!arg || !arg[0]) return INVALID_ARG;
        if (!arg2 || !arg2[0]) return INVALID_ARG;
        if (!arg3 || !arg3[0]) return INVALID_ARG;
        
        Table t = q6_interativa(m, arg, arg2, arg3);
        err = show_func(t);
    }
    if (q == 7) {
        char *arg = strsep(&line, " ");
        char *arg2 = strsep(&line, " \n");
        if (!arg || !arg[0]) return INVALID_ARG;
        if (!arg2 || !arg2[0]) return INVALID_ARG;
        
        Table t = q7_interativa(m, arg, arg2);
        err = show_func(t);
    }
    if (q == 8) {
        char *arg = strsep(&line, " ");
        char *arg2 = strsep(&line, " \n");
        if (!arg || !arg[0]) return INVALID_ARG;
        if (!arg2 || !arg2[0]) return INVALID_ARG;

        Table t = q8_interativa(m, arg, arg2);
        err = show_func(t);
    }
    if (q == 9) {
        char *arg = strsep(&line, " ");
        char *arg2 = strsep(&line, " \n");
        if (!arg || !arg[0]) return INVALID_ARG;
        if (!arg2 || !arg2[0]) return INVALID_ARG;
        
        Table t = q9_interativa(m, arg, arg2);
        err = show_func(t);
    }
    return err;
}

// Description:

// This function takes in a string, 'var', and returns an integer representing a query. If the string matches one of the values "1", "2", "3", ..., "9", then the function returns the corresponding integer. Otherwise, it returns 0.

int is_query(char *var) {
    if (strcmp(var, "1") == 0) return 1;
    if (strcmp(var, "2") == 0) return 2;
    if (strcmp(var, "3") == 0) return 3;
    if (strcmp(var, "4") == 0) return 4;
    if (strcmp(var, "5") == 0) return 5;
    if (strcmp(var, "6") == 0) return 6;
    if (strcmp(var, "7") == 0) return 7;
    if (strcmp(var, "8") == 0) return 8;
    if (strcmp(var, "9") == 0) return 9;
    return 0;
}

//Description:

// This function implements an interactive interpreter. The main loop reads a line of input using getline. If the input is empty or contains only whitespaces, the loop continues. If the input is "load", the function calls 'load_model' with the following arguments and initializes the 'Model' structure 'm'.
// In the end, the function outputs either an error message if the input is invalid or a message indicating that the input is valid.

void interpretador_interativo() { 
    size_t size = 128;
    char* line = malloc(sizeof(char) * 128);
    int init = 0;
    Model m;

    clrscreen();
    print_format_guide();
    print_query_guide();
    init_intrep();

    while (getline(&line, &size, stdin) > 0) {
        while (line) {
            ERROR e = INVALID_INPUT;
            char* var = strsep(&line, " \n");
            if (!var || !var[0]) continue;
            int q;
            if (is_exit(var)) return; 
            else if (strcmp(var, "load") == 0) {
                char *rides = strsep(&line, " ");
                char *drivers = strsep(&line, " ");
                char *users = strsep(&line, " \n");
                m = load_model(rides, drivers, users);
                
                e = VALID;
                init = 1;
            }
            else if ((q = is_query(var)) != 0) {
                if (init == 0) continue;
                else e = call_function(q, line, m);
            }

            if (e != VALID) {
                print_error(e);
                break;
            } else
                print_error(VALID);
        }
    }
}