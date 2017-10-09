#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED
#define TAM 1000
#include <string.h>

typedef struct{

    char nome[100];
    char fone[20];
} Contato;

typedef struct{

    Contato contatos[TAM];
    int total;
} Agenda;

void iniciar_agenda(Agenda *a){//Inicia a agenda

    a->total = 0;
}

int ins_contato(Agenda *agenda,Contato novo){

    if (agenda->total == TAM){
        return 0;
    }

    strcpy(agenda->contatos[agenda->total].nome,novo.nome);
    strcpy(agenda->contatos[agenda->total].fone,novo.fone);
    agenda->total++;

    return 1;
}

int rmv_contato(Agenda *agenda, int pos){

    int i;

    for(i = pos; i < agenda->total - 1; i++)
        agenda->contatos[i] = agenda->contatos[i+1];

    agenda->total --;

    return 1;

}

void ordenar(Agenda* agenda){
    int i;
    int j;
    Contato aux;

    for (i = 1; i < agenda->total; i++){
        for (j = 1; j < agenda->total; j++){
            if (strcmp(agenda->contatos[j-1].nome, agenda->contatos[j].nome) > 0){//verifica o valor retornado pela função para decidir se deve mudar de posição ou não
                aux = agenda->contatos[j-1];
                agenda->contatos[j-1] = agenda->contatos[j];
                agenda->contatos[j] = aux;
            }
        }
    }
}
void importar_contatos(Agenda *agenda){//le os contatos de um txt

    int i;

    FILE *arquivo =  fopen("contatos.txt","r");//Faz a abertura no modo leitura de arquivo

    if(!arquivo){//Caso o arquivo não exista ele é riado aqui, e um aviso é gerado que não há informações salvas
        printf("Não foram encontrados dados para serem carregados.");
    }else{

        fscanf(arquivo,"%d\n",&agenda->total);

        if(agenda->total == 0)//se o arquivo existir mas não contiver contatos uma aviso será exibido tambem
            printf("Não foram encontrados dados para serem carregados.");

        for (i = 0; i < agenda->total; i++){

                fscanf(arquivo,"%s\n",&agenda->contatos[i].nome);

                fscanf(arquivo,"%s\n",&agenda->contatos[i].fone);

        }
    }
    int fclose(FILE *arquivo);
}

void exportar_contatos (Agenda agenda){//salva os contatos em um txt

    int i;

    FILE *arquivo =  fopen("contatos.txt","w+");

    if(!arquivo){
        printf("Não foram encontrados dados para serem carregados.");
        arquivo =  fopen("contatos.txt","w+");
    }

    fprintf(arquivo,"%d\n",agenda.total);

    for (i = 0; i < agenda.total; i++){

            fprintf(arquivo,"%s\n",agenda.contatos[i].nome);

            fprintf(arquivo,"%s\n",agenda.contatos[i].fone);

    }

    int fclose(FILE *arquivo);
}

#endif // AGENDA_H_INCLUDED
