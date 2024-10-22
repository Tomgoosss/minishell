/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:37:29 by tgoossen          #+#    #+#             */
/*   Updated: 2024/10/22 15:41:56 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_buildin(t_env *var)
{
	t_node	*temp;

	temp = var->head_env;
	while (temp)
	{
		printf("%s\n", temp->data);
		temp = temp->next;
	}
	return (0);
}

int	pwd_buildin(void)
{
	char	cwd[4069];

	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (0);
}

void	update_pwd(t_node *temp, const char *cwd)
{
	free(temp->data);
	temp->data = ft_strjoin("PWD=", cwd);
}
