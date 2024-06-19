#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>

typedef struct node{
	char *data;
	struct node *next;
} node_t;

typedef struct s_token{
	char **command;
	struct s_token *next;
	char *type;
} t_token;

typedef struct s_env{
	char **env;
	node_t *head;
} t_env;

void free2pointers(char **str);
char	*remove_white_spaces(char *line);
char	*ft_strjoinfree(char const *s1, char const *s2);
void fill_nodes_env(t_env *man);
void add_node(node_t **head, node_t *new);
node_t *make_node(char *line);
void main_pars(char *line, t_env *man);
void	main_pars(char *line, t_env *var);
int	check_whitespaces(char *line, int i);


#endif