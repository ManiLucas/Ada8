/* Programa: muestar un mensaje o frase cada x segundos*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//arreglo con frases

int main( int argc, char* argv[] )
{
    char *palabra[] = {"Recuerda que si puedes imaginarlo, puedes crearlo", 
                       "Lo unico imposible es aquello que no intentas",
                       "Cuando miras al abismo el abismo te regresa la mirada",
                       "La peor lucha es la que no se hace ",
                       "No hay noche, por larga que sea, que no encuentre el día ",
                       "Aquellos que no quieren imitar nada no producirán nada",
                       "Nunca moriría por mis creencias, porque podría estar equivocado",
                       "No os toméis la vida demasiado en serio; de todas maneras, no saldréis vivos de esta ",
                       };
    
    int SLEEPTIME = 5;
   	int cont=0;
    int i=0, tam;
    tam = sizeof(palabra)/sizeof(char *);

   for( ; ; ) {
        fprintf(stderr,"%s", "\007");
		cont++;
		fprintf(stderr,"%s\n", palabra[i]);
        //printf("%d\n",i);
        i++;
        if(i==tam){
            i = tam%i;
            //printf("fin\n");
        }
        sleep(SLEEPTIME);
    }  
      
   
  return 0; 
}