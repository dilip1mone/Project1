#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>
#include <syslog.h>
#include<unistd.h>
#include <stdlib.h>

#define PORT 5000
#define LENGTH 5000


void init_log()
{
   setlogmask(LOG_UPTO(LOG_NOTICE));
  //printf("Session started!");
   //openlog("junk",LOG_CONS | LOG_PID | LOG_NDELAY |LOG_PERROR, LOG_LOCAL1);
   openlog("server1" , LOG_CONS , LOG_AUTH) ;
}

int main(void)
  {
     char sa_data[1000] ;
     int sockfd = socket(AF_INET,SOCK_STREAM, 0);

     if(sockfd == 0)
       {
          printf("FAILD TO CREATE SOCKET");
          return -1;
       }

     struct sockaddr_in addr;

     addr.sin_family = AF_INET;
     addr.sin_port = htons(PORT);
     //inet_aton("63.161.169.137", &myaddr.sin_addr.s_addr);
     addr.sin_addr.s_addr = INADDR_ANY;

     int addrlen = sizeof(addr);

     int bind_val = bind(sockfd, (struct sockaddr *)&addr, addrlen);

            if(bind_val < 0)
              {
                printf("UNABLE TO BIND");
                return -1;
              }

        int listen_port = listen(sockfd, 3);

        if(listen_port < 0)
          {
            printf("Unable to create the listen port");
            return -1 ;
          }

          int new_socket;

    if ((new_socket = accept(sockfd, (struct sockaddr *)&addr, (socklen_t*)&addrlen))<0)
         {
           printf("UNABLE TO ACCEPT");
           return -1;
         }
         int valread ;

          char buffer[1024] = "ASSIGNMENT IN CRAY";
          char *hello = "Hello from server";



          system("dmesg > newfile.txt");
          system("cat newfile.txt| tr -s '[:blank:]' ',' > ofile.csv");
          system("cat /proc/meminfo > newfile1.txt");
          system("cat newfile1.txt| tr -s '[:blank:]' ',' > ofile1.csv");
          system("cat ofile.csv ofile1.csv > outputfile.csv");


         send(new_socket , hello , strlen(hello) , 0 );
         printf("Hello message sent\n");
         valread = read( new_socket , buffer, 1024);
         printf("%s\n",buffer );


          init_log();
          printf("Session started!");
          syslog(LOG_ERR, "Session started!!");
        //  closelog();



         char* fs_name = "/home/kiit/Documents/outputfile.csv";
         char sdbuf[LENGTH]; // Send buffer
         printf("[Server] Sending %s to the Client...", fs_name);
         FILE *fs = fopen(fs_name, "r");
         if(fs == NULL)
         {
             printf("ERROR: File %s not found on server.\n", fs_name);
             exit(1);
         }

         bzero(sdbuf, LENGTH);
         int fs_block_sz;
         while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0)
         {
             if(send(new_socket, sdbuf, fs_block_sz, 0) < 0)
             {
                 printf("ERROR: Failed to send file %s.\n", fs_name);
                 exit(1);
             }
             bzero(sdbuf, LENGTH);
         }
         printf("Ok sent to client!\n");


         system("cat /var/log/syslog | grep WARNING ");
         printf("________________________________________");
         system("cat /var/log/syslog | grep Error ");

         closelog();

         return 0;

}
