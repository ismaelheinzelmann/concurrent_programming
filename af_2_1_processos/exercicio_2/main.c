#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// for pid in $(ps -ef | awk '/program/ {print $2}'); do kill -9 $pid; done

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar

int main(int argc, char **argv)
{
    pid_t childs[2];
    pid_t fatherPid = getpid();

    for (size_t i = 0; i < 2; i++)
    {
        childs[i] = fork();

        if (childs[i] == 0)
        {
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            for (int i = 0; i < 3; i++)
            {
                pid_t grandChild = fork();

                if (grandChild == 0){
                    printf("Processo %d, filho de %d\n", getpid(), getppid());
                    sleep(5);
                    break;
                }
            }
            
            break;
        }
    }

    while (wait(NULL) >= 0)
    {
        ;
    }

    if (getpid() == fatherPid)
    {
        printf("Processo principal %d finalizado\n", fatherPid);
    }
    else
    {
        printf("Processo %d finalizado\n", getpid());
    }

    return 0;
}
