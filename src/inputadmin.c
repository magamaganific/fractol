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
	if (ft_strncmp("rainbow", input, ft_strlen(input)) != RIGHT
		&& ft_strncmp("pastel", input, ft_strlen(input)) != RIGHT
		&& ft_strncmp("neon", input, ft_strlen(input)) != RIGHT
		&& ft_strncmp("bichromatic", input, ft_strlen(input)) != RIGHT)
		return (WRONG);
	return (RIGHT);
}

int	ft_check_input(int ac, char **av)
{
	if (ft_strncmp("Mandelbrot", av[1], ft_strlen(av[1])) == RIGHT && ac > 2)
		return (WRONG);
	else if(ft_strncmp("Julia", av[1], ft_strlen(av[1])) == RIGHT)
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
	imag = ft_atol(imag);
}


void	ft_input_admin(int ac, char **av, t_fractal *f)
{
	if (ft_strncmp("Julia", av[1], ft_strlen(av[1])) == RIGHT)
	{
		f->set_type = 1;
		if (ac >= 4)
		{
			ft_jul_param(av[2], av[3], f);
			if (ac == 5)
				ft_style(av[4], f);
		}
		else
		{
			f->c_re = -0.9;
			f->c_im = 0.156;
		}
	}
	else
	{
		f->set_type = 0;
		if (ac == 3)
			ft_style(av[2], f);
	}
	
}

int main(int ac, char **av)
{
	t_fractal 	f;
 	
	if (ac == 1 || ft_check_input(ac, av) == WRONG)
	{
		ft_print_av_param();
		return (0);
	}
	ft_window_prep(&f);
	ft_input_admin(ac, av, &f);
	draw_set(&f);
	ft_controls(&f);
	mlx_loop(f.mlx);
	return (0);
}
