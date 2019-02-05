#include <stdlib.h>
#include <unistd.h>
#include <threads.h>

#include "test_utils.h"

void writer(void *);

char string1[] = "Is this the real life? \nIs this just fantasy? \nCaught in a landslide \nNo escape from reality \nOpen your eyes \nLook up to the skies and see \nI'm just a poor boy, I need no sympathy \nBecause I'm easy come, easy go \nA little high, little low \nAnyway the wind blows, doesn't really matter to me, to me \nMama, just killed a man \nPut a gun against his head \nPulled my trigger, now he's dead \nMama, life had just begun \nBut now I've gone and thrown it all away \nMama, oh oh \nDidn't mean to make you cry \nIf I'm not back again this time tomorrow \nCarry on, carry on, as if nothing really matters \nToo late, my time has come \nSends shivers down my spine \nBody's aching all the time \nGoodbye everybody I've got to go \nGotta leave you all behind and face the truth \nMama, oh oh (anyway the wind blows) \nI don't want to die \nSometimes wish I'd never been born at all \n";
char string2[] = "I see a little silhouetto of a man \nScaramouch, Scaramouch will you do the Fandango \nThunderbolt and lightning very very frightening me \nGallileo, Gallileo, Gallileo, Gallileo, Gallileo, figaro, magnifico \nI'm just a poor boy and nobody loves me \nHe's just a poor boy from a poor family \nSpare him his life from this monstrosity \nEasy come easy go will you let me go \nBismillah, no we will not let you go, let him go \nBismillah, we will not let you go, let him go \nBismillah, we will not let you go, let me go \n(Will not let you go) let me go (never, never let you go) let me go (never let me go) \nOh oh no, no, no, no, no, no, no \nOh mama mia, mama mia, mama mia let me go \nBeelzebub has a devil put aside for me for me for me \n";
char string3[] = "So you think you can stop me and spit in my eye \nSo you think you can love me and leave me to die \nOh baby can't do this to me baby \nJust gotta get out just gotta get right outta here \nOh oh oh yeah, oh oh yeah \nNothing really matters \nAnyone can see \nNothing really matters \nNothing really matters to me \nAnyway the wind blows";

int length1 = sizeof(string1) - 1;
int length2 = sizeof(string2) - 1;
int length3 = sizeof(string3) - 1;

// Tests writing.
int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);
    InitTerminal(2);
    InitTerminal(3);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    ThreadCreate(writer, NULL);

    ThreadWaitAll();

    struct termstat *stats = malloc(sizeof(struct termstat) * 4);
    TerminalDriverStatistics(stats);
    print_td_stats(stats);
    free(stats);

    exit(0);
}

void
writer(void *arg)
{
    int num_char_written = WriteTerminal(1, string1, length1);
    printf("Num of characters written = %d.\n", num_char_written);

    num_char_written = WriteTerminal(2, string2, length2);
    printf("Num of characters written = %d.\n", num_char_written);

    num_char_written = WriteTerminal(3, string3, length3);
    printf("Num of characters written = %d.\n", num_char_written);
    fflush(stdout);
}
