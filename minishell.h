/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:40:27 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/22 15:41:11 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern int				g_signal;

typedef struct node
{
	char				*data;
	struct node			*next;
}						t_node;

typedef struct s_env
{
	char				**env;
	t_node				*head_env;
	t_node				*head_exp;
}						t_env;

typedef enum e_minishell
{
	REDIR_OUT_APPEND,
	REDIR_OUT,
	REDIR_IN_HERE_DOC,
	REDIR_IN,
	PIPE,
	STRING
}						t_minishell;

typedef struct redirection
{
	char				*file;
	t_minishell			type;
	struct redirection	*next;
}						t_redirection;

typedef struct s_token
{
	char				**command;
	struct s_token		*next;
	t_redirection		*redirection;
}						t_token;

typedef struct execute
{
	int					fd[2];
	int					prev_fd[2];
	char				*path;
	int					amound_commands;
	int					exit_status;
	int					in_dup;
	int					out_dup;
	int					heredoc_fd;
}						t_ex;

void					free2pointers(char **str);
char					*remove_white_spaces(char *line);
char					*ft_strjoinfree(char const *s1, char const *s2);
void					fill_nodes_env(t_env *var, char **env);
void					add_node(t_node **head, t_node *new);
t_node					*make_node(char *line);
t_token					*main_pars(char *line, t_env *var, t_ex *ex);
int						check_whitespaces(char *line, int i);
void					fill_nodes_exp(t_env *var);
int						ft_strcmp(const char *s1, const char *s2);
void					swap_nodes(char **first, char **second);
void					sort_export(t_env *var);
int						closing_quote(char *line, int i, char c, int extra);
char					**ft_split_mod(char const *s, char c);
void					buildins(char *line, t_env *var);
int						valid_redirection(char *str);
void					remove_node(t_token **token);
int						export(t_env *var, char **command);
void					main_execute(t_token *token, t_env *env, t_ex *ex);
int						check_exit(char **cmd_array);
int						check_if_buildin(t_token *token, t_env *var);
int						env_buildin(t_env *var);
int						pwd_buildin(void);
void					error_lines(char *arg, int i);
int						open_files(t_token *token, int i);
int						is_space(char c);
int						check_buildin(t_token *token);
int						cd_buildin(t_token *token, t_env *var);
void					free_env(t_env *var);
void					free_token(t_token *token);
void					free_list(t_node *head);
int						buildins_par(t_token *token, t_env *var);
int						empty_line(char *line);
int						echo(char **command);
int						unset(t_token *token, t_env *var);
void					remove_current_node(t_node **head, t_node *node);
void					copy_dup(t_ex *ex, int i);
void					error_lines(char *arg, int i);
void					make_path(t_token *token, t_ex *ex, t_env *var);
int						find_path(char **temp_path, t_ex *ex, t_token *token);
void					close_pipes_par(t_ex *ex, int count);
void					close_pipes_child(t_ex *ex, int count);
void					make_2d_env(t_env *env);
int						count_nodes(t_token *token);
int						find_slash(t_token *token);
int						check_if_dir(t_token *token);
void					cleanup_execution(t_ex *ex, int i);
void					setup_pipe(t_ex *ex, int i);
void					update_pwd(t_node *temp, const char *cwd);
void					remove_current_node(t_node **head, t_node *node);
void					printf_export(t_env *var);
char					*prepare_for_export(char *line);
int						remove_double_env(t_env *var, char *arg);
int						red_in_heredoc(t_redirection *red);
char					*ft_strndup(const char *s, size_t n);
int						get_token_length(const char *s, int *quote_len);
int						is_quote(char c);
int						is_delimiter(const char *s);
void					print_str_array(char **str);
void					free_str_array(char **str, int i);
void					setup_signals(void);
void					reset_signals(void);
void					handle_sigint(int sig);
void					handle_sigquit(int sig);
void					signals_ignore(void);
int						handle_heredocs(t_token *token);

#endif
