/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:07:05 by hanjkim           #+#    #+#             */
/*   Updated: 2024/06/23 16:00:53 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>

# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"

void	ft_putchar(char c, int *len);
void	ft_putstr(char *args, int *len);
void	ft_string(char args, int len);
void	ft_putnbr(int n, int *len);
void	ft_hexa(unsigned int hex, int *len, char x_X);
void	print_hexa(unsigned int hex, char *base_char_set, int *len);
void	ft_unsigned_int(unsigned int ui, int *len);
void	ft_pointer(size_t pointer, int *len);
void	print_pointer(size_t pointer, int *len);
int		ft_printf(const char *str, ...);

#endif
