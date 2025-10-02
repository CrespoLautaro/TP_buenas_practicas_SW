#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Libro 
{
	char titulo[100];
	char autor[50];
	int anioDePubli;
};

void aniadirLibro (struct Libro libros[], int *cant);
void mostrarLibros (struct Libro libros[], int cant);
void buscarLibro(struct Libro libros[], int cant);
//void guardarLibro(struct Libro libros[], int cant);

int main()
{
	struct Libro libros[10];
	int cant=0;
	int opcion;
	printf("Bienvenidos a la libreria\n");
	do 
	{
		printf("\nMenu:\n");
		printf("1. Añadir nuevo libro.\n");
		printf("2. Mostrar los libros disponibles.\n");
		printf("3. Buscar libro por Autor.\n");
        printf("4. Guardar los libros en un archivo.\n");
		printf("0. Salir\n");
		printf("Ingrese su opcion: ");
		scanf("%d", &opcion);
		
		switch(opcion) 
		{
		case 1:
			aniadirLibro(libros, &cant);
			break;
		case 2:
			mostrarLibros(libros, cant);
			break;
		case 3:
			buscarLibro(libros, cant);
			break;
		case 4:
			//guardarLibros(libros, cant);
			break;
		case 0:
			printf("Saliendo del programa...\n");
			break;
		default:
			printf("Opcion invalida. Intente nuevamente.\n");
		}
	} 
	while(opcion != 0);
	return 0;
}	

void aniadirLibro(struct Libro libros[], int *cant) 
{
	if (*cant >= 10) 
	{
		printf("No se pueden añadir mas libros.\n");
		return;
	}
	printf("\n--- Añadir nuevo libros ---\n");
	printf("Ingrese su titulo: ");
	scanf("%s", libros[*cant].titulo);
	printf("Ingrese su Autor: ");
	scanf("%s", libros[*cant].autor);
	printf("Ingrese su año de publicacion: ");
	scanf("%d", &libros[*cant].anioDePubli);
	
	(*cant)++;
	printf("Libro añadido con exito.\n");
}

void mostrarLibros(struct Libro libros[], int cant) 
{
	if (cant == 0) 
	{
		printf("No hay libros cargados.\n");
		return;
	}	
	printf("\n--- Lista de libros ---\n");
	for (int i = 0; i < cant; i++) 
	{
		printf("\nLibro n° %d:\n", i + 1);
		printf("Titulo: %s\n", libros[i].titulo);
		printf("Autor: %s\n", libros[i].autor);
		printf("Año de Publicacion: %d\n", libros[i].anioDePubli);
	}
}

void buscarLibro(struct Libro libros[], int cant) 
{
	char buscarAutor[50];
	int encontrado = 0;	
	printf("\nIngrese el autor a buscar: ");
	scanf("%s", buscarAutor);
	for (int i = 0; i < cant; i++) 
	{
		if (strcmp(libros[i].autor, buscarAutor) == 0) 
		{
			printf("\nLibro encontrado n°%d:\n", i+1);
			printf("Titulo: %s\n", libros[i].titulo);
			printf("Autor: %s\n", libros[i].autor);
			printf("Año de publicacion: %d\n", libros[i].anioDePubli);
			encontrado = 1;
		}
	}
	
	if (!encontrado) 
	{
		printf("Libro no encontrado.\n");
	}
}

/*void guardarLibro(struct Libro libros[], int cant);
{
 FILE *fp;
 
	
}
*/
