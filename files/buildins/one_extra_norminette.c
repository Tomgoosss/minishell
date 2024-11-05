/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_extra_norminette.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:17:46 by fbiberog          #+#    #+#             */
/*   Updated: 2024/11/05 15:53:38 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_check(char *temp, char *arg)
{
	if (ft_strchr(temp, '=') && !ft_strchr(arg, '='))
		return (0);
	return (1);
}

void	check_if_add(t_env *var, char *arg)
{
	if (check_no_def(var->head_exp, arg) == 1)
		add_node(&var->head_exp, make_node(arg));
}
