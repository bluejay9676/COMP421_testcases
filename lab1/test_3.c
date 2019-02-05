#include <stdlib.h>
#include <unistd.h>
#include <threads.h>

#include "test_utils.h"

#define BUFFER_SIZE 20

void reader(void *);
void writer(void *);

void reader_wrong_term(void *);
void writer_wrong_term(void *);

char string[] = "COMP 421\n";
int length = sizeof(string) - 1;

// a. WriteTerminal : test_3a
//     b. ReadTerminal : test_3b

int
main(int argc, char **argv)
{
    int ret = 0;
    ret = InitTerminalDriver();
    ThreadCreate(reader, NULL); // Should be outputing -1
    ThreadCreate(writer, NULL); // Should be outputing -1
    if (ret == -1) {
        printf("FAIL InitTerminalDriver should return 0 not -1\n");
        return;
    }
    // Error InitTerminal
    ret = InitTerminalDriver();
    if (ret == 0) {
        printf("FAIL InitTerminalDriver should return -1 not 0\n");
        return;
    }

    ret = InitTerminal(1);
    if (ret == -1) {
        printf("FAIL InitTerminal should be 0 not -1\n");
        return;
    }

    ret = InitTerminal(1);
    if (ret == 0) {
        printf("FAIL InitTerminal should return -1 not 0\n");
        return;
    }


    ThreadCreate(reader_wrong_term, NULL); // out of bound term
    ThreadCreate(writer_wrong_term, NULL); // out of bound term

    ThreadWaitAll();

    sleep(1);

    struct termstat *stats = NULL;
    ret = TerminalDriverStatistics(stats);
    if (ret == 0) {
        printf("FAIL TerminalDriverStatistics should return -1 not 0\n");
        print_td_stats(stats);
        return;
    }
    stats = malloc(sizeof(struct termstat) * 4);
    ret = TerminalDriverStatistics(stats);
    if (ret == -1) {
        printf("FAIL TerminalDriverStatistics should be 0 not -1\n");
        print_td_stats(stats);
        return;
    }
    free(stats);

    exit(0);
}

void
reader(void *arg)
{
    char* buf = malloc(sizeof(char) * BUFFER_SIZE);

    // Leave the last for null char...
    int num_char_read = ReadTerminal(1, buf, BUFFER_SIZE - 1);
    printf("0 Num of characters read : %d\n", num_char_read);
    free(buf);
}

void
writer(void *arg)
{
    int num_char_written = WriteTerminal(1, string, length);
    printf("0 Num of characters written = %d.\n", num_char_written);
    fflush(stdout);
}

void
reader_wrong_term(void *arg)
{
    char* buf;

    int num_char_read = ReadTerminal(1, buf, BUFFER_SIZE - 1);
    printf("1 Num of characters read : %d\n", num_char_read);

    buf = malloc(sizeof(char) * BUFFER_SIZE);

    num_char_read = ReadTerminal(1, buf, BUFFER_SIZE - 1);
    printf("Correct // Num of characters read : %d\n", num_char_read);
    
    num_char_read = ReadTerminal(NUM_TERMINALS + 10, buf, BUFFER_SIZE - 1);
    printf("2 Num of characters read : %d\n", num_char_read);
    num_char_read = ReadTerminal(-100, buf, BUFFER_SIZE - 1);
    printf("3 Num of characters read : %d\n", num_char_read);

    num_char_read = ReadTerminal(1, buf, -1);
    printf("4 Num of characters read : %d\n", num_char_read);

    free(buf);
}

void
writer_wrong_term(void *arg)
{
    char* buf;
    int num_char_written = WriteTerminal(1, buf, length);
    printf("1 Num of characters written = %d.\n", num_char_written);

    num_char_written = WriteTerminal(1, string, length);
    printf("Correct // Num of characters written = %d.\n", num_char_written);

    num_char_written = WriteTerminal(NUM_TERMINALS + 10, string, length);
    printf("2 Num of characters written = %d.\n", num_char_written);
    num_char_written = WriteTerminal(-100, string, length);
    printf("3 Num of characters written = %d.\n", num_char_written);
    num_char_written = WriteTerminal(1, string, -1);
    printf("4 Num of characters written = %d.\n", num_char_written);
}

