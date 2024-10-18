/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:07:23 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/18 17:13:25 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	draw(t_map *map, t_data *data)
{
	(void)map;
mlx_loop(data->mlx_ptr);
mlx_destroy_image(data->mlx_ptr, data->img.ptr);
mlx_destroy_image(data->mlx_ptr, data->img_fov.ptr);
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

/* int	draw_2d_map(t_map *map, t_data *data)
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
	//pixels += (data->width * 1224) + (data->width); // offset to show in center of screen
	y = 0.;
	while (y < HEIGHT)
	{
		new_y = y / 30;
		draw_y = y * WIDTH;
		x = 0.;
		while (x < WIDTH)
		{
			draw_x = x;
			new_x = x / 30;
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
} */

void	draw_fov(t_data *data)
{
	char *pixels = data->img_fov.addr;
	int i = 0;
	while (i < 100)
		((int *)pixels)[i++] = ORANGE;
}

int	draw_new_2d(t_map *map, t_data *data)
{
	char	*pixels;
	int		draw_y;
	int		x;
	int		y;
	int		new_y;
	int		new_x;
	int		width;
	int		height;
/* 	t_ray	ray_fov;

	ray_fov.origin.x = map->player_position->x;
	ray_fov.origin.y = map->player_position->y;
	ray_fov.direction.x = map->player_position->x;
	ray_fov.direction.y = 0;*/
	width = map->size->y;
	height = map->size->x;
	pixels = data->img.addr;
	pixels += (data->width * 1224) + (data->width); // offset to show in center of screen
	y = 0.;
 //	int fov_y = map->player_position->y * WIDTH;
	
	while (y < HEIGHT)
	{
		new_y = y / 40;
		draw_y = y * WIDTH;
		x = 0.;
		while (x < WIDTH)
		{
			new_x = x / 40;
			if (new_x < width && new_y < height)
			{
			/* 	while (fov_y > 0)
				{
					((int *)pixels)[map->player_position->x + fov_y] = (ORANGE);
					fov_y--;
				} */
				if (map->map[new_y][new_x] == '1')
					((int *)pixels)[x + draw_y] = (PINK);
				else if (player_position(new_x, new_y, map) == 0)
					((int *)pixels)[x + draw_y] = (PASTEL_PURPLE);
				else if (map->map[new_y][new_x] == 'F' || \
					map->map[new_y][new_x] == '0' || \
					!find_player(map->map[new_y][new_x]))
					((int *)pixels)[x + draw_y] = (LIME_GREEN);
			}
			x += 1;
		}
		y += 1;
	}
	return (0);
}
