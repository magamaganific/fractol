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

ft_input_admin()
{
	av[1];
}

int main(int ac, char **av)
{
	t_fractal f;
	
	ft_input_admin();
	ft_window_prep();
	draw_set();
	ft_controls();
	mlx_loop(f.mlx);
	return (0);
}
