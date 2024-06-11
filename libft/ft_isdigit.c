/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:05:11 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/18 11:27:30 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	int word1 = ft_isdigit ('10');
// 	int word2 = isdigit('10');

// 	printf("%i\n", word1);
// 	printf("%i", word2);
// }