#include <stdlib.h>
#include <stdio.h> 

char** read_data(char* filename, int* rows, int* cols){
    FILE *file = fopen(filename, "r"); 

    size_t row_count=0, col_count = 0; 

    char ch; 

    while((ch = fgetc(file)) != EOF && ch != '\n'){
        if(ch != ' ' && ch != '\t'){
            col_count++; 
        }
    }

    while((ch=fgetc(file)) != EOF){
        if(ch == '\n'){
            row_count++; 
        }
    }
    if(col_count > 0){
        row_count++; 
    }

    *rows = row_count; 
    *cols = col_count; 
    rewind(file); 
    char**data = malloc(row_count * sizeof(char*)); 

    for(int i = 0; i< row_count; i++){
        data[i] = malloc(col_count * sizeof(char)); 
    }
    for(size_t i = 0; i<row_count; i++){
        for(size_t j = 0; j < col_count; j++){
            fscanf(file, " %c", &data[i][j]); 
        }
    }
    fclose(file); 
    return data; 
}


int count_neighbors(char** data, int total_rows, int total_cols,  int row, int col){
    int count = 0; 
    int row_offset[] = {-1, -1, -1, 0, 0, 1, 1, 1}; 
    int col_offset[] = {-1, 0, 1, -1, 1, -1, 0, 1}; 

    int num_neighbors = 8; 

    char empty_val = '.'; 
    for(int i = 0; i<num_neighbors; i++){
        int n_row = row + row_offset[i]; 
        int n_col = col + col_offset[i];  
        if(n_row >=0 && n_row < total_rows && n_col >=0 && n_col < total_cols){
            if(data[n_row][n_col] == '@'){
                count++; 
            }
        }
    }
    return count; 
}

int solve_part_one(char** data, int rows, int cols){
    int final = 0; 
    for(int i =0; i<rows; i++){
        for(int j = 0; j < cols; j++){
            if(data[i][j] == '@'){
                int total_count= count_neighbors(data, rows, cols, i, j); 
                if(total_count < 4) { final ++;}
            }
        }
    }
    return final; 
} 


int solve_part_2(char** data, int rows, int cols){

    int num_removed = 0; 
    int changed; 

    do {
        changed = 0; 
        for(int i = 0; i< rows; i++){
            for(int j = 0; j< cols; j++){
                if(data[i][j] == '@'){
                    int neighbors = count_neighbors(data, rows, cols, i, j) ;
                    if(neighbors < 4){ 
                        data[i][j] = 'X'; 
                        num_removed++; 
                        changed = 1; 
                    }
                }
            }
        }
    } while(changed); 
    return num_removed; 
}


    


int main(){
   int rows, cols; 
   int final = 0; 
   int final_2 = 0; 
   char** data =  read_data("day4.txt", &rows, &cols); 
    for(int i = 0; i< rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%c ", data[i][j]); 
        } 
    }
    printf("\n"); 

    //solving the problem:
    //go row by row, if there is a roll there, stop and count all 8 neighbors 
    // if there are less than or equal to four populated neighbors (i.e if there are less than or equal to four rolls of paper), then we increment the count by one and continue 

    //part 1: 
    final = solve_part_one(data, rows, cols);  
    final_2 = solve_part_2(data, rows, cols); 
    
    printf("The total amount of non-empty positions is: %d\n ", final); 
    printf("The total amount of rolls that can be removed is: %d\n", final_2); 

}