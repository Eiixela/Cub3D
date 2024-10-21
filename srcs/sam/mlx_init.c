/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:15 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/21 17:09:41 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	handle_win_exit(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int check_collision(t_map *map, double x, double y)
{
    int map_x = (int)(x / SQUARE_SIZE);
    int map_y = (int)(y / SQUARE_SIZE);

    if (map->map[map_y][map_x] == '1')
        return (1);
    return (0);
}


int	key_loop(t_data *data)
{
	int	moved;
    double new_x = data->map->player_position->x;
    double new_y = data->map->player_position->y;

	moved = 0;
	if (data->keys->left == 1)
	{
  		data->map->player_position->angle -= 0.1;
		if (data->map->player_position->angle < 0)
        	data->map->player_position->angle += 2 * PI;
    	data->map->player_position->dx = cos(data->map->player_position->angle) * 5;
    	data->map->player_position->dy = sin(data->map->player_position->angle) * 5;
	}
	if (data->keys->right == 1)
	{
    	data->map->player_position->angle += 0.1;
    	if (data->map->player_position->angle > 2 * PI)
        	data->map->player_position->angle -= 2 * PI;
    	data->map->player_position->dx = cos(data->map->player_position->angle) * 5;
    	data->map->player_position->dy = sin(data->map->player_position->angle) * 5;
	}
	if (data->keys->w == 1)
	{
		if (data->map->map[(int)(data->map->player_position->y - 0.19)]
			[(int)data->map->player_position->x] == '1')
		{
			printf("WALL: NORTH\nFACING: SOUTH\n\n");
			return (0);
		}
		data->map->player_position->y -= 0.064;
	}
	if (data->keys->s == 1)
	{
		if (data->map->map[(int)(data->map->player_position->y + 0.19)]
			[(int)data->map->player_position->x] == '1')
		{
			printf("WALL: SOUTH\nFACING: NORTH\n\n");
			return (0);
		}
		data->map->player_position->y += 0.064;
	}
	if (data->keys->a == 1)
	{
		if (data->map->map[(int)data->map->player_position->y]
			[(int)(data->map->player_position->x - 0.19)] == '1')
		{
			printf("WALL: WEST\nFACING: EAST\n\n");
			return (0);
		}
		data->map->player_position->x -= 0.064;
	}
	if (data->keys->d == 1)
	{
		if (data->map->map[(int)data->map->player_position->y]
			[(int)(data->map->player_position->x + 0.19)] == '1')
		{
			printf("WALL: EAST\nFACING: WEST\n\n");
			return (0);
		}
		data->map->player_position->x += 0.064;
	}
	new_x = data->map->player_position->x;
    new_y = data->map->player_position->y;
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
	data->img_fov.ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img_fov.addr = mlx_get_data_addr(data->img_fov.ptr, &data->img_fov.bit_per_pixel, \
		&data->img_fov.line_len, &data->img_fov.endian);
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
