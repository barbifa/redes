#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>


int main(int argc , char *argv[])
{
    char *porto_servidor = argv[1];
    char *tam_buffer = argv[2];
    int server_fd,client_fd;
    int opt = 1;
    char buffer[1024];
    char bufferLeitura[atoi(tam_buffer)];
    FILE *fp;
    fp = fopen("teste.txt","r");

    struct sockaddr_in server,client;
    int addrlen = sizeof(server);

    printf("Iniciando Servidor\n");
    // Criando Ipv4  socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("Servidor socket criado com fd %d\n",server_fd);


    // definindo as propriedades do socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(porto_servidor));

    // Tratando erro caso a porta ja esteja em uso
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // fazendo o bind do socket com a porta
    if (bind(server_fd, (struct sockaddr *)&server,
                                 sizeof(server))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Esperando a conexao do cliente
    if(listen(server_fd, 1) == -1)
    {
        perror("Listen error:");
        return EXIT_FAILURE;
    }


    printf("Escutando a porta %s\n",porto_servidor);

    //coloca a conexao para dormir ate que o cliente tente estabelecer conexao tcp
    if ((client_fd = accept(server_fd, (struct sockaddr *)&server,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    strcpy(buffer, "Ola Cliente !\n\0");
    if (send(client_fd,buffer, strlen(buffer), 0))
    {
        printf("Cliente conectado... Esperando por arquivo\n");
    }

    if (fp == NULL)
   {
        printf("Erro na abertura do arquivo");
        close(server_fd);
        close(client_fd);
   }
   else
   {
         while(fscanf(fp,"%s",bufferLeitura) != EOF)
        {
            printf(&bufferLeitura)  ;
            send(client_fd , bufferLeitura ,atoi(tam_buffer), 0 );

        }

   }
   fclose(fp);
   close(server_fd);
   close(client_fd);

    return 0;

}
