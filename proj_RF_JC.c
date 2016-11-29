#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


//constantes
#define MIN_NUM 1
#define MAX_LNOME 12
#define MAX_LOCAL 30
#define MAX_LAB 15
#define MAX_DESC 150
#define MAX_NSERIE 15
#define MAX_EQUIP 200
#define MAX_CUSTO 5000.00
#define MAX_PTRABALHO 100
#define MAX_DIA 30
#define MAX_MES 12
#define MIN_ANO 2016
#define MAX_ANO 2017
#define MIN_D_ANO 2015
#define MAX_D_ANO 2016



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

//MENUS
char menu(int qLab, int qPost, int qEquip, float qPerc);
char menuAv(void);
char menuLab(void);
char menuEquip(void);
char menuAlterarLab(void);
//LEITURA
int lerInteiro(char msg[],int minimo, int maximo);
int lerFloat(char msg[],float minimo, float maximo);
void lerString(char msg[],char nome[], int maxCaracteres);
void limparBufferStdin(void);
void limparEcra(void);
//LABORATORIOS
void inserirLaboratorio(int *qLab, tLab vLab[MAX_LAB]);
void listarLaboratorios(int qLab, tLab vLab[MAX_LAB]);
void alterarLaboratorios(int qLab, tLab vLab[MAX_LAB]);
int pesquisarNomeLab(char nome[MAX_LNOME], tLab vLab[MAX_LAB],int qLab);
//EQUIPAMENTOS
void inserirEquipamento(int *qEquip, tEquip vEquip[MAX_EQUIP]);
void listarEquipamentos(int qEquip, tEquip vEquip[MAX_EQUIP]);
int pesquisarNrSerie(char num[MAX_NSERIE], tEquip vEquip[MAX_EQUIP],int qEquip);



int main(void){

    char op,op2;
    int qPost = 0,qEquip = 0,qLab = 0;
    float qPerc = 0;
    tLab vLab[MAX_LAB];
    tEquip vEquip[MAX_EQUIP];
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
                    printf("\n\nRegista avarias");
                    break;
                case 'L':
                    printf("\n\nListar avarias");
                    break;
                case 'C':
                    printf("\n\nConsultar avarias");
                    break;
                case 'E':
                    printf("\n\nEliminar avarias incorretas");
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
                    printf("\n\n1(estado e local)Regista instalacao-instalar no lab, reparacao(avaria) ou abate de equipamento");
                    break;
                case 'L':
                    printf("\n\nLista dados de equipamentos");
                    listarEquipamentos(qEquip,vEquip);
                    break;
                case 'C':
                    printf("\n\nConsulta dados de equipamentos");
                    consultaEquip(vEquip,qEquip);
                    break;
                case 'I':
                    printf("\n\nInventariacao de equipamentos - inserir equipamento");
                    inserirEquipamento(&qEquip,vEquip);
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
                    inserirLaboratorio(&qLab, vLab);
                    break;
                case 'L':
                    printf("\nListar laboratorios\n");
                    listarLaboratorios(qLab, vLab);
                    break;
                case 'C':
                    printf("Consultar laboratorios");
                    break;
                case 'A':
                    printf("\nAlterar laboratorios\n");
                    alterarLaboratorios(qLab, vLab);
                    break;
                }
            }
            while(op2 != 'V');
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
        if(op != 'A' && op != 'E' && op != 'L' && op != 'D' && op != 'S')
        {
            printf("\nOpcao invalida");
        }
    }
    while(op != 'A' && op != 'E' && op != 'L' && op != 'S');
    limparBufferStdin();
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
    limparBufferStdin();
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
    limparBufferStdin();
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
    limparBufferStdin();
    return op;
}


char menuAlterarLab(void){
    char op;
    do
    {
        printf("\nQue dados pretende alterar?\n");
        printf("\nA - Nome");
        printf("\nB - Local");
        printf("\nC - Quantidade de postos de trabalho");
        printf("\nD - Quantidade de equipamentos");
        printf("\nV - Voltar");
        printf("\nOpcao: ");
        scanf(" %c", &op);
        op = toupper(op);
        if(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'V')
        {
            printf("\nOpcao invalida");
        }
    }
    while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'V');

    limparBufferStdin();
    return op;
}


char menuConsultaEquip(){
    char op;
    do
    {
        printf("\n\n\n------------------------------------------------------------------------------------");
        printf("\nConsulta de Equipamentos");
        printf("\n------------------------------------------------------------------------------------");
        printf("\nProcurar por:");
        printf("\n \tI - Numero de Inventario");
        printf("\n \tE - Estado");
        printf("\n \tD - Data");
        printf("\n \tS - Numero de Serie");
        printf("\n \tL - Local");
        printf("\n \tV - Voltar");
        printf("\n Opcao:");
        scanf(" %c", &op);
        op = toupper(op);
        if(op != 'I' && op != 'E' && op != 'D' && op != 'S' && op!='L' && op != 'V')
        {
            printf("\nOpcao invalida");
        }
    }
    while(op != 'I' && op != 'E' && op != 'D' && op != 'S' && op!='L' && op != 'V');
    limparBufferStdin();
    return op;
}
//Fim de funcoes de menu -------------------------------------



//FUNÇOES -> GESTAO LABORATORIOS -----------------------------
void inserirLaboratorio(int *qLab, tLab vLab[MAX_LAB]){
    int encontrado = -1;
    if(*qLab < MAX_LAB)
    {
        do
        {
            lerString("\nNome do laboratorio: ", vLab[*qLab].lNome,MAX_LNOME);
            encontrado = pesquisarNomeLab(vLab[*qLab].lNome,vLab,*qLab);
            if(encontrado != -1)
            {
                printf("\n Nome ja existe. Volte a inserir.");
            }
        }
        while(encontrado != -1);
        lerString("\nNome do local:", vLab[*qLab].lLocal,MAX_LNOME);
        vLab[*qLab].lPostoTrab = lerInteiro("\nQuantidade de posto de trabalho: ",MIN_NUM,MAX_PTRABALHO);
        //vLab[*qLab].lQuantEquip = lerInteiro("\nQuantidade de equipamentos: ",MIN_NUM,MAX_EQUIP);
        vLab[*qLab].lQuantEquip = 0;
    }
    else
    {
        printf("\nAtingiu o numero maximo de laboratorios.");
    }
    (*qLab)++;
}

void listarLaboratorios(int qLab, tLab vLab[MAX_LAB]){
    int i;
    if(qLab > 0){
        printf("\nLISTAGEM DOS LABORATORIOS");
        for(i=0; i< qLab; i++)
        {
            printf("\n\nNome do laboratorio: %s",vLab[i].lNome);
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

void alterarLaboratorios(int qLab, tLab vLab[MAX_LAB]){
    if(qLab > 0)
    {
        int posicao = -1;
        do
        {
            limparBufferStdin();
            lerString("\nIndique o nome do laboratorio no qual deseja alterar dados: ", vLab[qLab].lNome, MAX_LNOME);
            posicao = pesquisarNomeLab(vLab[qLab].lNome,vLab,qLab);
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
                    vLab[posicao].lPostoTrab = lerInteiro("\nIndique a quantidade de postos de trabalho alterada: ",MIN_NUM,MAX_PTRABALHO);
                    break;
                case 'D':
                    vLab[posicao].lQuantEquip = lerInteiro("\nIndique a quantidade de equipamentos alterada: ",MIN_NUM,MAX_EQUIP);
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

int pesquisarNomeLab(char nome[MAX_LNOME], tLab vLab[MAX_LAB],int qLab){
    int i,pos = -1;
    for(i=0; i<qLab; i++)
    {
        if(strcmp(vLab[i].lNome,nome) == 0)
        {
            pos = i;
            i = qLab;
        }
    }
    return pos;
}

//FINAL FUNÇOES LABORATORIOS    -----------------------------



//FUNÇOES -> GESTAO EQUIPAMENTOS
void inserirEquipamento(int *qEquip, tEquip vEquip[MAX_EQUIP]){
    int encontrado = -1;
    if(*qEquip < 200)
    {
        vEquip[*qEquip].nrInv++;
        do
        {
            lerString("\nNumero de serie: ", vEquip[*qEquip].nSerie,MAX_NSERIE);
            encontrado = pesquisarNrSerie(vEquip[*qEquip].nSerie,vEquip,*qEquip);
            if(encontrado != -1)
            {
                printf("\nNumero de serie ja existe. Volte a inserir.");
            }
        }
        while(encontrado != -1);
        lerFloat("\nCusto do equipamento: ",MIN_NUM,MAX_CUSTO);
        printf("\nIndique a data de inventariacao:");
        vEquip[*qEquip].dInv.dia = lerInteiro("\n",MIN_NUM,MAX_DIA);
        vEquip[*qEquip].dInv.mes = lerInteiro("\n",MIN_NUM,MAX_MES);
        vEquip[*qEquip].dInv.ano = lerInteiro("\n",MIN_ANO,MAX_ANO);
        strcpy(vEquip[*qEquip].local,"Armazem");
        lerString("\nDescricao de equipamento: ",vEquip[*qEquip].desc,MAX_DESC);
        vEquip[*qEquip].estado = 'D';
        (*qEquip)++;
    }
    else
    {
        printf("\nAtingiu o numero maximo de equipamentos");
    }
}

void listarEquipamentos(int qEquip, tEquip vEquip[MAX_EQUIP]){
    int i;
    if(qEquip > 0){
        printf("\nLISTAGEM DOS EQUIPAMENTOS");
        for(i=0; i< qEquip; i++)
        {
            printf("\n\nNumero de inventario: %d",vEquip[i].nrInv);
            printf("\nNumero de serie: %s",vEquip[i].nSerie);
            printf("\nLocal: %s",vEquip[i].local);
            printf("\nCusto do equipamento: %.2f",vEquip[i].custo);
            printf("\nData de inventario: %d/%d/%d",vEquip[i].dInv.dia,vEquip[i].dInv.mes,vEquip[i].dInv.ano);
            printf("\nDescricao: %s",vEquip[i].nSerie);
            printf("\nEstado: %c",vEquip[i].estado);
        }
    }
    else
    {
        printf("\nNao existem quaisquer equipamentos para listar.");
    }
}

int pesquisarNrSerie(char num[MAX_NSERIE], tEquip vEquip[MAX_EQUIP],int qEquip){
    int i,pos = -1;
    for(i=0; i<qEquip; i++)
    {
        if(strcmp(vEquip[i].nSerie,num) == 0)
        {
            pos = i;
            i = qEquip;
        }
    }
    return pos;
}

int pesquisarEquipI(int nrI, tEquip vEquip[MAX_EQUIP],int qEquip){
    int i,pos = -1;
    for(i=0; i<qEquip; i++)
    {
        if(nrI == vEquip[i].nrInv)
        {
            pos = i;
            i = qEquip;
        }
    }
    return pos;
}

int pesquisarEquipE(char estado, tEquip vEquip[MAX_EQUIP],int qEquip,int *nr){
    int i,pos[qEquip];
    *nr = 0;
    for(i=0; i<qEquip; i++)
    {
        if(strcmp(vEquip[i].estado,estado) == 0)
        {
            pos[*nr] = i;
            *(nr)++;
        }
    }
    return pos;
}

int pesquisarEquipD(tData procura, tEquip vEquip[MAX_EQUIP],int qEquip,int *nr){
    int i,pos[qEquip];
    *nr = 0;
    for(i=0; i<qEquip; i++)
    {
        if(procura.dia == vEquip[i].dInv.dia && procura.mes == vEquip[i].dInv.mes && procura.ano == vEquip[i].dInv.ano)
        {
            pos[*nr] = i;
            *(nr++);
        }
    }
    return pos;
}

void lerData(tData lData) {
    lData.dia = lerInteiro("\nDia: ",1,31);
    lData.mes = lerInteiro("\nMes: ",1,12);
    lData.ano = lerInteiro("\nAno: ",MIN_D_ANO,MAX_D_ANO);
}


void consultaEquip(tEquip vEquip[MAX_EQUIP],int qEquip){
    limparEcra();
    char nconsulta;
    char op;
    int nr,posC[qEquip];
    tData procura;
    op = menuConsultaEquip();
    switch(op){
        case 'I':
            do{
                nr = lerInteiro("\nIntroduza o numero de Inventario: ",1,999999999);
                nr = pesquisarEquipI(nr,vEquip,qEquip);
                if(nr == -1){
                    printf("\nNão foi encontrado nenhum equipamento com o numero de inventario escolhido");
                }
                else{
                    infoEquip(vEquip[nr]);
                }
            }while(nr = -1);
            break;
        case 'E':
            lerString("\nEscolha uma das opcoes: \n\t[D]isponivel\n\t[I]ndisponivel\n\t[A]batido",nconsulta,1);
            pesquisarEquipE(nconsulta,vEquip,qEquip,&nr);
            break;
        case 'D':
            lerData(procura);
            pesquisarEquipD(procura,vEquip,qEquip,&nr);
            break;
        case 'S':
            break;
        case 'L':
            break;
        case 'V':
            break;
    }
}

void infoEquip(tEquip vEquip){
    printf("\nNumero de inventario: %d",vEquip.nrInv);
    printf("\nNumero de serie: %e",vEquip.nSerie);
    printf("\nDescricao do equipamento: %s",vEquip.desc);
    printf("\nEstado: %c",vEquip.estado);
    printf("\nLocal: %s",vEquip.local);
    printf("\nCusto: %.2f",vEquip.custo);
    printf("\nData de aquisicao: %2d/%2d/%2d",vEquip.dInv.dia,vEquip.dInv.mes,vEquip.dInv.ano);
}

//FINAL FUNÇOES EQUIPAMENTOS


void limparEcra(void){
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else if defined(_UNIX_) || defined(_LINUX_) || defined(_APPLE_)
    system("clear");
#endif // defined \

}
