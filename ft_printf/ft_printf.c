/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:28:58 by hanjkim           #+#    #+#             */
/*   Updated: 2024/09/13 14:41:05 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_null_terminate(const char *str, int index)
{
	if (str[index] == '\0')
		return (-1);
	return (str[index]);
}

static void	parse_input(char c, va_list *args, int *len)
{
	if (c == 'c')
		ft_putchar(va_arg(*args, int), len);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(*args, int), len);
	else if (c == 'p')
		ft_pointer(va_arg(*args, size_t), len);
	else if (c == 'u')
		ft_unsigned_int(va_arg(*args, unsigned int), len);
	else if (c == 's')
		ft_putstr(va_arg(*args, char *), len);
	else if (c == 'x')
		ft_hexa(va_arg(*args, unsigned int), len, 'x');
	else if (c == 'X')
		ft_hexa(va_arg(*args, unsigned int), len, 'X');
	else if (c == '%')
		ft_putchar('%', len);
	else
	{
		(*len) = -1;
		return ;
	}
}

int	ft_printf(const char *str, ...)
{
	int		index;
	int		len;
	va_list	args;

	index = 0;
	len = 0;
	va_start(args, str);
	if (str == NULL)
		return (-1);
	while (str[index] != '\0')
	{
		if (str[index] == '%')
		{
			index++;
			if (check_null_terminate(str, index) == -1)
				return (va_end(args), -1);
			parse_input(str[index], &args, &len);
		}
		else
			ft_putchar(str[index], &len);
		index++;
	}
	va_end(args);
	return (len);
}
/*
#include <stdio.h>

int main()
{
    int your_res;
    int real_res;
	long a = 16;
	long *ptr = &a;
    
	printf("CHARS:\n");
    real_res = printf("%j", 'c');
    printf("\n");
    your_res = ft_printf("%j", 'c');
    printf("\nYours:%d Real:%d\n", your_res, real_res);
	
	printf("\nDIGIT/INT:\n");
	real_res = printf("%d", 123456789010, 9);
    printf("\n");
    your_res = ft_printf("%i", 123456789010, 9);
    printf("\nYours:%d Real:%d\n", your_res, real_res);
	
	printf("\nUNSIGNED INT:\n");
	real_res = printf("%u", NULL);
    printf("\n");
    your_res = ft_printf("%u", NULL);
    printf("\nYours:%d Real:%d\n", your_res, real_res);
	
	printf("\nSTRING:\n");
	real_res = printf("%s", NULL);
    printf("\n");
    your_res = ft_printf("%s", NULL);
    printf("\nYours:%d Real:%d\n", your_res, real_res);
	
	printf("\nPOINTER:\n");
    real_res = printf("%p", ptr);
    printf("\n");
    your_res = ft_printf("%p", ptr);
    printf("\nYours:%d Real:%d\n", your_res, real_res);
	
	printf("\nLOW HEXA:\n");
	real_res = printf("%x", 4294967295);
    printf("\n");
    your_res = ft_printf("%x", 4294967295);
    printf("\nYours:%d Real:%d\n", your_res, real_res);
	
	printf("\nUPPER HEXA:\n");
	real_res = printf("%X", 42949672956);
    printf("\n");
    your_res = ft_printf("%X", 42949672956);
    printf("\nYours:%d Real:%d\n", your_res, real_res);
	
	printf("\nNULL CHECK:\n");
    real_res = printf(NULL);
    printf("\n");
    your_res = ft_printf(NULL);
    printf("\nYours:%d Real:%d\n", your_res, real_res);
	
	printf("\nPERCENTAGE:\n");
    your_res = ft_printf("%");
	real_res = printf("%");
    printf("\nYours:%d Real:%d\n", your_res, real_res);
}*/
