/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:07:23 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/18 02:07:18 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* int	draw_2d_map(t_map *map, t_data *data)
{
	char	*pixels;
	int		draw_x;
	int		draw_y;
	int		x;
	int		y;
	int		width;
	int		height;

	width = map->size->x;
	height = map->size->y;
	pixels = data->img.addr;
	pixels += (data->width * 2048) + (data->width * 2); // offset to show in center of screen
	y = 0.;
	while (y < height)
	{
		draw_y = 3 * y * 2500;
		x = 0.;
		while (x < width)
		{
			draw_x = 3 * x;
			if (map->map[x][y] == '1')
			{
				((int *)pixels)[draw_x + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 1 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500  + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500 + 1 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500 + 2 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500 * 2 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500 * 2 + 1 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500  * 2 + 2 + draw_y] = (0xfff5ff);
			}
			else if (!find_player(map->map[x][y]))
			{
				((int *)pixels)[draw_x + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 1 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500  + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500 + 1 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500 + 2 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500 * 2 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500 * 2 + 1 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500  * 2 + 2 + draw_y] = (0xf02d00);
			}
			else if (map->map[x][y] == 'F')
			{
				((int *)pixels)[draw_x + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 1 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500  + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500 + 1 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500 + 2 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500 * 2 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500 * 2 + 1 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500  * 2 + 2 + draw_y] = (0x003eff);
			}
			x += 1;
		}
		y += 1;
	}
	return (0);
} */

int	draw(t_map *map, t_data *data)
{
	draw_2d_map(map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	// free(data->map);
	return (0);
}

int	player_position(int new_x, int new_y, t_map *map)
{
	if (new_x == map->player_position->x && new_y == map->player_position->y)
		return (0);
	return (1);
}

int	draw_2d_map(t_map *map, t_data *data)
{
	char	*pixels;
	int		draw_x;
	int		draw_y;
	int		x;
	int		y;
	int		new_y;
	int		new_x;
	int		width;
	int		height;

	width = map->size->y;
	height = map->size->x;
	pixels = data->img.addr;
	pixels += (data->width * 1224) + (data->width); // offset to show in center of screen
	y = 0.;
	while (y < HEIGHT)
	{
		new_y = y / 40;
		draw_y = y * WIDTH;
		x = 0.;
		while (x < WIDTH)
		{
			draw_x = x;
			new_x = x / 40;
			if (new_x < width && new_y < height)
			{
				if (map->map[new_y][new_x] == '1')
					((int *)pixels)[draw_x + draw_y] = (PINK);
				else if (!find_player(map->map[new_y][new_x]))
					((int *)pixels)[draw_x + draw_y] = (PASTEL_PURPLE);
				else if (map->map[new_y][new_x] == 'F' || map->map[new_y][new_x] == '0')
					((int *)pixels)[draw_x + draw_y] = (LIME_GREEN);
				// else if (player_position(y, x, map) == 0)
			}
			x += 1;
		}
		y += 1;
	}
	return (0);
}
int	draw_new_2d(t_map *map, t_data *data)
{
	char	*pixels;
	int		draw_x;
	int		draw_y;
	int		x;
	int		y;
	int		new_y;
	int		new_x;
	int		width;
	int		height;

	width = map->size->y;
	height = map->size->x;
	pixels = data->img.addr;
	pixels += (data->width * 1224) + (data->width); // offset to show in center of screen
	y = 0.;
	while (y < HEIGHT)
	{
		new_y = y / 40;
		draw_y = y * WIDTH;
		x = 0.;
		while (x < WIDTH)
		{
			draw_x = x;
			new_x = x / 40;
			if (new_x < width && new_y < height)
			{
				if (map->map[new_y][new_x] == '1')
					((int *)pixels)[draw_x + draw_y] = (PINK);
				else if (player_position(new_x, new_y, map) == 0)
					((int *)pixels)[draw_x + draw_y] = (PASTEL_PURPLE);
				else if (map->map[new_y][new_x] == 'F' || map->map[new_y][new_x] == '0' || !find_player(map->map[new_y][new_x]))
					((int *)pixels)[draw_x + draw_y] = (LIME_GREEN);
				// else if (map->map[new_y][new_x] != -32)
				// 	((int *)pixels)[draw_x + draw_y] = (LIME_GREEN);
			}
			x += 1;
		}
		y += 1;
	}
	return (0);
}
