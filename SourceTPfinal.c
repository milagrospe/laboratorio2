#include "HeaderTPfinal.h"

///CAMBIAR TAMAÑO CONSOLA
HWND WINAPI GetConsoleWindowNT(void)
{
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    GetConsoleWindowT GetConsoleWindow;
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib,TEXT("GetConsoleWindow"));
    if(GetConsoleWindow == NULL)
    {
        return NULL;
    }
    return GetConsoleWindow();
}

///DIBUJAR CUADRO
void dibujarCuadro(int x1,int y1,int x2,int y2)
{
    int i;
    for (i = x1; i<x2; i++)
    {
        gotoxy(i,y1);
        printf("\304"); //linea horizontal superior
        gotoxy(i,y2);
        printf("\304"); //linea horizontal inferior
    }
    for (i = y1; i < y2; i++)
    {
        gotoxy(x1,i);
        printf("\263"); //linea vertical izquierda
        gotoxy(x2,i);
        printf("\263"); //linea vertical derecha
    }
    gotoxy(x1,y1);
    printf("\332");
    gotoxy(x1,y2);
    printf("\300");
    gotoxy(x2,y1);
    printf("\277");
    gotoxy(x2,y2);
    printf("\331");
}

///FUNCION GOTOXY
void gotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon,dwPos);
}

///REGISTRO USUARIO
int registroUsuario()
{
    int acceso=0;
    int caracteres=0;
    int requisitosClave=0;
    int caracter = 0;
    int posArreglo=0;
    int i=0;
    stUsuario usuario;
    FILE *fp = fopen("Usuarios.bin", "ab");
    i = buscarUltimoIdUsuario();
    if (fp != NULL)
    {
        usuario.idUsuario = i + 1;
        dibujarCuadro(1,1,74,3);
        gotoxy(20,0);
        printf("\n\n\t\t\tVamos a crear tu usuario \n");
        do
        {
            printf("\n\tIngrese nombre de usuario.......................: ");
            fflush(stdin);
            gets(usuario.nombreUsuario);
            acceso = buscarUsuario(usuario.nombreUsuario);
            if (acceso == 1)
            {
                printf("\n\tEse usuario ya existe, ingrese otro nombre de usuario\n");
                fflush(stdin);
            }
        }
        while (acceso == 1);
        printf("\n\tRequisitos: entre 4 y 12 caracteres\n");
        printf("\n\tNo se permiten caracteres especiales\n");
        printf("\n\tIngrese password......................: ");
        do
        {
            fflush(stdin);
            //gets(usuario.pass);
            //caracteres = strlen(usuario.pass);
            while(caracter = getch())
            {
                if(caracter == 13)
                {
                    usuario.pass[posArreglo] = '\0';
                    break;
                }
                else if (caracter == 8)
                {
                    if(posArreglo>0)
                    {
                        posArreglo--;
                        printf("\b \b");
                    }
                }
                else
                {
                    if(posArreglo<DIM)
                    {
                        printf("*");
                        usuario.pass[posArreglo] = caracter;
                        posArreglo++;
                    }
                }
            }
            caracteres = strlen(usuario.pass);
            if ((caracteres >= 4) && (caracteres <= 12))
            {
                requisitosClave = 0 ;
            }
            else
            {
                requisitosClave = 1 ;
                printf ("\n\n\tLa clave no cumple con los requisitos\n\tIngrese una clave nuevamente\n");
                printf("\t");
            }
            posArreglo = 0;
        }
        while (requisitosClave == 1);
        printf("\n\n\tIngrese su anio de nacimiento...........: ");
        scanf("%d", &usuario.anioNacimiento);
        printf("\n\tIngrese genero (m: masculino - f: femenino - o: otro)........: ");
        fflush(stdin);
        scanf("%c",&usuario.genero);
        while((usuario.genero != 'm') && (usuario.genero != 'f') && (usuario.genero != 'o'))
        {
            printf("\tGenero erroneo. Intente nuvamente. (m: masculino - f: femenino - o: otro): ");
            fflush(stdin);
            scanf("%c", &usuario.genero);
        }
        printf("\n\tIngrese pais...............: ");
        fflush(stdin);
        gets(usuario.pais);
        usuario.eliminado=0;
        printf("\n\tUsuario creado exitosamente!\n\n");
        printf("\t");
        system("pause");
        system("cls");
        fwrite(&usuario, sizeof(stUsuario),1,fp);
        fclose(fp);
    }
    system("cls");
    printf("\n\t\t\t======================\n");
    printf("\n\t\t\tBienvenido al sistema!\n");
    printf("\n\t\t\t======================\n\n");
    printf("\t    ");
    system("pause");
    return usuario.idUsuario;
}

///BUSCAR ULIMO ID USUARIO
int buscarUltimoIdUsuario()
{
    stUsuario U;
    int id = 0;
    FILE *fp = fopen("Usuarios.bin", "rb");
    if(fp != NULL)
    {
        fseek(fp, (-1) * sizeof(stUsuario), SEEK_END);
        if(fread(&U,sizeof(stUsuario),1,fp) > 0)
        {
            id = U.idUsuario;
        }
        fclose(fp);
    }
    return id;
}

///BUSCAR USUARIO
int buscarUsuario(char nombre[])
{
    stUsuario U;
    int encontrar = 0 ;
    FILE *fp = fopen ("Usuarios.bin","rb");
    if (fp != NULL)
    {
        while ((fread(&U,sizeof(stUsuario),1,fp)>0) && (encontrar == 0))
        {
            if (strcmp(U.nombreUsuario, nombre) == 0)
            {
                encontrar = 1;
            }
        }
        fclose (fp);
    }
    return encontrar;
}

///LOGEO USUARIOS
int logeoUsuario(stCelda arrayUsers[], int validos)
{
    stUsuario usuario;
    int intento = 0;
    int ingresa = 0;
    char caracter;
    int idUser=0;
    int i=0;
    int posUsuario=0;
    FILE* fp = fopen("Usuarios.bin", "rb");
    if (fp == NULL)
    {
        printf("\n\t    No hay usuarios registrados, debe registrarse\n\n");
        printf("\t    ");
        system("pause");
        main();
    }
    do
    {
        printf("\n\t    Ingrese su usuario:........................");
        fflush(stdin);
        gets(usuario.nombreUsuario);
        printf("\n\t    Ingrese su contrasenia:....................");
        while(caracter = getch())
        {
            if(caracter == 13)
            {
                usuario.pass[i] = '\0';
                break;
            }
            else if (caracter == 8)
            {
                if(i>0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                if(i<DIM)
                {
                    printf("*");
                    usuario.pass[i] = caracter;
                    i++;
                }
            }
        }
        ingresa = verificarUsuarioClave(usuario.pass, usuario);
        i=0;
        intento++;
    }
    while((ingresa == 0) && (intento < 3));
    idUser = recuperarIdUsuario(arrayUsers, validos, usuario.nombreUsuario);
    posUsuario = buscarPosUsuario(arrayUsers, &validos, idUser);
    if (arrayUsers[posUsuario].usr.eliminado == 1)
    {
        printf("\n\n\t    Este usuario se encuentra dado de baja del sistema\n");
        exit(0);
    }
    if(ingresa == 1)
    {
        system("cls");
        printf("\n\t\t\t======================\n");
        printf("\n\t\t\tBienvenido al sistema!\n");
        printf("\n\t\t\t======================\n\n");
        printf("\t    ");
        system("pause");
    }
    if ((ingresa == 0) && (intento == 3))
    {
        printf("\n\tUsted ha sobrepasado el numero maximo de intentos permitidos\n");
        exit(0);
    }
    return idUser;
}

///VERIFICAR USUARIO Y CLAVE DE USUARIOS
int verificarUsuarioClave (char pass[20], stUsuario user)
{
    stUsuario usuarioGuardado;
    FILE *fp = fopen("Usuarios.bin", "rb");
    int ingresa = 0;
    if (fp != NULL)
    {
        while ((fread(&usuarioGuardado,sizeof(stUsuario),1,fp)>0) && (ingresa == 0))
        {
            if((strcmp(usuarioGuardado.nombreUsuario, user.nombreUsuario) == 0) && (strcmp(usuarioGuardado.pass, user.pass) == 0))
            {
                ingresa = 1;
            }
            else
            {
                ingresa = 0;
            }
        }
        if (ingresa == 0)
        {
            printf("\n\n\t    Usuario o clave son incorrectas\n\n");
        }
        fclose(fp);
    }
    return ingresa;
}

///RECUPERAR ID USUARIO A PARTIR DEL NOMBRE DE USUARIO
int recuperarIdUsuario (stCelda arrayUsers[], int validos, char nombreUsuario[30])
{
    int i=0;
    while (strcmp(arrayUsers[i].usr.nombreUsuario, nombreUsuario) != 0)
    {
        i++;
    }
    return arrayUsers[i].usr.idUsuario;
}

///PASAR USUARIOS DE ARCHIVO A ARREGLO
int pasarUsuarioArray (stCelda arrayUsers[], int validos)
{
    stUsuario user;
    int i=0;
    FILE* fp = fopen("Usuarios.bin", "rb");
    if (fp!=NULL)
    {
        while ((fread(&user, sizeof(stUsuario), 1, fp)>0) && (validos<DIMARRAY))
        {
            arrayUsers[i].usr = user;
            validos++;
            i++;
        }
        fclose(fp);
    }
    return validos;
}

///USUARIO LOGEADO
void userLogeado (stCelda arrayUsers[], int validos, int idUsuarioLogeado, nodoListaCancion* listaCanciones, nodoArbolCancion* arbolCanciones, int posUserLogeado)
{
    int opUserLog=0;
    char seguir;
    opUserLog = menuPrincipal();
    if (opUserLog == 1)
    {
        posUserLogeado=buscarUserID(arrayUsers, validos, idUsuarioLogeado);
        system("cls");
        mostrarUser(arrayUsers[posUserLogeado].usr);
        printf("\n\tDesea volver al menu principal? s/n-->");
        fflush(stdin);
        scanf("%c", &seguir);
        if (seguir == 's')
        {
            userLogeado(arrayUsers, validos, idUsuarioLogeado, listaCanciones, arbolCanciones, posUserLogeado);
        }
    }
    else
    {
        if (opUserLog == 2)
        {
            posUserLogeado=buscarUserID(arrayUsers, validos, idUsuarioLogeado);
            system("cls");
            mostrarLista(arrayUsers[posUserLogeado].listaCanciones);
            printf("\n\tDesea volver al menu principal? s/n-->");
            fflush(stdin);
            scanf("%c", &seguir);
            if (seguir == 's')
            {
                userLogeado(arrayUsers, validos, idUsuarioLogeado, listaCanciones, arbolCanciones, posUserLogeado);
            }
        }
        else
        {
            if (opUserLog == 3)
            {
                escucharCancion(arrayUsers, listaCanciones, arbolCanciones, idUsuarioLogeado);
                printf("\n\tDesea volver al menu principal? s/n-->");
                fflush(stdin);
                scanf("%c", &seguir);
                if (seguir == 's')
                {
                    userLogeado(arrayUsers, validos, idUsuarioLogeado, listaCanciones, arbolCanciones, posUserLogeado);
                }
            }
            else
            {
                if (opUserLog ==4)
                {
                    int encontrarKpop = 0;
                    int encontrarMetal = 0;
                    int encontrarPop = 0;
                    int encontrarReggaeton = 0;
                    int encontrarRock = 0;
                    encontrarKpop = buscarGenero(idUsuarioLogeado, "Kpop");
                    encontrarMetal = buscarGenero(idUsuarioLogeado, "Metal");
                    encontrarPop = buscarGenero(idUsuarioLogeado, "Pop");
                    encontrarReggaeton = buscarGenero(idUsuarioLogeado, "Reggaeton");
                    encontrarRock = buscarGenero(idUsuarioLogeado, "Rock");
                    system("cls");
                    printf("\t\t\t>>>RECOMENDACIONES PARA VOS<<<\n");
                    if(encontrarKpop == 1)
                    {
                        mostrarCancionPorGenero("Kpop");
                    }
                    if(encontrarMetal == 1)
                    {
                        mostrarCancionPorGenero("Metal");
                    }
                    if(encontrarPop == 1)
                    {
                        mostrarCancionPorGenero("Pop");
                    }
                    if(encontrarReggaeton == 1)
                    {
                        mostrarCancionPorGenero("Reggaeton");
                    }
                    if(encontrarRock == 1)
                    {
                        mostrarCancionPorGenero("Rock");
                    }
                    printf("\n\tDesea volver al menu principal? s/n-->");
                    fflush(stdin);
                    scanf("%c", &seguir);
                    if (seguir == 's')
                    {
                        userLogeado(arrayUsers, validos, idUsuarioLogeado, listaCanciones, arbolCanciones, posUserLogeado);
                    }
                }
            }
        }
    }
}

///MENU PRINCIPAL
int menuPrincipal()
{
    int opUser;
    system("cls");
    printf("\n\n\t    ===================================================\n");
    printf("\n\n\t    --- 1.Ver perfil-----------------------------------\n");
    printf("\n\n\t    --- 2.Mostrar Playlist-----------------------------\n");
    printf("\n\n\t    --- 3.Escuchar cancion-----------------------------\n");
    printf("\n\n\t    --- 4.Canciones recomendadas------------------------\n");
    printf("\n\n\t    ===================================================> ");
    scanf("%i", &opUser);
    return opUser;
}

///BUSCAR POSICION DE UN USUARIO EN ARREGLO POR ID
int buscarUserID (stCelda arrayUsuarios[], int validos, int idUserLogeado)
{
    int i=0;
    while ((i<validos) && (arrayUsuarios[i].usr.idUsuario != idUserLogeado))
    {
        i++;
    }
    return i;
}

///MOSTRAR USER
void mostrarUser (stUsuario user)
{
    printf("\n\n\t===================================================\n");
    printf("\tID usuario: %i\n", user.idUsuario);
    printf("\tNombre: %s\n", user.nombreUsuario);
    printf("\tAnio de nacimiento: %i\n", user.anioNacimiento);
    printf("\tGenero: %c\n", user.genero);
    printf("\tPais: %s\n", user.pais);
    printf("\t===================================================\n");
}

///INICIALIZAR LISTA
nodoListaCancion* inicLista()
{
    return NULL;
}

///CREAR LISTA DE CANCIONES
nodoListaCancion* crearListaCanciones (nodoListaCancion* listaCanciones)
{
    stCancion c;
    nodoListaCancion *nuevoNodo;
    FILE* fp = fopen("Canciones.bin", "rb");
    if (fp != NULL)
    {
        while(fread(&c, sizeof(stCancion), 1, fp)>0)
        {
            nuevoNodo = crearNodoCancion(c);
            listaCanciones = agregarAlFinal(listaCanciones, nuevoNodo);
        }
        fclose(fp);
    }
    return listaCanciones;
}

///CREAR NODO CANCION
nodoListaCancion* crearNodoCancion (stCancion cancion)
{
    nodoListaCancion* nuevoNodo = (nodoListaCancion*)malloc(sizeof(nodoListaCancion));
    nuevoNodo->c = cancion;
    nuevoNodo->sig = NULL;
    return nuevoNodo;
}

///AGREGAR AL PRINCIPIO NODO CANCION
nodoListaCancion* agregarPrincipio(nodoListaCancion* lista, nodoListaCancion* nuevoNodo)
{
    if(lista != NULL)
    {
        nuevoNodo->sig = lista;
    }
    lista = nuevoNodo;
    return lista;
}

///AGREGAR ORDENADO POR NOMBRE DE CANCION
nodoListaCancion* agregarOrdenado(nodoListaCancion* lista, nodoListaCancion* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        if(strcmp(nuevoNodo->c.titulo, lista->c.titulo)<0)
        {
            lista = agregarPrincipio(lista, nuevoNodo);
        }
        else
        {
            nodoListaCancion* ante = lista;
            nodoListaCancion* seg = lista->sig;
            while((seg != NULL)&&(strcmp(nuevoNodo->c.titulo, seg->c.titulo) >0))
            {
                ante = seg;
                seg = seg->sig;
            }
            nuevoNodo->sig = seg;
            ante->sig = nuevoNodo;
        }
    }
    return lista;
}

///AGREGAR AL FINAL NODO CANCION
nodoListaCancion* agregarAlFinal (nodoListaCancion* listaCanciones, nodoListaCancion* nuevoNodo)
{
    if(listaCanciones == NULL)
    {
        listaCanciones = nuevoNodo;
    }
    else
    {
        nodoListaCancion* ultimo = buscarUltimo(listaCanciones);
        ultimo->sig = nuevoNodo;
    }
    return listaCanciones;
}

///BUSCAR ULTIMO
nodoListaCancion* buscarUltimo(nodoListaCancion* listaCanciones)
{
    nodoListaCancion* iterador = listaCanciones;
    if(iterador != NULL)
    {
        while(iterador->sig != NULL)
        {
            iterador = iterador->sig;
        }
    }
    return iterador;
}

///MOSTRAR LISTA
void mostrarLista(nodoListaCancion* lista)
{
    if(lista != NULL)
    {
        nodoListaCancion* iterador = lista;
        while(iterador != NULL)
        {
            mostrarNodo(iterador);
            iterador = iterador->sig;
        }
    }
}

///MOSTRAR NODO CANCION
void mostrarNodo(nodoListaCancion* nodoActual)
{
    if (nodoActual->c.eliminado == 0)
    {
        printf("\t=======================================================\n");
        printf("\tID cancion: %i\n", nodoActual->c.idCancion);
        printf("\tTitulo: %s\n", nodoActual->c.titulo);
        printf("\tArtista: %s\n", nodoActual->c.artista);
        printf("\tDuracion: %i\n", nodoActual->c.duracion);
        printf("\tAnio: %i\n", nodoActual->c.anio);
        printf("\tGenero: %s\n", nodoActual->c.genero);
        printf("\tComentario: %s\n", nodoActual->c.comentario);
    }
}

///ESCUCHAR CANCION
void escucharCancion (stCelda arrayUsers[], nodoListaCancion* listaCanciones, nodoArbolCancion* arbolCanciones, int idUserLogeado)
{
    system("cls");
    int idCancion=0;
    char opcion;
    int encontrar=0;
    nodoArbolCancion* nodoCanBuscada;
    stCancion cancionBuscada;
    mostrarLista(listaCanciones);
    do
    {
        do
        {
            printf("\n\t======================================================\n");
            printf("\n\t Que cancion desea agregar a su playlist? Ingrese ID de la cancion\n");
            printf("\n\t======================================================> ");
            fflush(stdin);
            scanf("%i", &idCancion);
            encontrar = verificarExistenciaCancionArbol(arbolCanciones, idCancion);
            if (encontrar == 0)
            {
                printf("\n\tEl ID ingresado no existe. Ingrese un ID valido");
            }
            else
            {
                if (encontrar == 1)
                {
                    nodoCanBuscada = buscarCancionArbol(idCancion, arbolCanciones);
                    cancionBuscada = nodoCanBuscada->c;
                    agregarCancionADL (arrayUsers, cancionBuscada, idUserLogeado);
                    persistirPlaylist(idUserLogeado, cancionBuscada.idCancion);
                }
            }
        }
        while (encontrar == 0);
        printf("\n\tDesea agregar otra cancion? s-/n--->");
        fflush(stdin);
        scanf("%c", &opcion);
    }
    while (opcion == 's');
}

///AGREGAR UNA CANCION AL ARREGLO DE LISTAS
void agregarCancionADL (stCelda arrayUsers[], stCancion cancion, int idUserLogeado)
{
    int i=0;
    while (arrayUsers[i].usr.idUsuario != idUserLogeado)
    {
        i++;
    }
    nodoListaCancion* nuevoNodo;
    nuevoNodo = crearNodoCancion(cancion);
    arrayUsers[i].listaCanciones = agregarAlFinal(arrayUsers[i].listaCanciones, nuevoNodo);
}

///PERSISTIR DATOS DE LA PLAYLIST
void persistirPlaylist (int idUserLogeado, int idCancion)
{
    stPlaylist p;
    int i= buscarUltimoIdPlaylist();
    p.idCancion=idCancion;
    p.idUsuario=idUserLogeado;
    p.idPlaylist = i+1;
    FILE* fp = fopen("Playlist.bin", "ab");
    if (fp != NULL)
    {
        fwrite(&p, sizeof(stPlaylist), 1, fp);
        fclose(fp);
    }
}

///BUSCAR ULTIMO ID PLAYLIST
int buscarUltimoIdPlaylist()
{
    stPlaylist P;
    int id = 0;
    FILE *fp = fopen("Playlist.bin", "rb");
    if(fp != NULL)
    {
        fseek(fp, (-1)*sizeof(stPlaylist), SEEK_END);
        if(fread(&P,sizeof(stPlaylist),1,fp) > 0)
        {
            id = P.idPlaylist;
        }
        fclose(fp);
    }
    return id;
}

///BUSCAR CANCION EN ARBOL
nodoArbolCancion* buscarCancionArbol (int idCancion, nodoArbolCancion* arbolCanciones)
{
    nodoArbolCancion* rta = NULL;
    if(arbolCanciones != NULL)
    {
        if(idCancion == arbolCanciones->c.idCancion)
        {
            rta = arbolCanciones;
        }
        else
        {
            if(idCancion > arbolCanciones->c.idCancion)
            {
                rta = buscarCancionArbol(idCancion, arbolCanciones->der);
            }
            else
            {
                rta = buscarCancionArbol(idCancion, arbolCanciones->izq);
            }
        }
    }
    return rta;
}

///INICIALIZAR ARBOL CANCIONES
nodoArbolCancion* inicArbol()
{
    return NULL;
}

///CREAR NODO ARBOL DE CANCIONES
nodoArbolCancion* crearNodoArbol(stCancion dato)
{
    nodoArbolCancion* aux = (nodoArbolCancion*) malloc(sizeof(nodoArbolCancion));
    aux->c=dato;
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}

///INSERTAR EN EL ARBOL DE CANCIONES
nodoArbolCancion* insertar(nodoArbolCancion* arbol, stCancion dato)
{
    if(arbol==NULL)
    {
        arbol = crearNodoArbol(dato);
    }
    else
    {
        if(dato.idCancion > arbol->c.idCancion)
        {
            arbol->der = insertar(arbol->der, dato);
        }
        else
        {
            if (dato.idCancion < arbol->c.idCancion)
            {
                arbol->izq = insertar(arbol->izq, dato);
            }
        }
    }
    return arbol;
}

///CARGAR ARBOL DE CANCIONES DESDE EL ARCHIVO, ORDENANDO POR ID DE CANCION
nodoArbolCancion* pasarArchivoArbol(nodoArbolCancion* arbolCanciones)
{
    int cantCanciones=0;
    int nodoRaiz=0;
    stCancion cancion;
    FILE* fp = fopen("Canciones.bin", "rb");
    if (fp != NULL)
    {
        while (fread(&cancion, sizeof(stCancion), 1, fp) >0)
        {
            cantCanciones++;
        }

        nodoRaiz = cantCanciones/2;
        fseek(fp, sizeof(stCancion)*nodoRaiz, SEEK_SET);
        fread(&cancion, sizeof(stCancion), 1, fp);
        arbolCanciones = insertar(arbolCanciones, cancion);
        fseek(fp, 0, SEEK_SET);
        while(fread(&cancion, sizeof(stCancion), 1, fp)>0)
        {
            arbolCanciones = insertar(arbolCanciones, cancion);
        }
        fclose(fp);
    }
    return arbolCanciones;
}

///FUNCION MOSTRAR ARBOL CANCIONES INORDER
void inorder(nodoArbolCancion* arbol)
{
    if(arbol != NULL)
    {
        inorder(arbol->izq);
        printf("ID cancion: %i\n", arbol->c.idCancion);
        printf("Titulo: %s\n", arbol->c.titulo);
        printf("Artista: %s\n", arbol->c.artista);
        printf("--------------------------\n");
        inorder(arbol->der);
    }
}

///FUNCION MOSTRAR ARBOL CANCIONES POSTORDER
void postorder(nodoArbolCancion* arbol)
{
    if(arbol != NULL)
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        printf("ID cancion: %i\n", arbol->c.idCancion);
        printf("Titulo: %s\n", arbol->c.titulo);
        printf("Artista: %s\n", arbol->c.artista);
        printf("--------------------------\n");
    }
}

///FUNCION MOSTRAR ARBOL CANCIONES PREORDER
void preorder(nodoArbolCancion* arbol)
{
    if(arbol != NULL)
    {
        printf("ID cancion: %i\n", arbol->c.idCancion);
        printf("Titulo: %s\n", arbol->c.titulo);
        printf("Artista: %s\n", arbol->c.artista);
        printf("--------------------------\n");
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

///DESPERSISTIR ARCHIVO DE PLAYLIST
void despersistirArchPlaylist (stCelda arrayUsers[], int validos, nodoArbolCancion* arbolCanciones)
{
    stPlaylist playlist;
    int PosUser=0;
    nodoArbolCancion* nodoACancion;
    nodoListaCancion* nodoListaC;
    FILE *fp = fopen ("Playlist.bin", "rb");
    if (fp != NULL)
    {
        while (fread(&playlist, sizeof(stPlaylist), 1, fp)>0)
        {
            PosUser = buscarUserID(arrayUsers, validos, playlist.idUsuario);
            nodoACancion = buscarCancionArbol(playlist.idCancion, arbolCanciones);
            nodoListaC = crearNodoCancion(nodoACancion->c);
            arrayUsers[PosUser].listaCanciones = agregarAlFinal(arrayUsers[PosUser].listaCanciones, nodoListaC);
        }
        fclose(fp);
    }
}

///REGISTRO ADMIN
void registroAdmin()
{
    int acceso=0;
    int caracteres=0;
    int caracter = 0;
    int posArreglo = 0;
    int requisitosClave=0;
    stAdministrador admin;
    FILE *fp = fopen("Admin.bin", "ab");
    if (fp != NULL)
    {
        dibujarCuadro(1,1,74,3);
        gotoxy(20,0);
        printf("\n\n\t\t\tVamos a crear tu usuario administrador\n");
        do
        {
            printf("\n\tIngrese nombre usuario.......................: ");
            fflush(stdin);
            gets(admin.nombreUsuario);
            acceso = buscarUsuario(admin.nombreUsuario);
            if (acceso == 1)
            {
                printf("\n\tEse usuario ya existe, ingrese otro nombre de usuario\n");
                fflush(stdin);
            }
        }
        while (acceso == 1);
        printf("\n\tRequisitos: entre 4 y 12 caracteres\n");
        printf("\n\tNo se permiten caracteres especiales\n");
        printf("\n\tIngrese password......................: ");
        do
        {
            fflush(stdin);
            //gets(admin.pass);
            //caracteres = strlen(admin.pass);
            while(caracter = getch())
            {
                if(caracter == 13)
                {
                    admin.pass[posArreglo] = '\0';
                    break;
                }
                else if (caracter == 8)
                {
                    if(posArreglo>0)
                    {
                        posArreglo--;
                        printf("\b \b");
                    }
                }
                else
                {
                    if(posArreglo<DIM)
                    {
                        printf("*");
                        admin.pass[posArreglo] = caracter;
                        posArreglo++;
                    }
                }
            }
            caracteres = strlen(admin.pass);
            if ((caracteres >= 4) && (caracteres <= 12))
            {
                requisitosClave = 0;
            }
            else
            {
                requisitosClave = 1;
                printf ("\n\n\tLa clave no cumple con los requisitos\n\tIngrese una clave nuevamente\n");
                printf("\t");
            }
            posArreglo = 0;
        }
        while (requisitosClave == 1);
        printf("\n\n\tUsuario administrador creado exitosamente!\n\n");
        printf("\t");
        system("pause");
        system("cls");
        fwrite(&admin, sizeof(stAdministrador),1,fp);
        system("cls");
        fclose(fp);
    }
    system("cls");
    printf("\n\t\t\t======================\n");
    printf("\n\t\t\tBienvenido al sistema!\n");
    printf("\n\t\t\t======================\n\n");
    printf("\t    ");
    system("pause");
}

///BUSCAR USUARIO ADMINISTRADOR
int buscarUsuarioAdmin(char nombre[])
{
    stAdministrador A;
    int encontrar = 0;
    FILE *fp = fopen ("Admin.bin","rb");
    if (fp != NULL)
    {
        while ((fread(&A,sizeof(stAdministrador),1,fp)>0) && (encontrar == 0))
        {
            if (strcmp(A.nombreUsuario, nombre) == 0)
            {
                encontrar = 1;
            }
        }
        fclose (fp);
    }
    return encontrar;
}

///LOGEO ADMIN
void logeoAdmin()
{
    stAdministrador admin;
    int intento = 0;
    int ingresa = 0;
    char caracter;
    int i=0;
    FILE* fp = fopen("Admin.bin", "rb");
    if (fp == NULL)
    {
        printf("\n\t    No hay administradores registrados, debe registrarse\n\n");
        printf("\t    ");
        system("pause");
        main();
    }
    do
    {
        printf("\n\t    Ingrese su usuario:........................");
        fflush(stdin);
        gets(admin.nombreUsuario);
        printf("\n\t    Ingrese su contrasenia:....................");
        while(caracter = getch())
        {
            if(caracter == 13)
            {
                admin.pass[i] = '\0';
                break;
            }
            else if (caracter == 8)
            {
                if(i>0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                if(i<DIM)
                {
                    printf("*");
                    admin.pass[i] = caracter;
                    i++;
                }
            }
        }
        ingresa = verificarUsuarioClaveAdmin(admin.pass, admin);
        i=0;
        intento++;
    }
    while((ingresa == 0) && (intento<3));
    if(ingresa == 1)
    {
        system("cls");
        printf("\n\t\t\t======================\n");
        printf("\n\t\t\tBienvenido al sistema!\n");
        printf("\n\t\t\t======================\n\n");
        printf("\t    ");
        system("pause");
    }
    if ((ingresa == 0) && (intento == 3))
    {
        printf("\n\tUsted ha sobrepasado el numero maximo de intentos permitidos\n");
        exit(0);
    }
}

///VERIFICAR USUARIO Y CLAVE ADMINISTRADOR
int verificarUsuarioClaveAdmin (char pass[20], stAdministrador admin)
{
    stAdministrador adminGuardado;
    FILE *fp = fopen("Admin.bin", "rb");
    int ingresa = 0;
    if (fp != NULL)
    {
        while ((fread(&adminGuardado,sizeof(stAdministrador),1,fp)>0) && (ingresa == 0))
        {
            if((strcmp(adminGuardado.nombreUsuario, admin.nombreUsuario) == 0) && (strcmp(adminGuardado.pass, admin.pass) == 0))
            {
                ingresa = 1;
            }
            else
            {
                ingresa = 0;
            }
        }
        if (ingresa == 0)
        {
            printf("\n\n\t    Usuario o clave son incorrectas\n\n");
        }
        fclose(fp);
    }
    return ingresa;
}

///ADMINISTRADOR LOGEADO
void adminLogeado(stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    system("cls");
    dibujarCuadro(1,1,74,3);
    gotoxy(20,2);
    int opAdmin;
    printf("\t ..::Perfil Administrador::..\n\n") ;
    printf("\n\n\t    ===================================================\n");
    printf("\n\n\t    --- 1.Administracion de usuarios-------------------\n");
    printf("\n\n\t    --- 2.Administracion de canciones------------------\n");
    printf("\n\n\t    ====================================================> ");
    fflush(stdin);
    scanf("%i", &opAdmin);
    if (opAdmin == 1)
    {
        administrarUsuarios(arrayUsuarios, validos, arbolCanciones, listaCanciones);
    }
    else
    {
        if (opAdmin ==2)
        {
            administrarCanciones(arrayUsuarios, validos, arbolCanciones, listaCanciones);
        }
        else
        {
            printf("\n\tIngreso una opcion incorrecta\n");
        }
    }
}

///SUBMENU ADMINISTRAR USUARIOS
void administrarUsuarios (stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    int opAdminUs;
    system("cls");
    printf("\n\n\t    ===================================================\n");
    printf("\n\n\t    --- 1.Alta usuario---------------------------------\n");
    printf("\n\n\t    --- 2.Baja usuario---------------------------------\n");
    printf("\n\n\t    --- 3.Modificacion---------------------------------\n");
    printf("\n\n\t    --- 4.Consulta-------------------------------------\n");
    printf("\n\n\t    --- 5.Listado de usuarios--------------------------\n");
    printf("\n\n\t    ===================================================> ");
    fflush(stdin);
    scanf("%i", &opAdminUs);
    if (opAdminUs == 1)
    {
        registroUsuarioDesdeAdmin(arrayUsuarios, validos, arbolCanciones, listaCanciones);
    }
    else
    {
        if (opAdminUs == 2)
        {
            bajaUsuario(arrayUsuarios, validos, arbolCanciones, listaCanciones);
        }
        else
        {
            if (opAdminUs == 3)
            {
                modificarUsuario(arrayUsuarios, validos, arbolCanciones, listaCanciones);
            }
            else
            {
                if (opAdminUs == 4)
                {
                    consultaUsuario(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                else
                {
                    if (opAdminUs == 5)
                    {
                        listadoUsuarios(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                    }
                }
            }
        }
    }
}

///ADMINISTRAR CANCIONES
void administrarCanciones (stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    int opAdminCan;
    system("cls");
    printf("\n\n\t    ===================================================\n");
    printf("\n\n\t    --- 1.Alta cancion---------------------------------\n");
    printf("\n\n\t    --- 2.Baja cancion---------------------------------\n");
    printf("\n\n\t    --- 3.Modificacion---------------------------------\n");
    printf("\n\n\t    --- 4.Consulta-------------------------------------\n");
    printf("\n\n\t    --- 5.Listado de canciones-------------------------\n");
    printf("\n\n\t    ===================================================> ");
    fflush(stdin);
    scanf("%i", &opAdminCan);
    if (opAdminCan == 1)
    {
        altaCancion(arrayUsuarios, validos, arbolCanciones, listaCanciones);
    }
    else
    {
        if (opAdminCan == 2)
        {
            bajaCancion(arrayUsuarios, validos, arbolCanciones, listaCanciones);
        }
        else
        {
            if (opAdminCan == 3)
            {
                modificarCancion(arrayUsuarios, validos, arbolCanciones, listaCanciones);
            }
            else
            {
                if (opAdminCan == 4)
                {
                    consultaCanciones(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                else
                {
                    if (opAdminCan == 5)
                    {
                        listadoCanciones(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                    }
                }
            }
        }
    }
}

///REGISTRAR UN USUARIO DESDE EL ADMIN
void registroUsuarioDesdeAdmin(stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    system("cls");
    int acceso=0;
    int caracteres=0;
    int requisitosClave=0;
    int i=0;
    stUsuario usuario;
    FILE *fp = fopen("Usuarios.bin", "ab");
    i = buscarUltimoIdUsuario();
    if (fp != NULL)
    {
        usuario.idUsuario = i + 1;
        dibujarCuadro(1,1,74,3);
        gotoxy(20,0);
        printf("\n\n\t\t\tVamos a crear un usuario \n");
        do
        {
            printf("\n\tIngrese nombre de usuario.......................: ");
            fflush(stdin);
            gets(usuario.nombreUsuario);
            acceso = buscarUsuario(usuario.nombreUsuario);
            if (acceso == 1)
            {
                printf("\n\tEse usuario ya existe, ingrese otro nombre de usuario\n");
                fflush(stdin);
            }
        }
        while (acceso == 1);
        printf("\n\tRequisitos: entre 4 y 12 caracteres\n");
        printf("\n\tNo se permiten caracteres especiales\n");
        printf("\n\tIngrese password......................: ");
        do
        {
            fflush(stdin);
            gets(usuario.pass);
            caracteres = strlen(usuario.pass);
            if ((caracteres >= 4) && (caracteres <= 12))
            {
                requisitosClave = 0 ;
            }
            else
            {
                requisitosClave = 1 ;
                printf ("\n\tLa clave no cumple con los requisitos\n\tIngrese una clave nuevamente\n");
            }
        }
        while (requisitosClave == 1);
        printf("\n\tIngrese anio de nacimiento...........: ");
        scanf("%d", &usuario.anioNacimiento);
        printf("\n\tIngrese genero (m: masculino - f: femenino - o: otro)........: ");
        fflush(stdin);
        scanf("%c",&usuario.genero);
        while(usuario.genero != 'm' && usuario.genero != 'f' && usuario.genero != 'o')
        {
            printf("\tGenero erroneo. Intente nuvamente. (m: masculino - f: femenino - o: otro): ");
            fflush(stdin);
            scanf("%c", &usuario.genero);
        }
        printf("\n\tIngrese pais...............: ");
        fflush(stdin);
        gets(usuario.pais);
        printf("\n\tUsuario creado exitosamente!\n\n");
        printf("\t    ");
        system("pause");
        system("cls");
        fwrite(&usuario, sizeof(stUsuario),1,fp);
        fclose(fp);
    }
    actualizarArrayUsers(arrayUsuarios, validos, usuario);
    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
}

///AGREGAR USUARIO CREADO POR EL ADMIN AL ARREGLO DE USUARIOS
void actualizarArrayUsers (stCelda arrayUsuarios[], int* validos, stUsuario usuario)
{
    arrayUsuarios[(*validos)].usr = usuario;
    (*validos)++;
}

///BAJA USUARIO DESDE ADMIN
void bajaUsuario (stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    int idBaja;
    stUsuario u;
    int posUser=0;
    int i=0;
    int encontrar=0;
    system("cls");
    for (int i=0; i<(*validos); i++)
    {
        mostrarUserAdministrador(arrayUsuarios[i].usr);
    }
    do
    {
        printf("\n\t======================================================\n");
        printf("\n\tIngrese el ID del usuario que desea dar de baja\n");
        printf("\n\t======================================================> ");
        fflush(stdin);
        scanf("%i", &idBaja);
        encontrar = verificarExistenciaUsuario(idBaja);
        if (encontrar == 0)
        {
            printf("\n\tEl ID ingresado no existe. Ingrese un ID valido");
        }
        else
        {
            if (encontrar == 1)
            {
                FILE *fp = fopen("Usuarios.bin", "r+b");
                if (fp != NULL)
                {
                    while ((fread(&u, sizeof(stUsuario), 1, fp) > 0) && (u.idUsuario != idBaja))
                    {
                        posUser++;
                    }
                    u.eliminado = 1;
                    fseek(fp, sizeof(stUsuario)*posUser, SEEK_SET);
                    fwrite(&u, sizeof(stUsuario),1, fp);
                    fclose(fp);
                }
                while ((arrayUsuarios[i].usr.idUsuario != idBaja) && (i<(*validos)))
                {
                    i++;
                }
                arrayUsuarios[i].usr.eliminado = 1;
                arrayUsuarios[i].listaCanciones = borrarListaCompleta(arrayUsuarios[i].listaCanciones);
                printf("\n\t======================================================\n");
                printf("\n\tUsuario eliminado exitosamente!\n");
                deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
            }
        }
    }
    while (encontrar == 0);
}
///BORRAR LISTA COMPLETA
nodoListaCancion* borrarListaCompleta (nodoListaCancion* lista)
{
    nodoListaCancion* proximo;
    nodoListaCancion* seg;
    seg = lista;
    while(seg != NULL)
    {
        proximo = seg->sig;
        free(seg);
        seg = proximo;
    }
    return seg;
}

///MODIFICAR USUARIO DESDE ADMIN
void modificarUsuario (stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    system("cls");
    int idMod;
    int encontrar;
    int datoMod;
    int acceso=0;
    int caracteres = 0;
    int requisitosClave;
    stUsuario usuario;
    for (int i=0; i<(*validos); i++)
    {
        mostrarUser(arrayUsuarios[i].usr);
    }
    do
    {
        printf("\n\t======================================================\n");
        printf("\n\tIngrese el ID del usuario que desea modificar\n");
        printf("\n\t======================================================> ");
        fflush(stdin);
        scanf("%i", &idMod);
        encontrar = verificarExistenciaUsuario(idMod);
        if (encontrar == 0)
        {
            printf("\n\tEl ID ingresado no existe. Ingrese un ID valido");
        }
        else
        {
            if (encontrar == 1)
            {
                system("cls");
                printf("\n\t    ============================================\n");
                printf ("\n\t    Que dato desea modificar?");
                printf ("\n\t    1.Nombre usuario---------");
                printf ("\n\t    2.Contrasenia------------");
                printf ("\n\t    3.Anio de nacimiento-----");
                printf ("\n\t    4.Genero-----------------");
                printf ("\n\t    5.Pais-------------------");
                printf("\n\n\t   ============================================> ");
                fflush(stdin);
                scanf("%i", &datoMod);
                if (datoMod ==1)
                {
                    do
                    {
                        printf("\n\tIngrese nombre de usuario....................: ");
                        fflush(stdin);
                        gets(usuario.nombreUsuario);
                        acceso = buscarUsuario(usuario.nombreUsuario);
                        if (acceso == 1)
                        {
                            printf("\n\tEse usuario ya existe, ingrese otro nombre de usuario");
                            fflush(stdin);
                        }
                    }
                    while (acceso == 1);
                    modificarNombreUsuario(arrayUsuarios, validos, usuario, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                if (datoMod == 2)
                {
                    printf("\n\tRequisitos: entre 4 y 12 caracteres\n");
                    printf("\n\tNo se permiten caracteres especiales\n");
                    printf("\n\tIngrese password......................: ");
                    do
                    {
                        fflush(stdin);
                        gets(usuario.pass);
                        caracteres = strlen(usuario.pass);
                        if ((caracteres >= 4) && (caracteres <= 12))
                        {
                            requisitosClave = 0 ;
                        }
                        else
                        {
                            requisitosClave = 1 ;
                            printf ("\n\tLa clave no cumple con los requisitos\n\tIngrese una clave nuevamente\n");
                        }
                    }
                    while (requisitosClave == 1);
                    modificarPassword(arrayUsuarios, validos, usuario, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);

                }
                if (datoMod == 3)
                {
                    printf("\n\tIngrese anio de nacimiento...........: ");
                    scanf("%d", &usuario.anioNacimiento);
                    modificarAnio(arrayUsuarios, validos, usuario, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);

                }
                if (datoMod ==4)
                {
                    printf("\n\tIngrese genero (m: masculino - f: femenino - o: otro)........: ");
                    fflush(stdin);
                    scanf("%c",&usuario.genero);
                    while((usuario.genero != 'm') && (usuario.genero != 'f') && (usuario.genero != 'o'))
                    {
                        printf("\tGenero erroneo. Intente nuvamente. (m: masculino - f: femenino - o: otro): ");
                        fflush(stdin);
                        scanf("%c", &usuario.genero);
                    }
                    modificarGenero(arrayUsuarios, validos, usuario, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                if(datoMod == 4)
                {
                    printf("\n\tIngrese pais...............: ");
                    fflush(stdin);
                    gets(usuario.pais);
                    modificarPais(arrayUsuarios, validos, usuario, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
            }
        }
    }
    while (encontrar == 0);
}

///VERIFICAR LA EXISTENCIA DE UN USUARIO POR ID
int verificarExistenciaUsuario (int idUser)
{
    stUsuario U;
    int encontrar = 0 ;
    FILE *fp = fopen ("Usuarios.bin","rb");
    if (fp != NULL)
    {
        while ((fread(&U,sizeof(stUsuario),1,fp)>0) && (encontrar == 0))
        {
            if (idUser == U.idUsuario)
            {
                encontrar = 1;
            }
        }
        fclose (fp);
    }
    return encontrar;
}

///MODIFICAR NOMBRE DE USUARIO DESDE EL ADMIN
void modificarNombreUsuario(stCelda arrayUsers[], int* validos, stUsuario user, int idMod)
{
    stUsuario u;
    int posUser=0;
    int i=0;
    FILE *fp = fopen("Usuarios.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&u, sizeof(stUsuario), 1, fp) > 0) && (u.idUsuario != idMod))
        {
            posUser++;
        }
        strcpy(u.nombreUsuario, user.nombreUsuario);
        fseek(fp, sizeof(stUsuario)*posUser, SEEK_SET);
        fwrite(&u, sizeof(stUsuario),1, fp);
        fclose(fp);
    }
    while ((arrayUsers[i].usr.idUsuario != idMod) && (i<(*validos)))
    {
        i++;
    }
    arrayUsers[i].usr = u;
    printf("\n\t======================================================\n");
    printf("\n\tUsuario modificado exitosamente!\n");
}

///MODIFICAR PASSWORD DE USUARIO DESDE EL ADMIN
void modificarPassword(stCelda arrayUsers[], int* validos, stUsuario user, int idMod)
{
    stUsuario u;
    int posUser=0;
    int i=0;
    FILE *fp = fopen("Usuarios.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&u, sizeof(stUsuario), 1, fp) > 0) && (u.idUsuario != idMod))
        {
            posUser++;
        }
        fseek(fp, sizeof(stUsuario)*posUser, SEEK_SET);
        strcpy(u.pass, user.pass);
        fwrite(&u, sizeof(stUsuario),1, fp);
        fclose(fp);
    }
    while ((arrayUsers[i].usr.idUsuario != idMod) && (i<(*validos)))
    {
        i++;
    }
    arrayUsers[i].usr = u;
    printf("\n\t======================================================\n");
    printf("\n\tUsuario modificado exitosamente!\n");
}

///MODIFICAR ANIO DE NACIMIENTO DE USUARIO DESDE EL ADMIN
void modificarAnio(stCelda arrayUsers[], int* validos, stUsuario user, int idMod)
{
    stUsuario u;
    int posUser=0;
    int i=0;
    FILE *fp = fopen("Usuarios.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&u, sizeof(stUsuario), 1, fp) > 0) && (u.idUsuario != idMod))
        {
            posUser++;
        }
        fseek(fp, sizeof(stUsuario)*posUser, SEEK_SET);
        u.anioNacimiento = user.anioNacimiento;
        fwrite(&u, sizeof(stUsuario),1, fp);
        fclose(fp);
    }
    while ((arrayUsers[i].usr.idUsuario != idMod) && (i<(*validos)))
    {
        i++;
    }
    arrayUsers[i].usr = u;
    printf("\n\t======================================================\n");
    printf("\n\tUsuario modificado exitosamente!\n");
}

///MODIFICAR GENERO DE USUARIO DESDE EL ADMIN
void modificarGenero(stCelda arrayUsers[], int* validos, stUsuario user, int idMod)
{
    stUsuario u;
    int posUser=0;
    int i=0;
    FILE *fp = fopen("Usuarios.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&u, sizeof(stUsuario), 1, fp) > 0) && (u.idUsuario != idMod))
        {
            posUser++;
        }
        fseek(fp, sizeof(stUsuario)*posUser, SEEK_SET);
        u.genero = user.genero;
        fwrite(&u, sizeof(stUsuario),1, fp);
        fclose(fp);
    }
    while ((arrayUsers[i].usr.idUsuario != idMod) && (i<(*validos)))
    {
        i++;
    }
    arrayUsers[i].usr = u;
    printf("\n\t======================================================\n");
    printf("\n\tUsuario modificado exitosamente!\n");
}

///MODIFICAR PAIS DESDE EL ADMIN
void modificarPais(stCelda arrayUsers[], int* validos, stUsuario user, int idMod)
{
    stUsuario u;
    int posUser=0;
    int i=0;
    FILE *fp = fopen("Usuarios.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&u, sizeof(stUsuario), 1, fp) > 0) && (u.idUsuario != idMod))
        {
            posUser++;
        }
        fseek(fp, sizeof(stUsuario)*posUser, SEEK_SET);
        strcpy(u.pais, user.pais);
        fwrite(&u, sizeof(stUsuario),1, fp);
        fclose(fp);
    }
    while ((arrayUsers[i].usr.idUsuario != idMod) && (i<(*validos)))
    {
        i++;
    }
    arrayUsers[i].usr = u;
    printf("\n\t======================================================\n");
    printf("\n\tUsuario modificado exitosamente!\n");
}

///COSULTA USUARIO
void consultaUsuario (stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    int posUser=0;
    int idConsultar;
    int encontrar=0;
    system("cls");
    do
    {
        printf("\n\t======================================================\n");
        printf("\n\tIngrese el ID del usuario que desea consultar\n");
        printf("\n\t======================================================> ");
        fflush(stdin);
        scanf("%i", &idConsultar);
        encontrar = verificarExistenciaUsuario(idConsultar);
        if (encontrar == 0)
        {
            printf("\n\tEl ID ingresado no existe. Ingrese un ID valido");
        }
        else
        {
            if (encontrar == 1)
            {
                posUser = buscarPosUsuario(arrayUsuarios, validos, idConsultar);
                mostrarUserAdministrador(arrayUsuarios[posUser].usr);
            }
        }
    }
    while (encontrar == 0);
    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
}

///BUSCAR POSICION USUARIO
int buscarPosUsuario (stCelda arrayUsuarios[], int* validos, int idUser)
{
    int i=0;
    while ((i<(*validos)) && (arrayUsuarios[i].usr.idUsuario != idUser))
    {
        i++;
    }
    return i;
}

///FUNCION DESEA VOLVER AL MENU ADMIN
void deseaSeguir (stCelda arrayUsers[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    char seguir;
    printf("\n\tDesea volver al menu principal? s/n-->");
    fflush(stdin);
    scanf("%c", &seguir);
    if (seguir == 's')
    {
        adminLogeado(arrayUsers, validos, arbolCanciones, listaCanciones);
    }
}

///LISTADO USUARIOS
void listadoUsuarios (stCelda arrayUsers[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    system("cls");
    stUsuario array[DIMARRAY];
    stUsuario u;
    int i=0;
    int val=0;
    FILE* fp = fopen("Usuarios.bin", "rb");
    if (fp != NULL)
    {
        while (fread(&u, sizeof(stUsuario), 1, fp) >0)
        {
            array[i] = u;
            val++;
            i++;
        }
        fclose(fp);
    }
    ordenarArray(array, val);
    for (int j=0; j<val; j++)
    {
        mostrarUserAdministrador(array[j]);
    }
    deseaSeguir(arrayUsers, validos, arbolCanciones, listaCanciones);
}

///ORDENAR ARREGLO POR NOMBRE DE USUARIO
void ordenarArray (stUsuario a[], int validos)
{
    int posMenor;
    int i = 0;
    stUsuario aux;
    while(i< validos - 1)
    {
        posMenor = buscarPosMenor(a, validos, i);
        aux = a[posMenor];
        a[posMenor] = a[i];
        a[i] = aux;
        i++;
    }
}

///BUSCAR POS MENOR
int buscarPosMenor (stUsuario a[], int validos, int posicion)
{
    stUsuario menor = a[posicion];
    int menorPosicion = posicion;
    int i = posicion + 1;
    while(i<validos)
    {
        if(strcmp(a[i].nombreUsuario, menor.nombreUsuario) < 0)
        {
            menor = a[i];
            menorPosicion = i;
        }
        i++;
    }
    return menorPosicion;
}

///MOSTRAR USER DESDE ADMINISTRADOR
void mostrarUserAdministrador (stUsuario user)
{
    printf("\n\n\t===================================================\n");
    printf("\tID usuario: %i\n", user.idUsuario);
    printf("\tNombre: %s\n", user.nombreUsuario);
    printf("\tAnio de nacimiento: %i\n", user.anioNacimiento);
    printf("\tGenero: %c\n", user.genero);
    printf("\tPais: %s\n", user.pais);
    printf("\tEliminado: 1=eliminado - 0=no eliminado: %i\n", user.eliminado);
    printf("\t===================================================\n");
}

///ALTA CANCIONES DESDE ADMIN
void altaCancion (stCelda arrayUsers[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    system("cls");
    stCancion song;
    int idUltCancion;
    nodoListaCancion* nuevoNodo;
    printf("\n\tIngrese titulo de la cancion: ");
    fflush(stdin);
    gets(song.titulo);
    printf("\n\tIngrese artista: ");
    fflush(stdin);
    gets(song.artista);
    printf("\n\tIngrese duracion de la cancion: ");
    fflush(stdin);
    scanf ("%i", &song.duracion);
    printf("\n\tIngrese album: ");
    fflush(stdin);
    gets(song.album);
    printf("\n\tIngrese anio de lanzamiento: ");
    fflush(stdin);
    scanf("%i", &song.anio);
    printf("\n\tIngrese genero: ");
    fflush(stdin);
    gets(song.genero);
    printf("\n\tIngrese comentario: ");
    fflush(stdin);
    gets(song.comentario);
    song.eliminado = 0;
    idUltCancion = buscarUltimoIdCancion();
    song.idCancion = idUltCancion+1;
    persistirCancion(song);
    arbolCanciones = insertar(arbolCanciones, song);
    nuevoNodo = crearNodoCancion(song);
    listaCanciones = agregarAlFinal(listaCanciones, nuevoNodo);
    printf("\n\tCancion agregada exitosamente!\n");
    deseaSeguir(arrayUsers, validos, arbolCanciones, listaCanciones);
}

///BUSCAR ULTIMO ID DE CANCION
int buscarUltimoIdCancion()
{
    stCancion C;
    int id = 0;
    FILE *fp = fopen("Canciones.bin", "rb");
    if(fp != NULL)
    {
        fseek(fp, (-1) * sizeof(stCancion), SEEK_END);
        if(fread(&C,sizeof(stCancion),1,fp) > 0)
        {
            id = C.idCancion;
        }
        fclose(fp);
    }
    return id;
}

///PERSISTIR NUEVA CANCION
void persistirCancion (stCancion song)
{
    FILE *fp = fopen ("Canciones.bin", "ab");
    if (fp != NULL)
    {
        fwrite(&song, sizeof(stCancion), 1, fp);
        fclose(fp);
    }
}

///BAJA CANCION
void bajaCancion (stCelda arrayUsers[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    int idBaja;
    stCancion C;
    int posCancion=0;
    int encontrar=0;
    system("cls");
    mostrarListaAdmin(listaCanciones);
    do
    {
        printf("\n\t======================================================\n");
        printf("\n\tIngrese el ID de la cancion que desea dar de baja\n");
        printf("\n\t======================================================> ");
        fflush(stdin);
        scanf("%i", &idBaja);
        encontrar = verificarExistenciaCancionArbol(arbolCanciones, idBaja);
        if (encontrar == 0)
        {
            printf("\n\tEl ID ingresado no existe. Ingrese un ID valido");
        }
        else
        {
            if (encontrar == 1)
            {
                FILE *fp = fopen("Canciones.bin", "r+b");
                if (fp != NULL)
                {
                    while ((fread(&C, sizeof(stCancion), 1, fp) > 0) && (C.idCancion != idBaja))
                    {
                        posCancion++;
                    }
                    C.eliminado = 1;
                    fseek(fp, sizeof(stCancion)*posCancion, SEEK_SET);
                    fwrite(&C, sizeof(stCancion),1, fp);
                    fclose(fp);
                }
                listaCanciones = modificarListaCanciones(listaCanciones, C);
                bajaCancionPlaylist(arrayUsers, validos, arbolCanciones, listaCanciones, idBaja);
                printf("\n\t======================================================\n");
                printf("\n\tCancion eliminada exitosamente!\n");
                deseaSeguir(arrayUsers, validos, arbolCanciones, listaCanciones);
            }
        }
    }
    while (encontrar ==0);
}

///BAJA CANCION DEL ARCHIVO PLAYLIST
void bajaCancionPlaylist (stCelda arrayUsers[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones, int idBaja)
{
    stCancion C;
    FILE *fp = fopen("Playlist.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&C, sizeof(stCancion), 1, fp) > 0))
        {
            if (C.idCancion == idBaja)
            {
                C.eliminado = 1;
                fseek(fp, (-1)*sizeof(stCancion), SEEK_CUR);
                fwrite(&C, sizeof(stCancion),1, fp);
            }
        }
        fclose(fp);
    }
}

///MOSTRAR LISTA ADMINISTRADOR
void mostrarListaAdmin(nodoListaCancion* lista)
{
    if(lista != NULL)
    {
        nodoListaCancion* iterador = lista;
        while(iterador != NULL)
        {
            mostrarNodoAdmin(iterador);
            iterador = iterador->sig;
        }
    }
}

///MOSTRAR NODO CANCION ADMINISTRADOR
void mostrarNodoAdmin(nodoListaCancion* nodoActual)
{
    printf("\t=======================================================\n");
    printf("\tID cancion: %i\n", nodoActual->c.idCancion);
    printf("\tTitulo: %s\n", nodoActual->c.titulo);
    printf("\tArtista: %s\n", nodoActual->c.artista);
    printf("\tDuracion: %i\n", nodoActual->c.duracion);
    printf("\tAnio: %i\n", nodoActual->c.anio);
    printf("\tGenero: %s\n", nodoActual->c.genero);
    printf("\tComentario: %s\n", nodoActual->c.comentario);
    printf("\tEliminado (1=eliminado - 0=no eliminado): %i\n", nodoActual->c.eliminado);
}

///MODIFICAR CANCION
void modificarCancion (stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    system("cls");
    int idMod;
    int encontrar;
    int datoMod;
    stCancion cancion;
    mostrarListaAdmin(listaCanciones);
    do
    {
        printf("\n\t======================================================\n");
        printf("\n\tIngrese el ID de la cancion que desea modificar\n");
        printf("\n\t======================================================> ");
        fflush(stdin);
        scanf("%i", &idMod);
        encontrar = verificarExistenciaCancionArbol(arbolCanciones, idMod);
        if (encontrar == 0)
        {
            printf("\n\tEl ID ingresado no existe. Ingrese un ID valido");
        }
        else
        {
            if (encontrar == 1)
            {
                system("cls");
                printf ("\n\t    ============================================\n");
                printf ("\n\t    Que dato desea modificar?");
                printf ("\n\t    1.Titulo----------------------");
                printf ("\n\t    2.Artista---------------------");
                printf ("\n\t    3.Duracion--------------------");
                printf ("\n\t    4.Album-----------------------");
                printf ("\n\t    5.Anio------------------------");
                printf ("\n\t    6.Genero----------------------");
                printf ("\n\t    7.Comentario------------------");
                printf("\n\n\t   ============================================> ");
                fflush(stdin);
                scanf("%i", &datoMod);
                if (datoMod ==1)
                {
                    printf("\n\tIngrese titulo de la cancion....................: ");
                    fflush(stdin);
                    gets(cancion.titulo);
                    modificarTitulo(listaCanciones, cancion, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                if (datoMod == 2)
                {
                    printf("\n\tIngrese nombre del artista....................: ");
                    fflush(stdin);
                    gets(cancion.artista);
                    modificarArtista(listaCanciones, cancion, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                if (datoMod == 3)
                {
                    printf("\n\tIngrese duracion....................: ");
                    fflush(stdin);
                    scanf("%i", &cancion.duracion);
                    modificarDuracion(listaCanciones, cancion, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                if (datoMod ==4)
                {
                    printf("\n\tIngrese album....................: ");
                    fflush(stdin);
                    gets(cancion.album);
                    modificarAlbum(listaCanciones, cancion, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                if(datoMod == 5)
                {
                    printf("\n\tIngrese anio de lanzamiento....................: ");
                    fflush(stdin);
                    scanf("%i",&cancion.anio);
                    modificarAnioLanzamiento(listaCanciones, cancion, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                if(datoMod == 6)
                {
                    printf("\n\tIngrese genero....................: ");
                    fflush(stdin);
                    gets(cancion.genero);
                    modificarGeneroCancion(listaCanciones, cancion, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
                if(datoMod == 7)
                {
                    printf("\n\tIngrese comentario....................: ");
                    fflush(stdin);
                    gets(cancion.comentario);
                    modificarComentario(listaCanciones, cancion, idMod);
                    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
                }
            }
        }
    }
    while (encontrar == 0);
}

///VERIFICAR LA EXISTENCIA DE UNA CANCION POR ID
int verificarExistenciaCancion (int idCancion)
{
    stCancion C;
    int encontrar = 0 ;
    FILE *fp = fopen ("Canciones.bin","rb");
    if (fp != NULL)
    {
        while ((fread(&C,sizeof(stCancion),1,fp)>0) && (encontrar == 0))
        {
            if (idCancion == C.idCancion)
            {
                encontrar = 1;
            }
        }
        fclose (fp);
    }
    return encontrar;
}

///VERIFICAR EXISTENCIA CANCION ARBOL
int verificarExistenciaCancionArbol(nodoArbolCancion* arbol, int idMod)
{
    int rta=0;
    if(arbol!=NULL)
    {
        if(idMod == arbol->c.idCancion)
        {
            rta = 1;
        }
        else
        {
            if(idMod > arbol->c.idCancion)
            {
                rta = verificarExistenciaCancionArbol(arbol->der, idMod);
            }
            else
            {
                rta = verificarExistenciaCancionArbol(arbol->izq, idMod);
            }
        }
    }
    return rta;
}

///MODIFICAR TITULO DE LA CANCION
void modificarTitulo(nodoListaCancion* listaCanciones, stCancion song, int idMod)
{
    stCancion c;
    int posCan=0;
    FILE *fp = fopen("Canciones.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&c, sizeof(stCancion), 1, fp) > 0) && (c.idCancion != idMod))
        {
            posCan++;
        }
        fseek(fp, sizeof(stCancion)*posCan, SEEK_SET);
        strcpy(c.titulo, song.titulo);
        fwrite(&c, sizeof(stCancion),1, fp);
        fclose(fp);
    }
    modificarArchPlaylist(idMod, c);
    listaCanciones = modificarListaCanciones(listaCanciones, c);
    printf("\n\t======================================================\n");
    printf("\n\tCancion modificada exitosamente!\n");
}

///MODIFICAR CANCION DEL ARCHIVO DE PLAYLISTS
void modificarArchPlaylist (int idMod, stCancion song)
{
    stCancion C;
    FILE *fp = fopen("Playlist.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&C, sizeof(stCancion), 1, fp) > 0))
        {
            if (C.idCancion == idMod)
            {
                fseek(fp, (-1)*sizeof(stCancion), SEEK_CUR);
                fwrite(&song, sizeof(stCancion),1, fp);
            }
        }
        fclose(fp);
    }
}

///MODIFICAR LA LISTA DE CANCIONES
nodoListaCancion* modificarListaCanciones (nodoListaCancion* listaCanciones, stCancion song)
{
    nodoListaCancion* iterador;
    iterador = listaCanciones;
    while ((iterador != NULL) && (iterador->c.idCancion != song.idCancion))
    {
        iterador=iterador->sig;
    }
    iterador->c = song;
    return iterador;
}

///MODIFICAR ARTISTA
void modificarArtista(nodoListaCancion* listaCanciones, stCancion song, int idMod)
{
    stCancion c;
    int posCan=0;
    FILE *fp = fopen("Canciones.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&c, sizeof(stCancion), 1, fp) > 0) && (c.idCancion != idMod))
        {
            posCan++;
        }
        fseek(fp, sizeof(stCancion)*posCan, SEEK_SET);
        strcpy(c.artista, song.artista);
        fwrite(&c, sizeof(stCancion),1, fp);
        fclose(fp);
    }
    modificarArchPlaylist(idMod, c);
    listaCanciones = modificarListaCanciones(listaCanciones, c);
    printf("\n\t======================================================\n");
    printf("\n\tCancion modificada exitosamente!\n");
}

///MODIFICAR DURACION
void modificarDuracion(nodoListaCancion* listaCanciones, stCancion song, int idMod)
{
    stCancion c;
    int posCan=0;
    FILE *fp = fopen("Canciones.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&c, sizeof(stCancion), 1, fp) > 0) && (c.idCancion != idMod))
        {
            posCan++;
        }
        fseek(fp, sizeof(stCancion)*posCan, SEEK_SET);
        c.duracion = song.duracion;
        fwrite(&c, sizeof(stCancion),1, fp);
        fclose(fp);
    }
    modificarArchPlaylist(idMod, c);
    listaCanciones = modificarListaCanciones(listaCanciones, c);
    printf("\n\t======================================================\n");
    printf("\n\tCancion modificada exitosamente!\n");
}

///MODIFICAR ALBUM
void modificarAlbum(nodoListaCancion* listaCanciones, stCancion song, int idMod)
{
    stCancion c;
    int posCan=0;
    FILE *fp = fopen("Canciones.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&c, sizeof(stCancion), 1, fp) > 0) && (c.idCancion != idMod))
        {
            posCan++;
        }
        fseek(fp, sizeof(stCancion)*posCan, SEEK_SET);
        strcpy(c.album, song.album);
        fwrite(&c, sizeof(stCancion),1, fp);
        fclose(fp);
    }
    modificarArchPlaylist(idMod, c);
    listaCanciones = modificarListaCanciones(listaCanciones, c);
    printf("\n\t======================================================\n");
    printf("\n\tCancion modificada exitosamente!\n");
}

///MODIFICAR ANIO
void modificarAnioLanzamiento(nodoListaCancion* listaCanciones, stCancion song, int idMod)
{
    stCancion c;
    int posCan=0;
    FILE *fp = fopen("Canciones.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&c, sizeof(stCancion), 1, fp) > 0) && (c.idCancion != idMod))
        {
            posCan++;
        }
        fseek(fp, sizeof(stCancion)*posCan, SEEK_SET);
        c.anio = song.anio;
        fwrite(&c, sizeof(stCancion),1, fp);
        fclose(fp);
    }
    modificarArchPlaylist(idMod, c);
    listaCanciones = modificarListaCanciones(listaCanciones, c);
    printf("\n\t======================================================\n");
    printf("\n\tCancion modificada exitosamente!\n");
}

///MODIFICAR GENERO CANCION
void modificarGeneroCancion(nodoListaCancion* listaCanciones, stCancion song, int idMod)
{
    stCancion c;
    int posCan=0;
    FILE *fp = fopen("Canciones.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&c, sizeof(stCancion), 1, fp) > 0) && (c.idCancion != idMod))
        {
            posCan++;
        }
        fseek(fp, sizeof(stCancion)*posCan, SEEK_SET);
        strcpy(c.genero, song.genero);
        fwrite(&c, sizeof(stCancion),1, fp);
        fclose(fp);
    }
    modificarArchPlaylist(idMod, c);
    listaCanciones = modificarListaCanciones(listaCanciones, c);
    printf("\n\t======================================================\n");
    printf("\n\tCancion modificada exitosamente!\n");
}

///MODIFICAR COMENTARIO
void modificarComentario(nodoListaCancion* listaCanciones, stCancion song, int idMod)
{
    stCancion c;
    int posCan=0;
    FILE *fp = fopen("Canciones.bin", "r+b");
    if (fp != NULL)
    {
        while ((fread(&c, sizeof(stCancion), 1, fp) > 0) && (c.idCancion != idMod))
        {
            posCan++;
        }
        fseek(fp, sizeof(stCancion)*posCan, SEEK_SET);
        strcpy(c.comentario, song.comentario);
        fwrite(&c, sizeof(stCancion),1, fp);
        fclose(fp);
    }
    modificarArchPlaylist(idMod, c);
    listaCanciones = modificarListaCanciones(listaCanciones, c);
    printf("\n\t======================================================\n");
    printf("\n\tCancion modificada exitosamente!\n");
}

///CONSULTA CANCIONES
void consultaCanciones (stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    nodoListaCancion* canBuscada;
    int idConsultar;
    int encontrar=0;
    system("cls");
    do
    {
        printf("\n\t======================================================\n");
        printf("\n\tIngrese el ID de la cancion que desea consultar\n");
        printf("\n\t======================================================> ");
        fflush(stdin);
        scanf("%i", &idConsultar);
        encontrar = verificarExistenciaCancion(idConsultar);
        if (encontrar == 0)
        {
            printf("\n\tEl ID ingresado no existe. Ingrese un ID valido");
        }
        else
        {
            if (encontrar == 1)
            {
                canBuscada = buscarNodo(listaCanciones, idConsultar);
                mostrarNodoAdmin(canBuscada);
            }
        }
    }
    while (encontrar == 0);
    deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
}

///BUSCAR NODO DE UNA CANCION
nodoListaCancion* buscarNodo(nodoListaCancion* lista, int idConsultar)
{
    nodoListaCancion* iterador;
    iterador = lista;
    while ((iterador != NULL) && (iterador->c.idCancion != idConsultar))
    {
        iterador=iterador->sig;
    }
    return iterador;
}

void listadoCanciones (stCelda arrayUsuarios[], int* validos, nodoArbolCancion* arbolCanciones, nodoListaCancion* listaCanciones)
{
    int opMostrar;
    system("cls");
    stCancion arrayCanciones[DIMARRAY];
    int validosCanciones=0;
    printf("\n\n\t\tMostrar canciones ordenadas por:\n");
    printf("\n\t\t1.Titulo--------------------\n");
    printf("\n\t\t2.Genero--------------------\n");
    printf("\n\n\t\t============================================> ");
    fflush(stdin);
    scanf("%i", &opMostrar);
    validosCanciones = crearArregloCanciones(arrayCanciones, validosCanciones);
    if (opMostrar==1)
    {
        mostrarPorTitulo(arrayCanciones, validosCanciones);
        deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
    }
    else
    {
        if (opMostrar ==2)
        {
            mostrarPorGenero(arrayCanciones, validosCanciones);
            deseaSeguir(arrayUsuarios, validos, arbolCanciones, listaCanciones);
        }
    }
}

///CREAR ARREGLO CANCIONES
int crearArregloCanciones (stCancion arrayCanciones[], int validos)
{
    stCancion song;
    int i=0;
    FILE* fp = fopen("Canciones.bin", "rb");
    if (fp!=NULL)
    {
        while ((fread(&song, sizeof(stCancion), 1, fp)>0) && (validos<DIMARRAY))
        {
            arrayCanciones[i] = song;
            validos++;
            i++;
        }
        fclose(fp);
    }
    return validos;
}

///MOSTRAR POR TITULO
void mostrarPorTitulo (stCancion arrayCanciones[], int validos)
{
    system("cls");
    ordenarPorTitulo(arrayCanciones, validos);
    for (int j=0; j<validos; j++)
    {
        mostrarArregloCanciones(arrayCanciones[j], validos);
    }
}

///MOSTRAR POR GENERO
void mostrarPorGenero (stCancion arrayCanciones[], int validos)
{
    system("cls");
    ordenarPorGenero(arrayCanciones, validos);
    for (int j=0; j<validos; j++)
    {
        mostrarArregloCanciones(arrayCanciones[j], validos);
    }
}

///ORDERNAR POR TITULO (SELECCION)
void ordenarPorTitulo (stCancion a[], int validos)
{
    int posMenor;
    int i = 0;
    stCancion aux;
    while(i< validos-1)
    {
        posMenor = buscarPosicionMenor(a, validos, i);
        aux = a[posMenor];
        a[posMenor] = a[i];
        a[i] = aux;
        i++;
    }
}

///BUSCAR POS MENOR
int buscarPosicionMenor (stCancion arreglo[], int validos, int posicion)
{
    stCancion menor = arreglo[posicion];
    int menorPosicion = posicion;
    int i = posicion+1;
    while(i<validos)
    {
        if(strcmp(arreglo[i].titulo, menor.titulo) < 0)
        {
            menor = arreglo[i];
            menorPosicion = i;
        }
        i++;
    }
    return menorPosicion;
}

///MOSTRAR ARREGLO DE CANCIONES
void mostrarArregloCanciones (stCancion song, int validos)
{
    printf("\t=======================================================\n");
    printf("\tID cancion: %i\n", song.idCancion);
    printf("\tTitulo: %s\n", song.titulo);
    printf("\tArtista: %s\n", song.artista);
    printf("\tDuracion: %i\n", song.duracion);
    printf("\tAnio: %i\n", song.anio);
    printf("\tGenero: %s\n", song.genero);
    printf("\tComentario: %s\n", song.comentario);
    printf("\tEliminado (1=eliminado - 0=no eliminado): %i\n", song.eliminado);
}

///ORDENAR ARREGLO POR GENERO (INSERCION)
void ordenarPorGenero (stCancion arreglo[], int validos)
{
    for(int i=0 ; i<validos-1 ; i++)
    {
        insertarDato(arreglo, i, arreglo[i+1]);
    }
}

///INSERTAR DATO
void insertarDato (stCancion arrayC[], int validos, stCancion dato)
{
    int i=validos;
    while((i>=0) && (strcmp(dato.genero, arrayC[i].genero)<0))
    {
        arrayC[i+1] = arrayC[i];
        i--;
    }
    arrayC[i+1] = dato;
}

///BUSCAR GENERO
int buscarGenero(int idUserLogeado, char genero[])
{
    stPlaylist p;
    stCancion c;
    int encontrarGenero = 0;
    FILE* archi = fopen("Playlist.bin", "rb");
    FILE* archiCanciones = fopen("Canciones.bin", "rb");
    fseek(archi,0,SEEK_SET);
    if ((archi != NULL) && (archiCanciones != NULL))
    {
        while((fread(&p, sizeof(stPlaylist), 1, archi) > 0) && (encontrarGenero ==0))
        {
            if(p.idUsuario == idUserLogeado)
            {
                fseek(archiCanciones, 0, SEEK_SET);
                while (fread(&c, sizeof(stCancion), 1, archiCanciones) > 0)
                {
                    if((strcmp(c.genero, genero) ==0) && (p.idCancion == c.idCancion))
                    {
                        encontrarGenero = 1;
                    }
                }
            }
        }
        fclose(archiCanciones);
        fclose(archi);
    }
    return encontrarGenero;
}

///MOSTRAR CANCION POR GENERO
void mostrarCancionPorGenero(char genero[])
{
    stCancion c;
    FILE* archi = fopen("Canciones.bin", "rb");
    fseek(archi, 0, SEEK_SET);
    if(archi != NULL)
    {
        while(fread(&c, sizeof(stCancion), 1, archi) > 0)
        {
            if(strcmp(c.genero, genero) == 0)
            {
                printf("\t--------------------------\n");
                printf("\tTitulo: %s\t\n", c.titulo);
                printf("\tArtista: %s\t\n", c.artista);
                printf("\tGenero: %s\t\n", c.genero);
            }
        }
        fclose(archi);
    }
}
