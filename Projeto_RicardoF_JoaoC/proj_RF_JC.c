#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


//constantes
#define MAX_LNOME 12
#define MAX_LOCAL 30
#define MAX_LAB 15
#define MAX_DESC 150
#define MAX_NSERIE 15
#define MAX_EQUIP 200
#define MIN_NUM 1
#define MAX_NUM 100


//estruturas
typedef struct
{
    int dia,mes,ano;
} tData;

typedef struct
{
    char lNome[MAX_LNOME];
    char lLocal[MAX_LOCAL];
    int lPostoTrab;
    int lQuantEquip;
} tLab;

typedef struct
{
    int nrInv;
    float custo;
    tData dInv;
    char desc[MAX_DESC];
    char nSerie[MAX_NSERIE];
    char local[MAX_LOCAL];
    char estado;
} tEquip;

typedef struct
{
    int nrAv,nrInv;
    float custoR;
    tData dAv;
    char desc[MAX_DESC];
    char estado;
} tAvaria;


//prototipos
char menu(int qLab, int qPost, int qEquip, float qPerc);
char menuAv(void);
char menuLab(void);
char menuEquip(void);
char menuAlterarLab(void);
int lerInteiro(char msg[],int minimo, int maximo);
int lerFloat(char msg[],float minimo, float maximo);
void lerString(char msg[],char nome[], int maxCaracteres);
void limparBufferStdin(void);
void limparEcra(void);
void inserirLaboratorio(int *nLabs, tLab vLab[MAX_LAB]);
void listarLaboratorios(int nLabs, tLab vLab[MAX_LAB]);
void alterarLaboratorios(int nLabs, tLab vLab[MAX_LAB]);
int pesquisarNomeLab(char nome[MAX_LNOME], tLab vLab[MAX_LAB],int nLabs);


int main(void)
{
    int nLabs = 0;
    char op,op2;
    int qLab = 0,qPost = 0,qEquip = 0;
    float qPerc = 0;
    tLab vLab[MAX_LAB];
    do
    {
        op = toupper(menu(qLab,qPost,qEquip,qPerc));
        switch(op)
        {
        case 'A':
            do
            {
                op2 = toupper(menuAv());
                switch(op2)
                {
                case 'R':
                    printf("Regista avarias");
                    break;
                case 'L':
                    printf("Listar avarias");
                    break;
                case 'C':
                    printf("Consultar avarias");
                    break;
                case 'E':
                    printf("Eliminar avarias incorretas");
                    break;
                case 'V':
                    break;
                }
            }
            while(op2 != 'V');
            break;
        case 'E':
            do
            {
                op2 = toupper(menuEquip());
                switch(op2)
                {
                case 'R':
                    printf("Regista instalacao, reparacao ou abate de equipamento");
                    break;
                case 'L':
                    printf("Lista dados de equipamentos");
                    break;
                case 'C':
                    printf("Consulta dados de equipamentos");
                    break;
                case 'E':
                    printf("Inventariacao de equipamentos");
                    break;
                case 'V':
                    break;
                }
            }
            while(op2 != 'V');
            break;
        case 'L':
            do
            {
                op2 = toupper(menuLab());
                switch(op2)
                {
                case 'I':
                    printf("\nInserir laboratorio\n");
                    inserirLaboratorio(&nLabs, vLab);
                    break;
                case 'L':
                    printf("\nListar laboratorios\n");
                    listarLaboratorios(nLabs, vLab);
                    break;
                case 'C':
                    printf("Consultar laboratorios");
                    break;
                case 'A':
                    printf("\nAlterar laboratorios\n");
                    alterarLaboratorios(nLabs, vLab);
                    break;
                case 'V':
                    break;
                }
            }
            while(op2 != 'V');
            break;
        case 'S':
            break;
        default:
            printf("\nOpcao invalida\n");
            break;
        }
    }
    while(op != 'S');
    return 0;
}

//Funcoes

//Funcoes de leitura        --------------------------------------------
int lerInteiro(char msg[],int minimo, int maximo){
    int numero, aux;
    do
    {
        printf("%s (%d - %d): ", msg, minimo, maximo);
        aux=scanf("%d", &numero);
        limparBufferStdin();
        if( numero < minimo || numero > maximo
                || aux!=1)
        {
            printf("\n Numero invalido. ");
        }
    }
    while(numero < minimo || numero > maximo || aux!=1);
    return numero;
}

int lerFloat(char msg[],float minimo, float maximo){
    float numero, aux;
    do
    {
        printf("%s (%.2f - %.2f): ", msg, minimo, maximo);
        aux = scanf("%f", &numero);
        limparBufferStdin();
        if( numero < minimo || numero > maximo || aux!=1)
        {
            printf("\n Numero invalido. ");
        }
    }
    while(numero < minimo || numero > maximo || aux!=1);
    return numero;
}

void lerString(char msg[],char nome[], int maxCaracteres){
    int tamanhoString;
    do
    {
        printf("%s", msg); //puts(msg);
        fgets(nome, maxCaracteres, stdin);
        tamanhoString = strlen(nome);
        if(nome[tamanhoString-1] != '\n')
        {
            limparBufferStdin();
        }
        else
        {
            nome[tamanhoString-1] = '\0';
        }
    }
    while(tamanhoString == 1);
}

void limparBufferStdin(void){
    char lixo;
    do
    {
        lixo = getchar();
    }
    while(lixo != '\n' && lixo != EOF);
}

//Fim de funcoes de leitura -------------------------------------

//Inicio de funçoes menu    -------------------------------------
char menu(int qLab, int qPost, int qEquip, float qPerc){
    char op;
    do
    {
        printf("------------------------------------------------------------------------------------");
        printf("\nMenu Principal\n");
        printf("\n------------------------------------------------------------------------------------");
        printf("\nQuantidade de laboratorios: %d", qLab);
        printf("\t\tQuantidade total de postos de trabalho: %d   |", qPost);
        printf("\nQuantidade total de equipamentos: %d", qEquip);
        printf("\tPercentagem de equipamentos avariados: %.2f |", qPerc);
        printf("\n------------------------------------------------------------------------------------");
        printf("\n \tA - Gestao de avarias");
        printf("\n \tE - Gestao dos equipamentos");
        printf("\n \tL - Gestao dos laboratorios");
        printf("\n \tD - Dados estatisticos");
        printf("\n \tS - Sair");
        printf("\n Opcao:");
        scanf(" %c", &op);
        op = toupper(op);
    }
    while(op != 'A' && op != 'E' && op != 'L' && op != 'S');
    return op;
}

char menuAv(void){
    char op;
    do
    {
        printf("\n\n\n------------------------------------------------------------------------------------");
        printf("\nGestao das avarias");
        printf("\n------------------------------------------------------------------------------------");
        printf("\nDados de avarias:");
        printf("\n \tR - Registar avaria");
        printf("\n \tL - Listar dados de avarias");
        printf("\n \tC - Consultar dados de avarias");
        printf("\n \tE - Eliminar avarias incorretamente registadas");
        printf("\n \tV - Voltar");
        printf("\n Opcao:");
        scanf(" %c", &op);
        op = toupper(op);
        if(op != 'R' && op != 'L' && op != 'C' && op != 'E' && op != 'V')
        {
            printf("\nOpcao invalida");
        }
    }
    while(op != 'R' && op != 'L' && op != 'C' && op != 'E' && op != 'V');
    return op;
}

char menuEquip(void){
    char op;
    do
    {
        printf("\n\n\n------------------------------------------------------------------------------------");
        printf("\nGestao dos equipamentos");
        printf("\n------------------------------------------------------------------------------------");
        printf("\nDados dos equipamentos:");
        printf("\n \tR - Registar instalacao, reparacao ou abate de equipamento");
        printf("\n \tL - Listar dados de equipamentos");
        printf("\n \tC - Consultar dados de equipamentos");
        printf("\n \tI - Inventariacao de equipamentos");
        printf("\n \tV - Voltar");
        printf("\n Opcao:");
        scanf(" %c", &op);
        op = toupper(op);
        if(op != 'R' && op != 'L' && op != 'C' && op != 'I' && op != 'V')
        {
            printf("\nOpcao invalida");
        }
    }
    while(op != 'R' && op != 'L' && op != 'C' && op != 'I' && op != 'V');
    return op;
}

char menuLab(void){
    char op;
    do
    {
        printf("\n\n\n------------------------------------------------------------------------------------");
        printf("\nGestao dos laboratorios");
        printf("\n------------------------------------------------------------------------------------");
        printf("\nDados dos laboratorios:");
        printf("\n \tI - Inserir dados dos laboratorios");
        printf("\n \tL - Listar dados dos laboratorios");
        printf("\n \tC - Consultar dados dos laboratorios");
        printf("\n \tA - Alterar dados dos laboratorios");
        printf("\n \tV - Voltar");
        printf("\n Opcao:");
        scanf(" %c", &op);
        op = toupper(op);
        if(op != 'I' && op != 'L' && op != 'C' && op != 'A' && op != 'V')
        {
            printf("\nOpcao invalida");
        }
    }
    while(op != 'I' && op != 'L' && op != 'C' && op != 'A' && op != 'V');
    return op;
}

char menuAlterarLab(void){
    char op;
    printf("\nQue dados pretende alterar?\n");
    printf("\nA - Nome");
    printf("\nB - Local");
    printf("\nC - Quantidade de postos de trabalho");
    printf("\nD - Quantidade de equipamentos");
    printf("\nV - Voltar");
    printf("\nOpcao: ");
    scanf(" %c",&op);
    return op;
}

//Fim de funcoes de menu -------------------------------------

//FUNÇOES -> GESTAO LABORATORIOS -----------------------------

void inserirLaboratorio(int *nLabs, tLab vLab[MAX_LAB]){
    int encontrado = -1;
    if(*nLabs < MAX_LAB)
    {
        limparBufferStdin();
        lerString("\nNome do laboratorio: ", vLab[*nLabs].lNome,MAX_LNOME);
        encontrado = pesquisarNomeLab(vLab[*nLabs].lNome,vLab,*nLabs);
        if(encontrado != -1)
        {
            printf("\n Nome ja existe. Volte a inserir.");
        }

        lerString("\nNome do local:", vLab[*nLabs].lLocal,MAX_LNOME);
        vLab[*nLabs].lPostoTrab = lerInteiro("\nQuantidade de posto de trabalho: ",MIN_NUM,MAX_NUM);
        vLab[*nLabs].lQuantEquip = lerInteiro("\nQuantidade de equipamentos: ",MIN_NUM,MAX_NUM);
    }
    else
    {
        printf("\nAtingiu o numero maximo de laboratorios.");
    }
    (*nLabs)++;
}

void listarLaboratorios(int nLabs, tLab vLab[MAX_LAB]){
    int i;
    if(nLabs > 0){
        printf("\nLISTAGEM DOS LABORATORIOS");
        for(i=0; i< nLabs; i++)
        {
            printf("\n");
            printf("\nNome do laboratorio: %s",vLab[i].lNome);
            printf("\nLocal do laboratorio: %s",vLab[i].lLocal);
            printf("\nNumero total de postos de trabalho: %d",vLab[i].lPostoTrab);
            printf("\nNumero total de equipamentos: %d",vLab[i].lQuantEquip);

        }
    }
    else
    {
        printf("\nNao existem quaisquer laboratorios para listar.");
    }
}

void alterarLaboratorios(int nLabs, tLab vLab[MAX_LAB]){
    if(nLabs > 0)
    {
        int posicao = -1;
        do
        {
            limparBufferStdin();
            lerString("\nIndique o nome do laboratorio no qual deseja alterar dados: ", vLab[nLabs].lNome, MAX_LNOME);
            posicao = pesquisarNomeLab(vLab[nLabs].lNome,vLab,nLabs);
            if(posicao != -1)
            {
                char op;
                op = menuAlterarLab();
                switch(op)
                {
                case 'A':
                    limparBufferStdin();
                    lerString("\nIndique o nome alterado: ",vLab[posicao].lNome,MAX_LNOME);
                    break;
                case 'B':
                    limparBufferStdin();
                    lerString("\nIndique o local alterado: ",vLab[posicao].lLocal,MAX_LOCAL);
                    break;
                case 'C':
                    vLab[posicao].lPostoTrab = lerInteiro("\nIndique a quantidade de postos de trabalho alterada: ",MIN_NUM,MAX_NUM);
                    break;
                case 'D':
                    vLab[posicao].lQuantEquip = lerInteiro("\nIndique a quantidade de equipamentos alterada: ",MIN_NUM,MAX_NUM);
                    break;
                case 'V':
                    break;
                default:
                    printf("\nOpcao invalida.");
                    break;
                }
            }
            else
            {
                printf("\nO nome que inseriu não é válido. Tente novamente.");
            }
        }while(posicao != -1);
    }
    else
    {
            printf("\nNao existe quaisquer laboratorios para alterar.");
    }
}

int pesquisarNomeLab(char nome[MAX_LNOME], tLab vLab[MAX_LAB],int nLabs){
    int i,pos = -1;
    for(i=0; i<nLabs; i++)
    {
        if(strcmp(vLab[i].lNome,nome) == 0)
        {
            pos = i;
            i = nLabs;
        }
    }
    return pos;
}

//FINAL FUNÇOES LABORATORIOS    -----------------------------



