/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:19:53 by elouisia          #+#    #+#             */
/*   Updated: 2022/03/27 15:21:05 by elouisia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <errno.h>
# include "ft_printf.h"
# include "libft.h"

# define W_HEIGHT 900
# define W_WIDTH 900
# define MAX_ITER 200

typedef struct s_fractol_keys
{
	double	u_d;
	double	l_r;
	double	zoom;
	int		x_pos;
	int		y_pos;
}	t_keys;

typedef struct s_fractol_maths
{
	int		x;
	int		y;
	double	c_im;
	double	c_re;
	double	k_re;
	double	k_im;
}	t_maths;

typedef struct s_fractol_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	double	min_re;
	double	max_re;
	double	min_im;
	double	max_im;
}	t_img;

typedef struct s_fractol_flag
{
	int	mandel;
	int	julia;
	int	def_colour;
}	t_fractype;

typedef struct s_fractol_ptr
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_fractype	frac;
	t_img		img;
	t_maths		maths;
	t_keys		keys;
}	t_ptr;

/*
**	keys.c
*/

void	keys_init(t_ptr *win);
int		key_check(int key, t_ptr *win);
int		mouse_zoom(int key, int x, int y, t_ptr *win);
void	key_moves(int key, t_ptr *win);
void	key_colours(t_ptr *win, int key);

/*
**	utils.c
*/

int		ft_strcmp(char *s1, char *s2);
void	my_mlx_pixel_put(t_ptr *win, int x, int y, int color);
int		image_init(t_ptr *win);
double	ft_atof(char *str);
int		close_window(t_ptr *win);

/*
**	mandel_maths.c
*/

void	mandelbrot(t_ptr *win);

/*
**	julia_maths.c
*/

void	julia(t_ptr *win);

/*
**	colours.c
*/

int		def_colour_picker(int i);
int		blackout(t_ptr *win);
int		colour_switch(int i, int c);

#endif
