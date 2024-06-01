#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <dirent.h>
#include <pthread.h>

char** global_argv;
volatile int current_client_count=0;

void mp3_send(int, int, char**);

void client_manager(int);

void* new_client(void*);

int main(int argc, char** argv) 
{
   int server_socket, client_socket;
   socklen_t client_length;
   struct sockaddr_in server_address, client_address;
   global_argv = argv;

   if(argc < 3){
      fprintf(stderr, "Usage: %s <port_no>  <mp3_dir>\n", argv[0]);
      return EXIT_FAILURE;
   }


   // Create socket
   server_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (server_socket == -1) {
      perror("Error creating socket");
      exit(EXIT_FAILURE);
   }

    // Initialize server address structure
   memset(&server_address, 0, sizeof(server_address));
   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
   server_address.sin_port = htons(atoi(argv[1]));

    // Bind socket to address and port
   if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) 
   {
      perror("Error binding socket");
      exit(EXIT_FAILURE);
   }
//    printf("%d\n", server_socket);
    // Listen for connections
   if (listen(server_socket, 5) == -1) 
   {
       perror("Error listening on socket");
       exit(EXIT_FAILURE);
   }

   printf("Waiting for a connection...\n");
   
   client_manager(server_socket);

   close(server_socket);

   return 0;
}

void client_manager(int server_socket){
   int client_socket;
   socklen_t client_length;
   struct sockaddr_in  client_address;
//    printf("%d\n", server_socket);
    // Accept incoming connection
   client_length = sizeof(client_address);
   client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_length);
   if (client_socket == -1) 
   {
       perror("Error accepting connection");
       exit(EXIT_FAILURE);
   }
   else{;
    char str[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &client_address.sin_addr, str, INET_ADDRSTRLEN );
    std::cout<<str<<std::endl;
    pthread_t * thread = new pthread_t;
    pthread_create(thread, NULL, new_client, (void*)&client_socket);
   }
   client_manager(server_socket);
}

void* new_client(void * arg){
   int client_socket = *(int*)arg;
   pthread_detach(pthread_self());
   current_client_count++;

   printf("Connection accepted\n");

   char mp3_id;
   memset(&mp3_id,0,sizeof(mp3_id));

   // Receive mp3_id from client
   int id_succes = recv(client_socket, &mp3_id, sizeof(mp3_id), 0);

//    printf("%c\n\n", mp3_id);
   if (id_succes == -1) 
   {
       perror("Error receiving mp3 ID");
       exit(EXIT_FAILURE);
   }
   
   int song_id = atoi(&mp3_id);

   mp3_send(client_socket, song_id, global_argv);

   id_succes = recv(client_socket, &mp3_id, sizeof(mp3_id), 0); //f

    // Close sockets
   close(client_socket);
   current_client_count--;
   pthread_exit(NULL);
}

void mp3_send(int client_socket, int song_id, char **argv){

   char dir[64] = ""; 
   strcat(dir, argv[2]);
   printf("selected directory: %s \n", dir);

   int count = song_id-1;
   struct dirent *de;  // Pointer for directory entry 
     // opendir() returns a pointer of DIR type.  
  
   DIR *dr = opendir(dir); 
  
   if (dr == NULL)  // opendir returns NULL if couldn't open directory 
   { 
      printf("Could not open mp3 directory" ); 
      return; 
   } 
  
   while ((de = readdir(dr)) != NULL&& count--){
      continue;
      // printf("%s\n", de->d_name);               //used to verify file order if necessary
   }   

   strcat(dir, de->d_name);
   closedir(dr);
   

   printf("selected MP3 %s\n", de->d_name);

   FILE * MP3 = fopen(dir, "rb");
   int MP3_BUFFER_SIZE = 4096;
   char MP3_BUFFER[MP3_BUFFER_SIZE];
   
   size_t bytes_read;
   while(bytes_read = fread(MP3_BUFFER ,1 ,MP3_BUFFER_SIZE ,MP3)){
      send(client_socket, MP3_BUFFER, bytes_read, 0);
   }

}