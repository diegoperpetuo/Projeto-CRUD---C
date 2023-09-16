/* Caro futuro desenvolvedor que pegar este c�digo...
   Toda nossa mente e toda a nossa alma foi posta neste trabalho
   Ent�o, pedimos encarecidamente, n�o copie
   Ele est� com toda a cara de um estudante que s� queria f�rias
   
   Desde j�, agrade�emos: Th�o e Diego*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#define DATA_FILENAME "C:\\Users\\User\\Desktop\\projeto\\Dados\\Funcionarios.txt"
#define TMPDATA_FILENAME "C:\\Users\\User\\Desktop\\projeto\\Dados\\FuncionariosTemporarios.txt"

typedef struct cadastro{ //struct do cadastro
	char nome[50];
	int matricula;
	float sal;
} form;

int repetir(){  //fun��o para caso o usu�rio queira continuar no c�digo
	fflush(stdin);
	int tecla;

	printf("\n###################################\n\n");
	printf("Digite 1 para continuar.\n");
	printf("Digite 2 para sair.\n\n");
	tecla=getchar();

	if(tecla == 49){ //caso tecle 1 (ascii=49), continua no c�digo
		system("cls");
		return 1;
	}
}

void titulo(){ //fun��o para t�tulo do gerenciamento (n�o � muito importante)
	printf("***GERENCIAMENTO DE FUNCION�RIOS***");
	printf("\n\n");
}

void inicial(){ //fun��o que inicia o c�digo, aqui onde tudo ocorre
	int op;
	char tecla;
	float soma=0;
	int i=0;
	int matricula;

	do{
		printf("***GERENCIAMENTO DE FUNCION�RIOS***\n");
		printf("1) Novo funcion�rio\n");
		printf("2) Mostrar lista de funcion�rios\n");
		printf("3) Remover funcion�rio do sistema\n");
		printf("4) Alterar informa��es de um funcion�rio\n");
		printf("5) Sair\n\n");
		printf("Digite a a��o que queira realizar: ");
		scanf("%d",&op);
		fflush(stdin);
		printf("\n");

		switch(op){
			case 1: //novo funcion�rio
				system("cls");
				novo();
			break;
			case 2: //mostrar lista de funcion�rios
				system("cls");
				listar();
			break; 
			case 3: //remover funcionario
				system("cls");
				excluir();
			break;
			case 4: //alterar informa��es
				system("cls");
				alterar();
			break;
			case 5: //sair
				printf("Tchau =(");
				exit(0);
			break;
			default:
				system("cls");
		}
	}while(op > 6 && printf("Op��o inv�lida\n\n"));
}

int acha(int *matricula){ //fun��o para achar a matr�cula, relacionada aos cadastros dos funcion�rios
	form Dados;
	FILE *arq;
	arq=fopen(DATA_FILENAME,"r");
	rewind(arq);

	if(arq==NULL){
		printf("Erro ao abrir o arquivo.\n\n");
	}

	while(fread(&Dados,sizeof(Dados),1,arq)!=0){ //ler o arquivo e achar *matricula que recebe Dados.matricula
		if(*matricula == Dados.matricula){
			return 1;
		}
	}
	fclose(arq);
}

int valida(int *matricula){ //fun��o para validar a matricula dentro do arquivo
	form Dados;
	FILE *arq;
	int total=0;
	arq=fopen(DATA_FILENAME,"r");
	rewind(arq);

	if(arq == NULL){
		printf("Erro ao abrir o arquivo.\n");
	}

	while(fread(&Dados,sizeof(Dados),1,arq)!=0){
		if(*matricula == Dados.matricula){
			printf("Matr�cula j� cadastrada. Crie um novo registro.\n");
			return 1;
		}
	}
	fclose(arq);
}

int percorre(){ //fun��o qualquer, esque�a essa maluquice
	form Dados;
	FILE *arq;
	int total = 0;
	arq = fopen(DATA_FILENAME,"r");
	rewind(arq);

	while(fread(&Dados,sizeof(Dados),1,arq) != 0){
		total++;
	}

	return total;
}

int novo(){  //fun��o para criar novo registro
	form Dados;
	FILE *arq;
	int total=0;
	arq=fopen(DATA_FILENAME,"a+");

	titulo();
	printf("***REGISTRO NOVO FUNCION�RIO***\n\n");
	printf("Checando mem�ria...\n");
	sleep(1);
	printf("Criando arquivo...\n\n");
	sleep(1);

	do{	
		printf("Matr�cula: ");
		scanf("%d",&Dados.matricula);
	}while(valida(&Dados.matricula)==1); //chama fun��o para validar matricula no arquivo
		fflush(stdin);
		printf("Nome: ");
		gets(Dados.nome);
		fflush(stdin);
		printf("Sal�rio: R$ ");
		scanf("%f",&Dados.sal);
		fflush(stdin);
		printf("|-----------------------------------------------|\n\n");

		if(arq==NULL){ //caso n�o consiga criar o arquivo
			printf("Erro ao criar o arquivo.\n");
		}

		fwrite(&Dados,sizeof(Dados),1,arq); //escreve as coisas que o usu�rio digitou no arquivo

		if(fclose(arq)==0){ //caso consiga fechar o arquivo
			printf("Funcion�rio cadastrado com sucesso =D\n\n");
		}
		else{ //caso n�o
			printf("Problemas ao salvar o arquivo\n\n");
		}

		if(repetir()==1){ //if que chama fun��o para repetir a tela inicial
			inicial();
		}
}

int listar(){ //fun��o que lista os funcion�rios
	fflush(stdin);
	FILE *arq;
	form Dados;
	int reg = 0;
	float soma = 0;
	arq=fopen(DATA_FILENAME,"r");
	rewind(arq);

	if(arq==NULL){
		printf("Erro ao abrir o arquivo.");
	}

	titulo();
	printf("LISTAR\n\n");
	printf("MATR�CULA\tNOME\tSAL�RIO\n");

	while(fread(&Dados,sizeof(Dados),1,arq)!=0){
		printf("%d\t\t%s\t%.2f\n\n",Dados.matricula,Dados.nome,Dados.sal);
		printf("-------------------------------------------\n");
		reg++; //incrementa registros
		soma+=Dados.sal; //incrementa o sal�rio, fazendo a soma dos sal�rios registrados
	}

	printf("Total de registros: %d\tTotal de Sal�rios: R$ %.2f\n",reg,soma); //mostra o total de registros e sal�rios

	fclose(arq); //fecha arquivo

	if(repetir()==1){
		inicial();
	}
}

void excluirv(){ //fun��o que faz o trabalho sujo ao excluir
	form Dados;
	FILE *arq;
	arq=fopen(DATA_FILENAME,"w+");

	if(arq==NULL){
		printf("\nArquivo Funcionario.txt n�o pode ser aberto.\n");
	}

	FILE *temp;
	temp=fopen(TMPDATA_FILENAME,"a+");

	if(temp==NULL){
		printf("\nArquivo Funcionario.txt n�o pode ser aberto.\n");
	}

	while(fread(&Dados,sizeof(Dados),1,temp)!=0){
		fwrite(&Dados,sizeof(Dados),1,arq);
	}

	fclose(arq);
	fclose(temp);
}

int excluir(){ //fun��o que esconde o trabalho sujo
	FILE *arq;
	FILE *temp;
	arq=fopen(DATA_FILENAME,"a+");
	temp=fopen(TMPDATA_FILENAME,"a+");
	form Dados;
	int matricula;
	rewind (arq);

	if (arq == NULL){
		printf("Erro ao abrir o arquivo.\n\n");
	}

	titulo();
	printf("Matr�cula: ");
	scanf("%d",&matricula);

	if(acha(&matricula)==0){ //caso n�o encontre a matr�cula
		printf("Matr�cula n�o encontrada.\n\n");

		if(repetir()==1){
			inicial();
		}
	}

	while(fread(&Dados,sizeof(Dados),1,arq)!=0){ //while para ler o arquivo em busca da matricula
		if(Dados.matricula != matricula){
			fwrite(&Dados,sizeof(Dados),1,temp);
		}
	}

	fclose(arq);
	fclose(temp);

	excluirv(); //chama trabalho sujo
	remove(TMPDATA_FILENAME); //exclui registros tempor�rios
	printf("Excluido com sucesso.\n");

	if(repetir()==1){
		inicial();
	}
}

int alterar(){ //fun��o para modificar as informa��es do registro
	FILE *arq;
	FILE *temp;
	form Dados;
	int matricula;

	arq=fopen(DATA_FILENAME,"a+");
	temp=fopen(TMPDATA_FILENAME,"a+");

	titulo();
	alt_a(matricula); //fun��o que faz o trabalho sujo na hora de alterar
	printf("Confirme o n�mero da matr�cula: ");
	scanf("%d",&Dados.matricula);

	printf("\n\n");
	sleep(1);
	printf("Abrindo registro...\n\n");
	sleep(1);
	printf("Matr�cula: %d\n",Dados.matricula);
	printf("Novo nome: ");
	fflush(stdin);
	gets(Dados.nome);
	printf("Novo sal�rio: R$ ");
	fflush(stdin);
	scanf("%f",&Dados.sal);
	printf("|-----------------------------------------------|\n\n");

	fwrite(&Dados,sizeof(Dados),1,arq); //escreve no arquivo

	if(fclose(arq)==0){
		printf("Funcion�rio modificado com sucesso =D\n\n");
	}
	else{
		printf("Problemas ao salvar a modifica��o\n\n");
	}

	if(repetir()==1){
		inicial();
	}
}

int alt_a(int matricula){ //trabalho sujo na hora de alterar 
	FILE *arq;
	FILE *temp;
	form Dados;

	arq=fopen(DATA_FILENAME,"a+");
	temp=fopen(TMPDATA_FILENAME,"a+");

	titulo();
	printf("Digite o n�mero da matr�cula para ser modificada: ");
	scanf("%d",&matricula);

	while(fread(&Dados,sizeof(Dados),1,arq)!=0){
		if(Dados.matricula != matricula){
			fwrite(&Dados,sizeof(Dados),1,temp);
		}
	}

	fclose(arq);
	fclose(temp);

	excluirv();
	remove(TMPDATA_FILENAME);
}

int main(){ //fun��o principal
	setlocale(LC_ALL,"portuguese");

	inicial();
}
