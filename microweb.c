// SistemaBinario.c: creacion y uso de un archivo de acceso aleatorio (binario)
// para manejar informaci�n de alumnos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// capacidad maxima del archivo N_MAX = numero de registros
#define N_MAX 100

typedef struct {
	int id;			//4  bit
	char nom[30];	//30 bit
	float cal;		//4  bits
} Alumno;

FILE* archivo;
long int N_actual=0;  // numero de registros reales
long int N_activos=0; // registros activos
long int N_borrados=0; // registros marcados como borrados


void inicializar();
void leer();
void sobre_escribir();
void borrar();
void agregar();
void listar();
void contar();
void compactar(FILE **fa);
long int sizeFile(char *nameFile);




int main() {
	
	long int sfile=sizeFile("datos.txt");
	
	archivo = fopen("datos.txt","r+b");//abre para lectura y escritura, binario. 
	if (archivo==NULL){
		printf("No se pudo abrir el archivo.");
		exit(1);
	}
	
	N_actual = sfile / sizeof(Alumno);  //calculo de numero de registros reales
	
	int opcion;
	while(1)
	{   opcion=-1;
		contar(); //muestra totales de registros
		printf("\nQue desea hacer?");
		printf("\n0-Inicializar");
		printf("\n1-Modificar");
		printf("\n2-Leer");
		printf("\n3-Borrar");
		printf("\n4-Agregar");
		printf("\n5-Listar");
		printf("\n6-Compactar");
		printf("\n9-Salir");
		printf("\n\nOpcion: ");
		scanf("%d",&opcion);
		fflush(stdin);
		switch(opcion)
		{
		case 0:
			inicializar();
			break;
		case 1:
			sobre_escribir(); //escribe en posicion indicada
			break;	
		case 2:
			leer();  //lee el registro indicado
			break;
		case 3:
			borrar(); //queda marcado 
			break;
		case 4:
			agregar(); //agrega al final
			break;	
		case 5:
			listar(); //todos los registros
			break;	
		case 6:
			compactar(&archivo); //elimina marcados
			break;			
		case 9:
			fclose(archivo);
			printf("\nSistema cerrado correctamente\n");
			exit(0);
		default:
			printf("Elija opcion!\n");
			break;
		}
		getchar();
		//system("Pause");
		//system("cls");
	}
	fclose(archivo);
	return 0;
}

//Inicializa todos los registros actuales como borrados
void inicializar()
{
	unsigned int sn;
	Alumno nulo={-1,"                             ",0.0};
    printf("Se marcaran como borrados todos los registros, proceder? (s/n): ");
	sn = getc(stdin);
	if(sn=='s'){
	 rewind(archivo);
	 fseek(archivo, 0 , SEEK_SET);
	 for(int j=0; j<N_actual; j++)
	  fwrite(&nulo,sizeof(Alumno),1,archivo);
	}
}

//Recupera y muestra datos de un registro
int muestra_datos(int x){
	Alumno nuevo;
	fseek(archivo,sizeof(Alumno)*x, SEEK_SET); //desde el inicio
	fread(&nuevo,sizeof(Alumno),1,archivo);
	if(nuevo.id==-1 )
		printf("El Registro esta borrado de forma logica\n");
	else {
	 printf("Id: %d\n",nuevo.id);
	 printf("nombre: %s\n",nuevo.nom);
	 printf("calificacion: %2.2f\n",nuevo.cal);	
	}
	return nuevo.id; //id o estado del registro, borrado=-1
}

//Lee datos del alumno y muestra en pantalla
void leer()
{
	if(N_actual<=0)
	{
		printf("Aun no existen reegistros\n");
		return;
	}
	int x;
	do{
		printf("Ingresa id de alumno entre 1 y %ld: ",N_actual);
		scanf("%d",&x);
	}while(x < 1 || x > N_actual);
	
	muestra_datos(x-1);
	getchar();
}

//Sobre-escribe en un registro los datos de un Alumno
//valida que exista y pregunta
void sobre_escribir()
{
	int edo=0;
	char sn;
	
	if(N_actual<=0)
	{
		printf("Aun no existen reegistros\n");
		return;
	}
	Alumno nuevo;
	int x;
	do{
		printf("Introduzca el ID de Alumno [1,%ld]: ",N_actual);
		scanf("%d",&x);
		fflush(stdin);
	}while(x < 1 || x > N_actual);
	
	
	edo=muestra_datos(x-1);
	
	if(edo==-1) printf("\nRegistro marcado como borrado!\n");
	printf("\nEscribir en este registro (s/n): ");
	sn = getc(stdin);
	fflush(stdin);
	
	if (sn=='s') {
	 printf("Introduzca el Nombre del Alumno: ");
	 gets(nuevo.nom);
	//fflush(stdin);
	 do{
		printf("Introduzca Calificacion: ");
		scanf("%f",&nuevo.cal);
		fflush(stdin);
	 }while(nuevo.cal < 0 && nuevo.cal > 10);
	 nuevo.id = x;
	 fseek(archivo,sizeof(Alumno)*(x-1),SEEK_SET);
	 fwrite(&nuevo,sizeof(Alumno),1,archivo);
	}
}

//Lee datos de alumno y agrega registero al final 
//aumenta la capacidad del archivo 
void agregar()
{	
Alumno nuevo;
nuevo.id = N_actual + 1;
printf("ID de Alumno %d\n", nuevo.id );
printf("Introduzca el Nombre del Alumno: ");
getchar();
gets(nuevo.nom);
//fflush(stdin);
do{
	printf("Introduzca Calificacion: ");
	scanf("%f",&nuevo.cal);
	fflush(stdin);
}while(nuevo.cal < 0 && nuevo.cal > 10);

fseek(archivo,0,SEEK_END);
fwrite(&nuevo,sizeof(Alumno),1,archivo);
N_actual++;
}

// Lista todos los registros de alumno activos
void listar(){
	Alumno temp;
	int suma=0;
	long int j=0;
	fseek(archivo,0,SEEK_SET); //ir al inicio
	printf("\n***  Listado de alumnos **\n");
	for(j=0; j<N_actual; j++    ){
		fread(&temp,sizeof(Alumno),1,archivo);
		if(temp.id!=-1) {
		 printf("Id: %d\n",temp.id);
		 printf("nombre: %s\n",temp.nom);
		 printf("calificacion: %2.2f\n-------\n",temp.cal);
		 suma+=temp.cal;
	    }	
	}
	printf("\n** Promedio: %2.2f \n\n", (suma/(float)N_activos));
}
// Contabiliza tipos de registros
void contar(){
	Alumno temp;
	long int j=0;
	N_borrados=0;
	N_activos=0;
	fseek(archivo,0,SEEK_SET); //ir al inicio
	for(j=0; j<N_actual; j++    ){
		fread(&temp,sizeof(Alumno),1,archivo);
		if(temp.id!=-1) N_activos++;
		if(temp.id==-1) N_borrados++;
	}
	printf("**** SISTEMA DE REGISTRO DE CALIFICACIONES DE ALUMNOS ***\n");
	printf("*\nTotal registros   reales: %d   activos: %d    borrados: %d  \n*\n",N_actual, N_activos, N_borrados);
}

// Marca como borrado (-1) el registro de alumno indicado por el ID
void borrar(){
	char sn;
	int edo;
	if(N_actual<=0)
	{
		printf("Aun no existen reegistros\n");
		return;
	}
	int x;
	do{
		printf("Introduzca el ID del Alumno [1,%ld]: ",N_actual);
		scanf("%d",&x);
		fflush(stdin);
	}while(x <= 0 || x > N_actual);
	x--; //ajusta indice 
	
	edo=muestra_datos(x);
	if(edo==-1) printf("\nRegistro ya esta marcado como borrado!\n");
	else {
	 printf("\nBorrar este registro (s/n): ");
	 sn = getc(stdin);
	 fflush(stdin);
	 fseek(archivo,sizeof(Alumno)*x,SEEK_SET);
	 Alumno nulo = {-1,"                             ",0.0}; //-1 indica borrado
	 fwrite(&nulo,sizeof(Alumno),1,archivo);
	}
}

//Copia registros activos en otro archivo y luego renombra
//para hacerlo el archivo del sistema, elimina borrados
void compactar(FILE **fa){
FILE *ftemp;
Alumno dato;
int rb=0, cuenta=0;
N_actual=0;
ftemp = fopen("nuevo.tmp", "wb");
rewind(*fa);
while(fread(&dato, sizeof(Alumno), 1, *fa)){
   cuenta++;
   if(dato.id==-1) rb++;
   else //(dato.id != -1)
   {
	dato.id=N_actual+1; 
    fwrite(&dato, sizeof(Alumno), 1, ftemp);
	N_actual++;
   }
  }
fclose(ftemp);
fclose(*fa);
remove("datos.bak");
rename("datos.txt", "datos.bak");
rename("nuevo.tmp", "datos.txt");
*fa = fopen("datos.txt", "r+b");
printf("\n%d de %d registros liberados.\n", rb, cuenta);

}

// Calcula y regresa el tama�o de un archivo
long int sizeFile(char *nameFile){
	FILE * pFile;
	long int size=0;
	pFile = fopen ( nameFile, "rb" );  //abre en modo binario - bytes, debe existir
	if (pFile==NULL) 
	{
		printf ("Error al intentar abrir el archivo %s, se creara vacio", nameFile);
		pFile = fopen ( nameFile, "wb" ); 
	}
	
	else{
		fseek ( pFile , 0, SEEK_END );
		size=ftell(pFile);
		fclose ( pFile );
	}
	return size;
}
