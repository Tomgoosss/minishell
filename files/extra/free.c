#include "minishell.h"


void free2pointers(char **str)
{
	int i;

	i = 0;
	if(!str)
		return ;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void free_list(node_t *head)
{
	node_t *tmp;
	node_t *next;

	tmp = head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->data);
		free(tmp);
		tmp = next;
	}
}
void free_redirection(t_redirection *redirection)
{
	t_redirection *tmp;
	t_redirection *next;

	tmp = redirection;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->file);
		free(tmp);
		tmp = next;
	}
}
void free_token(t_token *token)
{
	t_token *tmp;
	t_token *next;

	tmp = token;
	while (tmp)
	{
		if(tmp->redirection)
			free_redirection(tmp->redirection);
		next = tmp->next;
		free2pointers(tmp->command);
		free(tmp);
		tmp = next;
	}
}


void free_env(t_env *var)
{
	if (var->head_exp)
		free_list(var->head_exp);
	if (var->head_env)
		free_list(var->head_env);
	if (var)
		free(var);
}

