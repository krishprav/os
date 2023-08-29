#ifndef PART1_H
#define PART1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>

// Define a structure for file information
typedef struct file {
    char name[20];
    char owner[20];
    long size;
    int permission;
    int inode;
} file;

// Define a structure for owner information
typedef struct owner {
    char name[20];
    int id;
} owner;

// Declare some global variables
extern file files[100]; // An array of files
extern owner owners[100]; // An array of owners
extern int file_count; // The number of files
extern int owner_count; // The number of owners

// A function to convert bytes to human readable format
char *human_readable_size(long bytes) {
    // Declare some variables for units and suffixes
    char *units[] = {"B", "KB", "MB", "GB", "TB"};
    char *suffix = "";
    
    // Declare a variable for the result and allocate memory
    char *result = (char *)malloc(20 * sizeof(char));
    
    // Loop through the units and divide the bytes by 1024 until it is less than 1024
    for (int i = 0; i < 5; i++) {
        if (bytes < 1024) {
            suffix = units[i];
            break;
        }
        bytes /= 1024;
    }
    
    // Format the result with the bytes and the suffix
    sprintf(result, "%ld %s", bytes, suffix);
    
    // Return the result
    return result;
}

// A function to list the file name, size, and owner name against each file in a given directory
void list_files(char *path) {
    // Open the directory
    DIR *dir = opendir(path);
    
    // Check if the directory is valid
    if (dir == NULL) {
        printf("Invalid directory.\n");
        return;
    }
    
    // Declare some variables for directory entry and file status
    struct dirent *entry;
    struct stat status;
    
    // Loop through the directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Get the full path of the entry
        char full_path[100];
        sprintf(full_path, "%s/%s", path, entry->d_name);
        
        // Get the status of the entry
        if (stat(full_path, &status) == -1) {
            printf("Error getting status of %s.\n", full_path);
            continue;
        }
        
        // Check if the entry is a regular file
        if (S_ISREG(status.st_mode)) {
            // Get the file information from the status
            file new_file;
            strcpy(new_file.name, entry->d_name);
            new_file.size = status.st_size;
            new_file.permission = status.st_mode & 0777;
            new_file.inode = status.st_ino;
            
            // Get the owner information from the status
            struct passwd *pw = getpwuid(status.st_uid);
            
            // Check if the owner is valid
            if (pw == NULL) {
                printf("Error getting owner of %s.\n", full_path);
                continue;
            }
            
            // Copy the owner name to the file information
            strcpy(new_file.owner, pw->pw_name);
            
            // Add the file to the array and increment the file count
            files[file_count] = new_file;
            file_count++;
            
            // Check if the owner is already in the array of owners
            int found = 0;
            for (int i = 0; i < owner_count; i++) {
                if (strcmp(new_file.owner, owners[i].name) == 0) {
                    found = 1;
                    break;
                }
            }
            
            // If not found, add the owner to the array and increment the owner count
            if (!found) {
                owner new_owner;
                strcpy(new_owner.name, new_file.owner);
                new_owner.id = pw->pw_uid;
                owners[owner_count] = new_owner;
                owner_count++;
            }
        }
    }
    
     // Close the directory
     closedir(dir);
     
     // Display the header of the table with the file names, sizes and owner names
     printf("Name\tSize\tOwner\n");
     
     // Loop through the files and display their information
     for (int i = 0; i < file_count; i++) {
         printf("%s\t%s\t%s\n", files[i].name, human_readable_size(files[i].size), files[i].owner);
     }
     
     // Display the total number of files and owners
     printf("Total number of files: %d\n", file_count);
     printf("Total number of owners: %d\n", owner_count);
}

// A function to display the menu options
void display_menu() {
    printf("Welcome to the DAC system. Please choose an option:\n");
    printf("1. List the file name, size, and owner name against each file in a given directory\n");
    printf("2. Store and display the file vs owner matrix\n");
    printf("3. List all the file names created by an user/owner\n");
    printf("4. Display owner and group name against each inode value\n");
    printf("5. Change the file permission of the files\n");
    printf("6. Exit\n");
}

#endif