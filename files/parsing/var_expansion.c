/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:16:01 by fbiberog          #+#    #+#             */
/*   Updated: 2024/11/02 20:19:39 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	max_expansion(t_env *var)
{
	int		i;
	int		size;
	t_node	*temp;

	temp = var->head_exp;
	i = 0;
	size = 0;
	while (temp)
	{
		i = ft_strlen(temp->data);
		if (i > size)
			size = i;
		temp = temp->next;
	}
	return (size);
}

char	*replace_variable(char *line, t_env *var)
{
	t_node	*temp;
	char	*var_name;
	char	*ret;
	int		var_length;

	if (is_space(line[0]))
		return (ft_strdup("$"));
	var_length = end_of_var(line);
	var_name = malloc(sizeof(char) * (var_length + 1));
	if (!var_name)
		return (NULL);
	ft_memcpy(var_name, line, var_length);
	var_name[var_length] = '\0';
	temp = var->head_env;
	while (temp)
	{
		if (ft_strncmp(temp->data, var_name, var_length) == 0
			&& temp->data[var_length] == '=')
		{
			ret = ft_strdup(temp->data + var_length + 1);
			return (free(var_name), ret);
		}
		temp = temp->next;
	}
	return (free(var_name), NULL);
}

static t_var_exp	init_var_exp(char *line, t_env *var, t_ex *ex)
{
	t_var_exp	exp;

	exp.line = line;
	exp.var = var;
	exp.ex = ex;
	exp.i = 0;
	exp.j = 0;
	exp.ret = malloc(sizeof(char) * (max_expansion(var)));
	if (!exp.ret)
	{
		exp.ret = NULL;
	}
	return (exp);
}

char	*check_dollar_sign(char *line, t_env *var, t_ex *ex)
{
	t_var_exp	exp;
	char		*result;

	if (!line)
		return (NULL);
	if (ft_strchr(line, '$') == NULL)
		return (ft_strdup(line));
	exp = init_var_exp(line, var, ex);
	if (!exp.ret)
		return (NULL);
	while (exp.line[exp.i] != '\0')
	{
		if (exp.line[exp.i] == '\'' && closing_quote(exp.line, exp.i, '\'', 0)
			&& !inside_double_quote(exp.line, exp.i))
			handle_single_quote(&exp);
		else if (exp.line[exp.i] == '$')
			handle_dollar_sign(&exp);
		else
			exp.ret[exp.j++] = exp.line[exp.i++];
	}
	exp.ret[exp.j] = '\0';
	result = ft_strdup(exp.ret);
	free(exp.ret);
	return (result);
}
