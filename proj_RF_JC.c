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
#define MAX_CUSTO 1500.00
#define MAX_PTRABALHO 100
#define MAX_DIA 30
#define MAX_MES 12
#define MIN_ANO 2016
#define MAX_ANO 2017


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
char menuConsultaEquip(void);
//LEITURA
int lerInteiro(char msg[],int minimo, int maximo);
float lerFloat(char msg[],float minimo, float maximo);
void lerString(char msg[],char nome[], int maxCaracteres);
void limparBufferStdin(void);
void limparEcra(void);
void lerData(tData *ldata);
//LABORATORIOS
void inserirLaboratorio(int *qPost,int *qLab, tLab vLab[MAX_LAB]);
void listarLaboratorios(int qLab, tLab vLab[MAX_LAB]);
void alterarLaboratorios(int qLab, tLab vLab[MAX_LAB]);
int pesquisarNomeLab(char nome[MAX_LNOME], tLab vLab[MAX_LAB],int qLab);
void pesquisarLocalLab(char plocal[MAX_LOCAL], tLab vLab[MAX_LAB], int qLab, int posC[qLab], int *nr);
void infoLab(tLab vLab);
//EQUIPAMENTOS
void inserirEquipamento(int *qEquip, tEquip vEquip[MAX_EQUIP]);
void listarEquipamentos(int qEquip, tEquip vEquip[MAX_EQUIP]);
int pesquisarNrSerie(char num[MAX_NSERIE], tEquip vEquip[MAX_EQUIP],int qEquip);
void pesquisarEquipE(char *estado, tEquip vEquip[MAX_EQUIP],int qEquip,int posC[qEquip],int *nr);
void pesquisarEquipD(tData *procura, tEquip vEquip[MAX_EQUIP],int qEquip,int posC[qEquip],int *nr);
void registaInstalacao(int qLab, tLab vLab[MAX_LAB],int qEquip, tEquip vEquip[MAX_EQUIP]);
void pesquisarEquipL(char local[MAX_LOCAL], tEquip vEquip[MAX_EQUIP],int qEquip,int posC[qEquip],int *nr);
void infoEquip(tEquip vEquip);
void consultaEquip(tEquip vEquip[MAX_EQUIP],int qEquip);
//SAVE/LOAD
void loadBinary(tEquip vEquip[MAX_EQUIP],tLab vLab[MAX_LAB],int *qEquip,int *qLab,int *qPost,float *qPerc);
void saveBinary(tEquip vEquip[MAX_EQUIP],tLab vLab[MAX_LAB],int qEquip,int qLab,int qPost,float qPerc);
char fichExiste(void);

int main(void)
{

    char op,op2;
    int qPost = 0,qEquip = 0,qLab = 0;
    float qPerc = 0;
    tLab vLab[MAX_LAB];
    tEquip vEquip[MAX_EQUIP];
    if(fichExiste() == 'S')
    {
        loadBinary(vEquip,vLab,&qEquip,&qLab,&qPost,&qPerc);
    }
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
                case 'I':
                    printf("\n\nInventariacao de equipamentos - inserir equipamento");
                    inserirEquipamento(&qEquip,vEquip);
                    break;
                case 'R':
                    printf("\n\n1(estado e local)Regista instalacao-instalar no lab, reparacao(avaria) ou abate de equipamento");
                    registaInstalacao(qLab,vLab,qEquip,vEquip);
                    break;
                case 'L':
                    printf("\n\nLista dados de equipamentos");
                    listarEquipamentos(qEquip,vEquip);
                    break;
                case 'C':
                    printf("\n\nConsulta dados de equipamentos");
                    consultaEquip(vEquip,qEquip);
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
                    inserirLaboratorio(&qPost,&qLab, vLab);
                    break;
                case 'L':
                    printf("\nListar laboratorios\n");
                    listarLaboratorios(qLab, vLab);
                    break;
                case 'C':
                    printf("Consultar laboratorios");
                    consultarLaboratorios(qLab,vLab);
                    break;
                case 'A':
                    printf("\nAlterar laboratorios\n");
                    alterarLaboratorios(qLab, vLab);
                    break;
                }
            }
            while(op2 != 'V');
            break;
        case 'O':
            loadBinary(vEquip,vLab,&qEquip,&qLab,&qPost,&qPerc);
            break;
        case 'G':
            saveBinary(vEquip,vLab,qEquip,qLab,qPost,qPerc);
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

float lerFloat(char msg[],float minimo, float maximo){
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

void lerData(tData *lData) {
    int maxDiasMes;

    lData->ano = lerInteiro("\nAno", MIN_ANO, MAX_ANO);
    lData->mes = lerInteiro("\nMes", 1, 12);

    switch (lData->mes)
    {
    case 2:
        if ((lData->ano % 400 == 0) || (lData->ano % 4 == 0 && lData->ano % 100 != 0))
        {
            maxDiasMes = 29;
        }
        else
        {
            maxDiasMes = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDiasMes = 30;
        break;
    default:
        maxDiasMes = 31;
    }
    lData->dia = lerInteiro("\nDia:", 1, maxDiasMes);
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
        printf("\n \tO - Obter dados de ficheiro binario");
        printf("\n \tG - Guardar dados em ficheiro binario");
        printf("\n \tS - Sair");
        printf("\n Opcao:");
        scanf(" %c", &op);
        op = toupper(op);
        if(op != 'A' && op != 'E' && op != 'L' && op != 'D' && op != 'O' && op != 'G' && op != 'S')
        {
            printf("\nOpcao invalida");
        }
    }
    while(op != 'A' && op != 'E' && op != 'L' && op != 'O' && op != 'G' && op != 'S');
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
        printf("\n \tI - Inventariacao de equipamentos");
        printf("\n \tR - Registar instalacao, reparacao ou abate de equipamento");
        printf("\n \tL - Listar dados de equipamentos");
        printf("\n \tC - Consultar dados de equipamentos");
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

char menuConsultaEquip(void){
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
        printf("\n V - Voltar");
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
void inserirLaboratorio(int *qPost,int *qLab, tLab vLab[MAX_LAB]){
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
        *qPost += vLab[*qLab].lPostoTrab;
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
            infoLab(vLab[i]);
        }
    }
    else
    {
        printf("\nNao existem quaisquer laboratorios para listar.");
    }
}

void alterarLaboratorios(int qLab, tLab vLab[MAX_LAB]){
    char op;
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
        }while(posicao != -1 && op!='V');
    }
    else
    {
            printf("\nNao existe quaisquer laboratorios para alterar.");
    }
}

void consultarLaboratorios(int qLab,tLab vLab[MAX_LAB]){
    char aConsulta[MAX_LAB],bConsulta[MAX_LOCAL];
    int pos = -1,posC[qLab],i;
    char op;
    do
    {
        printf("\nA - Por nome");
        printf("\nB - Por local");
        printf("\nV - Voltar");
        printf("\nOpcao: ");
        scanf(" %c",&op);
        op = toupper(op);
        limparBufferStdin();
        switch(op)
        {
        case 'A':
            lerString("\nIntroduza o nome do laboratorio que deseja consultar: ",aConsulta,MAX_LNOME);
            pos = pesquisarNomeLab(aConsulta,vLab,qLab);
            if(pos == -1)
            {
                printf("\nNao foi encontrado nenhum laboratorio com esse nome");
            }
            else
            {
                infoLab(vLab[pos]);
            }
            break;
        case 'B':
            do
            {
                lerString("\nIntroduza o local dos laboratorios que deseja consultar: ",bConsulta,MAX_LOCAL);
                pesquisarLocalLab(bConsulta,vLab,qLab,posC,&pos);
                if(pos != 0)
                {
                    for(i=0; i<pos; i++)
                    {
                        infoLab(vLab[posC[i]]);
                    }
                }
                else
                {
                    printf("\nNao foi encontrado nenhum local com esse nome");
                    printf("Deseja procurar novamente?\n[S]im \t[N]ao");
                    printf("\nOpcao: ");
                    scanf("%c",&op);
                    limparBufferStdin();
                }
            }
            while(pos == 0 && toupper(op) != 'N');
            break;
        }
    }while(op != 'V');

}

void pesquisarLocalLab(char plocal[MAX_LOCAL], tLab vLab[MAX_LAB], int qLab, int posC[qLab], int *nr){
    int i;
    *nr = 0;
    for(i=0; i<qLab; i++)
    {
        if(strcmpi(vLab[i].lLocal,plocal) == 0)
        {
            posC[*nr] = i;
            (*nr)++;
        }
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

void infoLab(tLab vLab){
    printf("\n-------------------------------------------------");
    printf("\nNome de laboratorio: %s",vLab.lNome);
    printf("\nLocal: %s",vLab.lLocal);
    printf("\nNumero de postos de trabalho: %d",vLab.lPostoTrab);
    printf("\nNumero de equipamentos: %d",vLab.lQuantEquip);
    printf("\n-------------------------------------------------");
}
//FINAL FUNÇOES LABORATORIOS    -----------------------------



//FUNÇOES -> GESTAO EQUIPAMENTOS
void inserirEquipamento(int *qEquip, tEquip vEquip[MAX_EQUIP]){
    int encontrado = -1;
    if(*qEquip < 200)
    {
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
        vEquip[*qEquip].nrInv = (*qEquip) + 1;
        vEquip[*qEquip].custo = lerFloat("\nCusto do equipamento: ",MIN_NUM,MAX_CUSTO);
        printf("\nIndique a data de inventariacao:");
        lerData(&vEquip[*qEquip].dInv);
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
 /*           printf("\n\nNumero de inventario: %d",vEquip[i].nrInv);
            printf("\nNumero de serie: %s",vEquip[i].nSerie);
            printf("\nLocal: %s",vEquip[i].local);
            printf("\nCusto do equipamento: %.2f",vEquip[i].custo);
            printf("\nData de inventario: %d/%d/%d",vEquip[i].dInv.dia,vEquip[i].dInv.mes,vEquip[i].dInv.ano);
            printf("\nDescricao: %s",vEquip[i].nSerie);
            printf("\nEstado: %c",vEquip[i].estado);*/
            infoEquip(vEquip[i]);
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

void pesquisarEquipE(char *estado, tEquip vEquip[MAX_EQUIP],int qEquip,int posC[qEquip],int *nr){
    int i;
    *nr = 0;
    for(i=0; i<qEquip; i++)
    {
        if((*estado) == vEquip[i].estado)
        {
            posC[*nr] = i;
            (*nr)++;
        }
    }
}

void pesquisarEquipD(tData *procura, tEquip vEquip[MAX_EQUIP],int qEquip,int posC[qEquip],int *nr){
    int i;
    *nr = 0;
    for(i=0; i<qEquip; i++)
    {
        if(procura->dia == vEquip[i].dInv.dia && procura->mes == vEquip[i].dInv.mes && procura->ano == vEquip[i].dInv.ano)
        {
            posC[*nr] = i;
            (*nr)++;
        }
    }
}

void pesquisarEquipL(char plocal[MAX_LOCAL], tEquip vEquip[MAX_EQUIP],int qEquip,int posC[qEquip],int *nr){
    int i;
    *nr = 0;
    for(i=0; i<qEquip; i++)
    {
        if(strcmpi(vEquip[i].local,plocal) == 0)
        {
            posC[*nr] = i;
            (*nr)++;
        }
    }
}

void consultaEquip(tEquip vEquip[MAX_EQUIP],int qEquip){
    char nconsulta;
    char op;
    char ns[MAX_NSERIE];
    char local[MAX_LOCAL];
    int nr,posC[qEquip],i;
    tData procura;
    if(qEquip > 0)
    {
        op = menuConsultaEquip();
        switch(op)
        {
//Consulta por N Inventario
        case 'I':
            do
            {
                nr = lerInteiro("\nIntroduza o numero de Inventario: ",1,MAX_EQUIP);
                nr = pesquisarEquipI(nr,vEquip,qEquip);
                if(nr == -1)
                {
                    printf("\nNão foi encontrado nenhum equipamento com o numero de inventario escolhido.");
                    printf("Deseja procurar novamente?\n[S]im \t[N]ao");
                    printf("\nOpcao: ");
                    scanf("%c",&nconsulta);
                    nconsulta = toupper(nconsulta);
                    limparBufferStdin();
                }
                else
                {
                    infoEquip(vEquip[nr]);
                }
            }
            while(nr == -1 && nconsulta!='N');
            break;
//Consulta por Estado
        case 'E':
            do
            {
                do{
                printf("\nEscolha uma das opcoes: \n\t[D]isponivel\n\t[I]ndisponivel\n\t[A]batido\nEscolha uma das opcoes: ");
                scanf("%c", &nconsulta);
                nconsulta = toupper(nconsulta);
                limparBufferStdin();
                if(nconsulta != 'D' && nconsulta != 'I' && nconsulta != 'A'){
                    printf("\nOpcao Invalida!\n");
                }
                }while(nconsulta != 'D' && nconsulta != 'I' && nconsulta != 'A');
                pesquisarEquipE(&nconsulta,vEquip,qEquip,posC,&nr);
                if(nr != 0)
                {
                    for(i=0; i<nr; i++)
                    {
                        infoEquip(vEquip[posC[i]]);
                    }
                }
                else
                {
                    printf("\nNao foi encontrado nenhum equipamento para a opcao escolhida.");
                    printf("Deseja procurar novamente?\n[S]im \t[N]ao");
                    printf("\nOpcao: ");
                    scanf("%c",&nconsulta);
                    nconsulta = toupper(nconsulta);
                    limparBufferStdin();
                }
            }
            while(nr == 0 && nconsulta!='N');
            break;
//Consulta por Data
        case 'D':
            do
            {
                lerData(&procura);
                pesquisarEquipD(&procura,vEquip,qEquip,posC,&nr);
                if(nr != 0)
                {
                    for(i=0; i<nr; i++)
                    {
                        infoEquip(vEquip[posC[i]]);
                    }
                }
                else
                {
                    printf("\nNao foi encontrado nenhum equipamento.");
                    printf("Deseja procurar novamente?\n[S]im \t[N]ao");
                    printf("\nOpcao: ");
                    scanf("%c",&nconsulta);
                    nconsulta = toupper(nconsulta);
                    limparBufferStdin();
                }
            }
            while(nr == 0 && nconsulta!='N');
            break;
//Consulta por N Serie
        case 'S':
            do
            {
                lerString("\nIntroduza o numero de serie que deseja pesquisar: ",ns,MAX_NSERIE);
                nr = pesquisarNrSerie(ns,vEquip,qEquip);
                if(nr != -1)
                {
                    infoEquip(vEquip[nr]);
                }
                else
                {
                    printf("\nNao foi encontrado nenhum equipamento.");
                    printf("Deseja procurar novamente?\n[S]im \t[N]ao");
                    printf("\nOpcao: ");
                    scanf("%c",&nconsulta);
                    nconsulta = toupper(nconsulta);
                    limparBufferStdin();
                }
            }
            while(nr == -1 && nconsulta!='N');
            break;
//Consulta por Local
        case 'L':
            do
            {
                lerString("\nIntroduza a localizacao: ",local,MAX_LOCAL);
                pesquisarEquipL(local,vEquip,qEquip,posC,&nr);
                if(nr != 0)
                {
                    for(i=0; i<nr; i++)
                    {
                        infoEquip(vEquip[posC[i]]);
                    }
                }
                else
                {
                    printf("\nNenhum foi encontrado nenhum equipamento para localizacao escolhida.");
                    printf("Deseja procurar novamente?\n[S]im \t[N]ao");
                    printf("\nOpcao: ");
                    scanf("%c",&nconsulta);
                    nconsulta = toupper(nconsulta);
                    limparBufferStdin();
                }
            }
            while(nr == 0 && nconsulta!='N');
            break;

        }
    }
    else{
        printf("Nao existem equipamentos para consultar");
    }
}

void infoEquip(tEquip vEquip){
    char estado[13];
    if(vEquip.estado == 'D')
    {
        strcpy(estado,"Disponivel");
    }
    else if(vEquip.estado == 'I'){
        strcpy(estado,"Indisponivel");
    }
    else if(vEquip.estado == 'A'){
        strcpy(estado,"Abatido");
    }
    printf("\n-------------------------------------------------");
    printf("\nNumero de inventario: %d",vEquip.nrInv);
    printf("\nNumero de serie: %s",vEquip.nSerie);
    printf("\nDescricao do equipamento: %s",vEquip.desc);
    printf("\nEstado: %s",estado);
    printf("\nLocal: %s",vEquip.local);
    printf("\nCusto: %.2f",vEquip.custo);
    printf("\nData de aquisicao: %02d/%02d/%02d",vEquip.dInv.dia,vEquip.dInv.mes,vEquip.dInv.ano);
    printf("\n-------------------------------------------------");
}

void registaInstalacao(int qLab, tLab vLab[MAX_LAB],int qEquip, tEquip vEquip[MAX_EQUIP]){
    int posSerie=-1,posLab=-1;
    char nome[MAX_LNOME],nSerie[MAX_NSERIE];
    do
    {
        printf("\n\n1 - DO");
        lerString("\nQual o numero de serie do equipamento que deseja registar: ",nSerie,MAX_NSERIE);
        posSerie = pesquisarNrSerie(nSerie,vEquip,qEquip);
        if(posSerie != -1)
        {
            printf("\n\n1 - IF");
            limparBufferStdin();
            do
            {
                printf("\n\n2 - DO");
                lerString("\nQual o nome do laboratorio para a instalacao: ",nome,MAX_LNOME);
                posLab = pesquisarNomeLab(nome,vLab,qLab);
                if(posLab != -1)
                {
                    printf("\n\n2 - IF \nValor de posSerie = %d\nValor de posLab = %d",posSerie,posLab);
                    strncpy(vEquip[posSerie].local,vLab[posLab].lLocal,MAX_LNOME);
                }
            }
            while(posLab == -1);
        }
    }
    while(posSerie != -1);
    printf("\n\nFIM");
}

//FINAL FUNÇOES EQUIPAMENTOS


//INICIO FICHEIRO
void saveBinary(tEquip vEquip[MAX_EQUIP],tLab vLab[MAX_LAB]/*,tAvaria vAvaria*/,int qEquip,int qLab,int qPost,float qPerc){
    FILE *ficheiro;
    int sElementos[2];
    ficheiro = fopen("data.bin","wb");

    if(ficheiro == NULL){
        printf("Nao foi possivel abrir o ficheiro para escrita");
    }
    else{
        fwrite(&qEquip,sizeof(int),1,ficheiro);
        fwrite(&qLab,sizeof(int),1,ficheiro);
        fwrite(&qPost,sizeof(int),1,ficheiro);
        fwrite(&qPerc,sizeof(float),1,ficheiro);
        sElementos[0] = fwrite(vEquip,sizeof(tEquip),qEquip,ficheiro);
        sElementos[1] = fwrite(vLab,sizeof(tLab),qLab,ficheiro);
        if(sElementos[0]<qEquip){
            printf("Apenas foi possivel gravar %d equipamentos",sElementos[0]);
        }
        if(sElementos[1]<qLab){
            printf("Apenas foi possivel gravar %d laboratorios",sElementos[1]);
        }
        if(fclose(ficheiro) == EOF){
            perror("Ocorreu um erro ao fechar o ficheiro");
        }
    }
}

void loadBinary(tEquip vEquip[MAX_EQUIP],tLab vLab[MAX_LAB]/*,tAvaria vAvaria*/,int *qEquip,int *qLab,int *qPost,float *qPerc){
    FILE *ficheiro;
    int lElementos[2];
    ficheiro = fopen("data.bin","rb");
    if(ficheiro == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro para leitura");
    }
    else{
        fread(qEquip,sizeof(int),1,ficheiro);
        fread(qLab,sizeof(int),1,ficheiro);
        fread(qPost,sizeof(int),1,ficheiro);
        fread(qPerc,sizeof(float),1,ficheiro);
        lElementos[0] = fread(vEquip,sizeof(tEquip),*qEquip,ficheiro);
        lElementos[1] = fread(vLab,sizeof(tLab),*qLab,ficheiro);
        if(lElementos[0]<*qEquip){
            printf("\nApenas foi possivel ler %d equipamentos",lElementos[0]);
        }
        if(lElementos[1]<*qLab){
            printf("\nApenas foi possivel ler %d laboratorios",lElementos[1]);
        }
        if(fclose(ficheiro) == EOF){
            perror("\nOcorreu um erro ao fechar o ficheiro");
        }else{
            printf("\nFicheiro aberto com sucesso!\n");
        }
    }
}

char fichExiste(void){
    char op = 'N';
    FILE *fp = fopen ("data.bin", "rb");
    if (fp!=NULL){
        fclose(fp);
        do{
            printf("\nDados guardados encontrados.Deseja abrir?\n[S]im\t[N]ao \n Opcao: ");
            scanf(" %c", &op);
            op = toupper(op);
            limparBufferStdin();
            if(op != 'S' && op!='N'){
                printf("Opçao Invalida!");
            }
        }while(op != 'S' && op!='N');
    }
    return op;
}
//FINAL FICHEIRO
