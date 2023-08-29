#ifndef PART3_H
#define PART3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part1.h" // The header file for part 1

// A function to list all the file names created by an user/owner
void list_files_by_owner() {
    // Check if the file and owner counts are positive
    if (file_count == 0 || owner_count == 0) {
        printf("No files or owners found.\n");
        return;
    }
    
    // Declare some variables for input and choice
    char input[20];
    int choice;
    
    // Display the options to fetch the file list
    printf("Please choose an option to fetch the file list:\n");
    printf("1. By owner ID\n");
    printf("2. By owner name\n");
    
     // Get the user input
     printf("Please enter your choice: ");
     scanf("%s", input);
     
     // Convert the input to an integer
     choice = atoi(input);
     
     // Perform different actions based on the choice
     switch (choice) {
         case 1:
             // Get the owner ID from input
             int id;
             printf("Please enter the owner ID: ");
             scanf("%d", &id);
             
             // Check if the owner ID is valid
             int found = 0;
             for (int i = 0; i < owner_count; i++) {
                 if (id == owners[i].id) {
                     found = 1;
                     break;
                 }
             }
             
             // If not found, display an error message
             if (!found) {
                 printf("Invalid owner ID.\n");
                 return;
             }
             
             // Loop through the files and display the ones that match the owner ID
             printf("The files created by owner ID %d are:\n", id);
             for (int j = 0; j < file_count; j++) {
                 if (id == getpwuid(files[j].owner)->pw_uid) {
                     printf("%s\n", files[j].name);
                 }
             }
             
             break;
         case 2:
             // Get the owner name from input
             char name[20];
             printf("Please enter the owner name: ");
             scanf("%s", name);
             
             // Check if the owner name is valid
             found = 0;
             for (int i = 0; i < owner_count; i++) {
                 if (strcmp(name, owners[i].name) == 0) {
                     found = 1;
                     break;
                 }
             }
             
             // If not found, display an error message
             if (!found) {
                 printf("Invalid owner name.\n");
                 return;
             }
             
             // Loop through the files and display the ones that match the owner name
             printf("The files created by owner name %s are:\n", name);
             for (int j = 0; j < file_count; j++) {
                 if (strcmp(name, files[j].owner) == 0) {
                     printf("%s\n", files[j].name);
                 }
             }
             
             break;
         default:
             printf("Invalid choice. Please try again.\n");
             break;
     }
}
#endif