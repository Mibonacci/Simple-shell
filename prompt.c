#include"shell.h"

void prompt(void)
{

    if (isatty(STDIN_FILENO))
    {
        write(1, "$ ", 2);
    }
}