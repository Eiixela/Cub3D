/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:13:52 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/14 13:01:24 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <stdbool.h>
# include <math.h>
# include "mlx.h"
# include <X11/keysym.h>
# include "libft.h"

# define BUFFER_SIZE 1
# define EXIT_CROSS 17

typedef struct	s_point
{
	int x;
	int y;
} t_point;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_map
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		*ceiling_c;
	int		*floor_c;
	char	**map;
	char	player_way;
	t_point	*size;
	t_point	*player_position;
}	t_map;


typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		line_len;
	int		bit_per_pixel;
	int		endian;
}	t_img;

typedef struct s_data
{
	int		width;
	int		height;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

//PARSING
int		parsing(int ac, char **av, t_map **map);

//parsing_utils
int		map_started(char *line);
char	*format_line(char *line);

//init
t_map	*init_map(void);

//mlx
void	data_init(t_data *data);

//file_check
int		file_check(char *file, t_map **map);

//cardinal_check
int		cardinal_check(int fd, t_map **map);

//textures_check
int		check_access_textures(t_map *map);

//color_check
int		color_check(int fd, t_map **map);

//map_check
int		map_good(t_map **map);
bool	check_borders(char **map, int height);

//map_check_utils
int		find_player(char c);
int		check_char_map(t_map **map);
int		valid_char(char c);

//fill_map
int		map_fill(int fd, t_map **map, int number_line_map);
int		count_line(int fd);
int		read_till_the_end(int fd, char *line);

//free
void	free_map(t_map **map);

//GNL
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
