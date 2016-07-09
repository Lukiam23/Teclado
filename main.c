#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
    struct Nota
    {
        char nome[7];
        int frequencia;
        int oitava;
    };
    
int notaPos(char* nome, struct Nota e[48]){
		int i;
		for(i=0; i<12; i++)	{
			
			if(strcmp(e[i].nome, nome) == 0){
				return i;
			}			

		}
	
}
    
int main()
{

    int i;
    struct Nota e[48];
    
    
    strcpy(e[0].nome,"Do");
    e[0].oitava=1;
    e[0].frequencia=132;
    
    strcpy(e[1].nome,"Do#/Reb");
    e[1].oitava=1;
    e[1].frequencia=137;
    
    strcpy(e[2].nome,"Re");
    e[2].oitava=1;
    e[2].frequencia=148;
    
    strcpy(e[3].nome,"Re#/Mib");
    e[3].oitava=1;
    e[3].frequencia=154;
    
    strcpy(e[4].nome,"Mi");
    e[4].oitava=1;
    e[4].frequencia=165;
    
    strcpy(e[5].nome,"Fa");
    e[5].oitava=1;
    e[5].frequencia=175;
    
    strcpy(e[6].nome,"Fa#/Solb");
    e[6].oitava=1;
    e[6].frequencia=183;
    
    strcpy(e[7].nome,"Sol");
    e[7].oitava=1;
    e[7].frequencia=198;
    
    strcpy(e[8].nome,"Sol#/Lab");
    e[8].oitava=1;
    e[8].frequencia=206;
    
    strcpy(e[9].nome,"La");
    e[9].oitava=1;
    e[9].frequencia=220;
    
    strcpy(e[10].nome,"La#/Sib");
    e[10].oitava=1;
    e[10].frequencia=229;
    
    strcpy(e[11].nome,"Si");
    e[11].oitava=1;
    e[11].frequencia=247;

	FILE *fp, *fopen();
	
	fp = fopen("ode.txt","r");
	
	char nomeNota[7];
	int oitava;
	int tempoN;
	int t = 500;
	
	while( ( fscanf(fp, "%s %d %d\n", nomeNota, &oitava, &tempoN) ) != EOF ){
		printf("%s %d %d\n", nomeNota, oitava, tempoN);
		int pos = notaPos(nomeNota, e);
		Beep(e[pos].frequencia*pow(2,oitava),t*tempoN);
	}

}
