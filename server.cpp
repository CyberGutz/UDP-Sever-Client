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
    const char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    //Criando o File Descriptor do socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) <0){
        perror("Falha ao criar Socket");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Preenchendo as informações do server
    // https://stackoverflow.com/questions/16508685/understanding-inaddr-any-for-socket-programming
    servaddr.sin_family = AF_INET; //IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;          // INADDR_ANY vincula o socket a todas as interfaces disponíveis, se você quiser vincular o server à um IP específico, use a função inet_addr("endereço");
    servaddr.sin_port = htons(PORT);

    // Vincular o socket com o endereço do server
    if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))<0){
        perror("Erro ao vincular");
        exit(EXIT_FAILURE);
    }

    socklen_t len;

    int n;

    len = sizeof(cliaddr); //len é um valor/resultado

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);          //Escuta o cliente.

    buffer[n] =  '\0';
    printf("Cliente : %s\n", buffer);
    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);   // Manda a Mensagem.

    std::cout<<"Mensagem enviada."<<std::endl;

    return 0;

 }