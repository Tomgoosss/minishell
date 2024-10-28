/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:16:01 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/28 16:38:54 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quote(t_var_exp *exp)
{
	exp->ret[exp->j++] = exp->line[exp->i++];
	while (exp->line[exp->i] && exp->line[exp->i] != '\'')
		exp->ret[exp->j++] = exp->line[exp->i++];
	if (exp->line[exp->i] == '\'')
		exp->ret[exp->j++] = exp->line[exp->i++];
}

void	handle_exit_status(t_var_exp *exp)
{
	char	*exit_code;

	exit_code = ft_itoa(exp->ex->exit_status);
	ft_strlcpy(&exp->ret[exp->j], exit_code, ft_strlen(exit_code) + 1);
	exp->j += ft_strlen(exit_code);
	exp->i += 2;
	while (exp->line[exp->i] && !is_space(exp->line[exp->i]))
		exp->ret[exp->j++] = exp->line[exp->i++];
	free(exit_code);
}

int	handle_variable(t_var_exp *exp)
{
	int		var_length;
	char	*var_name;
	char	*temp;

	var_length = end_of_var(&exp->line[exp->i + 1]);
	if (var_length > 0)
	{
		var_name = malloc(sizeof(char) * (var_length + 1));
		if (!var_name)
			return (0);
		ft_strlcpy(var_name, &exp->line[exp->i + 1], var_length + 1);
		temp = replace_variable(var_name, exp->var);
		free(var_name);
		if (temp)
		{
			ft_strlcpy(&exp->ret[exp->j], temp, ft_strlen(temp) + 1);
			exp->j += ft_strlen(temp);
			free(temp);
		}
		else
			exp->ret[exp->j] = '\0';
		exp->i += var_length + 1;
		return (1);
	}
	return (0);
}

void	handle_dollar_sign(t_var_exp *exp)
{
	if (exp->line[exp->i + 1] == '?')
	{
		handle_exit_status(exp);
	}
	else if (ft_isalpha(exp->line[exp->i + 1]) || exp->line[exp->i + 1] == '_')
	{
		if (!handle_variable(exp))
		{
			exp->ret[exp->j++] = exp->line[exp->i++];
		}
	}
	else
	{
		exp->ret[exp->j++] = exp->line[exp->i++];
	}
}

int	inside_double_quote(char *line, int i)
{
	int	j;
	int	end;

	j = 0;
	while (j < i)
	{
		if (line[j] == '"')
		{
			end = closing_quote(line, j, '"', 0);
			if (end - 1 > j)
				return (1);
		}
		j++;
	}
	return (0);
}
