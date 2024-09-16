#include "minishell.h"


void free2pointers(char **str)
{
	int i;

	i = 0;
	if(!str)
		return ;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void free_list(node_t *head)
{
	node_t *tmp;
	node_t *next;

	tmp = head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->data);
		free(tmp);
		tmp = next;
	}
}
void free_redirection(t_redirection *redirection)
{
	t_redirection *tmp;
	t_redirection *next;

	tmp = redirection;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->file);
		free(tmp);
		tmp = next;
	}
}
void free_token(t_token *token)
{
	t_token *tmp;
	t_token *next;

	tmp = token;
	while (tmp)
	{
		if(tmp->redirection)
			free_redirection(tmp->redirection);
		next = tmp->next;
		free2pointers(tmp->command);
		free(tmp);
		tmp = next;
	}
}


void free_env(t_env *var)
{
	if (var->head_exp)
		free_list(var->head_exp);
	if (var->head_env)
		free_list(var->head_env);
	if (var)
		free(var);
}
// Concatenates two strings and frees the first one.
// s1: The first string (will be freed).
// s2: The second string.
// Returns: A new string containing the concatenation of s1 and s2, or NULL if allocation fails.
char	*ft_strjoinfree(char const *s1, char const *s2)
{
	int		i;
	int		y;
	int		s1s2count;
	char	*copy;

	s1s2count = ft_strlen(s1) + ft_strlen(s2);
	copy = (char *)malloc((s1s2count + 1) * sizeof(char));
	i = 0;
	if (copy == 0)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y])
	{
		copy[i] = s2[y];
		y++;
		i++;
	}
	copy[i] = '\0';
	free((char *)s1);
	return (copy);
}
