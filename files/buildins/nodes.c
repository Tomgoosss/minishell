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

// puts the env in a linked list
void fill_nodes_env(t_env *var, char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		add_node(&var->head_env, make_node(env[i]));
		add_node(&var->head_exp, make_node(env[i]));
		i++;
	}
}
