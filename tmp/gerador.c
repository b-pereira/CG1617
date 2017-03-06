//
//  main.c
//  Projecto
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void drawPlano ( float length, float width, char *filename )
{   FILE *f;
    f = fopen ( filename,"w" );

    if ( f!=NULL )
    {   //face superior
        fprintf ( f,"%f,%d,%f ; ",-length/2, 0, -width/2 ); 	 //D
        fprintf ( f,"%f,%d,%f ; ",-length/2, 0, width/2 );		//A
        fprintf ( f,"%f,%d,%f\n",length/2, 0, width/2 );		//B
        fprintf ( f,"%f,%d,%f ; ",length/2, 0, width/2 );		//B
        fprintf ( f,"%f,%d,%f ; ",length/2, 0, -width/2 );		//C
        fprintf ( f,"%f,%d,%f\n",-length/2, 0, -width/2 );		//D
        //Face inferior
        fprintf ( f,"%f,%d,%f ; ",length/2, 0, width/2 );		//B
        fprintf ( f,"%f,%d,%f ; ",-length/2, 0, width/2 );		//A
        fprintf ( f,"%f,%d,%f\n",-length/2, 0, -width/2 ); 	 //D
        fprintf ( f,"%f,%d,%f ; ",-length/2, 0, -width/2 );		//D
        fprintf ( f,"%f,%d,%f ; ",length/2, 0, -width/2 );		//C
        fprintf ( f,"%f,%d,%f\n",length/2, 0, width/2 );		//B
    }

    fclose ( f );
}


void drawParalelipipedo ( float length, float height, float width, char *filename )
{   FILE *f;
    f = fopen ( filename,"w" );

    if ( f!=NULL )
    {   //face inferior vista para baixo
        fprintf ( f,"%f,%f,%f ; ",length/2, -height/2, -width/2 ); 	//C1
        fprintf ( f,"%f,%f,%f ; ",-length/2, -height/2, width/2 );	 //A1
        fprintf ( f,"%f,%f,%f\n",-length/2, -height/2, -width/2 );	 //D1
        fprintf ( f,"%f,%f,%f ; ",-length/2, -height/2, width/2 );	//A1
        fprintf ( f,"%f,%f,%f ; ",length/2, -height/2, -width/2 );	//C1
        fprintf ( f,"%f,%f,%f\n",length/2, -height/2, width/2 );	//B1
        //face superior vista para cima
        fprintf ( f,"%f,%f,%f ; ",length/2, height/2, -width/2 );	//C2
        fprintf ( f,"%f,%f,%f ; ",-length/2, height/2, -width/2 );	//D2
        fprintf ( f,"%f,%f,%f\n",-length/2, height/2, width/2 );	//A2
        fprintf ( f,"%f,%f,%f ; ",-length/2, height/2, width/2 );	//A2
        fprintf ( f,"%f,%f,%f ; ",length/2, height/2, width/2 );	//B2
        fprintf ( f,"%f,%f,%f\n",length/2, height/2, -width/2 );	//C2
        //face lateral prependicular ao eixo zz (lado positivo) vista para fora
        fprintf ( f,"%f,%f,%f ; ",-length/2, -height/2, width/2 );	//A1
        fprintf ( f,"%f,%f,%f ; ",length/2, -height/2, width/2 );	//B1
        fprintf ( f,"%f,%f,%f\n",-length/2, height/2, width/2 );	//A2
        fprintf ( f,"%f,%f,%f ; ",length/2, -height/2, width/2 );	//B1
        fprintf ( f,"%f,%f,%f ; ",length/2, height/2, width/2 );	//B2
        fprintf ( f,"%f,%f,%f\n",-length/2, height/2, width/2 );	//A2
        //face lateral prependicular ao eixo xx (lado positivo) vista para fora
        fprintf ( f,"%f,%f,%f ; ",length/2, -height/2, width/2 );	//B1
        fprintf ( f,"%f,%f,%f ; ",length/2, -height/2, -width/2 );	//C1
        fprintf ( f,"%f,%f,%f\n",length/2, height/2, width/2 );	//B2
        fprintf ( f,"%f,%f,%f ; ",length/2, -height/2, -width/2 );	//C1
        fprintf ( f,"%f,%f,%f ; ",length/2, height/2, -width/2 );	//C2
        fprintf ( f,"%f,%f,%f\n",length/2, height/2, width/2 );	//B2
        //face lateral perpendicular ao eixo zz (lado negativo) vista para tras LHS
        fprintf ( f,"%f,%f,%f ; ",length/2, -height/2, -width/2 );	//C1
        fprintf ( f,"%f,%f,%f ; ",-length/2, -height/2, -width/2 );	//D1
        fprintf ( f,"%f,%f,%f\n",length/2, height/2, -width/2 );	//C2
        fprintf ( f,"%f,%f,%f ; ",-length/2, -height/2, -width/2 );	//D1
        fprintf ( f,"%f,%f,%f ; ",-length/2, height/2, -width/2 );	//D2
        fprintf ( f,"%f,%f,%f\n",length/2, height/2, -width/2 );	//C2
        //face lateral perpedicular ao eixo xx(lado negativo) vista para tras lhs
        fprintf ( f,"%f,%f,%f ; ",-length/2, -height/2, -width/2 );	//D1
        fprintf ( f,"%f,%f,%f ; ",-length/2, -height/2, width/2 );	//A1
        fprintf ( f,"%f,%f,%f\n",-length/2, height/2, -width/2 );	//D2
        fprintf ( f,"%f,%f,%f ; ",-length/2, -height/2, width/2 );	//A1
        fprintf ( f,"%f,%f,%f ; ",-length/2, height/2, width/2 );	//A2
        fprintf ( f,"%f,%f,%f\n",-length/2, height/2, -width/2 );	//D2
    }

    fclose ( f );
}

void drawEsfera ( float radius, int slices, int stacks )
{   double step_theta = 360/ ( slices + 1 );
    double step_phi = 180/ ( stacks + 1 );

    for ( int i = 0; i < ( slices + 1 ); i++ )
    {
    }
}

int main ( int argc, char *argv[] )
{   if ( argc <= 1 )
    {   printf ( "ERRO Opções: plano | paralelipipedo\n" );
    }

    else if ( !strcmp ( argv[1],"plano" ) )
    {   if ( argc!=5 )
        {   printf ( "Parâmetros errados! Formato: 'plano' <comprimento> <largura> <nome_ficheiro>\n" );
        }

        else
        {   float length = atof ( argv[2] );
            float width = atof ( argv[3] );
            drawPlano ( length, width, argv[4] );
        }
    }

    else if ( !strcmp ( argv[1],"box" ) )
    {   if ( argc!=6 )
        {   printf ( "Parâmetros errados! Formato: 'paralelipipedo' <comprimento> <altura> <largura> <nome_ficheiro>\n" );
            exit ( 0 );
        }

        else
        {   float length = atof ( argv[2] );
            float height = atof ( argv[3] );
            float width = atof ( argv[4] );
            drawParalelipipedo ( length, height, width, argv[5] );
        }
    }

    return 0;
}


