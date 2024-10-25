/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:09:26 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/25 17:29:28 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_numeric_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
		i++;
	}
	ft_putstr_fd("exit\n", 1);
	return (ft_atoi(arg));
}

int	check_exit(char **cmd_array)
{
	if (cmd_array == NULL || cmd_array[0] == NULL)
		return (0);
	if (ft_strncmp(cmd_array[0], "exit", 4) == 0)
	{
		if (!cmd_array[1])
		{
			ft_putstr_fd("exit\n", 1);
			return (1);
		}
		if (cmd_array[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		return (check_numeric_argument(cmd_array[1]));
	}
	return (0);
}
