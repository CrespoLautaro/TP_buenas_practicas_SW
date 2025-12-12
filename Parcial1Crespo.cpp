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
	int anioDePublicacion;
};

void agregarLibro(struct Libro libros[], int *ptrCantidadLibros);
void mostrarLibros(struct Libro libros[], int cantidadLibros);
void buscarLibro(struct Libro libros[], int cantidadLibros);
void guardarLibros(struct Libro libros[], int cantidadLibros);
void cargarLibros(struct Libro libros[], int *ptrCantidadLibros);

int main()
{
	struct Libro coleccionLibros[MAX_LIBROS];
	int cantidadLibros = 0;
	int opcionMenu;
	
	do 
	{
		printf("\n========================================\n");
		printf("      SISTEMA DE GESTION DE LIBROS      \n");
		printf("========================================\n");
		printf("1. Agregar nuevo libro\n");
		printf("2. Mostrar todos los libros\n");
		printf("3. Buscar libro por Autor\n");
		printf("4. Guardar coleccion en archivo\n");
		printf("5. Cargar coleccion desde archivo\n");
		printf("0. Salir del sistema\n");
		printf("========================================\n");
		printf("Ingrese una opcion: ");
		scanf("%d", &opcionMenu);
		
		switch(opcionMenu) 
		{
		case 1:
			agregarLibro(coleccionLibros, &cantidadLibros);
			break;
		case 2:
			mostrarLibros(coleccionLibros, cantidadLibros);
			break;
		case 3:
			buscarLibro(coleccionLibros, cantidadLibros);
			break;
		case 4:
			guardarLibros(coleccionLibros, cantidadLibros);
			break;
		case 5:
			cargarLibros(coleccionLibros, &cantidadLibros);
			break;
		case 0:
			printf("\nFinalizando el programa...\n");
			break;
		default:
			printf("\nError: Opcion invalida. Intente nuevamente.\n");
		}
	} 
	while(opcionMenu != 0);
	
	return 0;
}	

void agregarLibro(struct Libro libros[], int *ptrCantidadLibros) 
{
	if (*ptrCantidadLibros >= MAX_LIBROS) 
	{
		printf("\nError: La biblioteca esta llena.\n", MAX_LIBROS);
		return;
	}
	
	printf("\n--- NUEVO LIBRO ---\n");
	
	printf("Ingrese el titulo del libro: ");
	scanf("%s", libros[*ptrCantidadLibros].titulo);
	
	printf("Ingrese el autor del libro: ");
	scanf("%s", libros[*ptrCantidadLibros].autor);
	
	printf("Ingrese el año de publicacion: ");
	scanf("%d", &libros[*ptrCantidadLibros].anioDePublicacion);
	
	(*ptrCantidadLibros)++;
	printf("\n El libro se ha registrado exitosamente.\n");
}

void mostrarLibros(struct Libro libros[], int cantidadLibros) 
{
	if (cantidadLibros == 0) 
	{
		printf("\nNo hay libros registrados en el sistema.\n");
		return;
	}	
	
	printf("\n--- LISTADO DE LIBROS ---\n");
	printf("%-4s | %-30s | %-20s | %s\n", "ID", "TITULO", "AUTOR", "AÑO");
	printf("------------------------------------------------------------------\n");
	
	for (int i = 0; i < cantidadLibros; i++) 
	{
		printf("%-4d | %-30s | %-20s | %d\n", 
			   i + 1, 
			   libros[i].titulo, 
			   libros[i].autor, 
			   libros[i].anioDePublicacion);
	}
	printf("------------------------------------------------------------------\n");
}

void buscarLibro(struct Libro libros[], int cantidadLibros) 
{
	char autorBusqueda[MAX_AUTOR];
	int seEncontro = 0;	
	
	printf("\n--- BUSQUEDA POR AUTOR ---\n");
	printf("Ingrese el nombre del autor: ");
	scanf("%s", autorBusqueda);
	
	printf("\nResultados de la busqueda:\n");
	for (int i = 0; i < cantidadLibros; i++) 
	{
		if (strcmp(libros[i].autor, autorBusqueda) == 0) 
		{
			printf("* Titulo: %-25s | Año: %d\n", libros[i].titulo, libros[i].anioDePublicacion);
			seEncontro = 1;
		}
	}
	
	if (!seEncontro) 
	{
		printf("No se encontraron libros de ese autor.\n");
	}
}

void guardarLibros(struct Libro libros[], int cantidadLibros)
{
	FILE *archivo; // Cambio: 'fp' por 'archivo'
	archivo = fopen(NOMBRE_ARCHIVO, "w");
	
	if (archivo == NULL)
	{
		printf("\nError: No se pudo crear o escribir en el archivo.\n");
		return;
	}
	
	for (int i = 0; i < cantidadLibros; i++)
	{
		fprintf(archivo, "%s %s %d\n", libros[i].titulo, libros[i].autor, libros[i].anioDePublicacion);
	}
	
	fclose(archivo);
	printf("\nBase de datos guardada correctamente en '%s'.\n", NOMBRE_ARCHIVO);
}

void cargarLibros(struct Libro libros[], int *ptrCantidadLibros)
{
	FILE *archivo;
	archivo = fopen(NOMBRE_ARCHIVO, "r");
	
	if (archivo == NULL)
	{
		printf("\nAviso: No existe base de datos previa o hubo error al abrir '%s'.\n", NOMBRE_ARCHIVO);
		return;
	}
	
	*ptrCantidadLibros = 0; 
	
	while (*ptrCantidadLibros < MAX_LIBROS && 
		   fscanf(archivo, "%s %s %d", 
				  libros[*ptrCantidadLibros].titulo, 
				  libros[*ptrCantidadLibros].autor, 
				  &libros[*ptrCantidadLibros].anioDePublicacion) == 3)
	{
		(*ptrCantidadLibros)++;
	}
	
	fclose(archivo);
	printf("\nSe han recuperado %d libros del archivo.\n", *ptrCantidadLibros);
}
