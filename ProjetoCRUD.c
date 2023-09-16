/* Caro futuro desenvolvedor que pegar este código...
   Toda nossa mente e toda a nossa alma foi posta neste trabalho
   Então, pedimos encarecidamente, não copie
   Ele está com toda a cara de um estudante que só queria férias
   
   Desde já, agradeçemos: Théo e Diego*/

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

int repetir(){  //função para caso o usuário queira continuar no código
	fflush(stdin);
	int tecla;

	printf("\n###################################\n\n");
	printf("Digite 1 para continuar.\n");
	printf("Digite 2 para sair.\n\n");
	tecla=getchar();

	if(tecla == 49){ //caso tecle 1 (ascii=49), continua no código
		system("cls");
		return 1;
	}
}

void titulo(){ //função para título do gerenciamento (não é muito importante)
	printf("***GERENCIAMENTO DE FUNCIONÁRIOS***");
	printf("\n\n");
}

void inicial(){ //função que inicia o código, aqui onde tudo ocorre
	int op;
	char tecla;
	float soma=0;
	int i=0;
	int matricula;

	do{
		printf("***GERENCIAMENTO DE FUNCIONÁRIOS***\n");
		printf("1) Novo funcionário\n");
		printf("2) Mostrar lista de funcionários\n");
		printf("3) Remover funcionário do sistema\n");
		printf("4) Alterar informações de um funcionário\n");
		printf("5) Sair\n\n");
		printf("Digite a ação que queira realizar: ");
		scanf("%d",&op);
		fflush(stdin);
		printf("\n");

		switch(op){
			case 1: //novo funcionário
				system("cls");
				novo();
			break;
			case 2: //mostrar lista de funcionários
				system("cls");
				listar();
			break; 
			case 3: //remover funcionario
				system("cls");
				excluir();
			break;
			case 4: //alterar informações
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
	}while(op > 6 && printf("Opção inválida\n\n"));
}

int acha(int *matricula){ //função para achar a matrícula, relacionada aos cadastros dos funcionários
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

int valida(int *matricula){ //função para validar a matricula dentro do arquivo
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
			printf("Matrícula já cadastrada. Crie um novo registro.\n");
			return 1;
		}
	}
	fclose(arq);
}

int percorre(){ //função qualquer, esqueça essa maluquice
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

int novo(){  //função para criar novo registro
	form Dados;
	FILE *arq;
	int total=0;
	arq=fopen(DATA_FILENAME,"a+");

	titulo();
	printf("***REGISTRO NOVO FUNCIONÁRIO***\n\n");
	printf("Checando memória...\n");
	sleep(1);
	printf("Criando arquivo...\n\n");
	sleep(1);

	do{	
		printf("Matrícula: ");
		scanf("%d",&Dados.matricula);
	}while(valida(&Dados.matricula)==1); //chama função para validar matricula no arquivo
		fflush(stdin);
		printf("Nome: ");
		gets(Dados.nome);
		fflush(stdin);
		printf("Salário: R$ ");
		scanf("%f",&Dados.sal);
		fflush(stdin);
		printf("|-----------------------------------------------|\n\n");

		if(arq==NULL){ //caso não consiga criar o arquivo
			printf("Erro ao criar o arquivo.\n");
		}

		fwrite(&Dados,sizeof(Dados),1,arq); //escreve as coisas que o usuário digitou no arquivo

		if(fclose(arq)==0){ //caso consiga fechar o arquivo
			printf("Funcionário cadastrado com sucesso =D\n\n");
		}
		else{ //caso não
			printf("Problemas ao salvar o arquivo\n\n");
		}

		if(repetir()==1){ //if que chama função para repetir a tela inicial
			inicial();
		}
}

int listar(){ //função que lista os funcionários
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
	printf("MATRÍCULA\tNOME\tSALÁRIO\n");

	while(fread(&Dados,sizeof(Dados),1,arq)!=0){
		printf("%d\t\t%s\t%.2f\n\n",Dados.matricula,Dados.nome,Dados.sal);
		printf("-------------------------------------------\n");
		reg++; //incrementa registros
		soma+=Dados.sal; //incrementa o salário, fazendo a soma dos salários registrados
	}

	printf("Total de registros: %d\tTotal de Salários: R$ %.2f\n",reg,soma); //mostra o total de registros e salários

	fclose(arq); //fecha arquivo

	if(repetir()==1){
		inicial();
	}
}

void excluirv(){ //função que faz o trabalho sujo ao excluir
	form Dados;
	FILE *arq;
	arq=fopen(DATA_FILENAME,"w+");

	if(arq==NULL){
		printf("\nArquivo Funcionario.txt não pode ser aberto.\n");
	}

	FILE *temp;
	temp=fopen(TMPDATA_FILENAME,"a+");

	if(temp==NULL){
		printf("\nArquivo Funcionario.txt não pode ser aberto.\n");
	}

	while(fread(&Dados,sizeof(Dados),1,temp)!=0){
		fwrite(&Dados,sizeof(Dados),1,arq);
	}

	fclose(arq);
	fclose(temp);
}

int excluir(){ //função que esconde o trabalho sujo
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
	printf("Matrícula: ");
	scanf("%d",&matricula);

	if(acha(&matricula)==0){ //caso não encontre a matrícula
		printf("Matrícula não encontrada.\n\n");

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
	remove(TMPDATA_FILENAME); //exclui registros temporários
	printf("Excluido com sucesso.\n");

	if(repetir()==1){
		inicial();
	}
}

int alterar(){ //função para modificar as informações do registro
	FILE *arq;
	FILE *temp;
	form Dados;
	int matricula;

	arq=fopen(DATA_FILENAME,"a+");
	temp=fopen(TMPDATA_FILENAME,"a+");

	titulo();
	alt_a(matricula); //função que faz o trabalho sujo na hora de alterar
	printf("Confirme o número da matrícula: ");
	scanf("%d",&Dados.matricula);

	printf("\n\n");
	sleep(1);
	printf("Abrindo registro...\n\n");
	sleep(1);
	printf("Matrícula: %d\n",Dados.matricula);
	printf("Novo nome: ");
	fflush(stdin);
	gets(Dados.nome);
	printf("Novo salário: R$ ");
	fflush(stdin);
	scanf("%f",&Dados.sal);
	printf("|-----------------------------------------------|\n\n");

	fwrite(&Dados,sizeof(Dados),1,arq); //escreve no arquivo

	if(fclose(arq)==0){
		printf("Funcionário modificado com sucesso =D\n\n");
	}
	else{
		printf("Problemas ao salvar a modificação\n\n");
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
	printf("Digite o número da matrícula para ser modificada: ");
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

int main(){ //função principal
	setlocale(LC_ALL,"portuguese");

	inicial();
}
