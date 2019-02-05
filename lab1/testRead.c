#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>
#include <hardware.h>

void reader(void *);

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(0);

    ThreadCreate(reader, NULL);
    
    ThreadWaitAll();
    fflush(stdout);
    exit(0);
}

void
reader(void *arg)
{
    int len1, len2, len3;
    char buf1[2];
    char buf2[10];
    char buf3[10];
    char buf4[10];

    printf("Writer is active.\n");
    fflush(stdout);
    len1 = ReadTerminal(0, buf1, 2);
    if (len1 != 2) {
        printf("FAIL: len1 should be 2. It is %d\n", len1);
        return;
    }
    if (buf1[0] != 'H' || buf1[1] != 'i') {
        printf("%c%c\n", buf1[0], buf1[1]);
        printf("FAIL: buf1 contains incorrect character(s). Modify the test to determine which one(s).\n");
        return;
    }
    printf("SUCCESS: buf1\n");
    fflush(stdout);

    len2 = ReadTerminal(0, buf2, 10);
    if (len2 != 1) {
        printf("FAIL: len2 should be 1. It is %d\n", len2);
        return;
    }
    if (buf2[0] != '\n') {
        printf("FAIL: buf2 does not contain a new line. It has: %c\n", buf2[0]);
        return;
    }
    printf("SUCCESS: buf2\n");
    fflush(stdout);

    len3 = ReadTerminal(0, buf3, 10);
    if (len3 != 6) {
        printf("FAIL: len3 should be 6. It is %d\n", len3);
        return;
    }
    if (buf3[0] != 'W' || buf3[1] != 'o' || buf3[2] != 'r' || buf3[3] != 'l' || buf3[4] != 'd' || buf3[5] != '\n') {
        printf("FAIL: buf3 contains incorrect character(s). Modify the test to determine which one(s).\n");
        return;
    }
    printf("SUCCESS: buf3\nPress Enter in order to finish the test. Nothing beyond this is verified.\n");
    fflush(stdout);

    len1 = ReadTerminal(0, buf4, 10);

    printf("\n\n\nTest appears successful. Closing Terminal...\n\n\n");
    fflush(stdout);
    sleep(1);
}
