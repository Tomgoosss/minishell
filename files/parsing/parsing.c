/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knockla <knockla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:09:51 by fbiberog          #+#    #+#             */
/*   Updated: 2024/09/18 17:59:00 by knockla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:09:51 by fbiberog          #+#    #+#             */
/*   Updated: 2024/09/16 14:52:42 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_whitespaces(char *line, int i)
{
	if (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
			|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f'))
		return (-1);
	while ((line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
			|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f')
		&& line[i])
	{
		i++;
		if (line[i] == '\0')
			return (-1);
	}
	return (1);
}

int	closing_quote(char *line, int i, char c)
{
	i++;
	while (line[i])
	{
		if (line[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_redirection(t_redirection **redirection, char *temp)
{
	t_redirection	*new_node;
	t_redirection	*last;

	new_node = malloc(sizeof(t_redirection));
	if (!new_node)
		return (0);
	new_node->next = NULL;
	new_node->file = NULL;
	if (ft_strcmp(temp, ">>") == 0)
		new_node->type = REDIR_OUT_APPEND;
	else if (ft_strcmp(temp, ">") == 0)
		new_node->type = REDIR_OUT;
	else if (ft_strcmp(temp, "<<") == 0)
		new_node->type = REDIR_IN_HERE_DOC;
	else if (ft_strcmp(temp, "<") == 0)
		new_node->type = REDIR_IN;
	else
		return (free(new_node), 0);
	if (*redirection == NULL)
		*redirection = new_node;
	else
	{
		last = *redirection;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	return (1);
}

void	add_command(t_token *token, char *cmd, int array_len)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (array_len + 2));
	if (!ret) // Check for malloc failure
		return;
	while (i != array_len)
	{
		ret[i] = ft_strdup(token->command[i]);
		if (!ret[i])
		{
			free2pointers(ret); // Free ret on failure
			return (free2pointers(token->command));
		}
		i++;
	}
	ret[i] = ft_strdup(cmd);
	if (!ret[i])
	{
		free2pointers(ret); // Free ret on failure
		return (free2pointers(token->command));
	}
	ret[i + 1] = 0;
	free2pointers(token->command);
	token->command = ret;
	return ;
}

void	place_file(t_redirection **redirection, char *temp)
{
	t_redirection	*last;

	if (*redirection == NULL)
		return ;
	last = *redirection;
	while (last->next != NULL)
		last = last->next;
	if (last == NULL)
		return ;
	if (last->file)
		free(last->file);
	last->file = ft_strdup(temp);
	if (!last->file)
		return ;
}

void	init_token(t_token **token, int pipe)
{
	if (pipe)
	{
		(*token)->next = malloc(sizeof(t_token));
		if (!(*token)->next)
		{
			free(*token); // Free token on failure
			return ;
		}
		(*token) = (*token)->next;
	}
	(*token)->redirection = NULL;
	(*token)->next = NULL;
	(*token)->command = NULL;
}

void	tokenize(t_token **token, char **temp)
{
	t_token	*temp_token;
	int		i;
	int		cmd;

	i = 0;
	cmd = 0;
	init_token(token, 0);
	if (!(*token))
		return (free2pointers(temp), free(*token));
	temp_token = *token;
	while (temp[i])
	{
		if (temp[i][0] == '|')
		{
			if(temp[i + 1] == NULL)
			{
				printf("syntax error near unexpected token `|'\n");
				return (free2pointers(temp), free2pointers(temp_token->command),
					free(temp_token));
			}
			init_token(&(*token), 1);
			if (!(*token))
				return (free2pointers(temp), free2pointers(temp_token->command),
					free(temp_token));
			i++;
			cmd = 0;
		}
		else if (check_redirection(&(*token)->redirection, temp[i]))
		{
			if (valid_redirection(temp[i + 1]))
			{
				place_file(&(*token)->redirection, temp[i + 1]);
				if (!(*token)->redirection->file)
					return (free2pointers(temp),
						free2pointers((*token)->command), free(*token));
			}
			else
				return (free2pointers(temp), free2pointers((*token)->command),
					free(*token));
			i += 2;
		}
		else
		{
			add_command(*token, temp[i], cmd);
			if (!(*token)->command)
				return (free2pointers(temp), free2pointers((*token)->command),
					free(*token));
			cmd++;
			i++;
		}
	}
	free2pointers(temp);
	*token = temp_token;
}

void	remove_node(t_token **token)
{
	t_token	*temp;

	if (token == NULL || *token == NULL)
		return ;
	temp = (*token)->next;
	(*token)->next = temp->next;
	free(temp);
}

int	end_of_var(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && ft_isalnum(line[i]))
		i++;
	return (i);
}

char	*replace_variable(char *line, t_env *var)
{
	node_t	*temp;
	char	*var_name;
	char	*ret;

	if (line[0] == '?')
		printf("error code. ADD exit status\n");
	if (is_space(line[0]))
		return (ft_strdup("$"));
	var_name = malloc(sizeof(char) * 1000);
	if (!var_name) // Check for malloc failure
		return (NULL);
	var_name = ft_memcpy(var_name, line, end_of_var(line));
	temp = var->head_env;
	while (temp)
	{
		if (ft_strncmp(temp->data, var_name, ft_strlen(var_name)) == 0)
		{
			ret = ft_strdup(temp->data + end_of_var(temp->data) + 1);
			free(var_name);
			return (ret);
		}
		temp = temp->next;
	}
	free(var_name); // Free var_name if not used
	return (NULL);
}

char *check_dollar_sign(char *line, t_env *var)
{
    int i, j;
    char *ret, *temp;
    
    if (!line)
        return (NULL);
    
    ret = malloc(sizeof(char) * (ft_strlen(line) * 2 + 1)); // Allocate more space
    if (!ret)
        return (NULL);
    
    if (ft_strchr(line, '$') == NULL)
    {
        free(ret);
        return (ft_strdup(line));
    }
    
    for (i = 0, j = 0; line[i]; i++)
    {
        if (line[i] == '\'' && closing_quote(line, i, '\''))
        {
            while (line[i] && line[i] != '\'')
                ret[j++] = line[i++];
            if (line[i])
                ret[j++] = line[i];
        }
        else if (line[i] == '$')
        {
            temp = replace_variable(&line[i + 1], var);
            if (temp)
            {
                ft_strlcpy(&ret[j], temp, ft_strlen(temp) + 1);
                j += ft_strlen(temp);
                free(temp);
            }
            i += end_of_var(&line[i + 1]);
        }
        else
        {
            ret[j++] = line[i];
        }
    }
    ret[j] = '\0';
    return (ret);
}


t_token	*main_pars(char *line, t_env *var)
{
	t_token	*token;
	char	**temp;
	char	*updated_line;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	temp = ft_split_mod(line, ' ');
	if (!temp)
	{
		free(token); // Free token on failure
		return (NULL);
	}
	updated_line = check_dollar_sign(line, var);
	// printf("updated_line: %s\n", updated_line);
	tokenize(&token, temp);
	// if(ft_strcmp(token->command[0], "export") == 0)
	// 	export(var, token->command);
	// free(updated_line);
	return (token);
}