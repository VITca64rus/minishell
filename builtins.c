#include "minishell.h"

void echo(t_data el)
{
    int i;

    i = 1;
    while (el.args[i + 1] != NULL)
    {
        printf("%s ", el.args[i]);
        i++;
    }
    printf("%s", el.args[i]);
}