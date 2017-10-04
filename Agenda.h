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



#endif // AGENDA_H_INCLUDED
