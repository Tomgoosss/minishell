/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbiberog <fbiberog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:35:21 by fbiberog          #+#    #+#             */
/*   Updated: 2024/10/28 17:35:33 by fbiberog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node_list(t_node *head)
{
	t_node	*next;

	if (!head)
		return ;
	next = head->next;
	if (head->data)
		free(head->data);
	free(head);
	free_node_list(next);
}

void	free_env(t_env *env)
{
	free_node_list(env->head_env);
	free_node_list(env->head_exp);
	if (env->env)
		free(env->env);
	free(env);
}
