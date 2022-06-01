#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <errno.h>

main()
{
        char pidline[1024];
        char *pid;
        int i=0;
        int n=0;
        int pidno[64];
        FILE *fp = popen("pidof daemonize","r");
        fgets(pidline,1024,fp);

        printf("%s",pidline);
        // pid = pidline;
        pid = strtok(pidline," ");
        int len = strlen(pid);
        
        pclose(fp);
        printf(pid);
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
            return 0;
}