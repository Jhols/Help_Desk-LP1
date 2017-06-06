#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define tam_empresa 50
#define tam_setor 30
#define tam_nome 50
#define tam_telefone 14
#define tam_email 50
#define tam_descricao 500
#define tam_data 12
#define tam_hora 9
#define tam_senha 11

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

typedef struct login {
	char nome[tam_nome];
	char senha[tam_senha];
	char email[tam_email];
	int codigo;
}func;

void cabecalho();
int fazer_login();
void cadastro();
void esqueceu_senha();
void listar_naoAtendidas();
void listar_emAtendimento();
void listar_finalizadas();
void atender();

int main() {
	
	FILE *arquivo;
	
	int opc, codFunc;
	func pessoa;
	
	do {
		cabecalho();
		
		printf(" Seja Bem-vindo ao Sistema de HelpDesk para suporte em Informatica!\n\n - O que deseja fazer?\n\n");
		printf(" 1 - Fazer Login		3 - Esqueceu a senha?\n 2 - Cadastrar-se		0 - Sair\n");
		do {
			printf ("\n > ");
			scanf (" %d", &opc);
			fflush(stdin);
			if (opc > 3 || opc < 0) {
				printf (" AVISO: Selecao Invalida! Por favor, tente novamente.\n");
			}
		}while (opc > 3 || opc < 0);
		
		switch (opc) {
			case 1:
				codFunc = fazer_login();
				arquivo = fopen("Funcionarios.dat", "rb");
				fseek(arquivo, codFunc*sizeof(func), SEEK_SET);
				fread(&pessoa, sizeof(func), 1, arquivo);
				fclose(arquivo);
				break;
			case 2:
				cadastro();
				codFunc = -1;
				break;
			case 3:
				esqueceu_senha();
				codFunc = -1;
				break;
			case 0:
				system("cls");
				printf (" ----------- Creditos -----------\n\n Sistema criado por: Joao Pedro Hegouet\n\n");
				return 0;
		}
	}while (codFunc < 0);
	
	//Menu Principal
	while(1) {
		
		cabecalho();
		
		printf (" Bem-vindo: %s\n Data: %s\n\n", pessoa.nome, __DATE__);
	
		printf(" - Menu:\n");
		printf(" 1 - Solicitacoes nao atendidas			3 - Solicitacoes finalizadas\n 2 - Socilitacoes em atendimento		0 - Sair do Programa\n\n");
		
		do {
			printf ("\n > ");
			scanf (" %d", &opc);
			fflush(stdin);
			if (opc > 3 || opc < 0) {
				printf (" AVISO: Selecao Invalida! Por favor, tente novamente.\n");
			}
		}while (opc > 3 || opc < 0);
		
		switch (opc) {
			case 1: 
				listar_naoAtendidas(codFunc);
				break;
			case 2:
				listar_emAtendimento(codFunc);
				break;
			case 3:
				listar_finalizadas();
				break;
			case 0:
				system("cls");
				printf (" ----------- Creditos -----------\n\n Sistema criado por: Joao Pedro Hegouet\n\n");
				return 0;
			default:
				printf(" AVISO: Opcao Invalida! Por favor, tente novamente.");
		}
	}
}

void cabecalho() {
	system ("cls");
	printf ("-------------------------- Sistema HelpDesk --------------------------\n\n");
	return;
}

int fazer_login() {
	
	FILE *funcionarios;
	int codFunc, flag;
	char senha[tam_senha], opc;
	func pessoa;
	
	funcionarios = fopen("Funcionarios.dat", "rb");
	if (!funcionarios) {
		printf("\n Arquivo \"Funcionarios.dat\" nao existe! Sera criado um novo arquivo.\n ");
		system("pause");
		printf ("\n");
		fclose(funcionarios);
		funcionarios = fopen ("Funcionarios.dat", "wb");
		if (!funcionarios) {
			printf ("\n Houve um problema na criacao de um novo arquivo!\n ");
			exit(1);
		}
		fclose(funcionarios);
	}
	
	do {
		flag = 0;
		
		cabecalho();
		
		printf( " - Digite seu Codigo de Funcionario:\n > ");
		scanf(" %d", &codFunc);
		fflush(stdin);
		
		funcionarios = fopen ("Funcionarios.dat", "rb");
		fseek(funcionarios, 0, SEEK_SET);
		
		fread(&pessoa, sizeof(func), 1, funcionarios);
		if (feof(funcionarios)) {
			printf("\n - Nao existem funcionarios cadastrados!\n ");
			system("pause");
			return -1;
		}
		
		while (!feof(funcionarios)) {
			if (codFunc != pessoa.codigo)
				fread(&pessoa, sizeof(func), 1, funcionarios);
			else
				break;
		}
		
		if (!feof(funcionarios)) {
			do {
				printf ("\n - Digite sua senha:\n");
				printf (" > ");
				gets(senha);
				fflush(stdin);
				if (strcmp(senha, pessoa.senha) != 0) {
					printf (" AVISO: Senha Invalida! Tentar novamente? (S)im ou (N)ao\n");
					do {
						printf (" > ");
						scanf (" %c", &opc);
						fflush(stdin);
						opc = toupper(opc);
						if (opc != 'S' && opc != 'N')
							printf (" AVISO: Comando Invalido! Por favor, digite S ou N apenas.");
					}while (opc != 'S' && opc != 'N');
				}
				
				else {
					fclose(funcionarios);
					return codFunc;
				}
					
			}while (opc != 'N');
		}
		
		else {
			printf (" AVISO: Este Codigo de Funcionario nao existe! Gostaria de tentar novamente? (S)im ou (N)ao\n");
			do {
				printf (" > ");
				scanf (" %c", &opc);
				opc = toupper(opc);
				if (opc == 'S')
					flag = 1;
				else if (opc != 'S' && opc != 'N')
					printf (" AVISO: Comando Invalido! Por favor, digite S ou N apenas.");
			}while (opc != 'S' && opc != 'N');
		}
	}while (flag);
	
	fclose(funcionarios);
	return -1;
	
}

void cadastro() {
	
	FILE *arquivo;
	func pessoa, aux;
	int cod;
	
	arquivo = fopen("Funcionarios.dat", "rb");
	if (!arquivo) {
		printf("\n Arquivo \"Funcionarios.dat\" nao existe! Sera criado um novo arquivo.\n ");
		system("pause");
		printf ("\n");
		fclose(arquivo);
		arquivo = fopen ("Funcionarios.dat", "wb");
		if (!arquivo) {
			printf ("\n Houve um problema na criacao de um novo arquivo!\n ");
			exit(1);
		}
		fclose(arquivo);
	}
	
	cabecalho();
	
	printf (" - Digite seu Nome:\n > ");
	gets(pessoa.nome);
	fflush(stdin);
	
	printf ("\n - Digite seu E-mail:\n > ");
	scanf(" %s", &pessoa.email);
	fflush(stdin);
	
	printf("\n - Digite uma Senha Pessoal: (Minimo: 6 caracteres, Maximo: 10 caracteres)\n");
	do {
		printf (" > ");
		gets(pessoa.senha);
		fflush(stdin);
		if (strlen(pessoa.senha) < 6)
			printf (" AVISO: Senha pequena! Minimo de 6 caracteres.\n");
		if (strlen(pessoa.senha) > tam_senha-1)
			printf (" AVISO: Senha muito grande! Maximo de 10 caracteres.\n");
	}while (strlen(pessoa.senha) > tam_senha-1 || strlen(pessoa.senha) < 6);
	
	arquivo = fopen("Funcionarios.dat", "rb");
	
	if (!arquivo)
			pessoa.codigo = 0;
		else {
			fread(&aux, sizeof(func), 1, arquivo);
			cod=0;
			while (!feof(arquivo)) {
				fread(&aux, sizeof(func), 1, arquivo);
				cod++;
			}
		}
	fclose(arquivo);
	
	pessoa.codigo = cod;
	
	system("cls");
	printf ("-------------------------- Dados do Cadastro --------------------------\n\n");
	printf("   Nome do Funcionario:   %s\n 	        E-mail:   %s\n\n Codigo de Funcionario:   %d\n 		 Senha:   %s\n\n\n\n ", pessoa.nome, pessoa.email, pessoa.codigo, pessoa.senha);
	
	arquivo = fopen("Funcionarios.dat", "ab");
	fwrite(&pessoa, sizeof(func), 1, arquivo);
	fclose(arquivo);

	system("pause");
}

void esqueceu_senha() {
	
	FILE *arquivo;
	func pessoa, aux;
	int flag;
	char opc;
	
	arquivo = fopen ("Funcionarios.dat", "rb");
	fread(&aux, sizeof(func), 1, arquivo);
	if (feof(arquivo)) {
		printf("\n - Nao existem funcionarios cadastrados!\n ");
		system("pause");
		return;
	}
	fclose(arquivo);
	
	do {
		cabecalho();
		flag = 0;
		
		printf (" - Digite seu Codigo de Funcionario:\n > ");
		scanf(" %d", &pessoa.codigo);
		fflush(stdin);
		
		printf ("\n - Digite seu Email:\n > ");
		gets(pessoa.email);
		fflush(stdin);
		
		arquivo = fopen ("Funcionarios.dat", "rb");
		fseek(arquivo, 0, SEEK_SET);
		
		fread(&aux, sizeof(func), 1, arquivo);
		while (!feof(arquivo)) {
			if (pessoa.codigo != aux.codigo)
				fread(&aux, sizeof(func), 1, arquivo);
			else {
				if (strcmp(pessoa.email, aux.email) == 0) {
					flag = 1;
					strcpy(pessoa.nome, aux.nome);
					break;
				}
				else {
					printf ("\n AVISO: O Email digitado esta invalido para o Codigo %d! Tentar novamente? (S)im ou (N)ao\n", pessoa.codigo);
					do {
						printf(" > ");
						scanf(" %c", &opc);
						fflush(stdin);
						opc = toupper(opc);
						if (opc == 'N') {
							fclose(arquivo);
							return;
						}
							
						if (opc != 'S')
							printf ("\n AVISO: Comando Invalido! Por favor, digite S ou N apenas.\n");
					}while (opc != 'S');
				}
			}
		}
		fclose(arquivo);
		
		
		if (!flag) {
			printf ("\n AVISO: Esse Codigo de Funcionario nao existe! Tentar novamente? (S)im ou (N)ao\n");
			do {
				printf(" > ");
				scanf(" %c", &opc);
				fflush(stdin);
				opc = toupper(opc);
				if (opc == 'N') {
					fclose(arquivo);
					return;
				}
				if (opc != 'S')
					printf ("\n AVISO: Comando Invalido! Por favor, digite S ou N apenas.\n");
			}while (opc != 'S');
		}
		
		else {
			printf ("\n - Digite a nova senha: (Minimo 6 caracteres, Maximo 10 caracteres)\n");
			do {
				printf (" > ");
				gets(pessoa.senha);
				fflush(stdin);
				if (strlen(pessoa.senha) < 6)
					printf ("\n AVISO: Senha pequena! Minimo de 6 caracteres.\n");
				if (strlen(pessoa.senha) > tam_senha-1)
					printf ("\n AVISO: Senha muito grande! Maximo de 10 caracteres.\n");
			}while (strlen(pessoa.senha) > tam_senha-1 || strlen(pessoa.senha) < 6);
			
			
			arquivo = fopen ("Funcionarios.dat", "r+b");
			fseek(arquivo, pessoa.codigo*(sizeof(func)), SEEK_SET);
			fwrite(&pessoa,sizeof(func), 1, arquivo);
			fclose(arquivo);
			
			printf("\n\n - Senha atualizada com sucesso!\n ");
			system("pause");
		}
	}while (opc == 'S');
	
	return;
		
}

void listar_naoAtendidas(int codigo_funcionario) {
	
	FILE *arquivo;
	char opc;
	int cod, flag = 0;
	reg solicitacao;
	
	cabecalho();
	
	arquivo = fopen("Solicitacoes.dat", "rb");
	
	fread(&solicitacao, sizeof(reg), 1, arquivo);
	if (!arquivo) {
		printf("\n - Nao existem dados no arquivo!\n\n");
		system("pause");
		return;
	}
	
	while (!feof(arquivo)) {
		if (solicitacao.situacao == 'A') {
			flag = 1;
			printf ("Codigo da Solicitacao: %d\n\nData: %s\nHora: %s\nEmpresa: %s\nSetor: %s\nNome: %s\nTelefone: %s\nE-mail: %s\n\n- Descricao do problema:\n%s\n\n", solicitacao.codigo, solicitacao.data, solicitacao.hora, solicitacao.empresa, solicitacao.setor, solicitacao.nome, solicitacao.telefone, solicitacao.email, solicitacao.descricao);
			printf ("------------------------------------------------------------------------------\n\n");
		}
			
		fread(&solicitacao, sizeof(reg), 1, arquivo);
	}
	
	fclose(arquivo);
	
	if (!flag) {
		printf (" - Nao existem solicitacoes em andamento!\n\n ");
		system("pause");
	}
	
	else {
		printf (" - Gostaria de resolver algum dos problemas descritos? (S)im ou (N)ao\n");
		do {
			printf (" > ");
			scanf(" %c", &opc);
			fflush(stdin);
			opc = toupper(opc);
			
			if (opc == 'S') {
				printf ("\n - Digite o codigo da solicitacao:\n");
				printf (" > ");
				scanf(" %d", &cod);
				fflush(stdin);
				atender(arquivo, cod, codigo_funcionario);
			}
			
			else
				if (opc != 'N')
					printf (" AVISO: Comando invalido! Digite S ou N apenas.\n");		
		}while (opc != 'S' && opc != 'N');
	}
	
	return;
}

void atender(FILE *arquivo, int codigo_solicitacao, int codigo_funcionario) {
	
	reg solicitacao;
	char opc;
	
	cabecalho();
	
	arquivo = fopen("Solicitacoes.dat", "r+b");
	
	fseek(arquivo, codigo_solicitacao * sizeof(reg), SEEK_SET);
	fread(&solicitacao, sizeof(reg), 1, arquivo);
	
	solicitacao.situacao = 'E';
	solicitacao.funcionario = codigo_funcionario;
	strcpy(solicitacao.solucao, " ");
	
	fseek(arquivo, codigo_solicitacao * sizeof(reg), SEEK_SET);
	fwrite(&solicitacao, sizeof(reg), 1, arquivo);
	
	fclose(arquivo);
	
	printf ("Codigo da solicitacao: %d\n\nData: %s\nHora: %s\nEmpresa: %s\nSetor: %s\nNome: %s\nTelefone: %s\nE-mail: %s\n\n- Descricao do problema:\n%s\n\n", solicitacao.codigo, solicitacao.data, solicitacao.hora, solicitacao.empresa, solicitacao.setor, solicitacao.nome, solicitacao.telefone, solicitacao.email, solicitacao.descricao);
	
	printf ("- Digite a solucao do problema:\n");
	gets(solicitacao.solucao);
	fflush(stdin);
	
	arquivo = fopen("Solicitacoes.dat", "r+b");
	
	printf("\n - Tem certeza de que finalizou a solucao? Gostaria de enviar a resposta (S) ou ainda nao (N)?\n");
	do {
		printf (" > ");
		scanf (" %c", &opc);
		opc = toupper(opc);
		
		if (opc == 'S') {
			solicitacao.situacao = 'F';
			fseek(arquivo, codigo_solicitacao * sizeof(reg), SEEK_SET);
			fwrite(&solicitacao, sizeof(reg), 1, arquivo);
			printf ("\n - Resposta Enviada!\n\n ");
			system("pause");
		}
		
		else
			if (opc != 'N')
				printf (" AVISO: Comando Invalido! Digite S ou N apenas.");
	}while (opc != 'S' && opc != 'N');
	
	fclose(arquivo);
	
}

void listar_emAtendimento(int codigo_funcionario) {
	
	reg solicitacao;
	FILE *arquivo;
	char opc;
	int cod, flag=0;
	
	cabecalho();
	
	arquivo = fopen("Solicitacoes.dat", "rb");
	
	fread(&solicitacao, sizeof(reg), 1, arquivo);
	if (!arquivo) {
		printf("\n - Nao existem dados no arquivo!\n\n");
		system("pause");
		return;
	}
	
	while (!feof(arquivo)) {
		if (solicitacao.situacao == 'E' && solicitacao.funcionario == codigo_funcionario) {
			flag = 1;
			printf ("Codigo da Solicitacao: %d\n\nData: %s\nHora: %s\nEmpresa: %s\nSetor: %s\nNome: %s\nTelefone: %s\nE-mail: %s\n\n- Descricao do problema:\n%s\n\n", solicitacao.codigo, solicitacao.data, solicitacao.hora, solicitacao.empresa, solicitacao.setor, solicitacao.nome, solicitacao.telefone, solicitacao.email, solicitacao.descricao);
			printf ("------------------------------------------------------------------------------\n\n");
		}
			
		fread(&solicitacao, sizeof(reg), 1, arquivo);
	}
	
	if (!flag) {
		printf (" - Voce nao tem solicitacoes em atendimento\n\n ");
		system("pause");
	}
		
	else {
		printf (" - Gostaria de continuar a resolver algum dos problemas descritos? (S)im ou (N)ao\n");
		do {
			printf (" > ");
			scanf(" %c", &opc);
			fflush(stdin);
			opc = toupper(opc);
			
			if (opc == 'S') {
				printf ("\n - Digite o codigo da solicitacao:\n");
				printf (" > ");
				scanf(" %d", &cod);
				fflush(stdin);
				atender(arquivo, cod, codigo_funcionario);
			}
			
			else
				if (opc != 'N')
					printf (" AVISO: Comando invalido! Digite S ou N apenas.\n");		
		}while (opc != 'S' && opc != 'N');
	}
	
	return;
}

void listar_finalizadas() {
	reg solicitacao;
	FILE *arquivo;
	int flag = 0;
	
	cabecalho();
	
	arquivo = fopen("Solicitacoes.dat", "rb");
	
	fread(&solicitacao, sizeof(reg), 1, arquivo);
	if (!arquivo) {
		printf("\n - Nao existem dados no arquivo!\n\n");
		system("pause");
		return;
	}
	
	while (!feof(arquivo)) {
		if (solicitacao.situacao == 'F') {
			flag = 1;
			printf ("Codigo da Solicitacao: %d\nCodigo do Funcionario: %d\n\nData: %s\nHora: %s\nEmpresa: %s\nSetor: %s\nNome: %s\nTelefone: %s\nE-mail: %s\n\n- Descricao do problema:\n%s\n\nSolucao: %s\n\n", solicitacao.codigo, solicitacao.funcionario,solicitacao.data, solicitacao.hora, solicitacao.empresa, solicitacao.setor, solicitacao.nome, solicitacao.telefone, solicitacao.email, solicitacao.descricao, solicitacao.solucao);
			printf ("------------------------------------------------------------------------------\n\n");
		}
			
		fread(&solicitacao, sizeof(reg), 1, arquivo);
	}
	
	if (!flag)
		printf (" - Nao existem solicitacoes finalizadas!\n ");
	
	printf ("\n ");
	
	system("pause");
	
	return;
}

