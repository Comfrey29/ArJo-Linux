/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
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

// Implementació de la comanda ls
void cmd_ls() {
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

// Implementació de la comanda pwd
void cmd_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

// Implementació de la comanda cd
void cmd_cd(char *path) {
    if (path == NULL) {
        printf("cd: falta el directori\n");
        return;
    }
    if (chdir(path) != 0) {
        perror("cd");
    }
}

// Implementació de la comanda mkdir
void cmd_mkdir(char *dirname) {
    if (dirname == NULL) {
        printf("mkdir: falta el nom del directori\n");
        return;
    }
    if (mkdir(dirname, 0755) != 0) {
        perror("mkdir");
    }
}

// Implementació de la comanda rmdir
void cmd_rmdir(char *dirname) {
    if (dirname == NULL) {
        printf("rmdir: falta el nom del directori\n");
        return;
    }
    if (rmdir(dirname) != 0) {
        perror("rmdir");
    }
}

// Implementació de la comanda touch
void cmd_touch(char *filename) {
    if (filename == NULL) {
        printf("touch: falta el nom del fitxer\n");
        return;
    }
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        perror("touch");
        return;
    }
    fclose(f);
}

// Implementació de la comanda cat
void cmd_cat(char *filename) {
    if (filename == NULL) {
        printf("cat: falta el nom del fitxer\n");
        return;
    }
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("cat");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), f)) {
        printf("%s", buffer);
    }
    fclose(f);
}

// Implementació de la comanda whoami
void cmd_whoami() {
    struct passwd *pw = getpwuid(getuid());
    printf("%s\n", pw ? pw->pw_name : "usuari");
}

// Implementació de la comanda date
void cmd_date() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%c", tm_info);
    printf("%s\n", buffer);
}

// Implementació de la comanda echo
void cmd_echo(char **args) {
    int i = 1;
    while (args[i]) {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
}

// Implementació de la comanda clear
void cmd_clear() {
    printf("\033[H\033[J");
}

// Implementació de la comanda cp
void cmd_cp(char *src, char *dest) {
    if (!src || !dest) {
        printf("cp: falta origen/destí\n");
        return;
    }
    
    FILE *f_src = fopen(src, "rb");
    if (!f_src) {
        perror("cp");
        return;
    }
    
    FILE *f_dest = fopen(dest, "wb");
    if (!f_dest) {
        perror("cp");
        fclose(f_src);
        return;
    }
    
    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), f_src)) > 0) {
        fwrite(buffer, 1, bytes, f_dest);
    }
    
    fclose(f_src);
    fclose(dest);
}

// Implementació de la comanda grep
void cmd_grep(char *pattern, char *filename) {
    if (!pattern || !filename) {
        printf("grep: falta patró o fitxer\n");
        return;
    }
    
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("grep");
        return;
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, pattern)) {
            printf("%s", line);
        }
    }
    fclose(f);
}

// Implementació de la comanda apt (simulació)
void cmd_apt_simulate(char **args) {
    char cmd[MAX_CMD] = "sudo apt -s";
    int i = 1;
    while (args[i]) {
        strcat(cmd, " ");
        strcat(cmd, args[i]);
        i++;
    }
    system(cmd);
}

// Implementació de la comanda neofetch
void cmd_neofetch() {
    printf("\n");
    printf("  OS: Arjo Linux 1.0\n");
    printf("  Kernel: 6.1.0-custom\n");
    printf("  Shell: arjo-terminal\n");
    printf("  CPU: Intel i7-12700K (simulat)\n");
    printf("  Memory: 16GB DDR5\n\n");
}

// Implementació de la comanda help
void cmd_help() {
    printf("Comandes disponibles:\n");
    printf("  ls           - Llista fitxers/directoris\n");
    printf("  pwd          - Mostra directori actual\n");
    printf("  cd [dir]     - Canvia de directori\n");
    printf("  mkdir [dir]  - Crea directori\n");
    printf("  rmdir [dir]  - Elimina directori buit\n");
    printf("  touch [fitx] - Crea fitxer buit\n");
    printf("  cat [fitx]   - Mostra contingut fitxer\n");
    printf("  cp [src][dst]- Copia fitxers\n");
    printf("  grep [pat][f]- Busca text en fitxer\n");
    printf("  apt [cmd]    - Simulació gestió paquets\n");
    printf("  neofetch     - Mostra info del sistema\n");
    printf("  clear        - Neteja pantalla\n");
    printf("  exit         - Surt de la terminal\n");
}

int main() {
    char input[MAX_CMD];
    char *args[MAX_ARG];

    struct passwd *pw = getpwuid(getuid());
    char *username = pw ? pw->pw_name : "usuari";

    printf("Terminal Arjo Linux (escriu 'help' per ajuda)\n");

    while (1) {
        printf("%s@arjo:~$ ", username);
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
            cmd_cat(args[1]);
        } else if (strcmp(args[0], "cp") == 0) {
            cmd_cp(args[1], args[2]);
        } else if (strcmp(args[0], "grep") == 0) {
            cmd_grep(args[1], args[2]);
        } else if (strcmp(args[0], "apt") == 0) {
            cmd_apt_simulate(args);
        } else if (strcmp(args[0], "neofetch") == 0) {
            cmd_neofetch();
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
        } else if (strcmp(args[0], "exit") == 0) {
            break;
        } else {
            printf("Comanda no reconeguda: %s\n", args[0]);
        }
    }
    return 0;
}
