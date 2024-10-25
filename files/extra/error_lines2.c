/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_lines2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:58:14 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/25 17:09:28 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_prefix(void)
{
	ft_putstr_fd("bash: ", 2);
}

void	print_command_not_found(char *arg)
{
	print_error_prefix();
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	print_no_such_file(char *arg)
{
	print_error_prefix();
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	print_not_enough_args(char *arg)
{
	print_error_prefix();
	ft_putstr_fd("not enough arguments: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
}

void	print_too_many_args(char *arg)
{
	print_error_prefix();
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": too many arguments\n", 2);
}
