void ficheiro_output(int pid);
void ficheiro_input();
void make_fifo(char* pipe);
int open_file(char* file, int restricoes);

void write_file(int file, char* buffer);

void sprintf_file(char* buffer, char* string, int pid);