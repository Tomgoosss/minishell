/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:37:41 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/22 15:42:20 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_oldpwd(t_env *var, char *path)
{
	t_node	*temp;

	temp = var->head_env;
	while (temp)
	{
		if (ft_strncmp(temp->data, "OLDPWD", 6) == 0)
		{
			free(temp->data);
			temp->data = ft_strjoin("OLDPWD=", path);
			break ;
		}
		temp = temp->next;
	}
	temp = var->head_exp;
	while (temp)
	{
		if (ft_strncmp(temp->data, "OLDPWD", 6) == 0)
		{
			free(temp->data);
			temp->data = ft_strjoin("OLDPWD=", path);
			break ;
		}
		temp = temp->next;
	}
}

void	change_current_dir(t_env *var)
{
	t_node	*temp;
	char	cwd[9999];

	getcwd(cwd, sizeof(cwd));
	temp = var->head_env;
	while (temp)
	{
		if (ft_strncmp(temp->data, "PWD", 3) == 0)
		{
			update_pwd(temp, cwd);
			break ;
		}
		temp = temp->next;
	}
	temp = var->head_exp;
	while (temp)
	{
		if (ft_strncmp(temp->data, "PWD", 3) == 0)
		{
			update_pwd(temp, cwd);
			break ;
		}
		temp = temp->next;
	}
}

char	*get_home(t_env *var)
{
	t_node	*temp;
	char	*home;

	temp = var->head_env;
	while (temp)
	{
		if (ft_strncmp(temp->data, "HOME", 4) == 0)
		{
			home = temp->data;
			return (home + 5);
		}
		temp = temp->next;
	}
	return (NULL);
}

static int	change_directory(t_token *token, t_env *var, char *cwd)
{
	char	*path;

	if (ft_strcmp(token->command[1], "-") == 0)
		return (pwd_buildin());
	if (token->command[1] == NULL)
	{
		chdir(get_home(var));
		change_current_dir(var);
		return (0);
	}
	path = token->command[1];
	if (chdir(path) != 0)
	{
		error_lines(path, 2);
		return (1);
	}
	change_current_dir(var);
	getcwd(cwd, sizeof(cwd));
	return (0);
}

int	cd_buildin(t_token *token, t_env *var)
{
	char	cwd[4096];

	if (token->command[2])
	{
		error_lines("cd", 4);
		return (1);
	}
	if (token == NULL || token->command == NULL || token->command[0] == NULL)
		return (1);
	getcwd(cwd, sizeof(cwd));
	change_oldpwd(var, cwd);
	return (change_directory(token, var, cwd));
}
