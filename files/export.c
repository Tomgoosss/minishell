#include "../minishell.h"

int sorted(t_env *var)
{
	node_t *temp;

	temp = var->head_exp;
	while(temp && temp->next)
	{
		if(ft_strcmp(temp->data, temp->next->data) > 0)
			return 0;
		temp = temp->next;

	}
	return 1;
}

void sort_export(t_env *var)
{
	node_t *head;

	head = var->head_exp;
	while(sorted(var) == 0 && head->next && head)
	{
		while(head && head->next)
		{
			if(ft_strcmp(head->data, head->next->data) > 0)
				swap_nodes(&head->data, &head->next->data);
			head = head->next;
		}
		head = var->head_exp;
	}
}
