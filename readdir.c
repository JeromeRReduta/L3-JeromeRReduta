/**
 * Lovingly copy and pasted from Schedule page
 * 
 * readdir.c
 *
 * Demonstrates reading directory contents.
 */

#include <dirent.h>
#include <stdio.h>

int main(void) {
    DIR *directory; // Opens dir

    // Case: Directory is null (does not exist)
    if ((directory = opendir(".")) == NULL) {
        perror("opendir");
        return 1;
    }

    /* Case: Directory exists
    *  create entry, set it to readdir(directory), print entry, and readdir(directory) runs out of entries
    */
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        printf("-> %s\n", entry->d_name);
    }

    // Close your resources
    closedir(directory);

    return 0;
}