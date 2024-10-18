/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:15 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/18 02:13:26 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	handle_win_exit(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	key_loop(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->keys->w == 1)
	{
		data->map->player_position->y -= 1;
	}
	if (data->keys->s == 1)
	{
		data->map->player_position->y += 1;
	}
	if (data->keys->a == 1)
	{
		data->map->player_position->x -= 1;
	}
	if (data->keys->d == 1)
	{
		data->map->player_position->x += 1;
	}
	draw_new_image(data);
	return (0);
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
	data->keys->w = 0;
	data->keys->s = 0;
	data->keys->a = 0;
	data->keys->d = 0;
	data->keys->right = 0;
	data->keys->left = 0;
	mlx_hook(data->win_ptr, EXIT_CROSS, 0, &handle_win_exit, data);
	mlx_hook(data->win_ptr, 2, 1L<<0, &key_press, data);  // 2 is key press code
	mlx_hook(data->win_ptr, 3, 1L<<1, &key_release, data);  // 3 is key release
	mlx_loop_hook(data->mlx_ptr, &key_loop, data);
}
