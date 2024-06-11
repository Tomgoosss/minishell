/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:21:12 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 15:34:11 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	if (is_alpha(c) || is_digit(c))
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	int word1 = ft_isalnum('*');
// 	int word2 = isalnum('*');

// 	printf("%i\n", word1);
// 	printf("%i", word2);
// }