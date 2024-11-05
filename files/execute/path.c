/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:08 by tgoossen          #+#    #+#             */
/*   Updated: 2024/11/05 15:28:08 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path(char **temp_path, t_ex *ex, t_token *token)
{
	int	i;

	i = 0;
	while (temp_path[i])
	{
		ex->path = ft_strjoin(temp_path[i], "/");
		ex->path = ft_strjoinfree(ex->path, token->command[0]);
		if (access(ex->path, X_OK) == 0)
		{
			free2pointers(temp_path);
			return (0);
		}
		free(ex->path);
		i++;
	}
	free2pointers(temp_path);
	if (ft_strchr(token->command[0], '/') && access(token->command[0],
			X_OK) == 0)
	{
		ex->path = ft_strdup(token->command[0]);
		return (0);
	}
	return (1);
}

void	make_path(t_token *token, t_ex *ex, t_env *var)
{
	int		i;
	char	**temp_path;

	i = 0;
	if (ft_strchr(token->command[0], '/') && access(token->command[0],
			X_OK) == 0)
	{
		ex->path = ft_strdup(token->command[0]);
		return ;
	}
	while (var->head_env && ft_strncmp(var->env[i], "PATH=", 5) != 0)
		i++;
	if (var->env[i] == NULL)
		return ;
	temp_path = ft_split(var->env[i] + 5, ':');
	if (find_path(temp_path, ex, token) == 0 || check_buildin(token))
		return ;
	error_lines(token->command[0], 1);
	exit(127);
}
