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

    printf("Digite o numero do novo contato: ");
    fflush(stdin);
    fgets(novo.fone,20,stdin);

    return ins_contato(agenda,novo);
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
            case 6:
                sair = 1;

            default:
                break;
        }

    } while(sair == 0);
    //printf("a = %d,\n Nome do contato: %s, \nnumero: %s",a,agenda.contatos[0].nome,agenda.contatos[0].fone);

    return 0;

}
