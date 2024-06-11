/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomgoossens <tomgoossens@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:48:13 by tgoossen          #+#    #+#             */
/*   Updated: 2024/02/02 16:57:45 by tomgoossens      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *s)
{
	int	c;

	c = 0;
	while (s[c] != '\0')
		c++;
	return (c);
}

// int	main(void)
// {
// 	int	word = ft_strlen("tdsdsfst");
// 	printf("%i", word);
// }