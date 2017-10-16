#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED
#define TAM 1000
#include <string.h>
/**
    Developed by Eduardo Luiz Oliani
*/
typedef struct{

    char nome[100];
    long long fone;
} Contato;

typedef struct{

    Contato contatos[TAM];
    int total;
} Agenda;

int iniciar_agenda(Agenda *a){

    a->total = 0;

    if(a->total != 0)
        return 0;

    return 1;
}

int ins_contato(Agenda *agenda,Contato novo){

    if (agenda->total == TAM){
        return 0;
    }

    agenda->contatos[agenda->total] = novo;
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
void bb_sort(Agenda* agenda){

	int i;
	int j;
	int cond = 1;
	Contato aux;

	for (i =(agenda->total) - 1; (i >= 1) && (cond == 1); i--){
		cond = 0;
		for (j=0; j < i ;j++){
			if (agenda->contatos[j+1].fone < agenda->contatos[j].fone){
				aux = agenda->contatos[j];
				agenda->contatos[j] = agenda->contatos[j+1];
				agenda->contatos[j+1] = aux;
				cond = 1;
			}
		}
	}
}

int bi_search(Agenda agenda, long long key){

      int inicio = 0;
      int fim = agenda.total - 1;
      int meio;
      while(inicio <= fim)
      {
            meio = (inicio + fim) / 2;
            if(key > agenda.contatos[meio].fone)
                  inicio = meio + 1;
            else if(key < agenda.contatos[meio].fone)
                  fim = meio - 1;
            else
                  return meio;
      }
      return -1;
}

Agenda pesquisa_nominal(Agenda agenda, char keyword[100]){

    int i;
    int j;
    int aux;
    int k;
    Agenda encontrados;
    encontrados.total = 0;

    for(i = 0; i < agenda.total; i++){
        aux = 0;
        for(j = 0; j < strlen(agenda.contatos[i].nome) ; j++){
            if(agenda.contatos[i].nome[j] == keyword[0]){
                for (k = 0; k < strlen(keyword);k++,j++){
                    if(agenda.contatos[i].nome[j] == keyword[k]){
                        aux++;
                    }
                }
            }
        }
        if(aux >= strlen(keyword)){
            encontrados.contatos[encontrados.total] = agenda.contatos[i];
            encontrados.total++;
        }
    }
    return encontrados;
}

int importar_contatos(Agenda *agenda){//le os contatos de um txt

    int i;

    FILE *arquivo =  fopen("contatos.txt","r");//Faz a abertura no modo leitura de arquivo

    if(!arquivo){//Caso o arquivo não exista ele é riado aqui, e um aviso é gerado que não há informações salvas
        return 0;
    }else{

        fscanf(arquivo,"%d\n",&agenda->total);

        if(agenda->total == 0)//se o arquivo existir mas não contiver contatos uma aviso será exibido tambem
            return 0;

        for (i = 0; i < agenda->total; i++){

                fscanf(arquivo,"%s\n",&agenda->contatos[i].nome);

                fscanf(arquivo,"%d\n",&agenda->contatos[i].fone);
        }
    }
    int fclose(FILE *arquivo);
    return 1;
}

int exportar_contatos (Agenda agenda){//salva os contatos em um txt

    if (agenda.total < 1)
        return 0;

    int i;

    FILE *arquivo =  fopen("contatos.txt","w+");

    if(!arquivo)
        arquivo =  fopen("contatos.txt","w+");


    fprintf(arquivo,"%d\n",agenda.total);

    for (i = 0; i < agenda.total; i++){

            fprintf(arquivo,"%s\n",agenda.contatos[i].nome);

            fprintf(arquivo,"%d\n",agenda.contatos[i].fone);

    }

    int fclose(FILE *arquivo);
    return 1;
}

#endif // AGENDA_H_INCLUDED
