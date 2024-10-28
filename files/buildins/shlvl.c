/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:30:51 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/28 17:32:42 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_shlvl(char *line)
{
	char	*shlvl;
	int		temp;

	temp = ft_atoi(line + 6);
	temp++;
	if (temp >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(temp, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		temp = 1;
	}
	shlvl = ft_itoa(temp);
	if (!shlvl)
		return (NULL);
	return (shlvl);
}

void	handle_shlvl(t_env *var, char *env_line)
{
	char	*shlvl;
	char	*temp;

	shlvl = create_shlvl(env_line);
	if (!shlvl)
		return ;
	temp = ft_strjoin("SHLVL=", shlvl);
	if (!temp)
	{
		free(shlvl);
		return ;
	}
	add_node(&var->head_env, make_node(temp));
	add_node(&var->head_exp, make_node(temp));
	free(temp);
	free(shlvl);
}
