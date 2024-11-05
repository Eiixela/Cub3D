/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/05 13:57:16 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	player_where(t_map *map, int *player_y, int *player_x)
{
	int	x;
	int	y;
	int	count_player;

	count_player = 0;
	x = 0;
	while (x < map->size->x)
	{
		y = 0;
		while (map->map[x][y])
		{
			if (!find_player(map->map[x][y]))
			{
				map->player_way = map->map[x][y];
				map->map[x][y] = '0';
				*player_y = y;
				*player_x = x;
				count_player++;
			}
			y++;
		}
		x++;
	}
	return (count_player);
}
 
static int is_border(t_map *map, int x, int y)
{
	return (x == 0 || y == 0 || y == map->size->y - 1 || map->map[y][x + 1] == '\0');
}

static void	add_to_queue(t_queue *queue, t_vector2D current)
{
	queue->point[queue->writing_index] = current;
	queue->writing_index++;
}

static void should_add_to_queue(char **map, t_queue *queue, t_vector2D current)
{
    if (map[(int)(current.y)][(int)(current.x + 1)] == '0')
        add_to_queue(queue, (t_vector2D){current.x + 1, current.y});
    if (map[(int)(current.y)][(int)(current.x - 1)] == '0')
        add_to_queue(queue, (t_vector2D){current.x - 1, current.y});
    if (map[(int)(current.y + 1)][(int)(current.x)] == '0')
        add_to_queue(queue, (t_vector2D){current.x, current.y + 1});
    if (map[(int)(current.y - 1)][(int)(current.x)] == '0')
        add_to_queue(queue, (t_vector2D){current.x, current.y - 1});
}

static bool resize_of_queue(t_queue *queue)
{
	t_vector2D	*resize;

	resize = queue->point;
	queue->point = malloc((queue->size_queue * 2) * sizeof(t_vector2D));
	if (!queue->point)
		return (1);
	ft_memmove(queue->point, resize, queue->writing_index);
	free(resize);
	queue->size_queue *= 2;
	return (0);
}

//TODO work in progress
static	int	iter_flood_fill(t_map *map)
{
	t_queue queue;
	t_vector2D current;
	
	queue.size_queue = 4;
	queue.point = malloc(sizeof(t_vector2D) * (queue.size_queue + 1));
	if (!queue.point)
		return (1);
	queue.reading_index = 0;
	queue.writing_index = 0;
	add_to_queue(&queue, (t_vector2D){map->player_position->x, map->player_position->y});
	while (queue.reading_index < queue.writing_index)
	{
		current = queue.point[queue.reading_index++];
		if (is_border(map, current.x, current.y))
			if (map->map[(int)(current.y)][(int)(current.x)] == '0')
				return (free(queue.point), 1);	
		if (map->map[(int)(current.y)][(int)(current.x)] != '0')
			continue ;
		map->map[(int)(current.y)][(int)(current.x)] = 'F';
		if ((queue.writing_index + 4) >= queue.size_queue)
			if(resize_of_queue(&queue))
				return (free(queue.point), 1);
		should_add_to_queue(map->map, &queue, current);
	}
	return (free(queue.point), 0);
}

static void	set_angle_view(t_map *map)
{
	if (map->player_way == 'N')
		map->player_position->angle = 3 * PI / 2;
	if (map->player_way == 'S')
		map->player_position->angle = PI / 2;
	if (map->player_way == 'E')
		map->player_position->angle = 0;
	if (map->player_way == 'W')
		map->player_position->angle = PI;
}

int	map_good(t_map *map, t_player *player)
{
	int	player_x;
	int	player_y;

	player_x = 0;
	player_y = 0;
 	if (check_char_map(&map))
		return (1);
	if (player_where(map, &player_x, &player_y) != 1)
		return (1);
	player->x = player_x;
	player->y = player_y;
	map->player_position->x = player_x;
	map->player_position->y = player_y;
	if (iter_flood_fill(map))
		return (1);
	set_angle_view(map);
	map->map[player_y][player_x] = '0';
	return (0);
}
