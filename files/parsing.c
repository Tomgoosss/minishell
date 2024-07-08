/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:09:51 by fbiberog          #+#    #+#             */
/*   Updated: 2024/07/08 13:36:24 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check_whitespaces function is used to skip whitespaces in the line
// it returns
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

//
// check_redirections function is used to check if there is any redirection in the line
// // it returns -1 if there is no redirection in the line
// // it returns 1 if there is a redirection in the line
// // it returns 0 if there is a redirection in the line but it is not valid,

int	check_redirections(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			break ;
		i++;
		if (line[i] == '\0')
			return (-1);
	}
	i = 0;
	while (line[i + 2])
	{
		if (((line[i] == '<' && line[i + 1] == '<') || ((line[i] == '>')
					&& line[i + 1] == '>')) && check_whitespaces(line, (i
					+ 2)) == 1)
			return (1);
		if (check_whitespaces == -1)
			return (0);
		i++;
	}
	return (0);
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

void	tokenize(t_token **token, char *line)
{
	t_token	*head;
	char	**temp;
	int		i;

	i = 0;
	head = (*token);
	temp = ft_split_mod(line, ' ');
	while (temp[i])
	{
		(*token)->command = temp[i];
		(*token)->next = malloc(sizeof(t_token));
		if (ft_strcmp(temp[i], ">>") == 0)
			(*token)->type = REDIR_OUT_APPEND;
		else if (ft_strcmp(temp[i], ">") == 0)
			(*token)->type = REDIR_OUT;
		else if (ft_strcmp(temp[i], "<<") == 0)
			(*token)->type = REDIR_IN_HERE_DOC;
		else if (ft_strcmp(temp[i], "<") == 0)
			(*token)->type = REDIR_IN;
		else if (ft_strcmp(temp[i], "|") == 0)
			(*token)->type = PIPE;
		else
			(*token)->type = 0;
		(*token) = (*token)->next;
		i++;
	}
	(*token)->next = NULL;
	(*token) = head;
}

void	prep_commands(t_token **token, char *line)
{
	t_token	*head;
	int		i;
	int		commands;

	i = 0;
	commands = 0;
	head = (*token);
	while ((*token)->next)
	{
		if ((*token)->type == 0)
		{
			if ((*token)->command[0] == "'" || (*token)->command[0] == 34)
				{
					(*token)->type =(*token)->file;
					(*token)->type = 7;
				}
				else
					(*token)->type = 8;
			}
		(*token) = (*token)->next;
	}
	(*token) = head;
	return ;
}
void remove_node(t_token **token)
{
	t_token *temp;

	temp = (*token)->next;
	(*token)->next = temp->next;
	free(temp);
}
int flagcounter(t_token *token)
{
	int count;

	count = 0;
	while(token->next)
	{
		if(token->type == 8)
			count++;
		token = token->next;
	}
	return (count);
}
void command_and_flags(t_token **token)
{
	t_token *head;
	t_token *node;
	char **temp;
	int i;

	i = 1;	
	head = (*token);
	temp = malloc(sizeof(char *) * flagcounter((*token)) + 2); //counts amounts of flags and adds 2 for the command itself and NULL
	temp[0] = (*token)->command;
	node = (*token);
	while((*token)->next)
	{
		while((*token)->next && (*token)->type == 8)
		{
			temp[i] = ft_strdup((*token)->command);
			remove_node(token);
			(*token) = (*token)->next;
			i++;
		}
		if((*token)->type != 8)
			(*token) = (*token)->next;
	}
	temp[i] = NULL;
	node->command = temp;
	(*token) = head;
}

void regroup_commands(t_token **token)
{
	t_token *head;

	head = (*token);
	while((*token)->next)
	{
		if((*token)->type == 7)
			command_and_flags(token);
		if((*token)->type < 6)
		{
			(*token)->file = (*token)->next->command;
			printf("%s\n", (*token)->file);
			remove_node(token);
		}
		else
			(*token)->file = NULL;
		(*token) = (*token)->next;	
	}
	(*token) = head;
}
void	main_pars(char *line, t_env *var)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	tokenize(&token, line);
	prep_commands(&token, line);
	regroup_commands(&token);
	// while(token->next)
	// {
	// 	printf("command: %s\n", token->command[0]);
	// 	token = token->next;
	// }
	return ;
}
