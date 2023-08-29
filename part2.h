#ifndef PART2_H
#define PART2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part1.h" // The header file for part 1

// A function to store and display the file vs owner matrix
void store_and_display_matrix() {
    // Check if the file and owner counts are positive
    if (file_count == 0 || owner_count == 0) {
        printf("No files or owners found.\n");
        return;
    }
    
    // Initialize the matrix with zeros
    for (int i = 0; i < owner_count; i++) {
        for (int j = 0; j < file_count; j++) {
            matrix[i][j] = 0;
        }
    }
    
    // Loop through the files and owners and update the matrix with ones if they match
    for (int i = 0; i < owner_count; i++) {
        for (int j = 0; j < file_count; j++) {
            if (strcmp(owners[i].name, files[j].owner) == 0) {
                matrix[i][j] = 1;
            }
        }
    }
    
    // Display the header of the table with the file names
    printf("\t");
    for (int j = 0; j < file_count; j++) {
        printf("%s\t", files[j].name);
    }
    printf("\n");
    
    // Display the rows of the table with the owner names and the matrix values
    for (int i = 0; i < owner_count; i++) {
        printf("%s\t", owners[i].name);
        for (int j = 0; j < file_count; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
#endif