#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{

    char *host_do_servidor = argv[1];
    char *porto_servidor = argv[2];
    char *nome_arquivo = argv[3];
    char *tam_buffer = argv[4];

    //socket servidor
    struct sockaddr_in server;

    int sockfd;

    int len = sizeof(server);
    int slen;

    //receber buffer
    char buffer_in[atoi(tam_buffer)];
    //enviar buffer
    char buffer_out[atoi(tam_buffer)];

    printf("Iniciando Client\n");

    //criando o socket para o cliente
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Erro na criacao do socket");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Client socket criado com fd: %d\n", sockfd);

    //definindo os atributos do socket
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(porto_servidor));
    server.sin_addr.s_addr = inet_addr(host_do_servidor);

    // Tenta conectar com o servidor
    if (connect(sockfd, (struct sockaddr*) &server, len) == -1) {
        perror("Nao foi possivel conectar com o servidor");
        return EXIT_FAILURE;
    }

    //enviando o nome do arquivo para o servidor
    strcpy(buffer_out,nome_arquivo);
    send(sockfd, buffer_out, strlen(buffer_out), 0);

    slen = recv(sockfd, buffer_in, strlen(tam_buffer), 0);
    printf("Server answer: %s\n", buffer_in);



    close(sockfd);
    fprintf(stdout, "\nConnection closed\n\n");


}
