#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "coisas.h"
#include "list.h"
#include "commandlinereader.h"

#define EXIT_GLOBAL   "exit-global\n"
#define EXIT          "exit\n"
#define STATS         "stats\n"
#define LER 	      O_RDONLY
#define ESCREVER      O_WRONLY


int main(int argc, char* argv[]){

	char buffer[100];
	int entrada;

	entrada = open_file("par-shell-in", ESCREVER);

	sprintf_file(buffer, "new_terminal %d\n", getpid());

	write_file(entrada, buffer);

	while(1){

		if(fgets(buffer, 100, stdin) == NULL){
			perror("erro a ler do stdin");
			exit(EXIT_FAILURE);
		}
		

		if (strcmp(buffer, EXIT_GLOBAL) == 0){

			write_file(entrada, buffer);
			
			close(entrada);
			exit(EXIT_SUCCESS);	
    	}	


    	if (strcmp(buffer, EXIT) == 0){

			sprintf_file(buffer,"exit %d\n", getpid());
			write_file(entrada, buffer);

			close(entrada);	
      		exit(EXIT_SUCCESS);
   		}

    	if (strcmp(buffer, STATS) == 0){
    		int temp, status, total_process_time;
    		char buffer2[30];

    		
			sprintf_file(buffer2, "temp_fifo_%d", getpid());

      		make_fifo(buffer2);

			sprintf_file(buffer, "stats %d\n", getpid());

			write_file(entrada, buffer);
      		
      		temp = open_file(buffer2, LER); 

      		if(read(temp, buffer2, (sizeof(char)) * 30) < 0){
      			perror("Erro a ler");
				exit(EXIT_FAILURE);
      		}

      		sscanf(buffer2, "%d %d", &status, &total_process_time);

      		printf("Numero de filhos a correr: %d\t Tempo total de processos:%d\n", status, total_process_time);

			close(temp);
			unlink(buffer2);

    	}

    	else{

			write_file(entrada, buffer);
    	}
    }
}

