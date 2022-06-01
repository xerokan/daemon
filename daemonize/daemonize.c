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
    
    /* Open the log file */
    openlog ("daemonlog", LOG_PID, LOG_DAEMON);
}

    int main()
{
    skeleton_daemon();
    char pidline[1024];
    char *pid;
    int pidno[64];
    while (1)
    {   
        int i=0;
        int n=0;
        FILE *fp = popen("pidof daemonize","r");
        fgets(pidline,1024,fp);

        printf("%s",pidline);
        // pid = pidline;
        pid = strtok(pidline," ");
        int len = strlen(pid);
        
        pclose(fp);
        for (i=0;len>0;i++){
            len--;
            if (!((pid[i]>='0'&&pid[i]<='9') || pid[i] == ' ' || pid[i] == '\n')){
            // if (!((pid[i]>='0'&&pid[i]<='9') || pid[i] == '\n')){
               n=1;
            }
            }
            if (n != 0){
                printf("ne PID");
            } else printf("PID");
        sleep (10);
    }
   
    syslog (LOG_NOTICE, "First daemon terminated.");
    closelog();
    
    return EXIT_SUCCESS;
}