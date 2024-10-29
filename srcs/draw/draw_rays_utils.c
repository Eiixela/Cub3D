/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:39:12 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/29 16:44:10 by aljulien         ###   ########.fr       */
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

void	draw_texture(t_data *data, int n_ray, int draw_start, int draw_end, double wall_height)
{
	(void)draw_end;
	int	tex_x;
	int	tex_y;
	int	screen_index;
	int	tex_index;
	int	wall_top;

	wall_top = draw_start;
	//tex_x = (n_ray % 1) * data->tex->width;
	tex_x = (n_ray % data->tex->width);
	while (draw_start++ <= draw_end)
	{
		tex_y = (draw_start - wall_top) * (data->tex->height / wall_height);
		if (n_ray >= 0 && n_ray < WIDTH && draw_start >= 0 && draw_start < HEIGHT && tex_x >= 0 && tex_x < data->tex->width && tex_y >= 0 && tex_y < data->tex->height) 
		{
			screen_index = draw_start * data->img.line_len + n_ray * (data->img.bit_per_pixel / 8);
			tex_index = tex_y * data->tex->line_len + tex_x * (data->tex->bit_per_pixel / 8);
			// if (data->tex->side == 0)
			// 	texture_init(data);
			// else
			// 	texture_init(data);
			(*(unsigned int *)(data->img.addr + screen_index)) = (*(unsigned int *)(data->tex->addr + tex_index));
		}
	}
}

// void	draw_texture(t_data *data, int x, int y)
// {
// 	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 		((int *)data->img.addr)[y * WIDTH + x] = *((unsigned int *)data->tex->addr + (y * data->tex->line_len + x * (data->tex->bit_per_pixel / 8)));
// }

void	draw_point(t_data *data, int x, int y, int draw_end,int color)
{
	while (y++ <= draw_end)
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			((int *)data->img.addr)[y * WIDTH + x] = color;
}

double	calculate_distance(double x, double y, double x1, double y1)
{
	return (sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)));
}
