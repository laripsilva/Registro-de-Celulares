#include <iostream>
#include <string.h>
#include <Windows.h>
#include <locale>

struct reg
{
	char marca[20];
	char modelo[20];
	char cor[20];
	char status;
};

int tamanho(FILE *);
void cadastrar(FILE *);
void consultar(FILE *);
void geraarqtxt(FILE *);
void excluir(FILE *);

int main()
{
	int op;
	FILE *arq;

	if ((arq = fopen("celulares.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("celulares.dat", "wb+")) == NULL)
		{
			printf("Falha ao abrir o arquivo!\n");
			system("pause");
		}
	}


	do
	{
		setlocale(LC_ALL,"");
		system("CLS");
		printf("\n=======CONTROLE DE ESTOQUE======= \n");
		printf("1.Cadastrar\n");
		printf("2.Consultar por codigo\n");
		printf("3.Gerar arquivo\n");
		printf("4.Excluir registro\n");
		printf("5.Sair\n");
		printf("===========CELULARES===========%d\n", tamanho(arq));
		printf("Opção:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			cadastrar(arq);
			break;
		case 2:
			consultar(arq);
			break;
			
			break;
		case 3: geraarqtxt(arq);
			
			break;
		case 4: 
			excluir(arq); 
			break;

		case 5: fclose(arq);
		}
	} while (op != 5);
}

void cadastrar(FILE *arq)
{
	setlocale(LC_ALL,"");
	reg contato;
	char confirma;
	contato.status = ' ';
	fflush(stdin);

	printf("Cadastrando novo celular:\n");
	printf("\nNúmero do registro:%d\n", tamanho(arq) + 1);
	printf("Marca.......:");
	gets(contato.marca);
	printf("Modelo......:");
	gets(contato.modelo);
	printf("Cor........:");
	gets(contato.cor);
	printf("\nConfirma <s/n>:");
	fflush(stdin);
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\nGravando...\n\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&contato, sizeof(reg), 1, arq);

	}
	system("pause");
}

void consultar(FILE *arq)
{
	setlocale(LC_ALL,"");
	reg contato;
	int nr;
	printf("\nConsulta pelo codigo\n");
	printf("\nInforme o Codigo...:");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\nMarca......:%s", contato.marca);
			printf("\nModelo..:%s", contato.modelo);
			printf("\nCor....:%s\n\n", contato.cor);
		}

		else
			printf("\nRegistro excluido! \n");

	}
	else
	{
		printf("\nNúmero de registro inválido!\n");
	}
	system("pause");
}

void geraarqtxt(FILE *arq)
{
	setlocale(LC_ALL,"");
	char nomearq[20];
	printf("Nome do arquivo texto:");
	scanf("%s", nomearq);
	strcat(nomearq, ".txt");
	FILE *arqtxt = fopen(nomearq, "w");
	if (!arqtxt)
	{
		printf("Nao foi possível criar esse arquivo!\n");
		system("pause");
	}
	fprintf(arqtxt, "Marca                Modelo    Cor                   Status\n");
	fprintf(arqtxt, "================================================================\n");
	int nr;
	reg contato;
	for (nr = 0; nr<tamanho(arq); nr++)
	{
		fseek(arq, nr * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		fprintf(arqtxt, "%-20s%-12s%-25s- %c\n", contato.marca, contato.modelo, contato.cor, contato.status);
	
	}
	fprintf(arqtxt, "================================================================\n");
	fclose(arqtxt);
}

void excluir(FILE *arq)
{
	setlocale(LC_ALL,"");
	reg contato;
	char confirma;
	int nr;

	printf("\nInforme o código do registro para excluir\n");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\nMarca......:%s", contato.marca);
			printf("\nModelo..:%s", contato.modelo);
			printf("\nCor....:%s\n", contato.cor);
			printf("\nConfirma a exclusão: <s/n>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nexcluindo...\n\n");
				fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
				contato.status = '*';
				fwrite(&contato, sizeof(reg), 1, arq);
			}
		}
	else
		printf("Registro inexistente! \n");
	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}

int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}

