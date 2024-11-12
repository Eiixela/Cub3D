/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:13:52 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/12 12:54:33 by saperrie         ###   ########.fr       */
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
# define WIDTH 2800
# define HEIGHT 1400
# define PI	3.1415926535
# define VISIBLE_MAP_SIZE 200
# define PLAYER_SIZE 0.20
# define SQUARE_SIZE 15
# define MOVE_SPEED 0.2
# define ROTATION_ANGLE 0.06
# define FOV 1.0472 // 60 degree field of view
# define P2 1.5707963267 // PI/2
# define P3 4.7123889803 // 3*PI/2
# define NORTH 0
# define SOUTH 1
# define EAST  2
# define WEST  3

//--------------------------------------------------|

//Barbie color palette for 2d map
# define GRID_COLOR 0x808080
# define PASTEL_PURPLE 0xb1a3ff
# define DARK_PINK 0xFF36AF
# define LIGHT_PINK 0xFFC4F3

typedef struct s_vector2d
{
	double	x;
	double	y;
}	t_vector2D;

typedef struct s_map2d
{
	int	map_offset_x;
	int	map_offset_y;
	int	screen_x;
	int	screen_y;
}	t_map2d;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_pplane
{
	int		width;
	int		height;
	int		center_w;
	int		center_h;
	int		dst_from_player;
	double	angle_between_rays;
}	t_pplane;

typedef struct s_point
{
	double	x;
	double	y;
	double	angle;
	double	dx;
	double	dy;
}	t_point;

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
	t_point	*play_pos;
}	t_map;

typedef struct s_texture
{
	void	*ptr;
	char	*addr;
	int		width;
	int		height;
	int		line_len;
	int		bit_per_pixel;
	int		endian;
	int		side;
}	t_texture;

typedef struct s_draw_tex
{
	double		step;
	double		tex_pos_win;
	int			screen_index;
	int			tex_index;
	int			y;
}	t_draw_tex;

typedef struct s_draw_params
{
	int		n_ray;
	int		draw_start;
	int		draw_end;
	double	perpen_dst;
	double	wall_height;
	double	ray_distance;
}	t_draw_params;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		line_len;
	int		bit_per_pixel;
	int		endian;
}	t_img;

typedef struct s_ray_data
{
	t_vector2D	ray_dir;
	t_vector2D	side_dist;
	t_vector2D	delta_dist;
	t_vector2D	map_pos;
	t_vector2D	step;
	double		wall_dist;
	double		ray_len;
	int			side;
	int			wall_direction;
	int			wall_id;
}	t_ray_data;

typedef struct s_queue
{
	t_vector2D	*point;
	int			size_queue;
	int			writing_index;
	int			reading_index;
}	t_queue;

typedef struct s_data
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_map		*map;
	t_pplane	*pplane;
	t_keys		*keys;
	t_texture	tex[4];
	t_ray_data	*ray;
}	t_data;

//---------------------------------------DRAW-----------------------------------

//draw
void	draw_image(t_data *data, bool first_image);

//draw_rays
void	draw_all_rays(t_data *data, t_map *map);

//ray_casting
double	final_distance(t_ray_data *ray, t_vector2D player_coor);
void	get_wall_orientation(t_ray_data *ray, int what_use);
double	dda(t_data *data, t_ray_data *ray);
void	calculate_step_and_side_dist(t_ray_data *ray, \
		t_vector2D player_coor);
void	init_ray(t_ray_data *ray, double *angle, t_vector2D player_coor);

//draw_rays_utils
double	calculate_distance(double x, double y, double x1, double y1);
void	draw_texture(t_data *data, t_draw_params *draw_param, \
	t_texture *tex, double ray_distance);
int		is_out_of_bounds(t_map *map, int map_x, int map_y);
int		max(int a, int b);

//draw_map2d
int		draw_map2d(t_map *map, t_data *data);

//draw_ceiling_floor
void	draw_ceiling_and_floor(t_data *data);

//big_init
int		big_init(t_data *data, t_pplane *pplane, t_map *map);

//---------------------------------------MLX_INIT-------------------------------

//mlx_init
void	data_init(t_data *data);
int		texture_init(t_data *data);
int		handle_win_exit(t_data *data);
void	mlx_cleanup(t_data *data);

//key_hook_happenning
void	move_player(t_data *data, double dx, double dy);
void	left_arrow(t_data *data);
void	right_arrow(t_data *data);
void	s_key(t_data *data);
void	w_key(t_data *data);
void	a_key(t_data *data);
void	d_key(t_data *data);

//handle_input
int		handle_key_release(int keysym, t_data *data);
int		handle_key_press(int keysym, t_data *data);
int		key_loop(t_data *data);

//---------------------------------------PARSING--------------------------------

//parsing
int		parsing(int ac, char **av, t_map *map);

//init
bool	init_map(t_map *map);

//parsing_utils
int		map_started(char *line);
char	*format_line(char *line);

//file_check
int		file_check(char *file, t_map *map);

//cardinal_check
int		cardinal_check(int fd, t_map *map);

//cardinal_found_all
bool	found_all_cardinal(t_map *map);
int		did_found_all_cardinal(bool all_car, t_map *map);

//textures_check
int		check_access_textures(t_map *map);

//get_color
int		color_check(int fd, t_map *map);

//check_color
bool	check_color_value(t_map *map);
t_map	*check_for_color(t_map *map);
int		color_cmp(char *line);
int		count_array_size(char **s);
int		*fill_color_tab(int	*color_tab);

//fill_color
t_map	*fill_color(char *line, char *path, t_map *map, int *all_colour_found);

//map_check
int		map_good(t_map *map);

//flood_fill
int		iter_flood_fill(t_map *map);

//map_check_utils
int		find_player(char c);
int		check_char_map(t_map **map);
int		valid_char(char c);

//fill_map
int		map_fill(int fd, t_map *map, int number_line_map);
int		count_line(int fd);
int		read_till_the_end(int fd, char *line);

//fill_map_square
char	**map_fill_square(t_map *map);
int		read_till_the_end_map(int fd, char *line);

//free_once_map_square
void	free_char_map(t_map *map);
void	map_free_square(char **map_square, int i);

//free
void	free_map(t_map *map);

//---------------------------------------GNL--------------------------------
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
