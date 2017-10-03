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
    int a;

    Agenda agenda;
    iniciar_agenda(&agenda);

    printf("\n\t\tMenu da agenda\n\n\t\t1 - Novo contato\n\t\t2 - Remover contato\n\t\t3 - Pesquisar por telefone\n\t\t4 - Pesquisar por nome\n\t\t5 - Exibir todos os contatos\n\t\t6 - Sair\n\n\t\tEscolha: ");
    scanf(" %d",&a);



    if(a==1)
    a  = inserir(&agenda);

    printf("a = %d,\n Nome do contato: %s, \nnumero: %s",a,agenda.contatos[0].nome,agenda.contatos[0].fone);





    return 0;

}
