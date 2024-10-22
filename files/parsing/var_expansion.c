/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:16:01 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/22 16:35:52 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void handle_single_quote(char *line, char *ret, int *i, int *j)
{
	ret[(*j)++] = line[(*i)++];
	while (line[*i] && line[*i] != '\'')
		ret[(*j)++] = line[(*i)++];
	if (line[*i] == '\'')
		ret[(*j)++] = line[(*i)++];
}

static void handle_exit_status(char *ret, int *j, char *line, int *i, int exit_status)
{
	*i = add_exit_code(ret, *j, line, *i, exit_status);
	*j = ft_strlen(ret);
}

static int handle_variable(char *ret, int *j, char *line, int *i, t_env *var)
{
	int var_length = end_of_var(&line[*i + 1]);
	char *var_name;
	char *temp;

	if (var_length > 0)
	{
		var_name = malloc(sizeof(char) * (var_length + 1));
		if (!var_name)
			return 0;
		ft_strlcpy(var_name, &line[*i + 1], var_length + 1);
		temp = replace_variable(var_name, var);
		free(var_name);
		if (temp)
		{
			size_t temp_len = ft_strlen(temp);
			ft_strlcpy(&ret[*j], temp, temp_len + 1);
			*j += temp_len;
			free(temp);
		}
		else
			ret[*j] = '\0';
		*i += var_length + 1;
		return 1;
	}
	return 0;
}

static void handle_dollar_sign(char *ret, int *j, char *line, int *i, t_env *var, t_ex *ex)
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

char *check_dollar_sign(char *line, t_env *var, t_ex *ex)
{
	int i = 0, j = 0;
	char *ret;

	if (!line)
		return NULL;
	if (ft_strchr(line, '$') == NULL)
		return ft_strdup(line);
	ret = malloc(sizeof(char) * (max_expansion(var)));
	if (!ret)
		return NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && closing_quote(line, i, '\'', 0) && !inside_double_quote(line, i))
			handle_single_quote(line, ret, &i, &j);
		else if (line[i] == '$')
			handle_dollar_sign(ret, &j, line, &i, var, ex);
		else
			ret[j++] = line[i++];
	}
	ret[j] = '\0';
	return ret;
}
