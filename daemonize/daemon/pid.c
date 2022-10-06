#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <errno.h>


int main()
{
        char pidline[1024];
        char *pid;
        int i=0;
        int n=0;
        FILE *fp = popen("pidof java","r");
        fgets(pidline,1024,fp); 
        printf("%s",pidline);
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
            if (n != 0){  // PID НЕТ
                FILE *pidf= fopen("pid.txt", "a");  
                fprintf(pidf,"n");
                fclose(pidf);
                return 0;
            } else { // PID ЕСТЬ
                FILE *pidf= fopen("pid.txt", "a");  
                fprintf(pidf,"y");
                fclose(pidf);
             return 1;
             }
        
}