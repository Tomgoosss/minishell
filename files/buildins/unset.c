#include "minishell.h"


void check_unset_env(node_t *env, char **commands, t_env *var)
{
	int i;
	node_t *tmp;

	i = 1;
	while (env)
	{
		while(commands[i])
		{
			if(env && ft_strncmp(env->data, commands[i], ft_strlen(commands[i])) == 0 
				&& env->data[ft_strlen(commands[i])] == '=')
			{
				tmp = env->next;
				remove_current_node(&var->head_env, env);
				env = tmp;
				i = 0;
			}
			i++;
		}
		i = 1;
		if (env)
			env = env->next;
	}
}

void check_unset_exp(node_t *exp, char **commands, t_env *var)
{
	int i;
	node_t *tmp;

	i = 1;
	while (exp)
	{
		while(commands[i])
		{
			if(exp && ft_strncmp(exp->data, commands[i], ft_strlen(commands[i])) == 0
				&& exp->data[ft_strlen(commands[i])] == '=')
			{
				tmp = exp->next;
				remove_current_node(&var->head_exp, exp);
				exp = tmp;
				i = 0;
			}
			i++;
		}
		i = 1;
		if (exp)
			exp = exp->next;
	}
}
int unset(t_token *token, t_env *var)
{
	node_t *tmp_env;
	node_t *tmp_exp;
	char **commands;

	if(token->command == NULL || token->command[1] == NULL)
		return (0);
	tmp_env = var->head_env;
	tmp_exp = var->head_exp;
	commands = token->command;
	check_unset_env(tmp_env, commands, var);
	check_unset_exp(tmp_exp, commands, var);
	return (0);
}