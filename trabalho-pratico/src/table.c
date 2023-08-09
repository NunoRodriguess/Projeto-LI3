#include "table.h"

struct table {
    int ncols;
    int last;
    char **headers;
    char ***content;
};

// header:
// HEADER 1 || HEADER 2 || HEADER 3

// content:
//  CELL 1  ||  CELL 2  ||  CELL 3
//  CELL 1  ||  CELL 2  ||  CELL 3
//  CELL 1  ||  CELL 2  ||  CELL 3

// Description:

// Frees the memory allocated for the table.

void free_table(Table t) {
    for (int i = 0; i < t->ncols; i++) {
        free(t->headers[i]);
        for (int j = 0; j < t->last; j++)
            free(t->content[j][i]);
        free(t->content[i]);
    }
    free(t->headers);
    free(t->content);
    free(t);
}

// Description:

// Initializes the table with n columns and headers given by params, which is a string of header names separated by " || "

Table init_table(int n, char *params) {
    Table t = (Table) malloc(sizeof(struct table));
    t->headers = (char **) malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
        t->headers[i] = strdup(strsep(&params, " \n"));
    t->ncols = n;
    t->last = 0;

    return t;
}

// Description:

//  Initializes the content of the table with n rows.

void init_entries(Table t, int n) {
    t->content = (char ***) malloc(sizeof(char **) * n);
    for (int i = 0; i < n; i++)
        t->content[i] = (char **) malloc(sizeof(char *) * t->ncols);
}

// Description

// Adds an entry (row) to the table with the values given by params, which is an array of strings that represent the values in a row.

void add_entry(Table t, char **params) {
    for (int i = 0; i < t->ncols; i++){
        t->content[t->last][i] = strdup(params[i]);
        }
    t->last++;
}

// Description:

// Initializes the table with n columns and headers given by params, which is an array of header names.

Table init_table_list(int n, char **params) {
    Table t = (Table) malloc(sizeof(struct table));
    t->headers = (char **) malloc(sizeof(char *) * n);
    for (int i = 0; i < n; i++)
        t->headers[i] = strdup(params[i]);
    t->ncols = n;
    t->last = 0;

    return t;
}

// Description

// Converts the table t by extracting only the rows from min to max.

Table convert_table(Table t, int min, int max) {
    Table new = init_table_list(t->ncols, t->headers);
     init_entries(new,t->last);
    for (int i = min; i < max; i++) {
        if (i < t->last){
        add_entry(new, t->content[i]);
        
        }
    }
    
    return new;
}

// Description:

// Prints n spaces to the file specified by fp.

int print_spaces(int n, FILE *fp) {
    if (n < 0) return 0;
    for (int i = 0; i < n; i++) fprintf(fp, " ");
    return n;
}

// Description:

// Prints a string str centralized in size spaces to the file specified by fp.

int print_str_centralized(int size, char *str, FILE *fp) {
    int total = 0;
    size -= strlen(str);
    if (size < 0) printf("\nERROR\n");
    int space_l = size / 2;
    int space_r = size % 2 ? space_l + 1 : space_l;
    total += print_spaces(space_l, fp);
    total += fprintf(fp, "%s", str);
    total += print_spaces(space_r, fp);
    return total;
}

// Description:

// Prints a line of the table, where line is the row to print, 

void print_table_line(char **line, size_t *max_len_fields, size_t n_fields, size_t range, FILE *fp) {
    for (size_t i = 0; i < n_fields; i++) {
        fprintf(fp, "+");
        for (size_t j = 0; j < (max_len_fields[i] + 2 * range); j++)
            fprintf(fp, "-");
        fprintf(fp, "+");
    }
    fprintf(fp, "\n");
    for (size_t i = 0; i < n_fields; i++) {
        fprintf(fp, "|");
        print_str_centralized((max_len_fields[i] + 2 * range), line[i], fp);
        fprintf(fp, "|");
    }
    putchar('\n');
}

// Description:

// Returns an array of the maximum length of the values in each column of the table t.

size_t *get_max_len_fields(Table t) {
    size_t *max_len_fields = malloc(sizeof(size_t) * t->ncols);
    for (size_t i = 0; i < t->ncols; i++)
        max_len_fields[i] = strlen(t->headers[i]);

    for (size_t i = 0; i < t->last; i++) {
        for (size_t j = 0; j < t->ncols; j++) {
            size_t elem_size = strlen(t->content[i][j]);
            if (elem_size > max_len_fields[j])
                max_len_fields[j] = elem_size;
        }
    }
    return max_len_fields;
}

// Description:

// This function displays the content of the table on a file specified by fp.

void show(Table t, FILE *fp) {
    if (t == NULL) {
        printf("[Error] table is empty\n");
        return;
    }

    size_t *max_len_fields = get_max_len_fields(t);

    size_t range = 10;
    size_t with = 0;
    for (size_t i = 0; i < t->ncols; i++)
        with += 2 * range + max_len_fields[i];

    if (with > 80) range /= 2;

    print_table_line(t->headers, max_len_fields, t->ncols, range, fp);
    for (size_t i = 0; i < t->last; i++)
        print_table_line(t->content[i], max_len_fields, t->ncols, range, fp);

    for (size_t i = 0; i < t->ncols; i++) {
        fprintf(fp, "+");
        for (size_t j = 0; j < (max_len_fields[i] + 2 * range); j++)
            fprintf(fp, "-");
        fprintf(fp, "+");
    }
    fprintf(fp, "\n");
    free(max_len_fields);
}

// Description:

// Returns the last index that has a filled cell in the table

int get_last(Table t) {
    return t->last;
}

// Description:

// Returns the number of columns in the table.

int get_ncols(Table t) {
    return t->ncols;
}