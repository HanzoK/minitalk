/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:46:08 by hanjkim           #+#    #+#             */
/*   Updated: 2024/06/23 16:05:49 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hexa(unsigned int hex, char *base_char_set, int *len)
{
	if (hex != 0)
	{
		print_hexa(hex / 16, base_char_set, len);
		ft_putchar(base_char_set[hex % 16], len);
	}
}

void	ft_hexa(unsigned int hex, int *len, char x_or_X)
{
	char	*base_char_set;

	if (x_or_X == 'x')
		base_char_set = HEX_LOWER;
	if (x_or_X == 'X')
		base_char_set = HEX_UPPER;
	if (hex == 0)
	{
		ft_putchar('0', len);
		return ;
	}
	print_hexa(hex, base_char_set, len);
}
