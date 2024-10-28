/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:39:12 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/28 14:43:16 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	is_out_of_bounds(t_map *map, int map_x, int map_y)
{
	return (map_x < 0 || map_x >= map->size->y || map_y < 0
		|| map_y >= map->size->x);
}

void	draw_texture(t_data *data, int x, int y, int draw_end)
{
	(void)draw_end;
	int	tex_x;
	int	tex_y;
	int	screen_index;
	int	tex_index;

	tex_x = x % data->tex->width;
	tex_y = y % data->tex->width;
	// && tex_x >= 0 && tex_x < data->tex->width && tex_y >= 0 && tex_y < data->tex->height)
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) 
	{
		screen_index = y * data->img.line_len + x * (data->img.bit_per_pixel / 8);
		tex_index = tex_y * data->tex->line_len + tex_x * (data->tex->bit_per_pixel / 8);
		// if (data->tex->side == 0)
		// 	texture_init(data);
		// else
		// 	texture_init(data);
		*(unsigned int *)(data->img.addr + screen_index) = *(unsigned int *)(data->tex->addr + tex_index);
	}
}


// void	draw_texture(t_data *data, int x, int y)
// {
// 	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 		((int *)data->img.addr)[y * WIDTH + x] = *((unsigned int *)data->tex->addr + (y * data->tex->line_len + x * (data->tex->bit_per_pixel / 8)));
// }

void	draw_point(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		((int *)data->img.addr)[y * WIDTH + x] = color;
}

double	calculate_distance(double x, double y, double x1, double y1)
{
	return (sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)));
}
