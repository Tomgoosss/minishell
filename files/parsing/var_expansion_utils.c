/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:16:01 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/25 17:52:04 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quote(char *line, char *ret, int *i, int *j)
{
	ret[(*j)++] = line[(*i)++];
	while (line[*i] && line[*i] != '\'')
		ret[(*j)++] = line[(*i)++];
	if (line[*i] == '\'')
		ret[(*j)++] = line[(*i)++];
}

void	handle_exit_status(char *ret, int *j, char *line, int *i,
		int exit_status)
{
	*i = add_exit_code(ret, *j, line, *i, exit_status);
	*j = ft_strlen(ret);
}

int	handle_variable(char *ret, int *j, char *line, int *i, t_env *var)
{
	int		var_length;
	char	*var_name;
	char	*temp;
	size_t	temp_len;

	var_length = end_of_var(&line[*i + 1]);
	if (var_length > 0)
	{
		var_name = malloc(sizeof(char) * (var_length + 1));
		if (!var_name)
			return (0);
		ft_strlcpy(var_name, &line[*i + 1], var_length + 1);
		temp = replace_variable(var_name, var);
		free(var_name);
		if (temp)
		{
			temp_len = ft_strlen(temp);
			ft_strlcpy(&ret[*j], temp, temp_len + 1);
			*j += temp_len;
			free(temp);
		}
		else
			ret[*j] = '\0';
		*i += var_length + 1;
		return (1);
	}
	return (0);
}

void	handle_dollar_sign(char *ret, int *j, char *line, int *i, t_env *var,
		t_ex *ex)
{
	if (line[*i + 1] == '?')
	{
		handle_exit_status(ret, j, line, i, ex->exit_status);
	}
	else if (ft_isalpha(line[*i + 1]) || line[*i + 1] == '_')
	{
		if (!handle_variable(ret, j, line, i, var))
		{
			ret[(*j)++] = line[(*i)++];
		}
	}
	else
	{
		ret[(*j)++] = line[(*i)++];
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
