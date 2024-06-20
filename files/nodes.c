#include "../minishell.h"

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
void fill_nodes_env(t_env *var)
{
	int i;

	i = 0;
	while(var->env[i])
	{
		add_node(&var->head_env, make_node(var->env[i]));
		add_node(&var->head_exp, make_node(var->env[i]));
		i++;
	}
}

void swap_2_nodes(node_t **node)
{
	node_t *first;
	node_t *second;
	node_t *prev;
	
	prev = *node;
	first = prev->next;
	second = first->next;
	prev->next = second;
	if(second->next)
		first->next = second->next;
	second->next = first;
}
