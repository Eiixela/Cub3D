/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:15 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/17 13:50:13 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	handle_win_exit(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	handle_keyboard(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (handle_win_exit(data));
	// else if (keysym == 'w' || a || s || d)
		// move about or someth;
	else
		return (0);
	/*This part of the code is not reachable a the moment because it makes the minimap disapear of the screen

	
	mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	data->img.ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr, \
		&data->img.bit_per_pixel, &data->img.line_len, &data->img.endian);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);*/
}
void	data_init(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
	data->width, data->height, "smol wolf 3d");
	data->img.ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bit_per_pixel, \
		&data->img.line_len, &data->img.endian);
	mlx_hook(data->win_ptr, EXIT_CROSS, 0, &handle_win_exit, data);
	// mlx_hook(data->win_ptr, MOUSE_WHEEL, 1L << 2, &handle_mouse, data);
	mlx_key_hook(data->win_ptr, &handle_keyboard, data);
}
