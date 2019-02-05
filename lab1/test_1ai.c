#include <stdlib.h>
#include <unistd.h>
#include <threads.h>

#include "test_utils.h"

#define BUFFER_SIZE 20

void reader(void *);


// Tests reading.
int
main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    ThreadCreate(reader, NULL);

    ThreadWaitAll();

    sleep(10);

    struct termstat *stats = malloc(sizeof(struct termstat) * 4);
    TerminalDriverStatistics(stats);
    print_td_stats(stats);
    free(stats);

    exit(0);
}

void
reader(void *arg)
{
    char* buf = malloc(sizeof(char) * BUFFER_SIZE);

    for (int i = 0; i < 10; i++) {
        // Leave the last for null char...
        int num_char_read = ReadTerminal(1, buf, BUFFER_SIZE - 1);
        printf("Num of characters read : %d\n", num_char_read);
        printf("String read : ");
        print_char_arr(buf, BUFFER_SIZE - 1);
    }
    free(buf);
}
