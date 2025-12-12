#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LIBROS 10
#define MAX_TITULO 100
#define MAX_AUTOR 50
#define NOMBRE_ARCHIVO "biblioteca.txt" 

struct Libro 
{
	char titulo[MAX_TITULO];
	char autor[MAX_AUTOR];
	int anioDePubli;
};


void aniadirLibro (struct Libro libros[], int *cant);
void mostrarLibros (struct Libro libros[], int cant);
void buscarLibro(struct Libro libros[], int cant);
void guardarLibros(struct Libro libros[], int cant);
void cargarLibros(struct Libro libros[], int *cant);

int main()
{
	struct Libro libros[MAX_LIBROS];
	int cant = 0;
	int opcion;

	printf("Bienvenidos a la libreria\n");
	do 
	{
		printf("\nMenu:\n");
		printf("1. Añadir nuevo libro.\n");
		printf("2. Mostrar los libros disponibles.\n");
		printf("3. Buscar libro por Autor.\n");
		printf("4. Guardar los libros en un archivo.\n");
		printf("5. Cargar libros desde archivo.\n");
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
			guardarLibros(libros, cant);
			break;
		case 5:
			cargarLibros(libros, &cant);
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
	if (*cant >= MAX_LIBROS) 
	{
		printf("No se pueden añadir mas libros. Memoria llena (Max: %d).\n", MAX_LIBROS);
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
	char buscarAutor[MAX_AUTOR];
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

void guardarLibros(struct Libro libros[], int cant)
{
	FILE *fp;
	fp = fopen(NOMBRE_ARCHIVO, "w");
	
	if (fp == NULL)
	{
		printf("Error: No se pudo crear el archivo.\n");
		return;
	}
	
	for (int i = 0; i < cant; i++)
	{
		fprintf(fp, "%s %s %d\n", libros[i].titulo, libros[i].autor, libros[i].anioDePubli);
	}
	
	fclose(fp);
	printf("Archivo guardado exitosamente en '%s'.\n", NOMBRE_ARCHIVO);
}

void cargarLibros(struct Libro libros[], int *cant)
{
	FILE *fp;
	fp = fopen(NOMBRE_ARCHIVO, "r");
	
	if (fp == NULL)
	{
		printf("Error: No se encontro el archivo '%s'.\n", NOMBRE_ARCHIVO);
		return;
	}
	
	*cant = 0; 
	
	while (*cant < MAX_LIBROS && fscanf(fp, "%s %s %d", libros[*cant].titulo, libros[*cant].autor, &libros[*cant].anioDePubli) == 3)
	{
		(*cant)++;
	}
	
	fclose(fp);
	printf("Se han cargado %d libros desde el archivo.\n", *cant);
}
