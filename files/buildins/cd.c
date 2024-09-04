#include "minishell.h"

int cd_buildin(t_token *token, t_env *var)
{
    char *path;
    
    if (token->command[1] == NULL)
        return 0;
    path = token->command[1];
    if (chdir(path) != 0)
    {
        printf("cd: no such file or directory: %s\n", path);
        return 1;
    }
    return 0;
}
//to-do: update env with new path
//to-do: make sure to free everything
//to-do: when in directory 1/2/3 and you rm -r 1 make sure program doesnt seggfault
