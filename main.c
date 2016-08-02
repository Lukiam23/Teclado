#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>
struct Nota /*O registro quardarÃƒÂ¡ informaÃƒÂ§ÃƒÂµes das notas como o nome, a frequencia e a oita a qual ela pertence*/
{
    char nome[7];
    int frequencia;
    int oitava;
};
struct intervalo
{
    char nome[10];
    float tom;
};
struct Nome
{
	char *nome;
};
int elevar(struct Nota elemento,int oitava)/*Essa funÃ§Ã£o transporÃ¡ uma frequÃªncia para uma outra oitava ex: LÃ¡ 220 => LÃ¡ 440*/
{
	 int resultado = elemento.frequencia*pow(2,oitava);
	 return resultado;
}
void addinter(char *str,struct intervalo *vetor,float valor,int pos)
{
	strcpy(vetor[pos].nome,str);
	vetor[pos].tom=valor;
};
int search(struct intervalo *vetor, float value)
{
	int i = 0;
	while(vetor[i].tom!=value)
	{
		i++;
	}
	return i;
};
void printarvetor(struct intervalo *vetor)
{
	int count;
	for(count=0; count<7; count++)
	{
		printf("%s\n",vetor[count].nome);
	}
};
int notaPos(char* nome, struct Nota *e){ /*A funÃƒÂ§ÃƒÂµa recebe o nome,a oitava e um vetor de Notas e retorna a posiÃƒÂ§ÃƒÂ£o da nota no vetor*/
		int i;
		for(i=0; i<12; i++)	{ /*A funÃƒÂ§ÃƒÂ£o vai pecorrer a primeira oitava e verificar se os nomes sÃƒÂ£o iguais, se forem ele retorna a posiÃƒÂ§ÃƒÂ£o da nota no vetor*/
			
			if(strcmp(e[i].nome, nome) == 0){
				return i;
			}			

		}
	
}
void addNotas(char *nome, int oitava, int frequencia, struct Nota *vetor, int pos)
{
	strcpy(vetor[pos].nome,nome);
	vetor[pos].oitava=oitava;
	vetor[pos].frequencia=frequencia;
}

void play(struct Nota *vetor, int n, int t)
{
	int i,c;
	for(i=0; i<n; i++)
	{
		for(c=0; c<12; c++)
		{
			int frequencia = elevar(vetor[c],i);
			printf("%s%d\n",vetor[c].nome,i+1);
			Beep(frequencia,t);
		}
	}
};
void playN(struct Nota *vetor,int t)
{
	int i,c, pos;
	struct Nome notas[7] = {"Do","Re","Mi","Fa","Sol","La","Si"};
	for(i=0; i<=1; i++)/*Tocará de forma crescente EX: Do,Re,Mi...,Do*/
	{
		for(c=0; c<7; c++)/*Irá pecorrer o vetor com o nome das notas que queremos que sejam tocadas*/
		{
			if(i<1)/*Se o "i" for menor que 1 ele tocará a nota*/
			{
				pos = notaPos(notas[c].nome,vetor);
				printf("%s%d %d\n",vetor[pos].nome,i+2,elevar(vetor[pos],i));
				Beep(elevar(vetor[pos],i+2),t);
			}
			if(i==1)/*Se o i for igual a 1 somente o Do será tocado*/
			{
				if(strcmp(notas[c].nome,"Do")==0)
 				{
 					pos = notaPos(notas[c].nome,vetor);
 					printf("%s%d %d\n",vetor[pos].nome,i+2,elevar(vetor[pos],i));
 					Beep(elevar(vetor[pos],i+2),t);
 				}
			}
		}
		
	}
	for(i=1;i>=0;i--)/*Tocará de forma decrescente Ex: Do,Si,La,...,Do*/
	{
		for(c=6; c>=0; c--)/*Esse será o responsável por tocar as notas de forma descrescente*/
		{
			if(i<1)/*Enquanto do i for menor que 1 ele tocará as notas de morfa descrescente*/
			{
				pos = notaPos(notas[c].nome,vetor);/*REcebe a posição da nota que está no vetor de notas*/
				printf("%s%d %d\n",vetor[pos].nome,i+2,elevar(vetor[pos],i));/*Printa o nome da nota, frequência e oitava*/
				Beep(elevar(vetor[pos],i+2),t);/*Toca a nota, mas transposta, pois a primeira oitava é baixa*/
			}
			if(i==1)/*Se i for igual a 1 só o Do será tocado*/
			{
				if(strcmp(notas[c].nome,"Do")==0)
 				{
 					pos = notaPos(notas[c].nome,vetor);
 					printf("%s%d %d\n",vetor[pos].nome,i+2,elevar(vetor[pos],i));
 					Beep(elevar(vetor[pos],i+2),t);
 				}
			}
		}
	}
}
void playI(struct Nota *vetor, struct intervalo *intervalos, int t)
{
	int posicao_aleatoria, pos;
	float semitons;
	char nome[10], input[10];
	posicao_aleatoria = rand()%7;/*GerarÃ¡ um nÃºmero aleatÃ³rio*/
	semitons = posicao_aleatoria/2.0;/*MostrarÃ¡ quantos semitons a nota subiu*/
	pos = search(intervalos, semitons);/*vai procurar no vetor de intervalos qual intervalo Ã© compativel com o nÃºmero de semitons*/
			
	strcpy(nome,intervalos[pos].nome);/*Vai passar para variavel nome o nome do intervalo (2m, 2M etc)*/
	Beep(elevar(vetor[0],2),t*3);/*TocarÃ¡ o DÃ³ com frequencia igual a 264, pois o de 132 Â´2 muito baixo*/
	Beep(elevar(vetor[posicao_aleatoria],2),t*3);/*PegarÃ¡ a nota na primeira oitava e a transporÃ¡ para a prÃ³xima oitava */
	printf("As opcoes sao:\n");
	printarvetor(intervalos);/*MostrarÃ¡ ao usuÃ¡rio as opÃ§Ãµes que tem*/
	while(strcmp (input, nome) != 0)/*Enquanto a entrada do usuÃ¡rio nÃ£o for igual Ã  variÃ¡vel nome ele ficarÃ¡ no loop*/
	{
		printf("Digite o seu palpite: ");
		scanf("%s",&input);
		if(strcmp(input,"replay")==0)/*FarÃ¡ com que as notas sejam tocadas novamente*/
		{
			Beep(vetor[0].frequencia*pow(2,2),t*3);
			Beep(vetor[posicao_aleatoria].frequencia*pow(2,2),t*3);
		}
	}
	Beep(elevar(vetor[9],2),t/2);/*Efeito besta de vitÃ³ria*/
	Beep(elevar(vetor[10],2),t/2);/*Efeito besta de vitÃ³ria*/
	printf("\nIsso foi uma %s\n", nome);
	printf("A primeira nota tocada foi um Do4 e a segunda nota tocada foi %s %d\n",vetor[posicao_aleatoria].nome,vetor[posicao_aleatoria].oitava*2);
};
int main()
{

    int i;
    struct Nota e[48];
    
    addNotas("Do",1,132,e,0);
    addNotas("Do#/Reb",1,137,e,1);
    addNotas("Re",1,148,e,2);
    addNotas("Re#/Mib",1,154,e,3);
    addNotas("Mi",1,165,e,4);
    addNotas("Fa",1,175,e,5);
    addNotas("Fa#/Solb",1,183,e,6);
    addNotas("Sol",1,198,e,7);
    addNotas("Sol#/Lab",1,206,e,8);
    addNotas("La",1,220,e,9);
    addNotas("La#/Sib",1,229,e,10);
    addNotas("Si",1,247,e,11);

	FILE *fp;
	
	fp = fopen("ode.txt","r");
	
	char nomeNota[7];
	int oitava;
	int tempoN;
	int t = 500;
	int escolha;
	escolha=0;
	
	struct intervalo intervalos[10];
	addinter("2M",intervalos,1.0,1);
	addinter("2m",intervalos,0.5,0);
	addinter("3M",intervalos,2.0,3);
	addinter("3m",intervalos,1.5,2);
	addinter("4J",intervalos,2.5,4);
	addinter("5J",intervalos,3.5,6);
	addinter("4Aum",intervalos,3.0,5);
	
	int condicao = 1;
	
	while(condicao)
	{
		char escolha[1];
		
		printf("\n\nFaca a sua escolha:\n1.Tocar Ode a alegria\n2.Advinhar intervalo\n3.Tocar escala cromatica\n4.Tocar a escala natural\n5.Afinacao\n9.Sair\n");
		printf("Digite a sua escolha: ");
		scanf("%s",&escolha);	
		
		if(strcmp(escolha, "1") == 0)
		{
			while( ( fscanf(fp, "%s %d %d\n", nomeNota, &oitava, &tempoN) ) != EOF )
			{/*Quando o programa ler o aruivo ele vai procurar pelo o nome da nota, a oitava e o tempo*/
				printf("%s %d %d\n", nomeNota, oitava, tempoN);
				int pos = notaPos(nomeNota, e);/*Aqui ele passa para pos a  posiÃƒÂ§ÃƒÂ£o da nota, mas essa posiÃƒÂ§ÃƒÂ£o ÃƒÂ© apenas da primeira oitava*/
				Beep(elevar(e[pos],oitava),t*tempoN);/*ele passa para o Beep a frequencia e o tempo, ele pega a frequencia da nota na primera e transpÃƒÂµe pelo valor da oitava recebida*/	
			}
		}else if(strcmp(escolha, "2") == 0)
		{
			playI(e,intervalos,t);
		}else if(strcmp(escolha, "3") == 0)
		{
			play(e,4,t);
		}else if(strcmp(escolha, "4") == 0)
		{
			playN(e,t);
		}else if(strcmp(escolha, "5") == 0)
		{
			int pos = notaPos("La",e);
			int frequencia = elevar(e[pos],1);
			printf("%s %d",e[pos].nome,frequencia);
			Beep(frequencia,t*3);
		}else if(strcmp(escolha, "9") == 0){
			condicao = 0;
			
		}else{
			printf("\n Escolha incorreta! Tente novamente.");
		}
	}
	
}
