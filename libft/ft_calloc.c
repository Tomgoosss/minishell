/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:26:30 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/24 15:30:00 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	size_t	tsize;
// 	size_t	i;
// 	char	*mem;

// 	i = 0;
// 	tsize = nmemb * size;
// 	mem = malloc(tsize);
// 	if (nmemb == 0 || size == 0)
// 		return (NULL);
// 	while (i < tsize)
// 	{
// 		mem[i] = '0';
// 		i++;
// 	}
// 	return ((void *)mem);
// }

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	tsize;
	void	*mem;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	tsize = nmemb * size;
	mem = malloc(tsize);
	if (mem)
		ft_memset(mem, 0, tsize);
	return (mem);
}

// int main(void)
// {
// 	ft_calloc(100, sizeof(int));
// 	calloc(100, sizeof(int));
// }