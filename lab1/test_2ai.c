#include <stdlib.h>
#include <unistd.h>
#include <threads.h>

#include "test_utils.h"

#define BUFFER_SIZE 10

void reader1(void *);
void reader2(void *);

// Tests reading.
int
main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    ThreadCreate(reader1, NULL);
    ThreadCreate(reader2, NULL);

    ThreadWaitAll();

    sleep(10);

    struct termstat *stats = malloc(sizeof(struct termstat) * 4);
    TerminalDriverStatistics(stats);
    print_td_stats(stats);
    free(stats);

    exit(0);
}

void
reader1(void *arg)
{
    char* buf = malloc(sizeof(char) * BUFFER_SIZE);

    for (int i = 0; i < 10; i++) {
        int num_char_read = ReadTerminal(1, buf, BUFFER_SIZE - 1);
        printf("Reader 1\n", num_char_read);
        printf("Num of characters read : %d\n", num_char_read);
        printf("String read from terminal %d : ", 1);
        print_char_arr(buf, BUFFER_SIZE - 1);
    }
    free(buf);
}

void
reader2(void *arg)
{
    char* buf = malloc(sizeof(char) * BUFFER_SIZE);

    for (int i = 0; i < 5; i++) {
        int num_char_read = ReadTerminal(1, buf, BUFFER_SIZE - 1);
        printf("Reader 2\n", num_char_read);
        printf("Num of characters read : %d\n", num_char_read);
        printf("String read from terminal %d : ", 1);
        print_char_arr(buf, BUFFER_SIZE - 1);
    }
    free(buf);
}