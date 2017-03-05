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

void drawPlano(float length, float width, char* filename)
{
    FILE* f;
    f = fopen(filename,"w");
    
    if(f!=NULL)
    {
    	//face superior
        fprintf(f,"%f,%d,%f ; ",-length/2, 0, -width/2); 	 //D
        fprintf(f,"%f,%d,%f ; ",-length/2, 0, width/2);		//A
        fprintf(f,"%f,%d,%f\n",length/2, 0, width/2);		//B
        
        fprintf(f,"%f,%d,%f ; ",length/2, 0, width/2);		//B
        fprintf(f,"%f,%d,%f ; ",length/2, 0, -width/2);		//C
        fprintf(f,"%f,%d,%f\n",-length/2, 0, -width/2);		//D

        //Face inferior
        fprintf(f,"%f,%d,%f ; ",length/2, 0, width/2);		//B
        fprintf(f,"%f,%d,%f ; ",-length/2, 0, width/2);		//A
        fprintf(f,"%f,%d,%f\n",-length/2, 0, -width/2); 	 //D

        fprintf(f,"%f,%d,%f ; ",-length/2, 0, -width/2);		//D
        fprintf(f,"%f,%d,%f ; ",length/2, 0, -width/2);		//C
        fprintf(f,"%f,%d,%f\n",length/2, 0, width/2);		//B

    }
    
    fclose(f);
}


void drawParalelipipedo(float length, float height, float width, char* filename)
{
    FILE* f;
    f = fopen(filename,"w");
    
    if(f!=NULL)
    {
    	//face inferior vista para baixo
        fprintf(f,"%f,%f,%f ; ",length/2, -height/2, -width/2); 	//C1
        fprintf(f,"%f,%f,%f ; ",-length/2, -height/2, width/2);	    //A1
        fprintf(f,"%f,%f,%f\n",-length/2, -height/2, -width/2);	    //D1
        
		fprintf(f,"%f,%f,%f ; ",-length/2, -height/2, width/2);	//A1
        fprintf(f,"%f,%f,%f ; ",length/2, -height/2, -width/2);	//C1
        fprintf(f,"%f,%f,%f\n",length/2, -height/2, width/2);	//B1
        
        
        //face superior vista para cima
        fprintf(f,"%f,%f,%f ; ",length/2, height/2, -width/2);	//C2
        fprintf(f,"%f,%f,%f ; ",-length/2, height/2, -width/2);	//D2
        fprintf(f,"%f,%f,%f\n",-length/2, height/2, width/2);	//A2
        
        fprintf(f,"%f,%f,%f ; ",-length/2, height/2, width/2);	//A2
        fprintf(f,"%f,%f,%f ; ",length/2, height/2, width/2);	//B2
        fprintf(f,"%f,%f,%f\n",length/2, height/2, -width/2);	//C2


        //face lateral prependicular ao eixo zz (lado positivo) vista para fora
        fprintf(f,"%f,%f,%f ; ",-length/2, -height/2, width/2);	//A1
        fprintf(f,"%f,%f,%f ; ",length/2, -height/2, width/2);	//B1
        fprintf(f,"%f,%f,%f\n",-length/2, height/2, width/2);	//A2
        
        fprintf(f,"%f,%f,%f ; ",length/2, -height/2, width/2);	//B1
        fprintf(f,"%f,%f,%f ; ",length/2, height/2, width/2);	//B2
        fprintf(f,"%f,%f,%f\n",-length/2, height/2, width/2);	//A2


        //face lateral prependicular ao eixo xx (lado positivo) vista para fora
        fprintf(f,"%f,%f,%f ; ",length/2, -height/2, width/2);	//B1
        fprintf(f,"%f,%f,%f ; ",length/2, -height/2, -width/2);	//C1
        fprintf(f,"%f,%f,%f\n",length/2, height/2, width/2);	//B2
        
        fprintf(f,"%f,%f,%f ; ",length/2, -height/2, -width/2);	//C1
        fprintf(f,"%f,%f,%f ; ",length/2, height/2, -width/2);	//C2
        fprintf(f,"%f,%f,%f\n",length/2, height/2, width/2);	//B2
        

        //face lateral perpendicular ao eixo zz (lado negativo) vista para tras LHS
        fprintf(f,"%f,%f,%f ; ",length/2, -height/2, -width/2);	//C1
        fprintf(f,"%f,%f,%f ; ",-length/2, -height/2, -width/2);	//D1
        fprintf(f,"%f,%f,%f\n",length/2, height/2, -width/2);	//C2
        
        fprintf(f,"%f,%f,%f ; ",-length/2, -height/2, -width/2);	//D1
        fprintf(f,"%f,%f,%f ; ",-length/2, height/2, -width/2);	//D2
        fprintf(f,"%f,%f,%f\n",length/2, height/2, -width/2);	//C2
        

        //face lateral perpedicular ao eixo xx(lado negativo) vista para tras lhs
        fprintf(f,"%f,%f,%f ; ",-length/2, -height/2, -width/2);	//D1
        fprintf(f,"%f,%f,%f ; ",-length/2, -height/2, width/2);	//A1
        fprintf(f,"%f,%f,%f\n",-length/2, height/2, -width/2);	//D2
        
        fprintf(f,"%f,%f,%f ; ",-length/2, -height/2, width/2);	//A1
        fprintf(f,"%f,%f,%f ; ",-length/2, height/2, width/2);	//A2
        fprintf(f,"%f,%f,%f\n",-length/2, height/2, -width/2);	//D2
    }
    
    fclose(f);
}

void drawCone(float raio, float altura, int slices, int stacks)
{
    double slice = (360 / slices)*(M_PI / 180);
    double stack = altura / stacks;
    double r = raio / stacks;
    double doisPI = 2 * M_PI;
    double i;
    double j;

    FILE* f;
    f = fopen(filename,"w");
    
    if(f!=NULL)
    {
        fprintf("Base Cone:\n");
        for (double i = 0; i < doisPI; i += slice)
        {
            fprintf(f,"%f,%f,%f;",0.0,0.0,0.0);
            fprintf(f,"%f,%f,%f;",(sin(i + slice)*raio, 0, cos(i + slice)*raio));
            fprintf(f,"%f,%f,%f;\n",(sin(i)*raio, 0, cos(i)*raio));
        }
        
        fprintf("Pontos desde base até ponta do cone:\n")
        for (j = 0; j < altura; j += stack) {
            for (i = 0; i < doisPi; i += slice) {
               
                fprintf(f,"%f,%f,%f;",sin(i)*(raio - (r1 + r)), j + stack, cos(i)*(raio - (r1 + r)));
                fprintf(f,"%f,%f,%f;",sin(i)*(raio - r1), j, cos(i)*(raio - r1));
                fprintf(f,"%f,%f,%f;\n",sin(i + slice)*(raio - r1), j, cos(i + slice)*(raio - r1));

                fprintf(f,"%f,%f,%f;",sin(i)*(raio - (r1 + r)), j + stack, cos(i)*(raio - (r1 + r)));
                fprintf(f,"%f,%f,%f;",sin(i + slice)*(raio - r1), j, cos(i + slice)*(raio - r1));
                fprintf(f,"%f,%f,%f;\n",sin(i + slice)*(raio - (r1 + r)), j + stack, cos(i + slice)*(raio - (r1 + r)));
            }
            r1 += r;
        }
    }
    fclose(f);
}




int main(int argc, char* argv[])
{
    if(argc <= 1) { printf("ERRO Opções: plano | paralelipipedo | cone \n"); }
    
    else if(!strcmp(argv[1],"plano"))
    {
        if(argc!=5) { printf("ERRO Formato: 'plano' <comprimento> <largura> <nome do ficheiro>\n"); }
        else
        {
            float comprimento = atof(argv[2]);
            float largura = atof(argv[3]);
            drawPlano(length, width, argv[4]);
        }
    }
    
    else if(!strcmp(argv[1],"paralelipipedo"))
    {
        if(argc!=6) { printf("ERRO Formato: 'paralelipipedo' <comprimento> <altura> <largura> <nome do ficheiro>\n"); exit(0); }
        else
        {
            float comprimento = atof(argv[2]);
            float altura = atof(argv[3]);
            float largura = atof(argv[4]);
            drawParalelipipedo(length, height, width, argv[5]);
        }
    }
    return 0;

    else if(!strcmp(argv[1],"cone"))
    {
        if(argc!=7) { printf("ERRO Formato: 'cone' <raio> <altura> <fatias> <camadas> <nome do ficheiro>\n"); exit(0); }
        else
        {
            float raio = atof(argv[2]);
            float altura = atof(argv[3]);
            int slices = atoi(argv[4]);
            int stacks = atoi(argv[5]);
            drawCone(raio, altura, slices, stacks, argv[6]);
        }
    }
}


