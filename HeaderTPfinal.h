#ifndef HEADERTPFINAL_H_INCLUDED
#define HEADERTPFINAL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#define DIM 50
#define DIMARRAY 200

///ESTRUCTURA DE CANCION
typedef struct
{
    int idCancion;
    char titulo[30];
    char artista[20];
    int duracion;
    char album[20];
    int anio;
    char genero[20];
    char comentario[100];
    int eliminado; // 1= eliminado - 0= no eliminado
} stCancion;


///ESTRUCTURA DE USUARIO
typedef struct
{
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int eliminado; // 1= eliminado - 0= no eliminado
} stUsuario;

///LISTA DE CANCIONES
typedef struct nodoListaCancion
{
    stCancion c;
    struct nodoListaCancion * sig;
} nodoListaCancion;

///ARBOL DE CANCIONES
typedef struct nodoArbolCancion
{
    stCancion c;
    struct nodoArbolCancion* izq;
    struct nodoArbolCancion* der;
} nodoArbolCancion;

///ARREGLO DE USUARIOS
typedef struct
{
    stUsuario usr;
    nodoListaCancion* listaCanciones;
} stCelda;

///ESTRUCTURA DE CANCIONES ESCUCHADAS POR CADA USUARIO
typedef struct
{
    int idPlaylist;
    int idUsuario;
    int idCancion;
} stPlaylist;

typedef struct
{
    char nombreUsuario[30];
    char pass[20];
} stAdministrador;

///PROTOTIPADOS
int main();
void cargarArchivoCanciones();
HWND WINAPI GetConsoleWindowNT(void);
void dibujarCuadro(int, int, int, int);
void gotoxy(int, int);
int registroUsuario();
int buscarUltimoIdUsuario();
int buscarUsuario(char[]);
int logeoUsuario(stCelda[], int);
int verificarUsuarioClave (char[20], stUsuario);
int recuperarIdUsuario (stCelda[], int, char[30]);
int pasarUsuarioArray (stCelda[], int);
void userLogeado (stCelda[], int, int, nodoListaCancion*, nodoArbolCancion*, int);
int menuPrincipal();
int buscarUserID (stCelda[], int, int);
void mostrarUser (stUsuario);
nodoListaCancion* inicLista();
nodoListaCancion* crearListaCanciones (nodoListaCancion*);
nodoListaCancion* crearNodoCancion (stCancion);
nodoListaCancion* agregarPrincipio(nodoListaCancion*, nodoListaCancion*);
nodoListaCancion* agregarOrdenado(nodoListaCancion*, nodoListaCancion*);
nodoListaCancion* agregarAlFinal (nodoListaCancion*, nodoListaCancion*);
nodoListaCancion* buscarUltimo(nodoListaCancion*);
void mostrarLista(nodoListaCancion*);
void mostrarNodo(nodoListaCancion*);
void escucharCancion (stCelda[], nodoListaCancion*, nodoArbolCancion*, int);
void agregarCancionADL (stCelda[], stCancion, int);
void persistirPlaylist (int, int);
int buscarUltimoIdPlaylist();
nodoArbolCancion* buscarCancionArbol (int, nodoArbolCancion*);
nodoArbolCancion* inicArbol();
nodoArbolCancion* crearNodoArbol(stCancion);
nodoArbolCancion* insertar(nodoArbolCancion*, stCancion);
nodoArbolCancion* pasarArchivoArbol(nodoArbolCancion*);
void inorder(nodoArbolCancion*);
void postorder(nodoArbolCancion*);
void preorder(nodoArbolCancion*);
void despersistirArchPlaylist (stCelda[], int, nodoArbolCancion*);
void registroAdmin();
int buscarUsuarioAdmin(char[]);
void logeoAdmin();
int verificarUsuarioClaveAdmin (char[20], stAdministrador);
void adminLogeado(stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
void administrarUsuarios (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
void administrarCanciones (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
void registroUsuarioDesdeAdmin(stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
void actualizarArrayUsers (stCelda[], int*, stUsuario);
void bajaUsuario (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
nodoListaCancion* borrarListaCompleta (nodoListaCancion*);
void modificarUsuario (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
int verificarExistenciaUsuario (int);
void modificarNombreUsuario(stCelda[], int*, stUsuario, int);
void modificarPassword(stCelda[], int*, stUsuario, int);
void modificarAnio(stCelda[], int*, stUsuario, int);
void modificarGenero(stCelda[], int*, stUsuario, int);
void modificarPais(stCelda[], int*, stUsuario, int);
void consultaUsuario (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
void deseaSeguir (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
void listadoUsuarios (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
int buscarPosUsuario (stCelda[], int*, int);
void ordenarArray (stUsuario[], int);
int buscarPosMenor (stUsuario[], int, int);
void mostrarUserAdministrador (stUsuario);
void altaCancion (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
int buscarUltimoIdCancion();
void persistirCancion (stCancion);
void bajaCancion (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
void bajaCancionPlaylist (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*, int);
void mostrarListaAdmin(nodoListaCancion*);
void mostrarNodoAdmin(nodoListaCancion*);
void modificarCancion (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
int verificarExistenciaCancion (int);
int verificarExistenciaCancionArbol(nodoArbolCancion*, int);
void modificarTitulo(nodoListaCancion*, stCancion, int);
void modificarArchPlaylist (int, stCancion);
nodoListaCancion* modificarListaCanciones (nodoListaCancion*, stCancion);
void modificarArtista(nodoListaCancion*, stCancion, int);
void modificarDuracion(nodoListaCancion*, stCancion, int);
void modificarAlbum(nodoListaCancion*, stCancion, int);
void modificarAnioLanzamiento(nodoListaCancion*, stCancion, int);
void modificarGeneroCancion(nodoListaCancion*, stCancion, int);
void modificarComentario(nodoListaCancion*, stCancion, int);
void consultaCanciones (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
nodoListaCancion* buscarNodo(nodoListaCancion*, int);
void mostrarPorTitulo ();
void ordenarPorTitulo (stCancion[], int);
int buscarPosicionMenor (stCancion[], int, int);
void listadoCanciones (stCelda[], int*, nodoArbolCancion*, nodoListaCancion*);
int crearArregloCanciones (stCancion[], int);
void mostrarArregloCanciones (stCancion, int);
void ordenarPorGenero (stCancion[], int);
void mostrarPorGenero (stCancion[], int);
void insertarDato (stCancion[], int, stCancion);
int buscarGenero(int, char[]);
void mostrarCancionPorGenero(char[]);


#endif // HEADERTPFINAL_H_INCLUDED
