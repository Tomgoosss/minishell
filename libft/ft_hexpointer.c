/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:38:19 by tgoossen          #+#    #+#             */
/*   Updated: 2023/11/09 16:25:55 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_recursive(long long unsigned i);

static int	lengicount(long long unsigned n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n += INT_MAX;
	}
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	ft_hexpointer(void *str)
{
	long long unsigned	i;
	int					count;

	i = (long long unsigned)str;
	if (i == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count = lengicount(i);
	count += write(1, "0x", 2);
	ft_recursive(i);
	return (count);
}

void	ft_recursive(long long unsigned i)
{
	if (i >= 16)
		ft_recursive(i / 16);
	if (i % 16 >= 10)
		ft_putchar(i % 16 + 87);
	else
		ft_putchar(i % 16 + '0');
}
