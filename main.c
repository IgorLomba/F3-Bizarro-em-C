#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Faça um programa que receba o nome de um arquivo texto como argumento na linha de comando.
Seu programa deve calcular e escrever o número de caracteres, o número de linhas e o número de palavras neste arquivo.
Seu programa deve escrever também quantas vezes cada palavra e cada letra ocorre no arquivo. 
Considere que o arquivo não contém letras com acento e nem sinais de pontuação. 
Obs.: palavras são separadas por um ou mais caracteres espaço, tabulação ou nova linha. */

int conta_caracteres(char vetor[])
{
    int i, contador;
    char aux;
    aux = vetor[0];
    i = 0;
    contador = 0;
    for (i = 0; aux != '\0'; i++)
    {
        aux = vetor[i];
        if ((aux != '\n' && aux != '\0'))
            contador++;
    }

    return contador;
}

int conta_linhas(char vetor[])
{
    int i, cont;
    char aux;
    cont = 0;
    aux = vetor[0];
    i = 0;
    for (i = 0; aux != '\0'; i++)
    {
        aux = vetor[i];
        if (aux == '\n')
        {
            cont++;
        }
    }
    return cont + 1;
}

/*  Entendi que letra pode ser representada por qualquer caractere.
    Caso eu tenha entendido errado, e letra é qualquer caractere do alfabeto,
    é possivel filtrar na funcao a partir da conversao de char para inteiro; por exemplo:
    65 é o inteiro que representa A na tabela ASCII. Se eu printar 65 como um CHAR,
    o resultado será A. Ou seja, para filtrar seria necessário comparar se o caractere
    eh maior que 65 E menor que 90 OU maior que 97 E menor que 122. 
*/

/* LEIA ACIMA 
retorna a quantidade de todas os caracteres iguais ao caractere que foi buscado
*/
int conta_letras(char palavras[], char buscada)
{

    int i;
    int contador;
    contador = 0;

    for (i = 0; palavras[i]; i++)
    {
        if (palavras[i] == buscada)
        {
            contador++;
        }
    }

    return contador;
}

/* retorna todas as palavras iguais a buscada separadas por um ou mais caracteres espaco, tabulacao ou nova linha */
int conta_palavras(char palavra[], char buscada[])
{
    int contador, i;
    contador = i = 0;
    do
    {
        if (!strncmp(palavra + i, buscada, strlen(buscada)))
        {
            contador++;
            i += strlen(buscada);
        }
        else
        {
            i += 1;
        }
    } while (i < strlen(palavra));
    return contador;
}

/* modifica o vetor pra conter apenas caracteres nao repetidos */
void *mod_vetor(char vetor[])
{
    int tam, i, j, k;
    tam = (int)strlen(vetor);

    for (i = 0; i < tam; i++)
    {
        for (j = i + 1; j < tam;)
        {
            if (vetor[j] == vetor[i])
            {
                for (k = j; k < tam; k++)
                    vetor[k] = vetor[k + 1];
                tam--;
            }
            else
            {
                j++;
            }
        }
    }
    return 0;
}

/* abre o arquivo passado por argumento */
void *abrir_arquivo(char argv[], char texto[])
{
    int i = 0;
    char caractere;
    FILE *file;

    file = fopen(argv, "rt");

    if (file == NULL)
    {
        printf("\n\nERRO AO ABRIR O ARQUIVO '%s'\n\n\n\t\tBy: Igor Lomba\t\n\n", argv);
        return 0;
    }
    else
    {
        if (file != NULL)
        {
            while ((fscanf(file, "%c", &caractere)) != EOF)
            {
                texto[i] = caractere;
                i++;
            }
            texto[i] = '\0';
            fclose(file);
        }
        else
        {
            printf("Falha ao abrir arquivo!\n");
        }
    }
    return 0;
}

/* funcao principal */
void jogo_de_palavras(char texto[])
{
    int i, contador_palavras;
    char letra, palavra_buscada[999];
    char auxiliar_buscada[999];
    char palavras[1000];
    char *token;
    letra = '\0';
    palavra_buscada[0] = '\0';
    auxiliar_buscada[0] = '\0';
    palavras[0] = '\0';
    contador_palavras = i = 0;

    printf("\n\nTexto original: \n\n%s\n", texto);
    printf("\nTamanho do texto: %d\n", conta_caracteres(texto));
    printf("Quantidade de linhas: %d\n", conta_linhas(texto));

    /* separa os caracteres entre " ","\n" e "\t" em uma variavel */
    token = strtok(texto, " \n\t,.;:");
    while (token != NULL)
    {
        /* vai juntando os caracteres */
        strcat(palavras, token);
        strcat(palavras, " ");
        /* nao sabia se a , e o . entrariam aqui, entao nao coloquei */
        token = strtok(NULL, " \n\t,.;:");
        contador_palavras++;
    }
    printf("Quantidade de palavras: %d\n", contador_palavras);
    puts("");

    /* zera o vetor */
    for (i = 0; texto[i] != '\0'; i++)
    {
        texto[i] = '\0';
        i++;
    }

    strcpy(texto, palavras);
    mod_vetor(texto);
    i = 0;

    /* com o vetor modificado, apenas utilizo a funcao de contar as letras */
    while (texto[i] != '\0')
    {
        if (texto[i] != ' ')
        {
            letra = texto[i];
            printf("Quantidade do caractere %c: %d \n", letra, conta_letras(palavras, letra));
        }
        i++;
    }

    strcpy(texto, palavras);
    token = strtok(texto, " ");
    puts("");
    strcpy(palavra_buscada, token);
    strcat(auxiliar_buscada, palavra_buscada);
    strcat(auxiliar_buscada, " ");

    /* organizo todas as palavras nao repetidas em um vetor string auxiliar */
    while (token != NULL)
    {
        if (conta_palavras(auxiliar_buscada, token) == 0)
        {
            strcat(auxiliar_buscada, token);
            strcat(auxiliar_buscada, " ");
        }
        strcpy(palavra_buscada, token);
        token = strtok(NULL, " ");
    }

    /* separo a string com palavras nao repetidas em substrings e comparo com o vetor de palavras principal */
    token = strtok(auxiliar_buscada, " ");
    while (token != NULL)
    {
        printf("Quantidade da palavra %s: %d \n", palavra_buscada, conta_palavras(palavras, palavra_buscada));
        strcpy(palavra_buscada, token);
        token = strtok(NULL, " ");
    }
    puts("");
    puts("Obrigado por utilizar meu analisador de texto 2077!\n\n\t\tBy: Igor Lomba\t\n");
}

/* nao se esqueca de criar um arquivo antes de rodar isso ai */
int main(int argc, char *argv[])
{
    char texto[1000];
    texto[0] = '\0';

    abrir_arquivo(argv[1], texto);

    if (strlen(texto) != 0)
        jogo_de_palavras(texto);

    return 0;
}
