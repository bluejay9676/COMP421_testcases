#include <stdlib.h>
#include <unistd.h>
#include <threads.h>

#include "test_utils.h"

#define BUFFER_SIZE 1000

void read_writer(void *);


char string[] = "Is this the real life? \nIs this just fantasy? \nCaught in a landslide \nNo escape from reality \nOpen your eyes \nLook up to the skies and see \nI'm just a poor boy, I need no sympathy \nBecause I'm easy come, easy go \nA little high, little low \nAnyway the wind blows, doesn't really matter to me, to me \nMama, just killed a man \nPut a gun against his head \nPulled my trigger, now he's dead \nMama, life had just begun \nBut now I've gone and thrown it all away \nMama, oh oh \nDidn't mean to make you cry \nIf I'm not back again this time tomorrow \nCarry on, carry on, as if nothing really matters \nToo late, my time has come \nSends shivers down my spine \nBody's aching all the time \nGoodbye everybody I've got to go \nGotta leave you all behind and face the truth \nMama, oh oh (anyway the wind blows) \nI don't want to die \nSometimes wish I'd never been born at all \n";

int length = sizeof(string) - 1;

// Tests writing.
int main(int argc, char **argv)
{
    InitTerminalDriver();
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

    for (int i = 0; i < 5; i++) {
        memset(buf, '\0', sizeof(char) * BUFFER_SIZE); 
        WriteTerminal(1, question, sizeof(question) - 1);

        int num_char_read = ReadTerminal(1, buf, BUFFER_SIZE - 1);
        printf("Num of characters read : %d\n", num_char_read);
        printf("String read : ");
        print_char_arr(buf, BUFFER_SIZE - 1);

        int num_char_written = WriteTerminal(1, buf, strlen(buf) - 1);
        printf("Num of characters written = %d.\n", num_char_written);
        num_char_written = WriteTerminal(1, answer, sizeof(answer) - 1);
        printf("Num of characters written = %d.\n", num_char_written);
        
    }

    free(buf);
    return;
}