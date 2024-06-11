/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:03:39 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 15:34:31 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	cc;
	size_t			i;

	str = (unsigned char *)s;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*str == cc)
			return ((void *)str);
		i++;
		str++;
	}
	return (0);
}

//  int main(void)
//  {
// 	char string[] = "vind de letter z in deze zin";
// 	printf("%s\n", ft_memchr(string, 'z', 20));
// 	printf("%s\n", memchr(string, 'z', 20));
//  }