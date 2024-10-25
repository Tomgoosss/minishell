/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:16:01 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/25 18:10:09 by fbiberog         ###   ########.fr       */
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

int	add_exit_code(char *ret, int j, char *line, int i, int exit_status)
{
	char	*exit_code;

	exit_code = ft_itoa(exit_status);
	ft_strlcpy(&ret[j], exit_code, ft_strlen(exit_code) + 1);
	j += ft_strlen(exit_code);
	i += 2;
	while (line[i] && !is_space(line[i]))
		ret[j++] = line[i++];
	return (i);
}

char	*check_dollar_sign(char *line, t_env *var, t_ex *ex)
{
	int		i = 0, j;
	char	*ret;

	i = 0, j = 0;
	if (!line)
		return (NULL);
	if (ft_strchr(line, '$') == NULL)
		return (ft_strdup(line));
	ret = malloc(sizeof(char) * (max_expansion(var)));
	if (!ret)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && closing_quote(line, i, '\'', 0)
			&& !inside_double_quote(line, i))
			handle_single_quote(line, ret, &i, &j);
		else if (line[i] == '$')
			handle_dollar_sign(ret, &j, line, &i, var, ex);
		else
			ret[j++] = line[i++];
	}
	ret[j] = '\0';
	return (ret);
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
