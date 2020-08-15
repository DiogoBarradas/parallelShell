/*funcoes auxiliares*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


void ficheiro_output(int pid){

	int saida;
	char title[25];
	sprintf(title, "par-shell-in-%d.txt", pid);

	if((saida = open(title, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0){
		perror("Error opening the file");
		exit(EXIT_FAILURE);
	}

	
    if (close(STDOUT_FILENO) < 0) {
        perror("Erro a fechar STDOUT");
        close(saida);
        exit(EXIT_FAILURE);
    }
 
    
    if (dup(saida) != STDOUT_FILENO) {
        perror("Erro redirecionando a saida");
        close(saida); 
        exit(EXIT_FAILURE);
    }
 
    close(saida); 

}


void ficheiro_input(){

	int entrada;
	char title[25];
	sprintf(title, "par-shell-in");

	if((entrada = open(title, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR)) < 0){
		perror("Error opening the file");
		exit(EXIT_FAILURE);
	}


    if (close(STDIN_FILENO) < 0) {
        perror("Erro a fechar STDIN");
        close(entrada);
        exit(EXIT_FAILURE);
    }
 
    
    if (dup(entrada) != STDIN_FILENO) {
        perror("Erro redirecionando a saida");
        close(entrada); 
        exit(EXIT_FAILURE);
    }
 
    close(entrada); 

}


void make_fifo(char* pipe){

	if(unlink(pipe) < 0){
		if(errno != ENOENT){
			perror("Error unlink");
			exit(EXIT_FAILURE);
		}

	}

	if(mkfifo(pipe, 0666) < 0){
		perror("Error making fifo");
		exit(EXIT_FAILURE);
	}


}


int open_file(char* file, int restricoes){
	int entrada;
	if((entrada = open(file, restricoes)) < 0){
		perror("Erro a abrir");
		exit(EXIT_FAILURE);
	}

	return entrada;
}

void write_file(int file, char* buffer){

	if(write(file, buffer, strlen(buffer)) < 0){
		perror("erro a mandar mensagem");
		exit(EXIT_FAILURE);
	}

}


void sprintf_file(char* buffer, char* string, int pid){

	if(sprintf(buffer, string, pid) < 0){
		perror("erro a escrever no buffer");
		exit(EXIT_FAILURE);
	}
}














