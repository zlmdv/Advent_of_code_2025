#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include <sys/types.h>
#include <ctype.h>


typedef struct {
    int** nums; 
    char *ops; 
    int rows; 
    int cols; 
} Grid; 


int is_col_empty(Grid *grid, int col) {
    for (int r = 0; r < grid->rows; r++) {
        if (grid->nums[r][col] != -1) return 0; 
    }
    return 1;
}
 Grid* read_data_part_one(char* filename){
    FILE *file = fopen(filename, "r");
    size_t len;  
    size_t rows = 0;
    size_t cols = 0;
    char* line = NULL;
    ssize_t read = 0;
    while((read = getline(&line, &len, file)) != -1){
        rows++;
    }
    rewind(file);
    read = getline(&line, &len, file);
    char* temp = strdup(line);
    char* tok = strtok(temp, " \t\n");
    while (tok != NULL) {
        cols++;
        tok= strtok(NULL, " \t\n");
    }
    free(temp);
    Grid *grid = malloc(sizeof(Grid));
    grid->rows = rows - 1;  
    grid->cols = cols;
    grid->nums = malloc(grid->rows * sizeof(int*));
    int* nums_buf = malloc(grid->rows * grid->cols * sizeof(int));
    for(int i = 0; i < grid->rows; i++){
        grid->nums[i] = nums_buf + i * grid->cols;
    }
    grid->ops = malloc(grid->cols * sizeof(char));
    rewind(file);
    for(int i = 0; i < grid->rows; i++){
        read = getline(&line, &len, file);
        char* token = strtok(line, " \t\n");
        for(int j = 0; j < grid->cols && token != NULL; j++){
            grid->nums[i][j] = atoll(token);
            token = strtok(NULL, " \t\n");
        }
    }
    read = getline(&line, &len, file);
    char* token = strtok(line, " \t\n");
    for(int j = 0; j < grid->cols && token != NULL; j++){
        grid->ops[j] = token[0];  
        token = strtok(NULL, " \t\n");
    }
    fclose(file);
    return grid;
} 

Grid* read_data_part_two (char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    char **line_ptrs = NULL;
    size_t line_count = 0;
    size_t max_cols = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        if (read > 0 && (line[read-1] == '\n' || line[read-1] == '\r')) {
            line[read-1] = '\0';
            read--;
        }
        line_ptrs = realloc(line_ptrs, (line_count + 1) * sizeof(char*));
        line_ptrs[line_count] = strdup(line);
        if (read > max_cols) max_cols = read;
        line_count++;
    }
    free(line);
    fclose(file);

    Grid *grid = malloc(sizeof(Grid));
    grid->rows = line_count - 1; 
    grid->cols = max_cols;
    
    grid->nums = malloc(grid->rows * sizeof(int*));
    int* nums_buf = malloc(grid->rows * grid->cols * sizeof(int));
    for (int i = 0; i < grid->rows; i++) {
        grid->nums[i] = nums_buf + i * grid->cols;
 
        for (int j = 0; j < grid->cols; j++) grid->nums[i][j] = -1;
    }

    for (int r = 0; r < grid->rows; r++) {
        int actual_len = strlen(line_ptrs[r]);
        for (int c = 0; c < actual_len; c++) {
            if (isdigit(line_ptrs[r][c])) {
                grid->nums[r][c] = line_ptrs[r][c] - '0';
            }
        }
    }

    grid->ops = malloc(grid->cols * sizeof(char));
    memset(grid->ops, ' ', grid->cols); // Default to space
    int last_line_len = strlen(line_ptrs[line_count - 1]);
    for (int c = 0; c < last_line_len; c++) {
        grid->ops[c] = line_ptrs[line_count - 1][c];
    }

    for (int i = 0; i < line_count; i++) free(line_ptrs[i]);
    free(line_ptrs);

    return grid;
}


 long long solve_part_one(Grid *grid){
    long long total = 0;
    for(int i = 0; i< grid->cols; i++){
        char op = grid->ops[i];
        long long result;
            switch(op){
                case '*':
                    result = 1;
                    break;
                case '+':
                    result = 0;  
                    break;  
            }
        for(int j = 0; j< grid->rows; j++){
            switch(op){
                case '*':
                    result *= grid->nums[j][i];
                    break;
                case '+':
                    result += grid->nums[j][i];
                    break;  
            }
        }
        total += result;
    }
    return total;
}



long long make_number(int *row, int len){
    long long num = 0;
    for (int i = 0; i < len; i++) {
        if (row[i] != -1) { 
            num = num * 10 + row[i];
        }
    }
    return num;
} 


int** transpose(Grid *grid) {
    int rows = grid->rows;
    int cols = grid->cols;
    int **transposed = malloc(cols * sizeof(int*));
    int *buf = malloc(rows * cols * sizeof(int));
    for (int i = 0; i < cols; i++)
        transposed[i] = buf + i * rows;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            transposed[c][r] = grid->nums[r][c];
        }
    }
    return transposed; 
}

long long solve_part_two(Grid *grid){

    int **t_nums = transpose(grid);
    long long grand_total = 0;

    int i = grid->cols - 1;
    while (i >= 0) {
      
        if (make_number(t_nums[i], grid->rows) == 0) {
            i--;
            continue;
        }
        long long group_nums[256]; 
        int count = 0;
        
        while (i >= 0 && make_number(t_nums[i], grid->rows) != 0) {
            group_nums[count++] = make_number(t_nums[i], grid->rows);
            i--;
        }
        char op = grid->ops[i + 1];
        
        long long group_result = group_nums[0];
        for (int j = 1; j < count; j++) {
            if (op == '+') {
                group_result += group_nums[j];
            } else if (op == '*') {
                group_result *= group_nums[j];
            }
        }
        grand_total += group_result;
    }

    return grand_total;
}


int main(){
    Grid *data_part_one = read_data_part_one("day6.txt");  
    Grid *data_part_two = read_data_part_two("day6.txt"); 

    long long part_one = solve_part_one(data_part_one); 

    printf("The solution to part one is: %lld\n", part_one); 

    long long part_two = solve_part_two(data_part_two); 

    printf("The solution to part two is: %lld\n", part_two);
}