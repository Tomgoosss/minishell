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
void fill_nodes_env(t_minishell *man)
{
	int i;
	node_t *head;

	i = 0;
	head = NULL;
	// add_node(head, make_node(man->env[i]));
	// printf("%s\n", head->data);
	while(man->env[i])
	{
		add_node(&head, make_node(man->env[i]));
		i++;
	}
	man->head = head;
	// while(head->next != NULL)
	// {
	// 	printf("%s\n", head->data);
	// 	head = head->next;
	// }
}
