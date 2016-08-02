#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>

struct Nota /*O registro quardar informaacoes das notas como o nome, a frequencia e a oita a qual ela pertence*/
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
int elevar(struct Nota elemento,int oitava)/*Essa funcao transpoe uma frequencia para uma outra oitava ex: La 220 => La 440*/
{
	 int resultado = elemento.frequencia*pow(2, oitava);
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
	for(count=0; count<8; count++)
	{
		printf("%s\n",vetor[count].nome);
	}
};
int notaPos(char* nome, struct Nota *e){ /*A funcao recebe o nome,a oitava e um vetor de Notas e retorna a posicao da nota no vetor*/
		int i;
		for(i=0; i<12; i++)	{ /*A funcao vai pecorrer a primeira oitava e verificar se os nomes sao iguais, se forem ele retorna a posicao da nota no vetor*/
			
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

void playCromatica(struct Nota *vetor, int t)
{
	int c;
	for(c=0; c<12; c++)/*Toca de forma crescente a escala cromatica*/
	{
		int frequencia = elevar(vetor[c],2);
		printf("%s %d \n", vetor[c].nome,2);
		Beep(frequencia,t);
	}
	
	if(c==12){
		int frequencia = elevar(vetor[0],3);
		printf("%s %d \n", vetor[0].nome,3);
		Beep(frequencia,t);
	}
	
	for(c=11; c>=0; c--)/*Toca de forma descrescente a escala cromatica*/
	{
		int frequencia = elevar(vetor[c],2);
		printf("%s%d\n",vetor[c].nome,2);
		Beep(frequencia,t);

	}
};
void playNatural(struct Nota *vetor,int t)
{
	int i,c, pos;
	int oitava = 2;
	struct Nome notas[7] = {"Do","Re","Mi","Fa","Sol","La","Si"};
	
	/*Toca de forma crescente EX: Do,Re,Mi...,Do*/
	for(i=0; i<7; i++){/* Percorrendo a estrutura Notas com o nome das notas definidas */
		pos = notaPos(notas[i].nome, vetor);/*Aqui ele passa para pos a  posicao da nota, mas essa posicao eh apenas da primeira oitava*/
		printf("%s %d %d\n",vetor[pos].nome, oitava+1 , elevar(vetor[pos],oitava));
		Beep(elevar(vetor[pos],oitava),t);/*Ele passa para o Beep a frequencia e o tempo, ele pega a frequencia da nota na primera oitava e transpoe pelo valor da oitava recebida*/	
	}
	
	if( i == 7){
		printf("%s %d %d\n",vetor[0].nome, 3 , elevar(vetor[0],3));
		Beep(elevar(vetor[0],3),t);
	}
	
	/*Toca de forma decrescente Ex: Do,Si,La,...,Do*/	
	for (i = 6; i >= 0; i--){
		pos = notaPos(notas[i].nome, vetor);/*Aqui ele passa para pos a  posicao da nota, mas essa posicao eh apenas da primeira oitava*/
		printf("%s %d %d\n",vetor[pos].nome, oitava+1 , elevar(vetor[pos],oitava));
		Beep(elevar(vetor[pos],oitava),t);/*Ele passa para o Beep a frequencia e o tempo, ele pega a frequencia da nota na primera oitava e transpoe pelo valor da oitava recebida*/	
	}
	
}

void playIntervalo(struct Nota *vetor, struct intervalo *intervalos, int t){
	int posicao_aleatoria, pos;
	float semitons;
	char nome[10], input[10];
	
	srand((unsigned)time(NULL));
	posicao_aleatoria =  1 + ( rand() % 7 );/*Gera um numero aleatorio*/
	semitons = posicao_aleatoria/2.0;/*Mostra quantos semitons a nota subiu*/
	pos = search(intervalos, semitons);/*Procura no vetor de intervalos qual intervalo eh compativel com o numero de semitons*/
			
	strcpy(nome,intervalos[pos].nome);/*Passa para variavel nome o nome do intervalo (2m, 2M etc)*/
	Beep(elevar(vetor[0],2),t*3);/*Toca o Do com frequencia igual a 264, pois o de 132 eh muito baixo*/
	Beep(elevar(vetor[posicao_aleatoria],2),t*3);/*Pega a nota na primeira oitava e a transpoe para a proxima oitava */
	
	printf("As opcoes sao:\n");
	printarvetor(intervalos);/*Mostra ao usuario as opcoes que tem*/
	while(strcmp(input, nome) != 0)/*Enquanto a entrada do usuario nao for igual a  variavel nome ele ficara no loop*/
	{
		printf("Digite o seu palpite: ");
		scanf("%s",&input);
		if(strcmp(input,"replay")==0)/*Faz com que as notas sejam tocadas novamente*/
		{
			Beep(vetor[0].frequencia*pow(2,2),t*3);
			Beep(vetor[posicao_aleatoria].frequencia*pow(2,2),t*3);
		}
	}
	Beep(elevar(vetor[9],2),t/2);/*Efeito besta de vitoria*/
	Beep(elevar(vetor[10],2),t/2);/*Efeito besta de vitoria*/
	printf("\nIsso foi uma %s\n", nome);
	printf("A primeira nota tocada foi um Do4 e a segunda nota tocada foi %s %d\n",vetor[posicao_aleatoria].nome,vetor[posicao_aleatoria].oitava*2);
	
};

int main()
{

    int i;
    struct Nota vetorNotas[48];
    
    addNotas("Do",1,132,vetorNotas,0);
    addNotas("Do#/Reb",1,137,vetorNotas,1);
    addNotas("Re",1,148,vetorNotas,2);
    addNotas("Re#/Mib",1,154,vetorNotas,3);
    addNotas("Mi",1,165,vetorNotas,4);
    addNotas("Fa",1,175,vetorNotas,5);
    addNotas("Fa#/Solb",1,183,vetorNotas,6);
    addNotas("Sol",1,198,vetorNotas,7);
    addNotas("Sol#/Lab",1,206,vetorNotas,8);
    addNotas("La",1,220,vetorNotas,9);
    addNotas("La#/Sib",1,229,vetorNotas,10);
    addNotas("Si",1,247,vetorNotas,11);

	FILE *fp;
	
	fp = fopen("ode.txt","r");
	
	char nomeNota[7];
	int oitava;
	int tempoN;
	int t = 500;
	int escolha;
	escolha=0;
	
	struct intervalo intervalos[10];
	addinter("1M",intervalos,0.0,0);
	addinter("2m",intervalos,0.5,1);
	addinter("2M",intervalos,1.0,2);
	addinter("3m",intervalos,1.5,3);
	addinter("3M",intervalos,2.0,4);
	addinter("4J",intervalos,2.5,5);
	addinter("4Aum",intervalos,3.0,6);
	addinter("5J",intervalos,3.5,7);
	
	
	int condicao = 1;
	
	while(condicao)
	{
		char escolha[1];
		
		printf("\n\nFaca a sua escolha:\n1.Tocar Ode a alegria\n2.Advinhar intervalo\n3.Tocar escala cromatica\n4.Tocar a escala natural\n5.Afinacao\n9.Sair\n");
		printf("Digite a sua escolha: ");
		scanf("%s",&escolha);	
		
		if(strcmp(escolha, "1") == 0){
			while( ( fscanf(fp, "%s %d %d\n", nomeNota, &oitava, &tempoN) ) != EOF ){
				/*Quando o programa ler o aruivo ele vai procurar pelo o nome da nota, a oitava e o tempo*/
				printf("%s %d %d\n", nomeNota, oitava, tempoN);
				int pos = notaPos(nomeNota, vetorNotas);/*Aqui ele passa para pos a  posicao da nota, mas essa posicao eh apenas da primeira oitava*/
				Beep(elevar(vetorNotas[pos],oitava),t*tempoN);/*Ele passa para o Beep a frequencia e o tempo, ele pega a frequencia da nota na primera oitava e transpoe pelo valor da oitava recebida*/	
			}
			
		}else if(strcmp(escolha, "2") == 0){
			playIntervalo(vetorNotas,intervalos,t);
			
		}else if(strcmp(escolha, "3") == 0){
			playCromatica(vetorNotas,t);
			
		}else if(strcmp(escolha, "4") == 0){
			playNatural(vetorNotas,t);
			
		}else if(strcmp(escolha, "5") == 0){
			int pos = notaPos("La",vetorNotas);
			int frequencia = elevar(vetorNotas[pos],1);
			printf("%s %d",vetorNotas[pos].nome,frequencia);
			Beep(frequencia,t*3);
			
		}else if(strcmp(escolha, "9") == 0){
			condicao = 0;
			
		}else{
			printf("\n Escolha incorreta! Tente novamente.");
			
		}
	}
	
}
