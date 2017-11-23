#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MAX 5500 //Valor máximo permitido de linhas

int t_vector[MAX], x_vector[MAX],y_vector[MAX],z_vector[MAX];
int nro_linhas;
double roll[MAX], pitch[MAX];

//Nesta rotina e feita a leitura do arquivo
void leitura() {
	FILE *arq;
	char line[1000];
	char* res;
	int t,x,y,z,i,j=0;
	char file[100];
	
	//arq = fopen("attitude_exam.log", "rt"); 											//Maneira rápida em direta de ser feito
	cout<<"Favor escrever o caminho para o arquivo a ser lido."<<endl;					//Maneira personalizada
	cout<<"Por exemplo: D:\\Documentos\\Desafio_HXG\\attitude_exam.log"<<endl;
	cin>>file;
	arq = fopen(file, "rt");
	
	if (arq==NULL)																//Confirma se o arquivo foi aberto ou não
        {
           cout << "Erro na abertura do arquivo!\n";
           exit(-1);
        }
     else
         cout << "Arquivo aberto com sucesso !\n";
         

	while(fgets(line,100,arq) != NULL)							//Com o arquivo aberto faz as leituras dos valores linha por linha
  {
        for (i=0 ; i<strlen(line) ; i++)						//Esta rotina retira os ";" do arquivo para simplicar no momento de obter os dados
        {
           if (line[i] == ';')
               line[i] = ' ';
        }
        sscanf(line,"%d %d %d %d",&t,&x,&y,&z); 				//Le os dados 
    
	t_vector[j]=t;												//Salva em variaveis
	x_vector[j]=x;
	y_vector[j]=y;
	z_vector[j]=z;
	j++;
	}
	nro_linhas=j;		//Salva o numero de linhas
	
	fclose(arq);  //fecha o arquivo
}

//Nesta rotina sao feitos os calculos dos angulos e salvos nos seus respectivos vetores
void calculo(){
	int i;
	
	for (i=0; i<=nro_linhas;i++){
		pitch[i] = atan((-x_vector[i])/(sqrt(pow(y_vector[i],2)+pow(z_vector[i],2))));
		roll[i]= atan2(y_vector[i],z_vector[i]);
	}
}

//Nesta rotina e feita a escrita no arquivo de saida
void escrita(){
	int x,y;
	char file[100];
	char file_adress[100];
		cout<<"Favor digitar o caminho onde deseja salvar o arquivo junto com o nome"<<endl;
		cout<<"Por exemplo: D:\\Documentos\\Desafio_HXG\\angulos.log"<<endl;
		cin>>file_adress;

        FILE *arq;
        sprintf(file, file_adress);      	//esta criando o arquivo
        arq = fopen(file, "w");             //informa que sera escrito no arquivo
        
        fprintf(arq, "Time \t Roll \t Pitch\n");
        for (x=0;x<nro_linhas;x++)
            fprintf(arq, "%d; %lf; %lf \n", t_vector[x],roll[x],pitch[x]);
        cout<<"Foi salvo o arquivo no caminho:"<<file_adress<<endl;
}
int main()
{
	leitura();
	calculo();
	escrita();
	system("pause");
	return 0;
}
