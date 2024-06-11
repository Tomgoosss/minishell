/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allbase.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:39:48 by tgoossen          #+#    #+#             */
/*   Updated: 2023/11/09 13:42:30 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printall(long nb, char *base, int len)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (nb >= len)
		count = printall(nb / len, base, len);
	nb = nb % len;
	i = base[nb];
	count += write(1, &i, 1);
	return (count);
}

int	allbase(long nb, char *base)
{
	int	len;
	int	count;

	len = 0;
	count = 0;
	while (base[len])
		len++;
	if (nb < 0)
	{
		count += write(1, "-", 1);
		nb = -nb;
	}
	count += printall(nb, base, len);
	return (count);
}
