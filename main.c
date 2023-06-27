#include "HeaderTPfinal.h"

int main()
{
    int numPerfil;
    int numLog;
    int numLogAdmin;
    int validosUsers=0;
    int idUsuarioLogeado=0;
    int posUserLogeado=0;
    stCelda arrayUsers[DIMARRAY];
    //cargarArchivoCanciones();
    nodoListaCancion* listaCanciones = inicLista();
    nodoArbolCancion* arbolCanciones = inicArbol();
    arbolCanciones = pasarArchivoArbol(arbolCanciones);
    listaCanciones = crearListaCanciones(listaCanciones);
    validosUsers = pasarUsuarioArray(arrayUsers, validosUsers);
    for (int i=0; i<DIMARRAY; i++)
    {
        arrayUsers[i].listaCanciones = inicLista();
    }
    despersistirArchPlaylist(arrayUsers, validosUsers, arbolCanciones);
    HWND hWnd=GetConsoleWindowNT();
    MoveWindow(hWnd,350,100,650,450,TRUE);
    dibujarCuadro(0,0,76,24);
    gotoxy(20,2);
    system("COLOR B");
    dibujarCuadro(1,1,74,3);
    gotoxy(20,0);
    printf("   \n\n\t\tPor favor, ingrese el numero de su perfil\n");
    printf("\n\n\n");
    printf("\n\n\t    ===================================================\n");
    printf("\n\n\t    -- 1.Perfil Cliente ------------------------------ \n");
    printf("\n\n\t    -- 2.Perfil Administrador ------------------------ \n");
    printf("\n\n\t    ===================================================> ");
    scanf("%i", &numPerfil);
    if (numPerfil == 1)
    {
        system("cls");
        dibujarCuadro(1,1,74,3);
        gotoxy(20,2);
        printf("\t  ..::Perfil Cliente::..\n\n") ;
        printf("\n\n\t    ===================================================\n");
        printf("\n\n\t    --- 1.Registrarse ---------------------------------\n");
        printf("\n\n\t    --- 2.Login ---------------------------------------\n");
        printf("\n\n\t    ===================================================> ");
        scanf("%i", &numLog);
        system("cls");
        if (numLog ==1)
        {
            idUsuarioLogeado = registroUsuario();
            system("cls");
            validosUsers = pasarUsuarioArray(arrayUsers, validosUsers);
            userLogeado(arrayUsers, validosUsers, idUsuarioLogeado, listaCanciones, arbolCanciones, posUserLogeado);
        }
        else
        {
            if(numLog == 2)
            {
                idUsuarioLogeado = logeoUsuario(arrayUsers, validosUsers);
                userLogeado(arrayUsers, validosUsers, idUsuarioLogeado, listaCanciones, arbolCanciones, posUserLogeado);
            }
            else
            {
                printf("\n\tIngreso una opcion incorrecta");
            }
        }
    }
    else
    {
        if (numPerfil == 2)
        {
            system("cls");
            dibujarCuadro(1,1,74,3);
            gotoxy(20,2);
            printf("\t ..::Perfil Administrador::..\n\n") ;
            printf("\n\n\t    ===================================================\n");
            printf("\n\n\t    --- 1.Registrarse ---------------------------------\n");
            printf("\n\n\t    --- 2.Login ---------------------------------------\n");
            printf("\n\n\t    ===================================================> ");
            scanf("%i", &numLogAdmin);
            system("cls");
            if (numLogAdmin == 1)
            {
                registroAdmin();
                system("cls");
                adminLogeado(arrayUsers, &validosUsers, arbolCanciones, listaCanciones);
            }
            else
            {
                if (numLogAdmin == 2)
                {
                    logeoAdmin();
                    adminLogeado(arrayUsers, &validosUsers, arbolCanciones, listaCanciones);
                }
                else
                {
                    printf("\n\tIngreso una opcion incorrecta\n");
                }
            }
        }

    }
    return 0;
}

/*
void cargarArchivoCanciones ()
{
    stCancion cancion;
    FILE * fp = fopen("Canciones.bin","ab");
    if(fp != NULL)
    {
        cancion.idCancion=1; ///ver func para aunmentar i
        strcpy(cancion.titulo,"Mic Drop");
        strcpy(cancion.artista,"BTS");
        cancion.duracion=4;
        strcpy(cancion.album,"Love Yourself:Her");
        cancion.anio=2017;
        strcpy(cancion.genero,"Kpop");
        strcpy(cancion.comentario,"Buena para bailar Hip Hop");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=2;
        strcpy(cancion.titulo,"Pink Venom");
        strcpy(cancion.artista,"BlackPink");
        cancion.duracion=3;
        strcpy(cancion.album,"Born Pink");
        cancion.anio=2022;
        strcpy(cancion.genero,"Kpop");
        strcpy(cancion.comentario,"Buen comeback!");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=3;
        strcpy(cancion.titulo,"My Universe");
        strcpy(cancion.artista,"Coldplay");
        cancion.duracion=5;
        strcpy(cancion.album,"Music of the Spheres");
        cancion.anio=2021;
        strcpy(cancion.genero,"Pop");
        strcpy(cancion.comentario,"Show Galactico!");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=4;
        strcpy(cancion.titulo,"Smooth Criminal");
        strcpy(cancion.artista,"Michael Jackson");
        cancion.duracion=9;
        strcpy(cancion.album,"Bad 25");
        cancion.anio=2012;
        strcpy(cancion.genero,"Pop");
        strcpy(cancion.comentario,"Smooooth");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=5;
        strcpy(cancion.titulo,"Overprotected");
        strcpy(cancion.artista,"Britney Spears");
        cancion.duracion=4;
        strcpy(cancion.album,"Britney");
        cancion.anio=2001;
        strcpy(cancion.genero,"Pop");
        strcpy(cancion.comentario,"Free Britney!");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=6;
        strcpy(cancion.titulo,"A Place Where You Belong");
        strcpy(cancion.artista,"Bullet For My Valentine");
        cancion.duracion=5;
        strcpy(cancion.album,"Fever");
        cancion.anio=2010;
        strcpy(cancion.genero,"Metal");
        strcpy(cancion.comentario,"Muy buena");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=7;
        strcpy(cancion.titulo,"Sonne");
        strcpy(cancion.artista,"Rammstein");
        cancion.duracion=4;
        strcpy(cancion.album,"Mutter");
        cancion.anio=2001;
        strcpy(cancion.genero,"Metal");
        strcpy(cancion.comentario,"Muy buena");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=8;
        strcpy(cancion.titulo,"Master of Puppets");
        strcpy(cancion.artista,"Metallica");
        cancion.duracion=8;
        strcpy(cancion.album,"Master of Puppets");
        cancion.anio=1986;
        strcpy(cancion.genero,"Metal");
        strcpy(cancion.comentario,"Obey your master!");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=9;
        strcpy(cancion.titulo,"Somewhere I Belong");
        strcpy(cancion.artista,"Linkin Park");
        cancion.duracion=4;
        strcpy(cancion.album,"Meteora");
        cancion.anio=2003;
        strcpy(cancion.genero,"Metal");
        strcpy(cancion.comentario,"R.I.P Chester");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=10;
        strcpy(cancion.titulo,"Bohemian Rhapsody");
        strcpy(cancion.artista,"Queen");
        cancion.duracion=6;
        strcpy(cancion.album,"A Night at the Opera");
        cancion.anio=1975;
        strcpy(cancion.genero,"Rock");
        strcpy(cancion.comentario,"Obra maestra!");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=11;
        strcpy(cancion.titulo,"Too Many Tears");
        strcpy(cancion.artista,"Whitesnake");
        cancion.duracion=5;
        strcpy(cancion.album,"Restless Heart");
        cancion.anio=1997;
        strcpy(cancion.genero,"Rock");
        strcpy(cancion.comentario,"Clasico");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=12;
        strcpy(cancion.titulo,"Hey You");
        strcpy(cancion.artista,"Pink Floyd");
        cancion.duracion=5;
        strcpy(cancion.album,"The wall");
        cancion.anio=1979;
        strcpy(cancion.genero,"Rock");
        strcpy(cancion.comentario,"Muy buena");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=13;
        strcpy(cancion.titulo,"A Place Where You Belong");
        strcpy(cancion.artista,"Bullet For My Valentine");
        cancion.duracion=5;
        strcpy(cancion.album,"Fever");
        cancion.anio=2010;
        strcpy(cancion.genero,"Metal");
        strcpy(cancion.comentario,"Muy buena");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=14;
        strcpy(cancion.titulo,"SG");
        strcpy(cancion.artista,"Dj Snake, Ozuna Megan Thee Stalion y LISA");
        cancion.duracion=4;
        strcpy(cancion.album,"Carte Blanche");
        cancion.anio=2021;
        strcpy(cancion.genero,"Reggaeton");
        strcpy(cancion.comentario,"Pegadiza");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);

        cancion.idCancion=15;
        strcpy(cancion.titulo,"Llamado de Emergencia");
        strcpy(cancion.artista,"Daddy Yankee");
        cancion.duracion=5;
        strcpy(cancion.album,"Talento de Barrio");
        cancion.anio=2008;
        strcpy(cancion.genero,"Reggaeton");
        strcpy(cancion.comentario,"Muy buena");
        cancion.eliminado = 0;
        fwrite(&cancion,sizeof(stCancion),1,fp);
    }
    fclose(fp);
}
*/
