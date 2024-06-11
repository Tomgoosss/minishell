/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:03:43 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 15:53:04 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	if (src == 0 && dest == 0)
		return (NULL);
	if (s < d)
	{
		i = n;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
		return (d);
	}
	d = ft_memcpy(dest, src, n);
	return (d);
}

// int main(void)
// {
// 	char source[] = "this is my source that i want to copy";
// 	char dest[50];

// 	printf("%s\n", (char *)ft_memmove(dest, source, 20));
// 	printf("%s\n", (char*)memmove(dest, source, 20));
// }