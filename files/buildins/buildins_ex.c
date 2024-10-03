#include "minishell.h"

// int buildins_par(t_token *token, t_env *var)
// {
// 	if(token->command == NULL)
// 		return(0);
// 	if(strncmp(token->command[0], "cd", 2) == 0)
// 		return(cd_buildin(token, var));	
// 	if(strncmp(token->command[0], "export", 6) == 0)
// 		return(export(var, token->command));
// }

int check_if_buildin(t_token *token, t_env *var)
{
	if(strncmp(token->command[0], "echo", 4) == 0)
		return(echo(token->command));
	if(strncmp(token->command[0], "cd", 2) == 0)
		return(cd_buildin(token, var));
	if(strncmp(token->command[0], "pwd", 3) == 0)
		return(pwd_buildin());
	if(strncmp(token->command[0], "export", 6) == 0)
		return(export(var, token->command));
	// if(strncmp(token->command[0], "unset", 5))
	// 	// unset
	if(strncmp(token->command[0], "env", 3) == 0)
		return(env_buildin(var));
	// if(strncmp(token->command[0], "exit", 4))
	// 	// exit
	return(0);
}

int check_buildin(t_token *token)
{
	if(strncmp(token->command[0], "echo", 4) == 0)
		return(1);
	if(strncmp(token->command[0], "cd", 2) == 0)
		return(1);
	if(strncmp(token->command[0], "pwd", 3) == 0)
		return(1);
	if(strncmp(token->command[0], "export", 6) == 0)
		return(1);
	if(strncmp(token->command[0], "unset", 5) == 0)
		return(1);
	if(strncmp(token->command[0], "env", 3) == 0)
		return(1);
	if(strncmp(token->command[0], "exit", 4) == 0)
		return(1);
	return(0);
}