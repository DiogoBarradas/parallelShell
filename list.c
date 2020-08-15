/*
 * list.c - implementation of a linked list
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include "list.h"



list_t* lst_new()
{
   list_t *list;
   list = (list_t*) malloc(sizeof(list_t));
   list->first = NULL;
   return list;
}


void lst_destroy(list_t *list)
{
  struct lst_iitem *item, *nextitem;

  item = list->first;
  while (item != NULL){
    nextitem = item->next;
    free(item);
    item = nextitem;
  }
  free(list);
}


void insert_new_process(list_t *list, int pid, time_t starttime)
{
  lst_iitem_t *item;

  item = (lst_iitem_t *) malloc (sizeof(lst_iitem_t));
  item->pid = pid;
  item->starttime = starttime;
  item->endtime = 0;
  item->status = 0;
  item->next = list->first;
  list->first = item;
}

void update_terminated_process(list_t *list, int pid, time_t endtime, int status)
{
  lst_iitem_t *item;

  item = list->first;
  while(item != NULL) {
    if(item->pid == pid)
    {
      item->endtime = endtime;
      item->status = status;
      return;
    }
    item = item->next;
  }
  printf("list.c: update_terminated_process() error: pid %d not in list.\n", pid);
}


void lst_print(list_t *list)
{
  lst_iitem_t *item;

  printf("\nList of processes:\n");
  item = list->first;
  while (item != NULL){
    if(WIFEXITED(item->status))
      printf("pid: %d exited normally; status=%d.", item->pid, WEXITSTATUS(item->status));
    else
      printf("pid: %d terminated without calling exit.", item->pid);
    printf(" Execution time: %d s\n", (int)  (item->endtime - item->starttime));

    item = item->next;
  }
  printf("End of list.\n");
}

int process_start(list_t *list, int pid)
{
  lst_iitem_t *item;

  item = list->first;
  while(item != NULL) {
    if(item->pid == pid)
    {
      return item->starttime;
    }
    item = item->next;
  }
  return -1;
}






lista_pid_t* nova_lista()
{
   lista_pid_t *lista;
   lista = (lista_pid_t*) malloc(sizeof(lista_pid_t));
   lista->first = NULL;
   return lista;
}


void destroi_lista(lista_pid_t *lista)
{
  struct item_pid *item, *nextitem;

  item = lista->first;
  while (item != NULL){
    nextitem = item->next;
    free(item);
    item = nextitem;
  }
  free(lista);
}


void insere_novo_processo(lista_pid_t *lista, int pid)
{
  lista_pid *item;

  item = (lista_pid *) malloc (sizeof(lista_pid));
  item->pid = pid;
  item->next = lista->first;
  lista->first = item;
}


void destroi_processo(lista_pid_t* lista, int pid){
  lista_pid * temp_list, * temp_list2;

  if(lista->first->pid == pid){
    temp_list2 = lista->first;
    lista->first = lista->first->next;
    free(temp_list2);
  }

  for(temp_list = lista->first; temp_list != NULL; temp_list = temp_list->next){
    if(temp_list->next->pid == pid){
      temp_list2 = temp_list->next;
      temp_list->next = temp_list->next->next;
      free(temp_list2);
    }
  }

}




