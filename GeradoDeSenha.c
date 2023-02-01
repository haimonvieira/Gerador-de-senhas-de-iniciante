#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define TAMANHO_SENHA_MIN 10
#define TAMANHO_SENHA_MAX 128
#define TAMANHO_CARACTER_MAX 10
#define TAMANHO_NUMERO_MAX 10

const char *caracter_especial = "!@#$%^&*";
const char *numeros = "0123456789";
const char *letras = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

void copiar_para_area_transferencia(const char *senha)
{

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(senha) + 1);
    memcpy(GlobalLock(hMem), senha, strlen(senha) + 1);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

int main()
{
    int tamanho_senha;
    int num_caracter_especial;
    int num_numeros;
    int num_letras;
    int contador_senhas = 0;
    char senha[128], armazena_senhas[128][128];
    int opcao;

    do
    {

        srand(time(NULL));

        printf("Insira o tamanho da senha: ");
        scanf("%d", &tamanho_senha);

        if (tamanho_senha < TAMANHO_SENHA_MIN)
        {
            printf("Erro: o comprimento da senha deve ser de pelo menos %d caracteres\n", TAMANHO_SENHA_MIN);
            system("cls");
        }
        else if (tamanho_senha > TAMANHO_SENHA_MAX)
        {

            printf("Erro: o comprimento da senha deve ser de no maximo %d caracteres\n", TAMANHO_SENHA_MAX);
            system("cls");
        }

        printf("Insira o numero de caracteres especiais: ");
        scanf("%d", &num_caracter_especial);

        if (num_caracter_especial > TAMANHO_CARACTER_MAX)
        {
            printf("Erro: o maximo de caracteres especiais e de %d caracteres\n", TAMANHO_CARACTER_MAX);
            system("cls");
        }

        printf("Insira a quantidade de numeros: ");
        scanf("%d", &num_numeros);

        if (num_numeros > TAMANHO_NUMERO_MAX)
        {
            printf("Erro: o maximo de numeros e de %d numeros\n", TAMANHO_NUMERO_MAX);
            system("cls");
        }

        num_letras = tamanho_senha - num_caracter_especial - num_numeros;
        if (num_letras < 0)
        {
            printf("Erro: o numero total de caracteres e numeros especiais nao pode exceder o comprimento da senha\n");
            system("cls");
        }

        for (int i = 0; i < num_caracter_especial; i++)
        {
            int index = rand() % strlen(caracter_especial);
            senha[i] = caracter_especial[index];
        }

        for (int i = num_caracter_especial; i < num_caracter_especial + num_numeros; i++)
        {
            int index = rand() % strlen(numeros);
            senha[i] = numeros[index];
        }

        for (int i = num_caracter_especial + num_numeros; i < tamanho_senha; i++)
        {
            int index = rand() % strlen(letras);
            senha[i] = letras[index];
        }

        for (int i = 0; i < tamanho_senha; i++)
        {
            int j = rand() % tamanho_senha;
            int k = rand() % tamanho_senha;
            char temp = senha[j];
            senha[j] = senha[k];
            senha[k] = temp;
        }

        senha[tamanho_senha] = '\0';

        system("cls");

        printf("Sua senha e: %s\n", senha);
        printf("Deseja copiar a senha para a area de transferencia? (s/n): ");

        char resposta[4];
        scanf("%s", resposta);

        if (strcmp(resposta, "s") == 0)
        {
            copiar_para_area_transferencia(senha);
            printf("Senha copiada para a area de transferencia com sucesso!\n");
        }

        strcpy(armazena_senhas[contador_senhas], senha);
        contador_senhas++;

        system("cls");

        printf("Senha atual: %s", armazena_senhas);

        printf("\n\nEscolha uma opcao: \n");
        printf("1- Gerar nova senha;\n");
        printf("2- Ver senhas geradas.\n");
        printf("> ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            system("cls");
        }
        else if (opcao == 2)
        {
            system("cls");

            printf("Senhas geradas: \n");

            for (int i = 0; i < contador_senhas; i++)
            {

                printf("%d- %s\n", i + 1, armazena_senhas[i]);
            }
        }

        printf("\n");
        system("pause");
        system("cls");

    } while (opcao == 's' || opcao == 2 || tamanho_senha < TAMANHO_SENHA_MIN || num_letras < 0 || tamanho_senha > TAMANHO_SENHA_MAX || num_caracter_especial > TAMANHO_CARACTER_MAX || num_numeros > TAMANHO_NUMERO_MAX);
}
