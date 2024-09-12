#include "minishell.h"

void change_oldpwd(t_env *var, char *path)
{
    node_t *temp;

    temp = var->head_env;
    while (temp)
    {
        if (ft_strncmp(temp->data, "OLDPWD", 6) == 0)
        {
            free(temp->data);
            temp->data = ft_strjoin("OLDPWD=", path);
            break;
        }
        temp = temp->next;
    }
    temp = var->head_exp;
    while (temp)
    {
        if (ft_strncmp(temp->data, "OLDPWD", 6) == 0)
        {
            free(temp->data);
            temp->data = ft_strjoin("OLDPWD=", path);
            break;
        }
        temp = temp->next;
    }
}

void change_current_dir(t_env *var)
{
    node_t *temp;

    temp = var->head_env;
    char cwd[9999];
    getcwd(cwd, sizeof(cwd));
    while (temp)
    {
        if (ft_strncmp(temp->data, "PWD", 3) == 0)
        {
            free(temp->data);
            temp->data = ft_strjoin("PWD=", cwd);
            break;
        }
        temp = temp->next;
    }
    temp = var->head_exp;
    while (temp)
    {
        if (ft_strncmp(temp->data, "PWD", 3) == 0)
        {
            free(temp->data);
            temp->data = ft_strjoin("PWD=", cwd);
            break;
        }
        temp = temp->next;
    }
}
char *get_home(t_env *var)
{
    node_t *temp;
    char *home;

    temp = var->head_env;
    while (temp)
    {
        if (ft_strncmp(temp->data, "HOME", 4) == 0)
        {
            home = temp->data;
            return home + 5;
        }
        temp = temp->next;
    }
    return NULL;
}

int cd_buildin(t_token *token, t_env *var)
{
    char *path;
    char cwd[9999];

    if(token == NULL || token->command == NULL || token->command[0] == NULL)
        return 0;
    getcwd(cwd, sizeof(cwd));
    change_oldpwd(var, cwd);
    if (token->command[1] == NULL)
    {
        chdir(get_home(var));
        change_current_dir(var);
       return 0;
    }
    path = token->command[1];
    if (chdir(path) != 0)
    {
        printf("cd: no such file or directory: %s\n", path);
        return 1;
    }
    change_current_dir(var);
    getcwd(cwd, sizeof(cwd));
    return 0;
}
//to-do: update env with new path
//to-do: make sure to free everything
//to-do: when in directory 1/2/3 and you rm -r 1 make sure program doesnt seggfault
