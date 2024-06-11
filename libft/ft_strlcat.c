/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:14:55 by tgoossen          #+#    #+#             */
/*   Updated: 2023/10/18 11:29:03 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = 0;
	srclen = 0;
	i = 0;
	while (dst[dstlen] && dstlen < n)
		dstlen++;
	while (src[srclen])
		srclen++;
	if (dstlen >= n)
		return (dstlen + srclen);
	while (src[i] && (dstlen + i) < (n - 1))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

// int main(void)
// {
// 	char dst[30] = "dit is dest";
// 	char src[] = "dit is src";
// 	char dst1[30] = "dit is dest";
// 	char src1[] = "dit is src";
// 	size_t n = 6;

// 	printf("%d\n", ft_strlcat(src, dst, n));
// 	printf("%s\n", dst);
// 	printf("%zu\n", strlcat(src1, dst1, n));
// 	printf("%s", dst1);
// }