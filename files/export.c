#include "../minishell.h"


int sorted(t_env *var)
{
	node_t *temp;
	size_t first;
	size_t sec;

	temp = var->head_exp;
	while(temp)
	{
		first = ft_strlen(var->head_exp->data);
		sec = ft_strlen(var->head_exp->next->data);
		if(first < sec)
			first = sec;
		if(ft_strncmp(temp->data, temp->next->data, first) > 0)
			return 0;
		temp = temp->next;
	}
	return 1;
}
void fill_nodes_exp(t_env *var)
{
	node_t *temp;
	int i;

	i = 0;
	temp = NULL;
	temp = var->head_exp;
	while(!sorted(var))
	{
		if(ft_strcmp(temp->next->data, temp->next->next->data) > 0)
			swap_2_nodes(&temp);
		temp = temp->next;
	}

}





