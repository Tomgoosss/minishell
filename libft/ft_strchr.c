/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:27:25 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 15:28:56 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

// int main(void)
// {
// 	int c = 'f';
// 	char *a1 = ft_strchr("hello", c);
// 	// char *a2 = strchr("hello", c);

// 	printf("%c\n", *a1);
// 	// printf("%c", *a2);
// }