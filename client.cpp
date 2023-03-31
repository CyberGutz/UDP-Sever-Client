#include <bits/stdc++.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <netinet/in.h>

 #define PORT 8080
 #define MAXLINE 1024

 int main(){
    int sockfd;
    char buffer[MAXLINE];
    const char *hello = "Hello from client";
    struct sockaddr_in servaddr;


    // Criando o Descritor de Arquivo do Socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0) {       //SOCK_DGRAM significa que é UDP
        perror("Falha ao criar o socket");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Preenchendo as informações do server
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len;

    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr*) &servaddr, sizeof(servaddr));
    std::cout<<"Mensagem enviada."<<std::endl;

    n = recvfrom(sockfd, (char*)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);

    buffer[n] = '\0';

    std::cout<<"Server :"<<buffer<<std::endl;

    close(sockfd);  // Fecha o socket
    return 0;



 }