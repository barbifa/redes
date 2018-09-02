#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc , char *argv[])
{
    // processa argumentos
    char *hostDoServidor = argv[1];
    char *porto_servidor = argv[2];
    char *nomeDoArquivo = argv[3];
    char *tamBuffer = argv[4];

    struct timeval start, end;
    gettimeofday(&start, NULL);



    gettimeofday(&end, NULL);
    printf("%d", end.tv_usec - start.tv_usec);
  // muda pra segundo, que eh tv_sec


    return 0;

}
