/*
 * list.h - definitions and declarations of the integer list 
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>



/* lst_iitem - each element of the list points to the next element */
typedef struct lst_iitem {
   int pid;
   time_t starttime;
   time_t endtime;
   int status;
   struct lst_iitem *next;
} lst_iitem_t;

/* list_t */
typedef struct {
   lst_iitem_t * first;
} list_t;



typedef struct item_pid{
   int pid;
   struct item_pid *next;
} lista_pid;

/* list_t */
typedef struct {
   lista_pid * first;
}lista_pid_t;



/* lst_new - allocates memory for list_t and initializes it */
list_t* lst_new();

/* lst_destroy - free memory of list_t and all its items */
void lst_destroy(list_t *);

/* insert_new_process - insert a new item with process id and its start time in list 'list' */
void insert_new_process(list_t *list, int pid, time_t starttime);

/* update_terminated_process - updates endtime of element with pid 'pid' */
void update_terminated_process(list_t *list, int pid, time_t endtime, int status);

/* lst_print - print the content of list 'list' to standard output */
void lst_print(list_t *list);

/* process_start - returns the starttime of process 'pid' in list 'list'*/
int process_start(list_t *list, int pid);



lista_pid_t* nova_lista();

void destroi_lista(lista_pid_t *lista);

void insere_novo_processo(lista_pid_t *lista, int pid);

void destroi_processo(lista_pid_t* lista, int pid);
#endif
