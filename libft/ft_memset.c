/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:58:16 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 16:17:21 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*zin;
	unsigned char	let;
	size_t			i;

	zin = (unsigned char *)s;
	let = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		zin[i] = let;
		i++;
	}
	return (zin);
}

// int main(void)
// {
// 	char buffer[10] = "bbbbbbbbbb";
// 	char *res = ft_memset(buffer, 'a', 3);

// 	printf("%s", res);
// }