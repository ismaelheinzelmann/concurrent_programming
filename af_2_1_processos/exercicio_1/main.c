#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//       (pai)
//         |
//    +----+----+
//    |         |
// filho_1   filho_2

// ~~~ printfs  ~~~
// pai (ao criar filho): "Processo pai criou %d\n"
//    pai (ao terminar): "Processo pai finalizado!\n"
//  filhos (ao iniciar): "Processo filho %d criado\n"

// Obs:
// - pai deve esperar pelos filhos antes de terminar!

int main(int argc, char **argv)
{
    pid_t filho1, filho2;
    filho1 = fork();
    if (filho1 != 0){
        filho2 = fork();
    }
    

    if (filho1 >= 0 || filho2 >= 0)
    {
        if (filho1 == 0 || filho2 == 0)
        {
            printf("Processo filho %d criado\n", getpid());
            fflush(stdin);
        }
        else
        {
            printf("Processo pai criou %d\n", filho1);
            fflush(stdin);
            printf("Processo pai criou %d\n", filho2);
            fflush(stdin);
        }
    }
    else
    {
        printf("Erro ao criar processo\n");
        fflush(stdin);
    }

    while (wait(NULL) >= 0)
        ;
    if (filho1 != 0 && filho2 != 0){
        printf("Processo pai finalizado!\n");
        fflush(stdin);
    }
    fflush(stdin);
    return 0;
}
