/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:13:52 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/04 17:34:40 by saperrie         ###   ########.fr       */
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
# define SQUARE_SIZE 15 // 15
# define MOVE_SPEED 0.1 // 0.064 is 1 pixel
# define ROTATION_ANGLE 0.06 // initial value is 0.04
# define FOV 1.0472  // 60 degree field of view
# define P2 PI/2
# define P3 3*PI/2
# define ISAAC 0
# define MV 1
# define NORTH 0
# define SOUTH 1
# define EAST  2
# define WEST  3


//--------------------------------------------------|

//Define for colors

//basic colors
# define LIME_GREEN 0xdaf7a6
# define ORANGE 0xffc300
# define BRIGHT_RED 0xff5733
# define CRIMSON 0xc70039
# define PINK 0xff5cbe
# define PASTEL_PURPLE 0xb1a3ff
# define GRID_COLOR 0x808080
# define RED 0xFF0000
# define YELLOW 0xFFFF00

//Barbie color palette
# define BUBBLEGUM_PINK 0xFF9EE2
# define DARK_PINK 0xFF36AF
# define LIGHT_PINK 0xFFC4F3
# define LIGHT_BLUE 0x5DADE2

//pretty color palette
# define RICH_BLACK 0x001514
# define CITRON 0xC2D076
# define VIOLET 0xFFE1EA
# define PURPLE_PIZZAZZ 0xFFA0FD
# define MIMI_PINK 0xE952DE

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
	int		distance_from_player;
	double	angle_between_rays;
}	t_pplane;

typedef struct s_player
{
	int		view_height;
	double		fov;
	double	x;
	double	y;
	//double	move_speed;
    double	rotation_speed;
	double	view_angle; // x,y and view_angle is POV
}	t_player;

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
	t_point	*player_position;
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

} t_ray_data;

// typedef struct s_queue
// {
// 	t_vector2D 	point;
// 	t_queue		*next;
// }	t_queue;

typedef struct s_data
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_map		*map;
	t_player	*player;
	t_pplane	*pplane;
	t_keys		*keys;
	t_texture	tex[4];
	t_ray_data	*ray;
}	t_data;

//---------------------------------------DRAW-----------------------------------

//draw
void	draw_first_image(t_data *data);
void	draw_new_image(t_data *data);

//draw_rays
void	draw_all_rays(t_data *data, t_map *map);

//ray_casting
double	calculate_wall_distance(t_data *data, t_vector2D player_coor, double *angle);

//draw_rays_utils
double	calculate_distance(double x, double y, double x1, double y1);
void	draw_point(t_data *data, int x, int y, int draw_end, int color);
void	draw_texture(t_data *data, int n_ray, int draw_start, int draw_end, double wall_height, t_texture *tex, double ray_distance);
int		is_out_of_bounds(t_map *map, int map_x, int map_y);
int		max(int a, int b);

//draw_map2d
int		draw_map2d(t_map *map, t_data *data);

//draw_ceiling_floor
void	draw_ceiling_and_floor(t_data *data);

//big_init
int		big_init(t_data *data, t_player *player, t_pplane *pplane, t_map *map);
/*int		projection_plane_init(t_pplane *pplane, t_player *player);
int		player_init(t_player *player);*/

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
int		parsing(int ac, char **av, t_map *map, t_player *player);

//init
bool	init_map(t_map *map);

//parsing_utils
int		map_started(char *line);
char	*format_line(char *line);

//file_check
int		file_check(char *file, t_map *map);

//cardinal_check
int		cardinal_check(int fd, t_map *map);

//textures_check
int		check_access_textures(t_map *map);

//color_check
int		color_check(int fd, t_map *map);

//map_check
int		map_good(t_map *map, t_player *player);

//map_check_utils
int		find_player(char c);
int		check_char_map(t_map **map);
int		valid_char(char c);

//fill_map
int		map_fill(int fd, t_map *map, int number_line_map);
int		count_line(int fd);
int		read_till_the_end(int fd, char *line);

//free
void	free_map(t_map *map);

//GNL
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
