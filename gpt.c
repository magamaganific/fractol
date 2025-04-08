#include "../fractol.h"
#include <math.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 80

// Dibuja un píxel de color
void mlx_pixel_put_color(void *mlx, void *win, int x, int y, int color)
{
	mlx_pixel_put(mlx, win, x, y, color);
}

// Cálculo del conjunto de Mandelbrot
int mandelbrot(int x, int y, t_fractal *f)
{
	double real = ((x - WIDTH / 2.0) * 4.0 / WIDTH) / f->zoom + f->offset_x;
	double imag = ((y - HEIGHT / 2.0) * 4.0 / HEIGHT) / f->zoom + f->offset_y;
	double c_real = real;
	double c_imag = imag;
	int iter;

	for (iter = 0; iter < MAX_ITER; iter++)
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

// Dibuja el fractal en la ventana
void draw_fractal(t_fractal *f)
{
	int x, y, iter, color;

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			iter = mandelbrot(x, y, f);
			if (iter == MAX_ITER)
				color = 0x000000;
			else
				color = (iter * 255 / MAX_ITER) << 17;
			mlx_pixel_put_color(f->mlx, f->win, x, y, color);
		}
	}
}

// Cierra la ventana
int close_window(void *param)
{
	t_fractal *f = (t_fractal *)param;
	mlx_destroy_window(f->mlx, f->win);
	exit(0);
}

// Evento de zoom con el ratón
int mouse_hook(int button, int x, int y, void *param)
{
	t_fractal *f = (t_fractal *)param;

	double old_zoom = f->zoom;

	if (button == 4) // Scroll up
		f->zoom *= 1.2;
	else if (button == 5) // Scroll down
		f->zoom /= 1.2;
	else
		return (0);

	// Ajustar offset para que el zoom siga al cursor
	double mouse_real = ((x - WIDTH / 2.0) * 4.0 / WIDTH) / old_zoom + f->offset_x;
	double mouse_imag = ((y - HEIGHT / 2.0) * 4.0 / HEIGHT) / old_zoom + f->offset_y;

	f->offset_x = mouse_real - ((x - WIDTH / 2.0) * 4.0 / WIDTH) / f->zoom;
	f->offset_y = mouse_imag - ((y - HEIGHT / 2.0) * 4.0 / HEIGHT) / f->zoom;

	draw_fractal(f);
	return (0);
}

int main()
{
	t_fractal f;

	f.mlx = mlx_init();
	f.win = mlx_new_window(f.mlx, WIDTH, HEIGHT, "Mandelbrot Fractal");
	f.zoom = 1.0;
	f.offset_x = 0.0;
	f.offset_y = 0.0;

	draw_fractal(&f);

	mlx_mouse_hook(f.win, mouse_hook, &f);
	mlx_hook(f.win, 17, 0, close_window, &f);
	mlx_loop(f.mlx);
	return (0);
}
