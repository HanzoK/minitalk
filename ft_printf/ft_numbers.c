/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:17:40 by hanjkim           #+#    #+#             */
/*   Updated: 2024/06/23 15:47:01 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsigned_int(unsigned int ui, int *len)
{
	if (ui > 9)
		ft_unsigned_int(ui / 10, len);
	ft_putchar(ui % 10 + '0', len);
}

void	ft_putnbr(int num, int *len)
{
	if (num == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
		{
			(*len) = -1;
			return ;
		}
		(*len) += 11;
		return ;
	}
	if (num < 0)
	{
		ft_putchar('-', len);
		ft_putnbr(num * -1, len);
	}
	else
	{
		if (num > 9)
			ft_putnbr(num / 10, len);
		ft_putchar(num % 10 + '0', len);
	}
}
