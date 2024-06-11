/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:20:14 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/19 16:07:37 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
	{
		return (1);
	}
	return (0);
}

// int main (void)
// {
// 	int num = ft_isalpha('a');
// 	int r = isalpha('a');

// 	printf("%i\n", num);
// 	printf("%i", r);
// }