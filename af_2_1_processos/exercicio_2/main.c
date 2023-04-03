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

int child()
{
    pid_t grandChild1, grandChild2, grandChild3;
    grandChild1 = fork();
    if (grandChild1 != 0)
    {
        grandChild2 = fork();
        if (grandChild2 != 0)
        {
            grandChild3 = fork();
        }
    }

    if (grandChild1 >= 0 && grandChild2 >= 0 && grandChild3 >= 0)
    {
        if (grandChild1 == 0 || grandChild2 == 0 || grandChild3 == 0)
        {
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            sleep(5);
            printf("Processo %d finalizado\n", getpid());
            return 0;
        }
        else
        {
            while (wait(NULL) >= 0)
            {
                ;
            }
        }
    }
    else
    {
        printf("Erro ao criar processo.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    pid_t child1, child2;
    child1 = fork();
    if (child1 != 0)
    {
        child2 = fork();
    }

    if (child1 >= 0 || child2 >= 0)
    {

        if (child1 == 0 || child2 == 0)
        {
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            int childProcess = child();
            if (childProcess != 0)
            {
                return childProcess;
            }
            else if (childProcess > 0)
            {
                printf("Processo %d finalizado\n", getpid());
            }
            return 0;
        }
        else
        {
            while (wait(NULL) >= 0)
            {
                ;
            }
        }
    }
    else
    {
        printf("Erro ao criar processos.\n");
        return 1;
    }
    printf("Processo principal %d finalizado\n", getpid());
    return 0;
}
