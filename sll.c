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
        printf("$ ");
        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
        {
            printf("\n");
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
                    printf("%s\n", environ[i]);
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
                        if (execv(full_path, args) == -1)
                        {
                            fprintf(stderr, "%s: command not found\n", args[0]);
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
                    fprintf(stderr, "%s: command not found\n", args[0]);
                }
            }
        }
    }
    return (0);
}
