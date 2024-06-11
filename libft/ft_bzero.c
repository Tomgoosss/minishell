/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:25:18 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/18 11:27:07 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*word;

	word = (unsigned char *)s;
	while (n > 0)
	{
		*word = 0;
		word++;
		n--;
	}
}
// int main(void)
// {
// 	char zin[] = "dit is een zin";
// 	ft_bzero(zin, 10);
// }