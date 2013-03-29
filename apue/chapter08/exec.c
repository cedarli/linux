#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
        
/* env_list[] 需要用 NULL 结尾 */
char *env_list[] = {"USER=unknown", "PATH=/tmp", NULL};
        
/* When a process calls one of the exec functions, that process is
 * completely replaced by the new program, and the new program starts
 * executing at its main() function. The process ID does not change across
 * an exec, because a new process is not created; exec merely replaces the
 * current process--its text, data, heap, and stack segments--with a
 * brand new program from disk.
 * #include <unistd.h>
 * int execl(const char *pathname, const char *arg0, ... // (char *)0);
 * int execv(const char *pathname, char *const argv[]);
 * int execle(const char *pathname, const char *arg0, ...
 *              // (char *)0, char *const envp[]);
 * int execve(const char *pathname, char *const argv[], char *const envp[]);
 * int execlp(const char *filename, const char *arg0, ... // (char *)0);
 * int execvp(const char *filename, char *const argv[]);
 *      All six return: -1 on error, no return on success
 *
 * 下面的程序描述的是 execl 类型的函数, exev 类型的函数和 execl 类似.
 */
int main(void)
{
    pid_t pid;
    char current_dir[BUFSIZ];
        
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        return 1;
    }
    else if (pid == 0) {    /* child */
        if (execl("echoall", "EXECL ARG1", "arg2", (char *)0) < 0) {
            printf("execl echoall error: %m\n");
            return 1;
        }
    }
        
    if (waitpid(pid, NULL, 0) < 0) {
        printf("waitpid error\n");
        return 1;
    }
        
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        return 0;
    }
    else if (pid == 0) {    /* child */
        if (getcwd(current_dir, BUFSIZ) == NULL) {
            printf("getcwd error: %m\n");
            return 1;
        }
        
        strcat(current_dir, "/echoall");
        
        if (execle(current_dir, "echoall", "myarg1",
                    "MY ARG2", (char *)0, env_list) < 0) {
            printf("execle %s error: %m\n", current_dir);
            return 1;
        }
    }
        
    if (waitpid(pid, NULL, 0) < 0) {
        printf("waitpid %d error: %m\n", pid);
        return 1;
    }
        
    if ((pid = fork()) < 0) {
        printf("fork again error\n");
        return 1;
    }
    else if (pid == 0) {    /* child */
        if (execlp("./echoall", "only 1 arg", (char *)0) < 0) {
            printf("execlp echoall error: %m\n");
            return 1;
        }
    }
        
    if (waitpid(pid, NULL, 0) < 0) {
        printf("waitpid %d error: %m\n", pid);
        return 1;
    }
        
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        return 1;
    }
    else if (pid == 0) {    /* child */
        system("export PATH=$PATH:");
        if (execlp("echoall", "ARG1", "ARG2", (char *)0) < 0) {
            printf("execlp echoall error: %m\n");
            return 1;
        }
    }
        
    if (waitpid(pid, NULL, 0) < 0) {
        printf("waitpid error\n");
        return 1;
    }
        
    return 0;
}
