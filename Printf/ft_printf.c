/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:12:51 by elouisia          #+#    #+#             */
/*   Updated: 2022/01/18 15:24:39 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_checkptr(va_list arg, t_data *data)
{
	unsigned long	ptr;

	ptr = va_arg(arg, unsigned long);
	if (!ptr)
		return (ft_print_str(RETURN_NULL));
	else
	{
		data->len += ft_print_str("0x");
		data->len += ft_print_ptrbase(ptr);
	}
	return (0);
}

static int	ft_whatsnext(char i, va_list arg, t_data *data)
{
	if (i == 'c')
		data->len += ft_print_char(va_arg(arg, int));
	if (i == 's')
		data->len += ft_print_str(va_arg(arg, char *));
	if (i == 'i' || i == 'd')
		data->len += ft_print_nbr(va_arg(arg, int));
	if (i == 'u')
		data->len += ft_print_unbr(va_arg(arg, unsigned int));
	if (i == 'x' || i == 'X')
		data->len += ft_print_nbrbase(va_arg(arg, unsigned int), i);
	if (i == 'p')
		data->len += ft_checkptr(arg, data);
	if (i == '%')
		data->len += ft_print_char('%');
	return (data->len);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	t_data	data;

	i = 0;
	data.len = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_print_char(str[i]);
			data.len++;
		}
		else
		{
			i++;
			data.len = ft_whatsnext(str[i], arg, &data);
		}
		i++;
	}
	va_end(arg);
	return (data.len);
}
/*
#include <stdio.h>

int	main(void)
{
	int	i;

	i = 42;
	printf("ft len : %d\n", ft_printf("s 'Hey Hey' : %s\n", "Hey Hey"));
	printf("len : %d\n", printf("s 'Hey Hey' : %s\n", "Hey Hey"));
	printf("ft len : %d\n", ft_printf("%% : %%\n"));
	printf("len : %d\n", printf("%% : %%\n"));
	printf("ft len : %d\n", ft_printf("i -2147483648 : %i\n", -2147483648));
	printf("len : %d\n", printf("i -2147483648 : %i\n", -2147483648));
	printf("ft len : %d\n", ft_printf("i 21474848 : %i\n", 2147483648));
	printf("len : %d\n", printf("i 21474848 : %i\n", 2147483648));
	printf("ft len : %d\n", ft_printf("x 25 : %x\n", 25));
	printf("len : %d\n", printf("x 25 : %x\n", 25));
	printf("ft len : %d\n", ft_printf("X 16 : %X\n", 16));
	printf("len : %d\n", printf("X 16 : %X\n", 16));
	printf("ft len : %d\n", ft_printf("p 42 : %p\n", &i));
	printf("len : %d\n", printf("p 42 : %p\n", &i));
	printf("ft len %d\n ", ft_printf("p NULL : %p\n", NULL));
	printf("len %d\n", printf("p NULL : %p\n", NULL));
	printf("ft len : %d\n", ft_printf("x -1 : %x\n", -1));
	printf("len : %d\n", printf("x -1 : %x\n", -1));
	printf("ft len : %d\n", ft_printf("X -9 : %X\n", -9));	
	printf("len : %d\n", printf("X -9 : %X\n", -9));
	printf("ft len : %d\n", ft_printf("x 2147483648: %x\n", 2147483648));
	printf("len : %d\n", printf("x 2147483648: %x\n", 2147483648));
	printf("ft len : %d\n", ft_printf("x 0 : %x\n", 0));
	printf("len : %d\n", printf("x 0 : %x\n", 0));
	printf("ft len : %d\n", ft_printf("X -2147483648: %X\n", -2147483648));
	printf("len : %d\n", printf("X -2147483648: %X\n", -2147483648));
	printf("ft len : %d\n", ft_printf("%x\n", 9223372036854775807));
	printf("len : %d\n", printf("%x\n", 9223372036854775807));
	printf("ft len : %d\n", ft_printf("c 'y' : %c\n", 'y'));
	printf("len : %d\n", printf("c 'y' : %c\n", 'y'));
	printf("ft len : %d\n", ft_printf("u -2147483648 : %u\n", -2147483648));
	printf("len : %d\n", printf("u -2147483648 : %u\n", -2147483648));
	printf("ft len : %d\n", ft_printf("u 2147483648 : %u\n", 2147483648));
	printf("len : %d\n", printf("u 2147483648 : %u\n", 2147483648));

	return (0);
}
*/