#include <stdlib.h>
#include <unistd.h>
#include <threads.h>

#include "test_utils.h"

#define BUFFER_SIZE 20

void reader1(void *);
void reader2(void *);
void reader3(void *);

// Tests reading.
int
main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);
    InitTerminal(2);
    InitTerminal(3);

    ThreadCreate(reader1, NULL);
    ThreadCreate(reader2, NULL);
    ThreadCreate(reader3, NULL);
    ThreadCreate(reader1, NULL);

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
        printf("Num of characters read from terminal %d : %d\n", 1, num_char_read);
        printf("String read from terminal %d : ", 1);
        print_char_arr(buf, BUFFER_SIZE - 1);
    }
    free(buf);
}

void
reader2(void *arg)
{
    char* buf = malloc(sizeof(char) * BUFFER_SIZE);

    for (int i = 0; i < 10; i++) {
        int num_char_read = ReadTerminal(2, buf, BUFFER_SIZE - 1);
        printf("Reader 2\n", num_char_read);
        printf("Num of characters read from terminal %d : %d\n", 2, num_char_read);
        printf("String read from terminal %d : ", 2);
        print_char_arr(buf, BUFFER_SIZE - 1);
    }
    free(buf);
}

void
reader3(void *arg)
{
    char* buf = malloc(sizeof(char) * BUFFER_SIZE);

    for (int i = 0; i < 10; i++) {
        int num_char_read = ReadTerminal(3, buf, BUFFER_SIZE - 1);
        printf("Reader 3\n", num_char_read);
        printf("Num of characters read from terminal %d : %d\n", 3, num_char_read);
        printf("String read from terminal %d : ", 3);
        print_char_arr(buf, BUFFER_SIZE - 1);
    }
    free(buf);
}