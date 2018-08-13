#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/stat.h>
#include<string.h>
#include<syslog.h>
#include <netinet/in.h>
#include<unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<malloc.h>


#define PORT 5000
#define LENGTH 5120

int demon_creation(int sock_fd)
 {

    pid_t pid ;
    pid = fork();
   // sleep(5);

    if(pid < 0)
      {
    printf("DEMON IS NOT CREATED");
        return -1;
      }
      else
      {
        printf(" \nDEMON CREATED \n");

      }
     //sleep(5);
      if (setsid() < 0)
          return -1;

          int valread ;
         char buffer[1024] = "bvdbvdfmv ";
        char *hello = "Hello From The Client \n";
        send(sock_fd , hello , strlen(hello) , 0 );
        valread = read( sock_fd , buffer, 1024);
         size_t left = write(sock_fd, buffer , 1024);
        printf("%s\n",buffer );

      setlogmask(LOG_UPTO(LOG_NOTICE));
      openlog("server1" , LOG_CONS , LOG_AUTH) ;

      signal(SIGKILL , SIG_IGN);
      umask(0);

      return 0;

 }



int main(void)
  {
    int sockfd ;
    char revbuf[LENGTH];

    sockfd = socket(AF_INET,SOCK_STREAM, 0);

      if(sockfd <= 0)
         {
              printf("SOCKET IS NOT CREATED\n");
         }
         else
            {
              printf("SOCKET CREATED\n");
            }

        struct sockaddr_in saddr;
        memset(&saddr, '0', sizeof(saddr));
        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(PORT);


        FILE *fp;
        struct stat buf;
        fp=fopen("/home/kiit/Desktop/ipfile.txt","r");
        fseek(fp, 0, SEEK_END);
        int pos = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char *str = malloc(buf.st_size);
        while(!feof(fp))
        {
                char *s=malloc(1024);
                fgets(s,1024,fp);
                s[strlen(s)]='\0';
                strcat(str,s);
        }
        printf("%s",str);

        if(inet_pton(AF_INET, str , &saddr.sin_addr)<=0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }



       demon_creation(sockfd);
       printf("Session started!\n");
       sleep(5);
       syslog(LOG_ERR, "Session started!!");
       closelog();

  printf("[Client] Receiveing file from Server and saving it as finaloutput.csv...");
	char* fr_name = "/home/kiit/Desktop/finaloutput.csv";
	FILE *fr = fopen(fr_name, "a");
	if(fr == NULL)
		printf("File %s Cannot be opened.\n", fr_name);
	else
	{
	    bzero(revbuf, LENGTH);
	    int fr_block_sz = 0;
	    int success = 0;
	        while(fr_block_sz = recv(sockfd, revbuf, LENGTH, 0))
	        {
	            if(fr_block_sz < 0)
	            {
	                printf("Receive file error.\n");
	            }
	            int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
	            if(write_sz < fr_block_sz)
	            {
	                printf("File write failed.\n");
	            }
				else if(fr_block_sz)
				{
					break;
				}
	            bzero(revbuf, LENGTH);
	        }
	        printf("Ok received from server!\n");
	      //  success = 1;
	       fclose(fr);
	    }


  return 0;
  }
