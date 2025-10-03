#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX 1024
#define DELIM " \t\r\n"

// ---------- typeline ----------
void typeline(char *option, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open error");
        return;
    }
    char line[256];
    int count = 0;

    if (strcmp(option, "-a") == 0) {
        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
        }
    } else if (option[0] == '+') {
        int n = atoi(option + 1);
        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
            count++;
            if (count >= n) break;
        }
    } else {
        printf("Invalid typeline option\n");
    }
    fclose(fp);
}

// ---------- list ----------
void list(char *option, char *dirname) {
    DIR *dp;
    struct dirent *entry;

    dp = opendir(dirname);
    if (dp == NULL) {
        perror("opendir error");
        return;
    }

    int count = 0;
    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(option, "f") == 0) {
            printf("%s\n", entry->d_name);
        } else if (strcmp(option, "i") == 0) {
            printf("%s\t%lu\n", entry->d_name, entry->d_ino);
        }
        count++;
    }
    if (strcmp(option, "n") == 0) {
        printf("Total entries: %d\n", count);
    }
    closedir(dp);
}

// ---------- count ----------
void count(char *option, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open error");
        return;
    }
    int ch, words = 0, lines = 0, chars = 0;
    int inword = 0;

    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n') lines++;
        if (ch == ' ' || ch == '\n' || ch == '\t')
            inword = 0;
        else if (inword == 0) {
            inword = 1;
            words++;
        }
    }

    if (strcmp(option, "c") == 0)
        printf("Characters: %d\n", chars);
    else if (strcmp(option, "w") == 0)
        printf("Words: %d\n", words);
    else if (strcmp(option, "l") == 0)
        printf("Lines: %d\n", lines);
    else
        printf("Invalid count option\n");

    fclose(fp);
}

// ---------- search ----------
void search(char *option, char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File open error");
        return;
    }
    char line[256];
    int lineno = 0, found = 0;

    while (fgets(line, sizeof(line), fp)) {
        lineno++;
        if (strstr(line, pattern)) {
            found++;
            if (strcmp(option, "a") == 0) {
                printf("Line %d: %s", lineno, line);
            } else if (strcmp(option, "f") == 0) {
                printf("First occurrence at line %d: %s", lineno, line);
                fclose(fp);
                return;
            }
        }
    }
    if (strcmp(option, "c") == 0) {
        printf("Occurrences of '%s': %d\n", pattern, found);
    } else if (found == 0) {
        printf("Pattern not found\n");
    }
    fclose(fp);
}

// ---------- execute other commands ----------
void execute_cmd(char **args) {
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp error");
        }
        exit(0);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork failed");
    }
}

int main() {
    char input[MAX];
    char *args[64];

    while (1) {
        printf("myshell$ ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) break;

        // Tokenize
        int i = 0;
        args[i] = strtok(input, DELIM);
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, DELIM);
        }

        if (args[0] == NULL) continue;

        if (strcmp(args[0], "exit") == 0) break;

        // Custom commands
        if (strcmp(args[0], "typeline") == 0) {
            if (args[1] && args[2])
                typeline(args[1], args[2]);
            else
                printf("Usage: typeline +n filename | typeline -a filename\n");

        } else if (strcmp(args[0], "list") == 0) {
            if (args[1] && args[2])
                list(args[1], args[2]);
            else
                printf("Usage: list f|n|i dirname\n");

        } else if (strcmp(args[0], "count") == 0) {
            if (args[1] && args[2])
                count(args[1], args[2]);
            else
                printf("Usage: count c|w|l filename\n");

        } else if (strcmp(args[0], "search") == 0) {
            if (args[1] && args[2] && args[3])
                search(args[1], args[2], args[3]);
            else
                printf("Usage: search a|f|c filename pattern\n");

        } else {
            // Normal Linux command
            execute_cmd(args);
        }
    }

    return 0;
}