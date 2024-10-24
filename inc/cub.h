/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:13:52 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/24 14:03:33 by aljulien         ###   ########.fr       */
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
# define WIDTH 2500
# define HEIGHT 1300
# define PI	3.1415926535
# define PLAYER_SIZE 5
# define SQUARE_SIZE 15
# define NUM_RAYS 320         // Number of rays to cast
# define FOV 1.0472  // 60 degree field of view
# define P2 PI/2
# define P3 3*PI/2

//--------------------------------------------------|

//Define for colors
# define LIME_GREEN 0xdaf7a6
# define ORANGE 0xffc300
# define BRIGHT_RED 0xff5733
# define CRIMSON 0xc70039
# define PINK 0xff5cbe
# define PASTEL_PURPLE 0xb1a3ff
# define GRID_COLOR 0x808080
# define RED 0xFF0000
# define YELLOW 0xFFFF00
# define BUBBLEGUM_PINK 0xFF9EE2
# define DARK_PINK 0xFF36AF
# define LIGHT_PINK 0xFFC4F3
# define LIGHT_BLUE 0x5DADE2

typedef struct {
    double x;
    double y;
} t_vector2D;

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
	int		fov;
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
	double dx;
	double dy;
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
    t_vector2D ray_dir;
    t_vector2D side_dist;
    t_vector2D delta_dist;
    t_vector2D map_pos;
    t_vector2D step;
    double wall_dist;
    int side;
} t_ray_data;

typedef struct s_data
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_img		img_fov;
	t_map		*map;
	t_player	*player;
	t_pplane	*pplane;
	t_keys		*keys;
}	t_data;

//---------------------------------------DRAW-------------------------------------------------------

//draw
void	draw_new_image(t_data *data);

//draw_rays
void	draw_all_rays(t_data *data, t_map *map);

//draw_rays_utils
double	calculate_distance(double x, double y, double x1, double y1);
void	draw_point(t_data *data, int x, int y, int color);
int		is_out_of_bounds(t_map *map, int map_x, int map_y);
int		max(int a, int b);

//draw_2D_map
int		draw_new_2d(t_map *map, t_data *data);

//draw_ceiling_floor
void	draw_ceiling_and_floor(t_data *data);

//big_init
int		big_init(t_data *data, t_player *player, t_pplane *pplane, t_map *map);
/*int		projection_plane_init(t_pplane *pplane, t_player *player);
int		player_init(t_player *player);*/

//---------------------------------------MLX_INIT-------------------------------------------------------

//mlx_init
void	data_init(t_data *data);
int		handle_win_exit(t_data *data);

//key_hook_happenning
void	left_arrow(t_data *data);
void	right_arrow(t_data *data);
void	s_key(t_data *data);
void	w_key(t_data *data);
void	a_key(t_data *data);
void	d_key(t_data *data);

//handle_input
int		key_release(int keysym, t_data *data);
int		key_press(int keysym, t_data *data);

//---------------------------------------PARSING-------------------------------------------------------

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
