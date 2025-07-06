/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:32:12 by hanjkim           #+#    #+#             */
/*   Updated: 2024/06/23 16:04:49 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_pointer(size_t pointer, int *len)
{
	char	*base_char_set;

	base_char_set = HEX_LOWER;
	if (pointer != 0)
	{
		print_pointer(pointer / 16, len);
		ft_putchar(base_char_set[pointer % 16], len);
	}
}

void	ft_pointer(size_t pointer, int *len)
{
	if (pointer == 0)
	{
		ft_putstr("(nil)", len);
		return ;
	}
	(*len) += 2;
	if (write(1, "0x", 2) == -1)
	{
		(*len) = -1;
		return ;
	}
	print_pointer(pointer, len);
}
