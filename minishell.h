#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>

typedef struct s_minishell{
	char **commands;
	char *env;
	char **envpath;
	char *path;
} t_minishell;

typedef struct node{
	char *data;
	struct node *next;
} node_t;

void free2pointers(char **str);
char	*ft_strjoinfree(char const *s1, char const *s2);


#endif