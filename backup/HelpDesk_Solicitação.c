#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_empresa 50
#define tam_setor 30
#define tam_nome 50
#define tam_telefone 14
#define tam_email 50
#define tam_descricao 500
#define tam_data 12
#define tam_hora 9

typedef struct registro{
	char empresa[tam_empresa];
	char setor[tam_setor];
	char nome[tam_nome];
	char telefone[tam_telefone];
	char email[tam_email];
	char descricao[tam_descricao];
	char data[tam_data];
	char hora[tam_hora];
	int codigo;
	char situacao;
	int funcionario;
	char solucao[tam_descricao];
}reg;

int main() {
	
	FILE *arquivo;
	reg solicitacao, aux;
	int cod;
	char opc = 'S';
	
	do {
		system("cls");
		printf("-------------------------- Atendimento ao Cliente --------------------------\n");
		printf ("\n Seja bem-vindo ao atendimento HelpDesk para suporte em informatica.\n Por favor insira os dados abaixo:\n");
		printf("\n Digite o nome da empresa:\n > ");
		gets(solicitacao.empresa);
		fflush(stdin);
		printf("\n Digite o setor da empresa:\n > ");
		gets(solicitacao.setor);
		fflush(stdin);
		printf("\n Digite o nome do solicitante:\n > ");
		gets(solicitacao.nome);
		fflush(stdin);
		printf("\n Digite o telefone de contato:\n > ");
		gets(solicitacao.telefone);
		fflush(stdin);
		printf("\n Digite o e-mail do solicitante:\n > ");
		gets(solicitacao.email);
		fflush(stdin);
		printf("\n Escreva uma breve descricao do problema (MAX: 500 caracteres):\n > ");
		gets(solicitacao.descricao);
		fflush(stdin);
		strcpy(solicitacao.data, __DATE__);
		strcpy(solicitacao.hora, __TIME__);
		solicitacao.situacao = 'A';
		
		arquivo = fopen("Solicitacoes.dat", "rb");
		if (!arquivo)
			solicitacao.codigo = 0;
		else {
			fread(&aux, sizeof(reg), 1, arquivo);
			cod=0;
			while (!feof(arquivo)) {
				fread(&aux, sizeof(reg), 1, arquivo);
				cod++;
			}
		}
		fclose(arquivo);
		
		solicitacao.codigo = cod;
		
		system("cls");
		printf ("-------------------------- Dados da Solicitacao --------------------------\n\n");
		printf("     Data da Solicitacao:	%s\n     Hora da Solicitacao:	%s\n\n", solicitacao.data, solicitacao.hora);
		printf("         Nome da Empresa:	%s\n        Setor da Empresa:	%s\n     Nome do Solicitante:	%s\n     Telefone de Contato:	%s\n                  E-mail:	%s\n\n Situacao do Atendimento:	Aguardando Atendimento...\n   Codigo do Atendimento:	%d\n", solicitacao.empresa, solicitacao.setor, solicitacao.nome, solicitacao.telefone, solicitacao.email, solicitacao.codigo);
		printf("\n Descricao do Problema:\n %s\n\n", solicitacao.descricao);
		
		arquivo = fopen("Solicitacoes.dat", "ab");
		fwrite(&solicitacao, sizeof(reg), 1, arquivo);
		fclose(arquivo);

		printf (" - Gostaria de fazer uma nova solicitacao? (S/N)\n");
		do {
			printf (" > ");
			scanf("%c", &opc);
			fflush(stdin);
			opc = toupper(opc);
			if (opc != 'S' && opc !='N')
				printf (" Comando Invalido! Por favor, tente novamente.\n");
		}while (opc != 'S' && opc != 'N');		
		
	}while (opc!='N');
	
	printf ("\nAgradecemos a solicitacao!\n");
	getchar();
	
	return 0;
}
