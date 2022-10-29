/* Programa: muestar un mensaje o frase cada x segundos*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//arreglo con frases
struct frases{
    char frase[100];
};

int main( int argc, char* argv[] )
{
    int SLEEPTIME = 10;
   	int cont=0;

   for( ; ; ) {
        fprintf(stderr,"%s", "\007");
		cont++;
		fprintf(stderr,"Monitoreando el correo de linux %d\n",cont);

      }  
      sleep(SLEEPTIME);
   
  return 0; 
}