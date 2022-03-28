/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:37:14 by elouisia          #+#    #+#             */
/*   Updated: 2022/03/27 14:51:11 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	check_fractal(t_ptr *win, char **param)
{
	if (ft_strcmp(param[1], "Mandelbrot") == 0)
	{
		win->frac.mandel = 1;
		win->img.min_re = -2;
		win->img.max_re = 1.2;
		win->img.min_im = -1.5;
		win->img.max_im = 1.5;
		mandelbrot(win);
	}
	else if (ft_strcmp(param[1], "Julia") == 0)
	{
		win->frac.julia = 1;
		win->img.min_re = -2;
		win->img.max_re = 2;
		win->img.min_im = -2;
		win->img.max_im = 2;
		win->maths.k_re = ft_atof(param[2]);
		win->maths.k_im = ft_atof(param[3]);
		julia(win);
	}
	return (0);
}

static int	check_julia_arg(int ac, char **av)
{
	int	i;

	i = 0;
	if (ft_strcmp(av[1], "Julia") == 0 && ac == 4)
	{
		while (av[2][i])
		{
			if ((av[2][i] < '0' || av[2][i] > '9')
			&& av[2][i] != '.' && av[2][i] != '-')
				return (1);
			i++;
		}
		i = 0;
		while (av[3][i])
		{
			if ((av[3][i] < '0' || av[3][i] > '9')
			&& av[3][i] != '.' && av[3][i] != '-')
				return (1);
			i++;
		}
	}
	return (0);
}

static int	check_arg(int ac, char **av)
{
	if (ac < 2 || ((ft_strcmp(av[1], "Mandelbrot") != 0)
			&& ft_strcmp(av[1], "Julia") != 0)
		|| (ft_strcmp(av[1], "Julia") == 0 && ac != 4))
	{
		ft_printf("Usage : ./fractol Mandelbrot / Julia x x");
		return (1);
	}
	if (check_julia_arg(ac, av) != 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_ptr		win;

	if (check_arg(ac, av) != 0)
		return (0);
	image_init(&win);
	keys_init(&win);
	check_fractal(&win, av);
	mlx_key_hook(win.win_ptr, &key_check, &win);
	mlx_mouse_hook(win.win_ptr, &mouse_zoom, &win);
	mlx_hook(win.win_ptr, 17, 1L << 3, &close_window, &win);
	mlx_loop(win.mlx_ptr);
	return (0);
}
