/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<stdlib.h>

struct list
  {
    char item[50];
    char title[50];
    char quantity[50];
} l1[3];

 
int main(int argc , char *argv[])
{
    //list l1[3];
    int sock,i,n,n1,n2;
    struct sockaddr_in server;
    char task[1000] , server_reply[2000], data[100], data1[100], data2[100], item_no[20], quan[20];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons( atoi(argv[2]));
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }  
     
     puts("Connected\n");
     
     //keep communicating with server
      write(sock, argv[3], sizeof(argv[3]));
     if(strcmp(argv[3],"list")==0)
     {
        // write(sock, task, sizeof(task));
         printf("\nItem\tTitle \t Quantity");
         for (i=0;i< 3;i++)
       {
        //Receive a reply from the server
          n=read(sock ,data , 100);
          //puts(data);
          n1=read(sock ,data1 , 100);
           //puts(data);
          n2=read(sock ,data2 , 100);
          //   puts(data);
        if( ( n && n1   && n2 )  < 0)
        {
            puts("recv failed");
            break;
        }
          
        //puts("\nServer reply \n:");
        //puts(server_reply);
        //for (i=0;i< sizeof(l1);i++)
        printf("\n%s\t%s\t%s\n", data, data1, data2);   //, l1[i].title, l1[i].quantity);
     }      
     close(sock);
    }
    else if(strcmp(argv[3],"order")==0)
   { 
	printf("Order sent");
      // write(sock, task,sizeof(task));
      // printf("\nEnter item no, quantity");
      // scanf("%s%s", data,data1);
       strcpy(task,argv[2]);
       strcpy(data1,"54");
       write(sock,argv[4], sizeof(argv[4]));
       write(sock, argv[5], sizeof(argv[5]));   
       read(sock, data2, sizeof(data2));
       printf("\n%s", data2);    
       close(sock);
   }

}




