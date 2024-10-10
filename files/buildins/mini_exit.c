/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:09:26 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/10 15:13:11 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit(char **cmd_array)
{
	int i;
	
	i = 0;
	if (cmd_array == NULL)
		return (0);
	if (ft_strncmp(cmd_array[0], "exit", 4) == 0 && !cmd_array[1])
	{
		ft_putstr_fd("exit\n", 1);  // Print to standard output
		return(1);
	}
	if (ft_strncmp(cmd_array[0], "exit", 4) == 0 && cmd_array[2])
	{
			ft_putstr_fd("exit: ", 2);
			// ft_putstr_fd(cmd_array[1], 2);
			ft_putstr_fd(": too many arguments\n", 2);
			return(1);
	}
	else if (ft_strncmp(cmd_array[0], "exit", 4) == 0 && cmd_array[1])
	{
		if (cmd_array[1][i] == '+' || cmd_array[1][i] == '-')
			i++;
		while (cmd_array[1][i])
		{
			if (!ft_isdigit(cmd_array[1][i]))
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(cmd_array[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				free2pointers(cmd_array);
				return(2); // Updated to match bash behavior
			}
			i++;
		}
		ft_putstr_fd("exit\n", 1);  // Print to standard output
		return(ft_atoi(cmd_array[1]));
	}
	return (0);
}

// exit

// exit 100		sluit af		exit code = 100

// exit 500		sluit af		exit code = 244

// exit p		sluit af		exit code = 2			error msg: p: numeric argument required

