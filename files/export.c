#include "../minishell.h"

void fill_nodes_exp(t_env *var)
{
	int i;
	int cap;
	int low;
	node_t *head;

	i = 0;
	cap = 65;
	low = 97;
	head = NULL;
	while(cap <= 90 && low <= 122)
	{
		while(var->env[i])
		{
			if(var->env[i][0] == low || var->env[i][0] == cap)
				add_node(&head, make_node(var->env[i]));
			i++;
		}
		i = 0;
		cap++;
		low++;
	}
	
	var->head_exp = head;
	return;
}
