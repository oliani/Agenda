/**
    Developed by Eduardo Luiz Oliani
*/

#include <stdio.h>
#include "Agenda.h"
#include <windows.h>
#include <locale.h>

int inserir(Agenda *agenda);

void exibir_contatos(Agenda *agenda);

int remover_contato(Agenda *agenda);

void pesquisa_numerica(Agenda agenda);

void pesquisar_nome(Agenda agenda);

int main()
{
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
                bb_sort(&agenda);
                procurar_numero(agenda);
                break;
            case 4:
                pesquisar_nome(agenda);
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

    int i;
    char fone[20];
    int aux;
    int aux2;
    Contato novo;

    printf("Digite o nome do novo contato: ");
    fflush(stdin);
    gets(novo.nome);

    for (i = 0; i < strlen(novo.nome);i++)
        novo.nome[i] = toupper(novo.nome[i]);

    do{//Verificando se há contatos con nomes repetidos
        aux = 0;
        for(i = 0; i < agenda->total; i ++){
            if(strcmp(novo.nome,agenda->contatos[i].nome) == 0)
                aux++;
        }

        if(aux > 0){
            printf("Este nome j%c foi cadastrado, tente novamente: ",133);
            fflush(stdin);
            gets(novo.nome);
        }

        for (i = 0; i < strlen(novo.nome);i++)
            novo.nome[i] = toupper(novo.nome[i]);

    }while(aux > 0);

    printf("Digite o numero do novo contato: ");
    fflush(stdin);
    fgets(fone,20,stdin);
    fone[strlen(fone)-1]= '\0';
    do{
        aux = 0;
        aux2 = 0;
        for (i = 0; i < strlen(fone);i++){
            if(fone[i] > 47 && fone [i] < 58)
                aux++;
        }
        if(aux == strlen(fone)){
            novo.fone = atoi(fone);
            for(i = 0; i <= agenda->total;i++){
                if(novo.fone == agenda->contatos[i].fone)
                    aux2++;
            }
        }
        else{
            printf("Digite apenas n%cmeros! Tente novamente: ",163);
            fflush(stdin);
            gets(fone);
        }

        if (aux2 != 0){
            printf("N%cmero repetido! Tente novamente: ",163);
            fflush(stdin);
            gets(fone);
        }

    }while(aux != strlen(fone) && aux2 == 0);

    novo.fone = atoi(fone);

    return ins_contato(agenda,novo);
}

void exibir_contatos(Agenda *agenda){

    int i;

    if (agenda->total == 0)
        printf("Agenda vazia!");
    else{
        for (i = 0; i < agenda->total; i++){
            printf("%d  - Nome: %s  |  Fone: %d \n",i+1,agenda->contatos[i].nome,agenda->contatos[i].fone);
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

void pesquisar_nome(Agenda agenda){

    char key[100];
    int i;
    Agenda encontrados;

    printf("Digite o termo de pesquisa: ");
    fflush(stdin);
    fgets(key,100,stdin);

    for (i = 0; i < strlen(key);i++)
        key[i] = toupper(key[i]);

        key[strlen(key)-1] = '\0';

    encontrados = pesquisa_nominal(agenda,key);

    printf("Total encrontrados %d\n",encontrados.total);

    for(i = 0; i<encontrados.total; i++){
        printf("%d - Nome: %s  |  Fone: %d\n",i+1,encontrados.contatos[i].nome,encontrados.contatos[i].fone);
    }
    if(encontrados.total == 0)
        printf("Nenhum contato com o termo %s foi encontrado.",key);
}
void procurar_numero(Agenda agenda){

    int controle;
    char fone[20];
    long long key;
    int aux;
    int i;

    printf("Digite o numero do contato a ser pesquisado: ");
    fflush(stdin);
    gets(fone);
    do{
        aux = 0;
        for (i = 0; i < strlen(fone);i++){
            if(fone[i] > 47 && fone [i] < 58)
                aux++;
        }
        if(aux != strlen(fone)){
            printf("Digite apenas n%cmeros! Tente novamente: ",163);
            fflush(stdin);
            gets(fone);
        }
        key = atoi(fone);
        printf("key = %d",key);

    }while(aux != strlen(fone));

    controle = bi_search(agenda,key);

    if(controle > -1)
        printf("Contato encontrado: Nome: %s  |  Fone: %d",agenda.contatos[controle].nome,agenda.contatos[controle].fone);
    else
        printf("Nenhum contato com o número %d foi encontrado!",key);
}
