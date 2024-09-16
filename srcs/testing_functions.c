#include "minishell.h"
int print_arr(char **array, char *array_name)
{
    int i = 0;
    while (array[i] != NULL)
    {
        printf("%s[%d] = %s\n", array_name, i, array[i]);
        i++;
    }
    return (0);
}

/*int look_at_bool()
{


}*/