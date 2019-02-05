#include <stdlib.h>
#include <unistd.h>
#include <threads.h>

#include "test_utils.h"

#define BUFFER_SIZE 1000

void read_writer(void *);

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(0);
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    ThreadCreate(read_writer, NULL);

    ThreadWaitAll();

    struct termstat *stats = malloc(sizeof(struct termstat) * 4);
    TerminalDriverStatistics(stats);
    print_td_stats(stats);
    free(stats);

    exit(0);
}

void
read_writer(void *arg)
{
    char question[] = "Is this the real life or is this just fantasy?\n";
    char answer[] = "\nThis is just COMP421\n";
    char* buf = malloc(sizeof(char) * BUFFER_SIZE);
    char* buf2 = malloc(sizeof(char) * BUFFER_SIZE);

    for (int i = 0; i < 5; i++) {
        memset(buf, '\0', sizeof(char) * BUFFER_SIZE); 
        memset(buf2, '\0', sizeof(char) * BUFFER_SIZE); 
        WriteTerminal(1, question, sizeof(question) - 1);

        int num_char_read = ReadTerminal(1, buf, BUFFER_SIZE - 1);
        printf("Num of characters read : %d\n", num_char_read);
        printf("String read : ");
        print_char_arr(buf, BUFFER_SIZE - 1);

        int num_char_written = WriteTerminal(1, buf, strlen(buf) - 1);
        printf("Num of characters written = %d.\n", num_char_written);
        num_char_written = WriteTerminal(1, answer, sizeof(answer) - 1);
        printf("Num of characters written = %d.\n", num_char_written);
        
        WriteTerminal(0, question, sizeof(question) - 1);

        num_char_read = ReadTerminal(0, buf2, BUFFER_SIZE - 1);
        printf("Num of characters read : %d\n", num_char_read);
        printf("String read : ");
        print_char_arr(buf2, BUFFER_SIZE - 1);

        num_char_written = WriteTerminal(0, buf2, strlen(buf2) - 1);
        printf("Num of characters written = %d.\n", num_char_written);
        num_char_written = WriteTerminal(0, answer, sizeof(answer) - 1);
        printf("Num of characters written = %d.\n", num_char_written);
    }

    free(buf);
    free(buf2);
    return;
}