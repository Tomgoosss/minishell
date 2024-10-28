/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:16 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/28 16:58:56 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_whitespaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
		|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f')
		i++;
	return (i);
}

int	check_env_variable(char *line)
{
	if (skip_whitespaces(line, 0) == ft_strlen(line))
		return (0);
	printf("line %c\n", line[0]);
	printf("len%i\n", ft_strlen(line));
	return (1);
}

int	count_nodes_extra(t_node *token)
{
	t_node	*temp;
	int		count;

	count = 0;
	temp = token;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

void	make_2d_env(t_env *env)
{
	int		i;
	t_node	*temp;

	if (env->env)
	{
		free(env->env);
		env->env = NULL;
	}
	i = count_nodes_extra(env->head_env);
	env->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env->env)
		return ;
	temp = env->head_env;
	i = 0;
	while (temp)
	{
		env->env[i] = temp->data;
		temp = temp->next;
		i++;
	}
	env->env[i] = NULL;
}
