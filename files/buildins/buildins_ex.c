/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:37:11 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/22 16:38:42 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_buildin(t_token *token, t_env *var)
{
	if (strncmp(token->command[0], "echo", 4) == 0)
		return (echo(token->command));
	if (strncmp(token->command[0], "cd", 2) == 0)
		return (cd_buildin(token, var));
	if (strncmp(token->command[0], "pwd", 3) == 0)
		return (pwd_buildin());
	if (strncmp(token->command[0], "export", 6) == 0)
		return (export(var, token->command));
	if (strncmp(token->command[0], "unset", 5) == 0)
		return (unset(token, var));
	if (strncmp(token->command[0], "env", 3) == 0)
		return (env_buildin(var));
	return (1);
}

int	check_buildin(t_token *token)
{
	if (token->command == NULL)
		return (0);
	if (strncmp(token->command[0], "echo", 4) == 0)
		return (1);
	if (strncmp(token->command[0], "cd", 2) == 0)
		return (1);
	if (strncmp(token->command[0], "pwd", 3) == 0)
		return (1);
	if (strncmp(token->command[0], "export", 6) == 0)
		return (1);
	if (strncmp(token->command[0], "unset", 5) == 0)
		return (1);
	if (strncmp(token->command[0], "env", 3) == 0)
		return (1);
	if (strncmp(token->command[0], "exit", 4) == 0)
		return (1);
	return (0);
}
