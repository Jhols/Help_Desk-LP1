#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

void cabecalho();
void carregar_lista();
void listar_naoAtendidas();
void listar_emAtendimento();
void listar_finalizadas();
void atender(FILE *arquivo, int codigo);

int main() {
	
	int opc;
	int codFunc;
	
	cabecalho();
	
	printf(" Digite o codigo de funcionario:\n > ");
	scanf(" %d", &codFunc);
	
	cabecalho();
	
	printf(" - Menu:\n");
	printf(" 1 - Solicitacoes nao atendidas			3 - Solicitacoes finalizadas\n 2 - Socilitacoes em atendimento		0 - Sair do Programa\n\n");
	do {
		printf("\n > ");
		scanf(" %d", &opc);
		switch (opc) {
			case 1: 
				listar_naoAtendidas();
				break;
			case 2:
				//listar_emAtendimento();
				break;
			case 3:
				//listar_finalizadas();
				break;
			case 0:
				break;
			default:
				printf(" Opcao Invalida! Por favor, tente novamente.");
		}
	}while (opc > 3 || opc < 0);
	
	return 0;
}


void cabecalho() {
	system ("cls");
	printf ("-------------------------- Sistema HelpDesk --------------------------\n\n");
	return;
}


void listar_naoAtendidas() {
	
	FILE *arquivo;
	char opc;
	int cod;
	reg solicitacao;
	
	cabecalho();
	
	arquivo = fopen("Solicitacoes.dat", "rb");
	
	fread(&solicitacao, sizeof(reg), 1, arquivo);
	if (!arquivo) {
		printf("\nNao existem dados no arquivo!\n\n");
		system("pause");
		return;
	}
	
	while (!feof(arquivo)) {
		if (solicitacao.situacao == 'A') {
			printf ("Codigo da solicitacao: %d\n\nData: %s\nHora: %s\nEmpresa: %s\nSetor: %s\nNome: %s\nTelefone: %s\nE-mail: %s\n\n- Descricao do problema:\n%s\n\n", solicitacao.codigo, solicitacao.data, solicitacao.hora, solicitacao.empresa, solicitacao.setor, solicitacao.nome, solicitacao.telefone, solicitacao.email, solicitacao.descricao);
			printf ("------------------------------------------------------------------------------\n\n");
		}
			
		fread(&solicitacao, sizeof(reg), 1, arquivo);
	}
	
	printf (" Gostaria de resolver algum dos problemas descritos? (S)im ou (N)ao\n");
	do {
		printf (" > ");
		scanf(" %c", &opc);
		fflush(stdin);
		opc = toupper(opc);
		
		if (opc == 'S') {
			printf ("\n Digite o codigo da solicitacao:\n");
			printf (" > ");
			scanf(" %d", &cod);
			atender(arquivo, cod);
		}
		
		else
			if (opc != 'N')
				printf (" Comando invalido! Digite S ou N apenas.\n");		
	}while (opc != 'S' && opc != 'N');
	
	return;
}

void atender(FILE *arquivo, int codigo_solicitacao) {
	
	reg solicitacao;
	char solucao[tam_descricao];
	
	cabecalho();
	
	arquivo = fopen("Solicitacoes.dat", "rb");
	
	fseek(arquivo, codigo_solicitacao * sizeof(reg), SEEK_SET);
	
	fread(&solicitacao, sizeof(reg), 1, arquivo);
	
	printf ("Codigo da solicitacao: %d\n\nData: %s\nHora: %s\nEmpresa: %s\nSetor: %s\nNome: %s\nTelefone: %s\nE-mail: %s\n\n- Descricao do problema:\n%s\n\n", solicitacao.codigo, solicitacao.data, solicitacao.hora, solicitacao.empresa, solicitacao.setor, solicitacao.nome, solicitacao.telefone, solicitacao.email, solicitacao.descricao);
	
	printf ("- Solucao do problema:\n");
	gets(solucao);
	
	fclose(arquivo);
	
}


