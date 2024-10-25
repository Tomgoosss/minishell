/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:46 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/25 17:33:54 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_unset_env(t_node *env, char **commands, t_env *var)
{
	int		i;
	t_node	*tmp;

	i = 1;
	while (env)
	{
		while (commands[i])
		{
			if (env && ft_strncmp(env->data, commands[i],
					ft_strlen(commands[i])) == 0
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

void	check_unset_exp(t_node *exp, char **commands, t_env *var)
{
	int		i;
	t_node	*tmp;

	i = 1;
	while (exp)
	{
		while (commands[i])
		{
			if (exp && ft_strncmp(exp->data, commands[i],
					ft_strlen(commands[i])) == 0)
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

int	unset(t_token *token, t_env *var)
{
	t_node	*tmp_env;
	t_node	*tmp_exp;
	char	**commands;

	if (token->command == NULL || token->command[1] == NULL)
		return (0);
	tmp_env = var->head_env;
	tmp_exp = var->head_exp;
	commands = token->command;
	check_unset_env(tmp_env, commands, var);
	check_unset_exp(tmp_exp, commands, var);
	return (0);
}
