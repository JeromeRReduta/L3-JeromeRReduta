#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* Function prototypes */
void initialize(void) __attribute__((constructor));
int open(const char *pathname, int flags);

/* Function pointers */
int (*orig_open)(const char * pathname, int flags) = NULL;

/* Preprocessor Directives */
#ifndef DEBUG
#define DEBUG 1
#endif
/**
 * Logging functionality. Set DEBUG to 1 to enable logging, 0 to disable.
 */
#define LOG(fmt, ...) \
    do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
            __LINE__, __func__, __VA_ARGS__); } while (0)

void initialize(void)
{
    orig_open = (int (*)(const char *, int)) dlsym(RTLD_NEXT, "open");
    LOG("Original open() location: %p\n", orig_open);
    LOG("New open() location: %p\n", open);
}

int open(const char *pathname, int flags)
{
    size_t len = strlen(pathname);
    printf("%s", pathname);
    printf("LENGTH:\t%lu", len);

    /* Whoo, we have the string length. Now what?! */

    // Maybe strstr messes with pathname pointer, and instead we should go through entire char[] one by one

    char myPath[] = "/home4/jrreduta/Le-JeromeRReduta/roll.txt";

    char* txt = strstr(pathname, "txt");
    char* java = strstr(pathname, "java");

    if (txt != NULL) {
        printf("get rolled");
        return (*orig_open)(myPath, flags);
    }
    if (java != NULL) {
        int errnum = 2;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("ENOENT");
        printf("%s", strerror(errnum));
        return -1;
    }

    return (*orig_open)(pathname, flags);
}


// $ LD_PRELOAD=$(pwd)/rick-ropen.so cat 