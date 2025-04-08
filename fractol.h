/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfornovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:15:03 by mfornovi          #+#    #+#             */
/*   Updated: 2024/12/11 14:15:06 by mfornovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "includes/libft/libft.h"
# include "includes/minilibx-linux/mlx.h"
# include <math.h>
# include <pthread.h>

# ifndef WIDTH
#  define WIDTH 800
# endif
# ifndef HEIGHT
#  define HEIGHT 600
# endif
# ifndef MAX_ITER
#  define MAX_ITER 2
# endif
# ifndef SET_TYPE
#  define SET_TYPE 0
# endif

typedef struct s_fractal
{
	void	*mlx;
	void	*win;
	double	zoom;
	double	offset_x;
	double	offset_y;
	int		set_type;  // 0 para Mandelbrot, 1 para Julia
	double	c_re;  // Parte real de c para Julia
	double	c_im;  // Parte imaginaria de c para Julia
}	t_fractal;

#endif