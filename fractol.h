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

typedef struct s_fractal
{
	void	*mlx;
	void	*win;
	void	*imag;
	void	*point_image;
	int		bits_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	double	offset_x;
	double	offset_y;
	double	zx;
	double	zy;
	double	zoom;
	char	*name;
	int		max_iterations;
}			t_fractal;

#endif