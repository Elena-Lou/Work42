/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:41:45 by elouisia          #+#    #+#             */
/*   Updated: 2022/03/27 15:19:55 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	my_mlx_pixel_put(t_ptr *win, int x, int y, int color)
{
	char	*dst;

	if (x > W_WIDTH - 1 || y > W_HEIGHT - 1 || x < 0 || y < 0)
		return ;
	dst = win->img.addr + (y * win->img.line_len + x * (win->img.bpp / 8));
	*(unsigned int *)dst = color;
}

int	image_init(t_ptr *win)
{
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		exit (0);
	win->win_ptr = mlx_new_window(win->mlx_ptr, W_WIDTH, W_HEIGHT, "mlx");
	win->img.img = mlx_new_image(win->mlx_ptr, W_WIDTH, W_HEIGHT);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	win->frac.julia = 0;
	win->frac.mandel = 0;
	win->frac.def_colour = 0;
	return (1);
}

double	ft_atof(char *str)
{
	int		count;
	char	*tmp;
	int		i;
	int		j;
	double	nb;

	i = 0;
	j = 0;
	count = ft_strlen(ft_strchr(str, '.')) - 1;
	tmp = ft_strdup(str);
	while (str[i] && str[i] != '.')
		tmp[j++] = str[i++];
	if (str[i] == '.')
		i++;
	while (str[i])
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	nb = ft_atoi(tmp);
	while ((count--) > 0)
		nb /= 10;
	free(tmp);
	return (nb);
}

int	close_window(t_ptr *win)
{
	mlx_destroy_image(win->mlx_ptr, win->img.img);
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	mlx_destroy_display(win->mlx_ptr);
	free(win->mlx_ptr);
	exit (0);
}
