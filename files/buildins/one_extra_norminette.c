/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_extra_norminette.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:17:46 by fbiberog          #+#    #+#             */
/*   Updated: 2024/11/05 15:19:28 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_check(char *temp, char *arg)
{
	if (ft_strchr(temp, '=') && !ft_strchr(arg, '='))
		return (0);
	return (1);
}
