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
	node_t *head;

	i = 0;
	head = NULL;
	while(var->env[i])
	{
		add_node(&head, make_node(var->env[i]));
		i++;
	}
	var->head_env = head;

}
