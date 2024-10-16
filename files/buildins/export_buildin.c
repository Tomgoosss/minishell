/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_buildin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:46:56 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/16 17:22:56 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_double_exp(t_env *var, char *arg)
{
	node_t	*temp;

	int len;

	temp = var->head_exp;
	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	while (temp)
	{
		if (ft_strncmp(temp->data, arg, len + 1) == 0)
		{
			if (ft_strchr(temp->data, '=') != 0)
			{
				remove_current_node(&var->head_exp, temp);
				return (1);
			}
			return (0);
		}
		temp = temp->next;
	}
	return 1;
}

int	add_to_lists(t_env *var, char *arg)
{
	char	*temp;

	if (ft_strchr(arg, '=') != 0)
	{
		add_node(&var->head_env, make_node(arg));
		temp = prepare_for_export(arg);
	}
	else
		temp = ft_strdup(arg);
	if (!temp)
		return (1);
	add_node(&var->head_exp, make_node(temp));
	sort_export(var);
	free(temp);
	temp = NULL;
	return (0);
}

int is_valid_identifier(const char *str)
{
	int i;

	i = 0;
    if (!str || !(*str) || (!ft_isalpha(*str) && *str != '_'))
        return 0;
    str++;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

static int process_export_arg(t_env *var, char *arg)
{
	char *equal_sign;
	int is_double;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';  // Temporarily split the string
		if (!is_valid_identifier(arg))
		{
			fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
			*equal_sign = '=';  // Restore the string
			return (1);
		}
		*equal_sign = '=';  // Restore the string
	}
	else if (!is_valid_identifier(arg))
	{
		fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	is_double = remove_double_env(var, arg) + remove_double_exp(var, arg);
	if (is_double != 0)
		add_to_lists(var, arg);
	return (0);
}

int export(t_env *var, char **command)
{
	int i = 1;
	
	if (command[i] == NULL)
	{
		printf_export(var);
		return (0);
	}
	while (command[i])
	{
		if (process_export_arg(var, command[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
