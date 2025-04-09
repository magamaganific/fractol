/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputadmin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:42:46 by mfornovi          #+#    #+#             */
/*   Updated: 2025/04/08 11:42:49 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

#define WRONG 1
#define RIGHT 0

void	ft_print_av_param(void)
{
	ft_printf(" \n\n    --------------_EXPECTED_INPUT_--------------\n");
	ft_printf("·                                                    ·\n");
	ft_printf("·                                                    ·\n");
	ft_printf("·                                                    ·\n");
	ft_printf("· > ./fractol [SET] ([SET_PARAMS][STYLE] optional)   ·\n");
	ft_printf("·   |                                                ·\n");
	ft_printf("·   |> Sets: [mandelbrot]                            ·\n");
	ft_printf("·   |  |                                             ·\n");
	ft_printf("·   |  |---- [julia]                                 ·\n");
	ft_printf("·   |        |> params:> [INT_REAL] [INT_IMAGINARY]  ·\n");
	ft_printf("·   |        |> default:>  (-0.9)        (0.156)     ·\n");
	ft_printf("·   |                       [-9]          [156]      ·\n");
	ft_printf("·   |                                                ·\n");
	ft_printf("·   |> Styles: rainbow/pastel/neon                   ·\n");
	ft_printf("·       |> default: bichromatic                      ·\n");
	ft_printf("·                                                    ·\n");
	ft_printf("·                                                    ·\n");
	ft_printf("·                                                    ·\n");
	ft_printf("·                                                    ·\n");
	ft_printf("·                                                    ·\n");
	ft_printf("    --------------_EXPECTED_INPUT_--------------\n");
}

void mlx_pixel_put_color(void *mlx, void *win, int x, int y, int color)
{
	mlx_pixel_put(mlx, win, x, y, color);
}

int	ft_str_is_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-' || arg[i] == '+')
			i++;
		if (ft_isdigit(arg[i]) == 0)
			return (WRONG);
		i++;
	}
	return (RIGHT);
}

int ft_input_params(char *real, char *imag)
{
	if (ft_str_is_num(real) == WRONG || ft_str_is_num(imag) == WRONG)
		return (WRONG);
	return (RIGHT);
}

int	ft_input_style(char *input)
{
	if (ft_strncmp("rainbow", input, ft_strlen("rainbow") - 1) != RIGHT
		&& ft_strncmp("pastel", input, ft_strlen("pastel") - 1) != RIGHT
		&& ft_strncmp("neon", input, ft_strlen("neon") - 1) != RIGHT
		&& ft_strncmp("bichromatic", input, ft_strlen("bichromatic") - 1) != RIGHT)
		return (WRONG);
	return (RIGHT);
}

int	ft_check_input(int ac, char **av)
{
	if (ft_strncmp("mandelbrot", av[1], ft_strlen("mandelbrot")) == RIGHT)
	{
		if ((ac == 3 && ft_input_style(av[2]) == WRONG) || ac > 3)
			return (WRONG);
	}
	else if(ft_strncmp("julia", av[1], ft_strlen("julia")) == RIGHT)
	{
		if (ac > 2)
		{
			if (ac == 3 && ft_input_style(av[2]) == WRONG)
				return (WRONG);
			if (ac == 4 && ft_input_params(av[2], av[3]) == WRONG)
				return (WRONG);
			if (ac == 5 && (ft_input_params(av[2], av[3]) == WRONG
				|| ft_input_style(av[4]) == WRONG))
				return (WRONG);
		}
	}
	return(RIGHT);
}

void	ft_window_prep(t_fractal *f)
{
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol");
	f->zoom = 1.0;
	f->offset_x = 0.0;
	f->offset_y = 0.0;
}

void	ft_jul_param(char *real, char *imag, t_fractal *f)
{
	double	re;
	double	im;

	re = ft_atol(real);
	im = ft_atol(imag);
	while (re >= 1.0 || im >= 1.0 || re <= -1.0 || im <= -1.0)
	{
		if (re >= 1)
			re = re / 10;
		if (im >= 1)
			im = im / 10;
	}
	f->c_re =  re;
	f->c_im = im;
}

void	ft_style(char *input, t_fractal *f)
{
	if (ft_strncmp("rainbow", input, ft_strlen(input)) == RIGHT)
		f->set_style = RAINBOW;
	else if (ft_strncmp("pastel", input, ft_strlen(input)) == RIGHT)
		f->set_style = PASTEL;
	else if (ft_strncmp("neon", input, ft_strlen(input)) == RIGHT)
		f->set_style = NEON;
	else if (ft_strncmp("bichromatic", input, ft_strlen(input)) == RIGHT)
		f->set_style = BICHRO;
}


void	ft_input_admin(int ac, char **av, t_fractal *f)
{
	if (ft_strncmp("Julia", av[1], ft_strlen(av[1])) == RIGHT)
	{
		f->set_type = JULIA;
		if (ac >= 4)
		{
			if (ft_input_params(av[2], av[3]) == RIGHT)
				ft_jul_param(av[2], av[3], f);
			if (ac == 5)
				ft_style(av[4], f);
		}
		else
		{
			f->c_re = -0.9;
			f->c_im = 0.156;
			f->set_style = BICHRO;
		}
	}
	else
	{
		f->set_type = MANDEL;
		f->set_style = BICHRO;
		if (ac == 3)
			ft_style(av[2], f);
	}
	
}

int	mandelbrot(int x, int y, t_fractal *f)
{
	double	real;
	double	imag;
	double	temp;
	int		iter;
	
	iter = -1;
	real = ((x - WIDTH / 2.0) * 4.0 / WIDTH) / f->zoom + f->offset_x;
	imag = ((y - HEIGHT / 2.0) * 4.0 / HEIGHT) / f->zoom + f->offset_y;
	f->c_re = real;
	f->c_im = imag;
	while (iter++ < MAX_ITER && (real * real + imag * imag) < 4)
	{
		temp = real * real - imag * imag + f->c_re;
		imag = 2 * real * imag + f->c_im;
		real = temp;
	}
	return (iter);
}

int	julia(int x, int y, t_fractal *f)
{
	double	real;
	double	imag;
	double	temp;
	int		iter;

	iter = -1;
	real = ((x - WIDTH / 2.0) * 4.0 / WIDTH) / f->zoom + f->offset_x;
	imag = ((y - HEIGHT / 2.0) * 4.0 / HEIGHT) / f->zoom + f->offset_y;
	while (iter++ < MAX_ITER && (real * real + imag * imag) < 4)
	{
		temp = real * real - imag * imag + f->c_re;
		imag = 2 * real * imag + f->c_im;
		real = temp;
	}
	return (iter);
}

int	get_rainbow_color(int iter, t_fractal *f)
{
	int	red;
	int	green;
	int	blue;
	int color_index;

	color_index = (iter * 15) % 256;

	red = (color_index) % 256;
	green = (color_index * 2) % 256;
	blue = (color_index * 3) % 256;

	red = (red + (int)(f->c_im * 50)) % 256;
	green = (green + (int)(f->c_re * 50)) % 256;
	
	return (red << 16) | (green << 8) | blue;
}

int	get_pastel_color(int iter, t_fractal *f)
{
	int	red;
	int	green;
	int	blue;

	red = (iter * 30) % 128 + 128;
	green = (iter * 15) % 128 + 128;
	blue = (iter * 5) % 128 + 128;

	red = (red + (int)(f->c_re * 20)) % 256;
	green = (green + (int)(f->c_im * 20)) % 256;

	return (red << 16) | (green << 8) | blue;
}

int get_neon_color(int iter)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(255 * sin(0.1 * iter));
	green = (int)(255 * sin(0.05 * iter));
	blue = (int)(255 * cos(0.1 * iter));

	red = red > 128 ? 255 : red * 2;
	green = green > 128 ? 255 : green * 2;
	blue = blue > 128 ? 255 : blue * 2;

	return (red << 16) | (green << 8) | blue;
}

int	get_bichro_color(int iter,t_fractal *f)
{
	int	red;
	int	green;
	int	blue;
	if (iter < MAX_ITER)
	{
		red = (iter * 9) % 256;
		green = (iter * 6) % 256;
		blue = (iter * 3) % 256;
	}
	else
	{
		red = 0;
		green = 0;
		blue = 0;
	}
	red = (red + (int)(f->c_im * 100)) % 256;
	green = (green + (int)(f->c_re * 100)) % 256;
	return (red << 16) | (green << 8) | blue;
}

int	get_color(int iter, t_fractal *f)
{
	if (f->set_style == RAINBOW)
		return (get_rainbow_color(iter, f));
	else if (f->set_style == PASTEL)
		return (get_pastel_color(iter, f));
	else if (f->set_style == NEON)
		return (get_neon_color(iter));
	else if (f->set_style == BICHRO)
		return (get_bichro_color(iter, f));
	return (get_bichro_color(iter, f));
}

void	draw_set(t_fractal *f)
{
	int	x;
	int	y;
	int	iter;
	int	color;

	y = -1;
	while (y++ < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
		{
			if (f->set_type == MANDEL)
				iter = mandelbrot(x, y, f);
			else if (f->set_type == JULIA)
				iter = julia(x, y, f);

			if (iter == MAX_ITER)
				color = 0x000000;
			else
				color = get_color(iter, f);

			mlx_pixel_put_color(f->mlx, f->win, x, y, color);
		}
	}
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_fractal	*f;
	double		old_zoom;
	double		mouse_real;
	double 		mouse_imag;

	f = (t_fractal *)param;
	old_zoom = f->zoom;
	if (button == 4)
		f->zoom *= 1.2;
	else if (button == 5)
		f->zoom /= 1.2;
	else
		return (0);
	mouse_real = ((x - WIDTH / 2.0) * 4.0 / WIDTH) / old_zoom + f->offset_x;
	mouse_imag = ((y - HEIGHT / 2.0) * 4.0 / HEIGHT) / old_zoom + f->offset_y;
	draw_set(f);
	return(0);
}

int close_window(void *param)
{
	t_fractal *f = (t_fractal *)param;
	mlx_destroy_window(f->mlx, f->win);
	exit(0);
}

int key_hook(int keycode, void *param)
{
	if (keycode == 65307)
		close_window(param);
	return (0);
}

void	ft_controls(t_fractal *f)
{
	mlx_mouse_hook(f->win, mouse_hook, f);
	mlx_key_hook(f->win, key_hook, f);
	mlx_hook(f->win, 17, 0, close_window, f);
}

int main(int ac, char **av)
{
	t_fractal 	f;
 	
	if (ac == 1 || ft_check_input(ac, av) == WRONG)
	{
		ft_print_av_param();
		return (0);
	}
	ft_input_admin(ac, av, &f);
	ft_window_prep(&f);
	draw_set(&f);
	ft_controls(&f);
	mlx_loop(f.mlx);
	return (0);
}
