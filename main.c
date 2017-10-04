/**
    Developed by Eduardo Luiz Oliani
*/

#include <stdio.h>
#include <stdlib.h>
#include "Agenda.h"

int inserir(Agenda *agenda){

    //Retorna 0 pra avisar que não foi possivel inserir o item, ou 1 se foi

    Contato novo;

    printf("Digite o nome do novo contato: ");
    fflush(stdin);
    fgets(novo.nome,100,stdin);
    novo.nome[strlen(novo.nome)-1]= '\0';//Remove o caractere new line

    printf("Digite o numero do novo contato: ");
    fflush(stdin);
    fgets(novo.fone,20,stdin);
    novo.fone[strlen(novo.fone)-1]= '\0';

    return ins_contato(agenda,novo);
}

void exibir_contatos(Agenda *agenda){

    int i;

    if (agenda->total == 0)
        printf("Agenda vazia!");
    else{
        for (i = 0; i < agenda->total; i++){
            printf("%d  - Nome: %s  |  Fone: %s \n",i+1,agenda->contatos[i].nome,agenda->contatos[i].fone);
        }
    }
}

int remover_contato(Agenda *agenda){

    int i;

    if (agenda->total == 0){
        printf("\t\tAgenda vazia!\n\tNão há contatos para serem removidos!");
        return 0;
    }

    exibir_contatos(agenda);
    printf("Digite o número do contato a ser removido: ");
    scanf(" %d",&i);

    return rmv_contato(agenda,i-1);



}

int main()
{
    int valor;
    int controle;
    int sair = 0;
    Agenda agenda;
    iniciar_agenda(&agenda);
    do{
        printf("\n\t\tMenu da agenda\n\n\t\t1 - Novo contato\n\t\t2 - Remover contato\n\t\t3 - Pesquisar por telefone\n\t\t4 - Pesquisar por nome\n\t\t5 - Exibir todos os contatos\n\t\t6 - Sair\n\n\t\tEscolha: ");
        scanf(" %d",&valor);

        switch(valor){

            case 1:
                controle = inserir(&agenda);
                if (controle == 1)
                    printf("Contato adicionado com sucesso!");
                else
                    printf("O contato não foi adicionado, agenda cheia!");
                break;
            case 2:
                controle = remover_contato(&agenda);
                if (controle == 1)
                    printf("Contato removido com sucesso!");
                else
                    printf("O contato não foi removido, agenda vazia!");
                break;
            case 5:
                exibir_contatos(&agenda);
                break;
            case 6:
                sair = 1;

            default:
                break;
        }

    } while(sair == 0);
    //printf("a = %d,\n Nome do contato: %s, \nnumero: %s",a,agenda.contatos[0].nome,agenda.contatos[0].fone);

    return 0;

}
