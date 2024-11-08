/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:15:46 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/08 10:55:57 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_border(t_map *map, int x, int y)
{
	return (x == 0 || y == 0 || y == map->size->y - 1
		|| map->map[y][x + 1] == -32 || map->map[y][x - 1] == -32
		|| map->map[y + 1][x] == -32 || map->map[y - 1][x] == -32);
}

static void	add_to_queue(t_queue *queue, t_vector2D current)
{
	queue->point[queue->writing_index] = current;
	queue->writing_index++;
}

static void	should_add_to_queue(char **map, t_queue *queue, t_vector2D current)
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

static bool	resize_of_queue(t_queue *queue)
{
	t_vector2D	*resize;

	resize = queue->point;
	queue->point = ft_calloc(queue->size_queue * 2, sizeof(t_vector2D));
	if (!queue->point)
		return (1);
	ft_memmove(queue->point, resize, queue->writing_index);
	free(resize);
	queue->size_queue *= 2;
	return (0);
}

//TODO OPTI envoyer le **map, changer les cast 
//(redeclarer struct vector en int),
int	iter_flood_fill(t_map *map)
{
	t_queue		queue;
	t_vector2D	current;

	queue.size_queue = 4;
	queue.point = malloc(sizeof(t_vector2D) * (queue.size_queue + 1));
	if (!queue.point)
		return (1);
	queue.reading_index = 0;
	queue.writing_index = 0;
	add_to_queue(&queue, (t_vector2D){map->play_pos->x, map->play_pos->y});
	while (queue.reading_index < queue.writing_index)
	{
		current = queue.point[queue.reading_index++];
		if (is_border(map, current.x, current.y))
			if (map->map[(int)current.y][(int)current.x] == '0')
				return (free(queue.point), 1);
		if (map->map[(int)(current.y)][(int)(current.x)] != '0')
			continue ;
		map->map[(int)(current.y)][(int)(current.x)] = 'F';
		if ((queue.writing_index + 4) >= queue.size_queue)
			if (resize_of_queue(&queue))
				return (free(queue.point), 1);
		should_add_to_queue(map->map, &queue, current);
	}
	return (free(queue.point), 0);
}
