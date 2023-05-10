#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

/* 
    you can use this in environments where no ps tool nor a package manager is available, changing stuff should be easy
    see https://linux.die.net/man/5/proc over what infos you can pull out of the /proc folder and sub-files
*/

#define MAX_FNAME 200

static int print_stat_file(long pid) {
    char filename[MAX_FNAME + 1] = {};
    snprintf(filename, MAX_FNAME, "/proc/%d/stat", pid);
    
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Failed to open file\n");
        return 1;
    }

    int unused;
    char comm[1000];
    char state;
    fscanf(f, "%d %s %c", &unused, comm, &state);
    fclose(f);

    printf("PID %u - %s - %c - ", pid, comm, state);
    return 0;
}

static int print_cmdline_file(long pid) {
    char filename[MAX_FNAME + 1] = {};
    snprintf(filename, MAX_FNAME, "/proc/%d/cmdline", pid);
    
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Failed to open file\n");
        return 1;
    }

    char content[100 + 1] = {};
    while(fgets(content, 100, f)) {
        printf("%s", content);
    }
    fclose(f);
    return 0;
}

int main (void)
{
    DIR *dp = opendir ("/proc");
    if (dp == NULL)
    {
        perror ("Couldn't open the directory");
        return -1;
    }

    struct dirent *ep;
    while ((ep = readdir (dp)) != NULL) {
        char *end = NULL;
        long pid = strtoul (ep->d_name, &end, 10);
        if (pid != 0) {
            if (print_stat_file(pid) != 0) {
                return -2;
            }
            if (print_cmdline_file(pid) != 0) {
                return -2;
            }
            printf("\n");
        }
    }

    (void) closedir (dp);
    return 0;
}