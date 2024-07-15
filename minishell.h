#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct node
{
	char			*data;
	struct node		*next;
}					node_t;

typedef struct s_env
{
	char			**env;
	node_t			*head_env;
	node_t			*head_exp;
}					t_env;

typedef enum e_minishell
{
	REDIR_OUT_APPEND,
	REDIR_OUT,
	REDIR_IN_HERE_DOC,
	REDIR_IN,
	PIPE,
	STRING
}					t_minishell;

typedef struct redirection
{
	char			*file;
	t_minishell		type;
	struct t_redirection 	*next;
}					t_redirection;

typedef struct s_token
{
	char			**command;
	struct s_token	*next;
	t_redirection	*redirection;
}					t_token;

void				free2pointers(char **str);
char				*remove_white_spaces(char *line);
char				*ft_strjoinfree(char const *s1, char const *s2);
void				fill_nodes_env(t_env *man);
void				add_node(node_t **head, node_t *new);
node_t				*make_node(char *line);
void				main_pars(char *line, t_env *man);
void				main_pars(char *line, t_env *var);
int					check_whitespaces(char *line, int i);
void				fill_nodes_exp(t_env *var);
int					ft_strcmp(const char *s1, const char *s2);
void				swap_nodes(char **first, char **second);
void				sort_export(t_env *var);
int					closing_quote(char *line, int i, char c);
char				**ft_split_mod(char const *s, char c);
void				buildins(char *line, t_env *var);

#endif