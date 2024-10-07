/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_buildin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:46:56 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/07 09:11:59 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*prepare_for_export(char *line)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(line) + 3);
	while (line[i] && line[i] != '=')
	{
		ret[i] = line[i];
		i++;
	}
	if (line[i] == '=')
	{
		ret[i] = line[i];
		i++;
	}
	ret[i] = '"';
	while (line[i])
	{
		ret[i + 1] = line[i];
		i++;
	}
	ret[i + 1] = '"';
	ret[i + 2] = '\0';
	return (ret);
}
void	printf_export(t_env *var)
{
	node_t	*temp;
	char 	*str;

	temp = var->head_exp;
	str = NULL;
	while (temp)
	{
		str = prepare_for_export(temp->data);
		printf("declare -x %s\n", temp->data);
		temp = temp->next;
		free(str);
	}
	temp = var->head_env;
}

void	remove_current_node(node_t *head, node_t *node)
{
	node_t	*temp;

	temp = head;
	while (temp->next != node)
		temp = temp->next;
	temp->next = node->next;
	free(node->data);
	free(node);
}
int	remove_double_env(t_env *var, char *arg)
{
	node_t	*temp;

	int len; // len of the arg until the = or end of string
	len = 0;
	temp = var->head_env;
	while (arg[len] && arg[len] != '=')
		len++;
	while (temp)
	{
		if (ft_strncmp(temp->data, arg, len + 1) == 0)
		{
				remove_current_node(var->head_env, temp);
				return 1;
		}
		temp = temp->next;
	}
	return 1;
}
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
				remove_current_node(var->head_exp, temp);
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

int export(t_env *var, char **command)
{
    int i;
    int is_double;
    
    i = 1;
    if (command[i] == NULL)
    {
        printf_export(var);
        return (0);
    }
    while (command[i])
    {
        if (!is_valid_identifier(command[i]))
        {
            fprintf(stderr, "export: `%s': not a valid identifier\n", command[i]);
            return (1);
        }
        is_double = 0;
        is_double = remove_double_env(var, command[i]);
        is_double += remove_double_exp(var, command[i]);
        if (is_double != 0)
            add_to_lists(var, command[i]);
        i++;
    }
    return (0);
}
