/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>

#define MAX_CMD 256
#define MAX_ARG 20

// --- Fictitious application functions ---
void app_nano() {
    printf("[APP] nano: Simple text editor.\n");
    printf("To use: type 'nano {filename}' to edit a file.\n");
    printf("Functions: Create, edit, and save text files in the terminal.\n");
}

void app_vim() {
    printf("[APP] vim: Advanced text editor.\n");
    printf("To use: type 'vim {filename}' to edit a file.\n");
    printf("Functions: Powerful editing, syntax highlighting, multi-mode editing.\n");
}

void app_gcc() {
    printf("[APP] gcc: GNU Compiler Collection.\n");
    printf("To use: type 'gcc file.c -o file' to compile C code.\n");
    printf("Functions: Compile C programs into executables.\n");
}

void app_geany() {
    printf("[APP] geany: Lightweight IDE.\n");
    printf("To use: type 'geany {filename}' to open a file in the IDE.\n");
    printf("Functions: Edit, compile, and run code with a graphical interface.\n");
}

void app_htop() {
    printf("[APP] htop: Interactive process viewer.\n");
    printf("To use: type 'htop' to view running processes.\n");
    printf("Functions: Monitor system resources, kill processes, sort by usage.\n");
}

// --- Basic commands ---
void cmd_ls() {
    printf("[INFO] Listing files and directories...\n");
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s  ", dir->d_name);
        }
        printf("\n");
        closedir(d);
    } else {
        perror("ls");
    }
}

void cmd_pwd() {
    printf("[INFO] Showing current directory...\n");
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

void cmd_cd(char *path) {
    printf("[INFO] Changing directory...\n");
    if (path == NULL) {
        printf("cd: missing directory\n");
        return;
    }
    if (chdir(path) != 0) {
        perror("cd");
    }
}

void cmd_mkdir(char *dirname) {
    printf("[INFO] Creating new directory...\n");
    if (dirname == NULL) {
        printf("mkdir: missing directory name\n");
        return;
    }
    if (mkdir(dirname, 0755) != 0) {
        perror("mkdir");
    }
}

void cmd_rmdir(char *dirname) {
    printf("[INFO] Removing directory...\n");
    if (dirname == NULL) {
        printf("rmdir: missing directory name\n");
        return;
    }
    if (rmdir(dirname) != 0) {
        perror("rmdir");
    }
}

void cmd_touch(char *filename) {
    printf("[INFO] Creating new file or updating timestamp...\n");
    if (filename == NULL) {
        printf("touch: missing file name\n");
        return;
    }
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        perror("touch");
        return;
    }
    fclose(f);
}

// New version: accepts multiple files
void cmd_cat(char **args) {
    int i = 1;
    if (args[1] == NULL) {
        printf("cat: missing file name\n");
        return;
    }
    while (args[i]) {
        FILE *f = fopen(args[i], "r");
        if (f == NULL) {
            perror(args[i]);
            i++;
            continue;
        }
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), f)) {
            printf("%s", buffer);
        }
        fclose(f);
        i++;
    }
}

void cmd_whoami() {
    printf("[INFO] Showing username...\n");
    struct passwd *pw = getpwuid(getuid());
    printf("%s\n", pw ? pw->pw_name : "user");
}

void cmd_date() {
    printf("[INFO] Showing current date and time...\n");
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%c", tm_info);
    printf("%s\n", buffer);
}

void cmd_echo(char **args) {
    printf("[INFO] Printing text...\n");
    int i = 1;
    while (args[i]) {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
}

void cmd_clear() {
    printf("[INFO] Clearing the screen...\n");
    printf("\033[H\033[J");
}

void cmd_help() {
    printf("[INFO] Showing list of available commands...\n");
    printf("Available commands:\n");
    printf("  ls                   - List files and directories\n");
    printf("  pwd                  - Show current directory\n");
    printf("  cd [dir]             - Change directory\n");
    printf("  mkdir [dir]          - Create a new directory\n");
    printf("  rmdir [dir]          - Remove an empty directory\n");
    printf("  touch [file]         - Create an empty file\n");
    printf("  cat [file ...]       - Show the contents of one or more files\n");
    printf("  whoami               - Show your username\n");
    printf("  date                 - Show current date and time\n");
    printf("  echo [text]          - Print text to the screen\n");
    printf("  clear                - Clear the screen\n");
    printf("  help                 - Show this help\n");
    printf("  apt install [app]    - Install a fictitious application (nano, vim, gcc, geany, htop)\n");
    printf("  exit                 - Exit the terminal\n");
}

// New version: simulates apt install and shows app info
void cmd_apt(char **args) {
    if (args[1] == NULL) {
        printf("Usage: apt install [app]\n");
        return;
    }
    if (strcmp(args[1], "install") == 0 && args[2]) {
        int found = 0;
        if (strcmp(args[2], "nano") == 0) {
            printf("[INFO] Installing nano... Done!\n");
            app_nano();
            found = 1;
        } else if (strcmp(args[2], "vim") == 0) {
            printf("[INFO] Installing vim... Done!\n");
            app_vim();
            found = 1;
        } else if (strcmp(args[2], "gcc") == 0) {
            printf("[INFO] Installing gcc... Done!\n");
            app_gcc();
            found = 1;
        } else if (strcmp(args[2], "geany") == 0) {
            printf("[INFO] Installing geany... Done!\n");
            app_geany();
            found = 1;
        } else if (strcmp(args[2], "htop") == 0) {
            printf("[INFO] Installing htop... Done!\n");
            app_htop();
            found = 1;
        }
        if (!found) {
            printf("[ERROR] Package not found: %s\n", args[2]);
        }
    } else {
        printf("[ERROR] Usage: apt install [app]\n");
    }
}

int main() {
    char input[MAX_CMD];
    char *args[MAX_ARG];

    struct passwd *pw = getpwuid(getuid());
    char *username = pw ? pw->pw_name : "user";

    printf("Mini Linux terminal (type 'help' to see commands, 'exit' to quit)\n");

    while (1) {
        printf("%s$ ", username);
        if (fgets(input, MAX_CMD, stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0;

        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < MAX_ARG-1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) continue;

        if (strcmp(args[0], "ls") == 0) {
            cmd_ls();
        } else if (strcmp(args[0], "pwd") == 0) {
            cmd_pwd();
        } else if (strcmp(args[0], "cd") == 0) {
            cmd_cd(args[1]);
        } else if (strcmp(args[0], "mkdir") == 0) {
            cmd_mkdir(args[1]);
        } else if (strcmp(args[0], "rmdir") == 0) {
            cmd_rmdir(args[1]);
        } else if (strcmp(args[0], "touch") == 0) {
            cmd_touch(args[1]);
        } else if (strcmp(args[0], "cat") == 0) {
            cmd_cat(args);
        } else if (strcmp(args[0], "whoami") == 0) {
            cmd_whoami();
        } else if (strcmp(args[0], "date") == 0) {
            cmd_date();
        } else if (strcmp(args[0], "echo") == 0) {
            cmd_echo(args);
        } else if (strcmp(args[0], "clear") == 0) {
            cmd_clear();
        } else if (strcmp(args[0], "help") == 0) {
            cmd_help();
        } else if (strcmp(args[0], "apt") == 0) {
            cmd_apt(args);
        } else if (strcmp(args[0], "exit") == 0) {
            printf("[INFO] Exiting mini-terminal...\n");
            break;
        } else {
            printf("[ERROR] Command not recognized: %s\n", args[0]);
        }
    }
    return 0;
}
