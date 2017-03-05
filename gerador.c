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

void drawCone(float radius, float height, int slices, int stacks, char* filename)
{
    float doisPi = 2*M_PI, slice = doisPi/slices;
    float stack = height/stacks;
    float raio = radius/stacks;
    int nPontos = slices*3 + 2*slices*stacks*3;
    
    FILE* f;
    f = fopen(filename,"w");
    
    if(f!=NULL)
    {
        fprintf(f,"%d\n",nPontos);
        
        for(int i=0; i < slices; i++)
        {
            fprintf(f,"%f,%f,%f,%f,%f,%f,%f,%f;\n",0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.5, 0.5);
            fprintf(f,"%f,%f,%f,%f,%f,%f,%f,%f;\n",sin((i+1)*slice)*radius, 0.0, cos((i+1)*slice)*radius, 0.0, -1.0, 0.0, ((i+1)*slice)/doisPi, 0.0);
            fprintf(f,"%f,%f,%f,%f,%f,%f,%f,%f;\n",sin(i*slice)*radius, 0.0, cos(i*slice)*radius, 0.0, -1.0, 0.0, (i*slice)/doisPi, 0.0);
        }
        
        float r = 0;
        for(int j=0; j < stacks; j++)
        {
            for(int i=0; i < slices; i++)
            {
                double p1[3] = { sin(i*slice)*(radius-(r+raio)), (j+1)*stack, cos(i*slice)*(radius-(r+raio)) };
                double p2[3] = { sin(i*slice)*(radius-r), j*stack, cos(i*slice)*(radius-r) };
                double p3[3] = { sin((i+1)*slice)*(radius-r), j*stack, cos((i+1)*slice)*(radius-r) };
                double p4[3] = { sin((i+1)*slice)*(radius-(r+raio)), (j+1)*stack, cos((i+1)*slice)*(radius-(r+raio)) };
                
                double *n1 = normal(p1,p2,p3);
                double *n2 = normal(p2,p3,p1);
                double *n3 = normal(p3,p1,p2);
                
                double *n4 = normal(p1,p3,p4);
                double *n5 = normal(p3,p4,p1);
                double *n6 = normal(p4,p1,p3);

                fprintf(f,"%f,%f,%f,%f,%f,%f,%f,%f;\n",p1[0],p1[1],p1[2],n1[0],n1[1],n1[2], (i*slice)/doisPi, -((j+1)*stack)/height); //p1
                fprintf(f,"%f,%f,%f,%f,%f,%f,%f,%f;\n",p2[0],p2[1],p2[2],n2[0],n2[1],n2[2], (i*slice)/doisPi, -(j*stack)/height); //p2
                fprintf(f,"%f,%f,%f,%f,%f,%f,%f,%f;\n",p3[0],p3[1],p3[2],n3[0],n3[1],n3[2], ((i+1)*slice)/doisPi, -(j*stack)/height); //p3
                
                fprintf(f,"%f,%f,%f,%f,%f,%f,%f,%f;\n",p1[0],p1[1],p1[2],n4[0],n4[1],n4[2], (i*slice)/doisPi, -((j+1)*stack)/height); //p1
                fprintf(f,"%f,%f,%f,%f,%f,%f,%f,%f;\n",p3[0],p3[1],p3[2],n5[0],n5[1],n5[2], ((i+1)*slice)/doisPi, -(j*stack)/height); //p3
                fprintf(f,"%f,%f,%f,%f,%f,%f,%f,%f;\n",p4[0],p4[1],p4[2],n6[0],n6[1],n6[2], ((i+1)*slice)/doisPi, -((j+1)*stack)/height); //p4
            }
            r += raio;
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
            float length = atof(argv[2]);
            float width = atof(argv[3]);
            drawPlano(length, width, argv[4]);
        }
    }
    
    else if(!strcmp(argv[1],"paralelipipedo"))
    {
        if(argc!=6) { printf("ERRO Formato: 'paralelipipedo' <comprimento> <altura> <largura> <nome do ficheiro>\n"); exit(0); }
        else
        {
            float length = atof(argv[2]);
            float height = atof(argv[3]);
            float width = atof(argv[4]);
            drawParalelipipedo(length, height, width, argv[5]);
        }
    }
    return 0;

    else if(!strcmp(argv[1],"cone"))
    {
        if(argc!=7) { printf("ERRO Formato: 'cone' <raio> <altura> <fatias> <camadas> <nome do ficheiro>\n"); exit(0); }
        else
        {
            float radius = atof(argv[2]);
            float height = atof(argv[3]);
            int slices = atoi(argv[4]);
            int stacks = atoi(argv[5]);
            drawCone(radius, height, slices, stacks, argv[6]);
        }
    }
}


