#include "minishell.h"

void swap_nodes(char **first, char **second)
{
	char *temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

node_t *make_node(char *line)
{
	node_t *new;

	new = malloc(sizeof(node_t));
	new->data = ft_strdup(line);
	new->next = NULL;
	return(new);
}

// adds a node behind the last node
void add_node(node_t **head, node_t *new)
{
	node_t *temp;
	if(new == NULL || head == NULL)
		return;
	if(*head == NULL)
	{
		*head = new;
		return;
	}
	temp = *head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
}

char *create_shlvl(char *line)
{
	char *shlvl;
	int temp;

	temp = ft_atoi(line + 6);
	temp++;
	if(temp >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(temp, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		temp = 1;
	}
	shlvl = ft_itoa(temp);
	return(shlvl);
}

void fill_nodes_env(t_env *var, char **env)
{
    int i;
    char *shlvl;
    char *temp;

    i = 0;
    while(env[i])
    {
        if(ft_strncmp(env[i], "SHLVL=", 6) == 0)
        {
            shlvl = create_shlvl(env[i]);
            temp = ft_strjoin("SHLVL=", shlvl);
            if (!temp)
            {
                free(shlvl);
                return;
            }
            add_node(&var->head_env, make_node(temp));
            add_node(&var->head_exp, make_node(temp));  // Add this line
            free(temp);
            free(shlvl);
        }
        else
        {
            add_node(&var->head_env, make_node(env[i]));
            add_node(&var->head_exp, make_node(env[i]));
        }
        i++;
    }
}
