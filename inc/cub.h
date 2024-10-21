/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:13:52 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/21 17:40:46 by aljulien         ###   ########.fr       */
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
# define PLAYER_SIZE 3
# define SQUARE_SIZE 64
# define NUM_RAYS 60         // Number of rays to cast
# define FOV (60 * PI / 180)  // 60 degree field of view
#define P2 PI/2
#define P3 3*PI/2



//--------------------------------------------------|

//Define for colors
# define LIME_GREEN 0xdaf7a6
# define ORANGE 0xffc300
# define BRIGHT_RED 0xff5733
# define CRIMSON 0xc70039
# define PINK 0xffa2cc
# define PASTEL_PURPLE 0xb1a3ff
# define GRID_COLOR 0x808080
# define RED 0xFF0000
# define YELLOW 0xFFFF00  


typedef struct {
    double x;
    double y;
} t_vector2D;

typedef struct {
    t_vector2D origin;
    t_vector2D direction;
} t_ray;

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

//PARSING
int		parsing(int ac, char **av, t_map *map, t_player *player);

//parsing_utils
int		map_started(char *line);
char	*format_line(char *line);

//init
bool	init_map(t_map *map);

//mlx
void	data_init(t_data *data);
int		draw_2d_map(t_map *map, t_data *data);
int		draw_new_2d(t_map *map, t_data *data);
void	draw_new_image(t_data *data);
int		key_press(int keysym, t_data *data);
int		key_release(int keysym, t_data *data);
int		handle_win_exit(t_data *data);
int		key_loop(t_data *data);

// init
int		big_init(t_data *data, t_player *player, t_pplane *pplane, t_map *map);

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
