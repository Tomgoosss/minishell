/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:37:11 by tgoossen          #+#    #+#             */
/*   Updated: 2024/11/02 20:01:00 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_buildin(t_token *token, t_env *var)
{
	if (ft_strcmp(token->command[0], "echo") == 0)
		return (echo(token->command));
	if (ft_strcmp(token->command[0], "cd") == 0)
		return (cd_buildin(token, var));
	if (ft_strcmp(token->command[0], "pwd") == 0)
		return (pwd_buildin());
	if (ft_strcmp(token->command[0], "export") == 0)
		return (export(var, token->command));
	if (ft_strcmp(token->command[0], "unset") == 0)
		return (unset(token, var));
	if (ft_strcmp(token->command[0], "env") == 0)
		return (env_buildin(var));
	return (1);
}

int	check_buildin(t_token *token)
{
	if (token->command == NULL)
		return (0);
	if (ft_strcmp(token->command[0], "echo") == 0)
		return (1);
	if (ft_strcmp(token->command[0], "cd") == 0)
		return (1);
	if (ft_strcmp(token->command[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(token->command[0], "export") == 0)
		return (1);
	if (ft_strcmp(token->command[0], "unset") == 0)
		return (1);
	if (ft_strcmp(token->command[0], "env") == 0)
		return (1);
	if (ft_strcmp(token->command[0], "exit") == 0)
		return (1);
	return (0);
}
