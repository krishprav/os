#ifndef PART4_H
#define PART4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "part1.h" // The header file for part 1

// A function to display the owner and group name against each inode value
void display_owner_and_group() {
    // Check if the file count is positive
    if (file_count == 0) {
        printf("No files found.\n");
        return;
    }
    
    // Display the header of the table
    printf("Inode\tOwner\tGroup\n");
    
    // Loop through the files and display the inode, owner and group names
    for (int i = 0; i < file_count; i++) {
        printf("%d\t%s\t%s\n", files[i].inode, files[i].owner, files[i].group);
    }
}

// A function to change the file permission of the files
void change_file_permission() {
    // Check if the file count is positive
    if (file_count == 0) {
        printf("No files found.\n");
        return;
    }
    
    // Declare some variables for input and choice
    char input[20];
    int choice;
    
    // Display the options to change the file permission
    printf("Please choose an option to change the file permission:\n");
    printf("1. By inode number\n");
    printf("2. By file name\n");
    
     // Get the user input
     printf("Please enter your choice: ");
     scanf("%s", input);
     
     // Convert the input to an integer
     choice = atoi(input);
     
     // Perform different actions based on the choice
     switch (choice) {
         case 1:
             // Get the inode number from input
             int inode;
             printf("Please enter the inode number: ");
             scanf("%d", &inode);
             
             // Check if the inode number is valid
             int found = 0;
             int index = -1;
             for (int i = 0; i < file_count; i++) {
                 if (inode == files[i].inode) {
                     found = 1;
                     index = i;
                     break;
                 }
             }
             
             // If not found, display an error message
             if (!found) {
                 printf("Invalid inode number.\n");
                 return;
             }
             
             // Get the new permission from input
             int permission;
             printf("Please enter the new permission (0-7): ");
             scanf("%d", &permission);
             
             // Check if the permission is valid
             if (permission < 0 || permission > 7) {
                 printf("Invalid permission.\n");
                 return;
             }
             
             // Get the full path of the file
             char full_path[100];
             sprintf(full_path, "%s/%s", path, files[index].name);
             
             // Get the current permission of the file
             int current_permission = files[index].permission;
             
             // Update the permission of the file using chmod system call
             if (chmod(full_path, permission) == -1) {
                 printf("Error changing permission of %s.\n", full_path);
                 return;
             }
             
             // Display a message with the previous and current permissions
             printf("You have successfully changed the permission of %s from %d to %d.\n", files[index].name, current_permission, permission);
             
             break;
         case 2:
              // Get the file name from input
              char name[20];
              printf("Please enter the file name: ");
              scanf("%s", name);
              
              // Check if the file name is valid
              found = 0;
              index = -1;
              for (int i = 0; i < file_count; i++) {
                  if (strcmp(name, files[i].name) == 0) {
                      found = 1;
                      index = i;
                      break;
                  }
              }
              
              // If not found, display an error message
              if (!found) {
                  printf("Invalid file name.\n");
                  return;
              }