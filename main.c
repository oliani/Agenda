/**
    Developed by Eduardo Luiz Oliani
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Agenda.h"
#include <windows.h>
#include <locale.h>

int inserir(Agenda *agenda);

void exibir_contatos(Agenda *agenda);

int remover_contato(Agenda *agenda);

void pesquisa_numerica(Agenda agenda);

int main()
{
    setlocale(LC_ALL,"Portuguese");

    system("color 0e");

    int valor;
    int controle;
    int sair = 0;
    char passe[20];
    Agenda agenda;

    controle = iniciar_agenda(&agenda);
    if (controle == 0){
        printf("Ocorreu um erro ao iniciar a agenda!");
        return EXIT_SUCCESS;
    }
    controle = importar_contatos(&agenda);
    if(controle == 0)
        printf("Nenhum contato salvo foi encontrado!");

    do{

        printf("\n\t\tMenu da agenda\n\n\t\t1 - Novo contato\n\t\t2 - Remover contato\n\t\t3 - Pesquisar por telefone\n\t\t4 - Pesquisar por nome\n\t\t5 - Exibir todos os contatos\n\t\t6 - Salvar e sair\n\n\t\tEscolha: ");
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
                ordenar(&agenda);
                controle = remover_contato(&agenda);
                if (controle == 1)
                    printf("Contato removido com sucesso!");
                else
                    printf("O contato não foi removido!");
                break;
            case 3:
                ordenar_numerica(&agenda);
                pesquisa_numerica(agenda);
                break;
            case 5:
                ordenar(&agenda);
                exibir_contatos(&agenda);
                break;
            case 6:
                ordenar(&agenda);
                controle = exportar_contatos(agenda);
                if (controle == 1)
                    printf("Contatos salvos com sucesso!");
                else
                    printf("Ocorreu um erro ao  salvar os contatos, ou não existem contatos a serem salvos!");
                sair = 1;
                break;
            default:
                break;
        }

    } while(sair == 0);


    return 0;

}

int inserir(Agenda *agenda){

    //Retorna 0 pra avisar que não foi possivel inserir o item, ou 1 se foi
    int i;
    Contato novo;

    printf("Digite o nome do novo contato: ");
    fflush(stdin);
    fgets(novo.nome,100,stdin);

    novo.nome[strlen(novo.nome)-1]= '\0';//Remove o caractere new line

    for (i = 0; i < strlen(novo.nome);i++)
        novo.nome[i] = toupper(novo.nome[i]);

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

    //Retorna 0 pra avisar que não foi possivel r item, ou 1 se foi
    int i;

    if (agenda->total == 0){
        printf("\t\tAgenda vazia!");
        return 0;
    }

    exibir_contatos(agenda);
    printf("Digite o número do contato a ser removido: ");
    scanf(" %d",&i);

    if(i < 1 || i > agenda->total){
        printf("Contato inexistente! Verifique o valor digitado.\n");
        return 0;
    }

    return rmv_contato(agenda,i-1);
}

void pesquisa_numerica(Agenda agenda){

    char passe[20];
    int controle;

    printf("Digite o numero do contato a ser pesquisado: ");
    fflush(stdin);
    fgets(passe,100,stdin);

    passe[strlen(passe) - 1] = '\0';

    controle = procura_binaria(agenda,passe);

    if(controle > -1)
        printf("Contato encontrado: Nome: %s  |  Fone: %s",agenda.contatos[controle].nome,agenda.contatos[controle].fone);
    else
        printf("Nenhum contato com o numero %s foi encontrado!",passe);

}
