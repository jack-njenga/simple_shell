#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 256
#define MAX_ARGS 64

extern char **environ;

char *search_path(char *cmd)
{
    char *path;
    char *p;
    char *dir;
    char *full_path;
    int len;

    if (cmd[0] == '/')
    {
        return (strdup(cmd));
    }
    path = getenv("PATH");
    if (path == NULL)
    {
        return (NULL);
    }
    p = path = strdup(path);
    while ((dir = strsep(&p, ":")) != NULL)
    {
        len = strlen(dir) + strlen(cmd) + 2;
        full_path = malloc(len);
        if (full_path == NULL)
        {
            return (NULL);
        }
        snprintf(full_path, len, "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free(path);
            return (full_path);
        }
        free(full_path);
    }
    free(path);
    return (NULL);
}

int main(void)
{
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int i;
    pid_t pid;
    int status;
    char *full_path;
    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
        {
            write(STDOUT_FILENO, "\n", 1);
            exit(0);
        }
        cmd[strcspn(cmd, "\n")] = '\0';
        if (strlen(cmd) > 0)
        {
            i = 0;
            args[i] = strtok(cmd, " ");
            while (args[i] != NULL)
            {
                i++;
                args[i] = strtok(NULL, " ");
            }
            if (strcmp(args[0], "exit") == 0)
            {
                exit(0);
            }
            else if (strcmp(args[0], "env") == 0)
            {
                for (i = 0; environ[i] != NULL; i++)
                {
                    write(STDOUT_FILENO, environ[i], strlen(environ[i]));
                    write(STDOUT_FILENO, "\n", 1);
                }
            }
            else
            {
                full_path = search_path(args[0]);
                if (full_path != NULL)
                {
                    pid = fork();
                    if (pid == 0)
                    {
                        if (execve(full_path, args, environ) == -1)
                        {
                            perror(args[0]);
                            exit(1);
                        }
                    }
                    else
                    {
                        wait(&status);
                    }
                    free(full_path);
                }
                else
                {
                    perror(args[0]);
                }
            }
        }
    }
    return (0);
}
