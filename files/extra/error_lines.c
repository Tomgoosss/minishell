/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:39:11 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/28 19:05:17 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_identifier(char *arg)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	print_is_directory(char *arg)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

void	print_permission_denied(char *arg)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	error_lines(char *arg, int i)
{
	if (i == 1)
		print_command_not_found(arg);
	else if (i == 2)
		print_no_such_file(arg);
	else if (i == 3)
		print_not_enough_args(arg);
	else if (i == 4)
		print_too_many_args(arg);
	else if (i == 5)
		print_is_directory(arg);
	else if (i == 6)
		print_permission_denied(arg);
}
