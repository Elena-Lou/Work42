/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:13:53 by elouisia          #+#    #+#             */
/*   Updated: 2022/01/18 15:40:56 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

# ifdef __APPLE__
#  define RETURN_NULL "0x0"
# elif __linux__
#  define RETURN_NULL "(nil)"
# endif

typedef struct s_list
{
	int		len;
}	t_data;

/*
** ft_printf.c
*/

int	ft_printf(const char *str, ...);

/*
** ft_printf_utils.c
*/

int	ft_strlen(char *str);
int	ft_print_char(char c);
int	ft_print_str(char *str);

/*
** ft_printf_n.c
*/

int	ft_getsize(long int nb);
int	ft_print_unbr(unsigned int n);
int	ft_print_nbr(int n);

/*
** ft_printf_base.c
*/

int	ft_print_nbrbase(unsigned int n, char i);
int	ft_getsizebase(unsigned int n);
int	ft_getsizeptr(unsigned long nb);
int	ft_print_ptrbase(unsigned long n);

#endif