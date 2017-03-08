/*
    C socket server example
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<stdlib.h>

  struct list1
  {
    char item[50];
    char title[50];
    char quantity[50];
} ;
   


int main(int argc , char *argv[])
{
     struct list1 l[3]=     { "1", "Star Wars", "100", "2", "Harry Potter", "80",  "3", "Inside Out", "50"};     
    int socket_desc , client_sock , c , read_size,i,quant,item,on,ret,n;
    struct sockaddr_in server , client;
    char client_message[100], data[100], data1[100], data2[100],msg[100], newbuffer[100];
    struct hostent *hostp;
    char *hostaddrp;
    char buf[100];
     
    while(1)
  {
    //Create socket   
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     on = 1;
      ret = setsockopt( socket_desc, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen    
    if(listen(socket_desc , 1)==0)
    printf("Waiting for the client\n");
    else
    printf("Error\n");
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
    
    read_size=read(client_sock, client_message, sizeof(client_message));

   /* if (read_size< 0)
   {
      puts("Received Failed");
      break;
    }*/
  
  if (strcmp(client_message,"list")==0)
{    
       puts("test");
        for(i=0;i <3; i++)
       {
        write(client_sock,l[i].item , 100);
        //puts(l[i].item);
        write(client_sock,l[i].title , 100);
         //puts(l[i].title);
        write(client_sock,l[i].quantity , 100);
         //puts(l[i].quantity);
       }
 close(client_sock);
 close(socket_desc);
}
      //memset(data, 0, sizeof(data));
   
    else  if(strcmp(client_message, "order")==0)
     {
	//printf("Order accepted");
           /*  puts("test");
          if((read(client_sock, data, sizeof(data))   &&  read(client_sock, data1, sizeof(data1)))<0)
      {
          //read(client_sock, data2, sizeof(data2));
       puts("receive error");
      }*/
	
    read(client_sock, data, sizeof(data));	
    item= atoi(data);
    read(client_sock, data1, sizeof(data1));  
    quant=atoi(data1); 
    printf("\n%d\t %d\t\n",item ,quant);
     int b;
      
         for(i=0;i<3;i++)
{          
           if(atoi(l[i].item)== item && (b=atoi(l[i].quantity))>quant)
          {          // b= b-quant;
                 //char num[50];
                char buffer [50];
                 int n;
               sprintf (buffer, " %d",b-quant);
                // printf ("[%s] is a string \n",buffer);
                strcpy( l[i].quantity, buffer);   
               write(client_sock, "Request fullfilled", 100);           
         
         }
         if(atoi(l[i].item)== item && (b=atoi(l[i].quantity))<quant)
                 write(client_sock, "Request cannot fullfilled", 100);
}

    close(client_sock);
    close(socket_desc);
   } 
   
}

     close(client_sock);
    close(socket_desc);
return 0;
}






