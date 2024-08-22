/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:09:26 by tgoossen          #+#    #+#             */
/*   Updated: 2024/08/20 14:39:45 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exit(char **cmd_array)
{
	if (cmd_array[0] == NULL)
		return (1);
	if (ft_strncmp(cmd_array[0], "exit", 4) == 0 && !cmd_array[1])
		return (1);
	return (0);
}

// exit

// exit 100		sluit af		exit code = 100

// exit 500		sluit af		exit code = 244

// exit p		sluit af		exit code = 2			error msg: p: numeric argument required

