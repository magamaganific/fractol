/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:14:24 by mfornovi          #+#    #+#             */
/*   Updated: 2024/12/11 14:14:26 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 30

void mlx_pixel_put_color(void *mlx, void *win, int x, int y, int color)
{
	mlx_pixel_put(mlx, win, x, y, color);
}

int mandelbrot(int x, int y, int max_iter)
{
	double real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
	double imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
	double c_real = real;
	double c_imag = imag;
	int iter;

	for (iter = 0; iter < max_iter; iter++)
	{
		double real2 = real * real - imag * imag + c_real;
		double imag2 = 2 * real * imag + c_imag;
		real = real2;
		imag = imag2;
		if (real * real + imag * imag > 4)
			break ;
	}
	return (iter);
}

int close_window(void *param)
{
	mlx_destroy_window(param, param);
	exit(0);
}

int main()
{
	void *mlx;
	void *win;
	int x, y;
	int iter, color;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "Mandelbrot Fractal");

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			iter = mandelbrot(x, y, MAX_ITER);
			if (iter == MAX_ITER)
				color = 0x000000;
			else
				color = (iter * 255 / MAX_ITER) << 17;
			mlx_pixel_put_color(mlx, win, x, y, color);
		}
	}
	mlx_hook(win, 17, 0, close_window, mlx);
	mlx_loop(mlx);
	return (0);
}
