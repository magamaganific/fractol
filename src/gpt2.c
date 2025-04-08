#include "../fractol.h"
#include <math.h>
#include <stdlib.h>

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

// Cálculo del conjunto de Julia
int julia(int x, int y, t_fractal *f)
{
	double real = ((x - WIDTH / 2.0) * 4.0 / WIDTH) / f->zoom + f->offset_x;
	double imag = ((y - HEIGHT / 2.0) * 4.0 / HEIGHT) / f->zoom + f->offset_y;
	int iter;

	for (iter = 0; iter < MAX_ITER; iter++)
	{
		double real2 = real * real - imag * imag + f->c_re;
		double imag2 = 2 * real * imag + f->c_im;
		real = real2;
		imag = imag2;
		if (real * real + imag * imag > 4)
			break ;
	}
	return (iter);
}

int get_neon_color(int iter)
{
    int red, green, blue;

    // Colores neón: muy saturados y brillantes
    if (iter == MAX_ITER)
    {
        red = 0;
        green = 0;
        blue = 0;
    }
    else
    {
        red = (int)(255 * sin(0.1 * iter));
        green = (int)(255 * sin(0.05 * iter));
        blue = (int)(255 * cos(0.1 * iter));

        // Hacerlo más "brillante" o neón
        red = red > 128 ? 255 : red * 2;
        green = green > 128 ? 255 : green * 2;
        blue = blue > 128 ? 255 : blue * 2;
    }

    return (red << 16) | (green << 8) | blue;
}

int get_pastel_color(int iter, t_fractal *f)
{
    int red, green, blue;

    // Usa un gradiente suave y con poca saturación
    red = (iter * 30) % 128 + 128;  // Colores suaves
    green = (iter * 15) % 128 + 128;
    blue = (iter * 5) % 128 + 128;

    // Le damos un pequeño toque con los valores de c
    red = (red + (int)(f->c_re * 20)) % 256;
    green = (green + (int)(f->c_im * 20)) % 256;

    // Combina los colores
    return (red << 16) | (green << 8) | blue;
}


int get_heatmap_color(int iter)
{
    int red, green, blue;

    if (iter == MAX_ITER)
    {
        red = 0;
        green = 0;
        blue = 0;  // Negro para los puntos dentro del conjunto
    }
    else
    {
        // Asignación de colores basada en el "calor"
        red = (iter * 10) % 256;
        green = (iter * 6) % 256;
        blue = 0;  // Sin azul, solo rojo y verde para "calor"

        // Los colores se vuelven más cálidos a medida que las iteraciones aumentan
        if (iter > MAX_ITER / 2)
        {
            red = 255;
            green = (int)(255 - ((iter - MAX_ITER / 2) * 255 / (MAX_ITER / 2)));
        }
    }

    // Combina los valores RGB en un solo valor
    return (red << 16) | (green << 8) | blue;
}

int get_spiral_color(int iter, t_fractal *f)
{
    int red, green, blue;

    // Use seno o coseno para crear un patrón de espiral
    red = (int)(128 + 127 * sin(0.1 * iter));
    green = (int)(128 + 127 * sin(0.1 * iter + 2));  // Desfase de fase
    blue = (int)(128 + 127 * sin(0.1 * iter + 4));   // Otro desfase

    // Modula con el valor de c para hacer la espiral más dinámica
    red = (red + (int)(f->c_re * 50)) % 256;
    green = (green + (int)(f->c_im * 50)) % 256;

    // Combina los componentes RGB
    return (red << 16) | (green << 8) | blue;
}

int get_rainbow_color(int iter, t_fractal *f)
{
    int red, green, blue;

    // Usamos un ciclo de colores basado en las iteraciones
    int color_index = (iter * 15) % 256;  // Escalar y ciclar entre 0-255

    // Crea un gradiente arco iris
    red = (color_index) % 256;
    green = (color_index * 2) % 256;
    blue = (color_index * 3) % 256;

    // La modulación con la constante c sigue siendo útil para variación
    red = (red + (int)(f->c_im * 50)) % 256;
    green = (green + (int)(f->c_re * 50)) % 256;

    // Combina los valores RGB en un solo color
    return (red << 16) | (green << 8) | blue;
}

// Genera un color basado en el número de iteraciones
int get_color(int iter, t_fractal *f)
{
	int red, green, blue;

	// Si no se ha llegado al máximo de iteraciones, genera colores
	if (iter < MAX_ITER)
	{
		red = (iter * 9) % 256;
		green = (iter * 6) % 256;
		blue = (iter * 3) % 256;
	}
	else
	{
		// Si el punto está dentro del conjunto, lo hacemos negro
		red = 0;
		green = 0;
		blue = 0;
	}

	// Se mezcla un poco con la parte imaginaria de c para cambiar la tonalidad
	red = (red + (int)(f->c_im * 100)) % 256;
	green = (green + (int)(f->c_re * 100)) % 256;

	// Combinamos los componentes RGB para obtener el color final
	return (red << 16) | (green << 8) | blue;
}

// Dibuja el fractal en la ventana
void draw_fractal(t_fractal *f)
{
	int x, y, iter, color;

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			if (f->set_type == 0)  // Mandelbrot
				iter = mandelbrot(x, y, f);
			else  // Julia
				iter = julia(x, y, f);

			if (iter == MAX_ITER)
				color = 0x000000;
			else
				color = get_neon_color(iter);

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

int key_hook(int keycode, void *param)
{
    if (keycode == 65307)  // 65307 es el código de la tecla ESC
    {
        close_window(param); // Cierra la ventana si se presiona ESC
    }
    return (0);
}

int main()
{
	t_fractal f;

	f.mlx = mlx_init();
	f.win = mlx_new_window(f.mlx, WIDTH, HEIGHT, "Fractal");
	f.zoom = 1.0;
	f.offset_x = 0.0;
	f.offset_y = 0.0;
	f.set_type = 1;  // 1 para Julia, 0 para Mandelbrot
	f.c_re = -0.9;   // Parte real de c (modifica según lo que quieras)
	f.c_im = 0.156;  // Parte imaginaria de c (modifica según lo que quieras)

	draw_fractal(&f);

	mlx_mouse_hook(f.win, mouse_hook, &f);
	mlx_key_hook(f.win, key_hook, &f);
	mlx_hook(f.win, 17, 0, close_window, &f);
	mlx_loop(f.mlx);
	return (0);
}
