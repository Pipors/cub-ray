/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatbir <aatbir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:14:11 by aatbir            #+#    #+#             */
/*   Updated: 2024/05/28 18:13:13 by aatbir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <ctype.h>
# include <fcntl.h>
#include <stdlib.h>
#include <string.h>
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../MLX/MLX42.h"


#define CUBE 10
# define TILE_PLAYER_SIZE 1
# define TILE_SIZE 64
#define WIDTH 512
#define HEIGHT 512
# define MSIZE 170
#define PLAYER_SPEED 2
# define SPEED_R 3
# define M_SPEED_R 1
# define SPEED_M 2
# define FOV 60


# define PIXEL_SIZE 50



// Initialize the player with default values


typedef struct s_cord
{
	bool	is_vertical;
	double	xstep;
	double	ystep;
}	t_cord;

typedef struct s_ray
{
	double	angle;
	double	dis;
	double	x;
	double	y;
	int		up;
	int		down;
	int		left;
	int		right;
	double	hwallx;
	double	hwally;
	double	vwallx;
	double	vwally;
	double	hdis;
	double	vdis;
	int		iswallh;
	int		iswallv;
	double	hx;
	double	hy;
	double	hxstep;
	double	hystep;
	double	hxnext;
	double	hynext;
	double	vx;
	double	vy;
	double	vxstep;
	double	vystep;
	double	vxnext;
	double	vynext;
	int		v;
	int		h;
}			t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	dirturn;
	double	dirwalk;
	double	dirwalkx;
	double	alpha;
	double	speedmove;
	double	speedretate;
	double	speedretate_m;
}		t_player;

typedef struct s_info
{
	char			pos;
	char			*first_info;
	char			*second_info;
	char			*third_info;
	char			*fourth_info;
	char			*first_color;
	char			*second_color;
	char			*addr;
	char			**map;
	double			angle;
	double			angle_fov;
	double			player_x;
	double			player_y;
	double			rad;
	double			view;
	double			viewangle;
	float			x;
	float			y;
	int				bits_per_pixel;
	int				cols;
	int				endian;
	int				line_length;
	int				nbr_rays;
	int				height;
	int				rows;
	int				width;
	int				_f[3];
	int				_c[3];
	void			*win;
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	mlx_t			*mlx;
	t_player		player;
	t_ray			*ray;


}	t_info;

typedef struct s_map
{
	t_info	*info;
	int		wid;
	int		hei;
}	t_map;

t_map	*info_path;

char	*read_file(char *filename);
void	ft_free_info(t_info *info);

t_info	*get_info(t_info *info, char *filename);
void	throw_err_2(char *err_msg);

int		only(char *line, int c, int d);
int		check_if_only_numbers(char **str);
int		valid_rgb_f(t_info *info, char *filename);
int		valid_rgb_c(t_info *info, char *filename);
char	**splimed_key_value_6(char *filename);


char	*ft_strtrim(char const *s1, char const *set);
char	*valid_first_info(t_info *info, char *filename);
char	*valid_second_info(t_info *info, char *filename);
char	*valid_third_info(t_info *info, char *filename);
char	*valid_fourth_info(t_info *info, char *filename);
int		*split_first_color(t_info *info, char *filename);
char	**textures(void);
int		compare_dup_text(t_info *info, char *filename);
void	parsing(t_info *info, char *filename);
int		compare(char *s1, char *s2);

void	arr_free(char **s);

char	**store_get_info_in_array(t_info *info, char *filename);
char	*valid_first_info(t_info *info, char *filename);
char	*ft_half_strtrim(char const *s1, char const *set);

char	*take_first_string(char *line);
char	*start_with(char *first_word, char *target, size_t size);
int		is_valid_textures(t_info *info, char *filename);
void	check_get_info(t_info	*info, char *filename);
void	player_pos(void);
int		get_height(void);
int		get_width(void);
void	draw_map(void *param);
void 	pos_player(t_info *map);
int32_t	run_game(void);
void 	init(t_info *map);


void hook_key(void *arg);
void key_hook(mlx_key_data_t keydata, void *param);
int	lenofmap(char **arr);
void	check_dir_angle(t_info *info);
t_cord	smallest(t_info *mlx, t_cord c1, t_cord c2);
t_cord	vertical_intersection(t_info *mlx, float ray_angle);
void 	drawline(t_info *map, int x1, int y1, int x2, int y2, uint32_t color);
t_cord	horizontal_intersection(t_info *mlx, float ray_angle);
bool	has_wall(t_info *mlx, int x, int y);
double	deg2rad(double degrees);
#endif