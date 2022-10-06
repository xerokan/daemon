/*
* daemonize.c
* This example daemonizes a process, writes a few log messages,
* sleeps 20 seconds and terminates afterwards.
* This is an answer to the stackoverflow question:
* https://stackoverflow.com/questions/17954432/creating-a-daemon-in-linux/17955149#17955149
* Fork this code: https://github.com/pasce/daemon-skeleton-linux-c
* Read about it: https://nullraum.net/how-to-create-a-daemon-in-c/
*/
    
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include<string.h>
#include <time.h>

    static void skeleton_daemon()
{
    pid_t pid;
    
    /* Fork off the parent process */
    pid = fork();
    
    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);
    
     /* Success: Let the parent terminate */
    if (pid > 0)

        exit(EXIT_SUCCESS);
    
    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);
    
    /* Catch, ignore and handle signals */
    /*TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    
    /* Fork off for the second time*/
    pid = fork();
    
    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);
    
    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    /* Set new file permissions */
    umask(0);
    
    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/daemon");
    
    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }
}

    static int isPID(FILE *f)
{
    const char *no = "n";
    char st[1];
    system("./pid");
    f = fopen("pid.txt", "r");  
    fscanf(f,"%s", st);
    fclose(f);
    f = fopen("pid.txt", "w");
    fclose(f);
    int d = strcmp(st,no);
    return d;
}

    int main()
{
    skeleton_daemon();
    const char *no = "n";
    long int ttime;
    FILE *pidf;
    system("./zapusk");
    while (1)
    { 
        sleep(5);
        if (isPID(pidf) == 0){  
            // сервис не работает
            ttime = time (NULL);
            FILE *log1= fopen("logfile.txt", "a");    
            fprintf(log1,"Service Время: %s   %s", ctime (&ttime)," Service stop\n");
            fclose(log1);
            //включенеи запускатора
            system("./zapusk");
            //старт сервиса
            ttime = time (NULL);
            FILE *log= fopen("logfile.txt", "a");  
            fprintf(log,"Service Время: %s   %s", ctime (&ttime)," Service starting\n");
            fclose(log);
        }   
            // else {
            //     //найден нужный пид
            // printf("PID");
            // ttime = time (NULL);
            // FILE *log1= fopen("logfile.txt", "a");  
            // fprintf(log1,"Service Время: %s   %s", ctime (&ttime)," Service stop\n");
            // fclose(log1);}
    }
}