/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatbir <aatbir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:41:17 by aatbir            #+#    #+#             */
/*   Updated: 2024/05/28 18:14:19 by aatbir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void hook_key(void *arg)
{  
	t_info *map = (t_info*)arg;
	double target_x = map->player_x;
	double target_y = map->player_y;

	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		target_x += PLAYER_SPEED * cos(map->angle);
		target_y += PLAYER_SPEED * sin(map->angle);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		target_x -= PLAYER_SPEED * cos(map->angle);
		target_y -= PLAYER_SPEED * sin(map->angle);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		target_y -= PLAYER_SPEED * cos(map->angle);
		target_x += PLAYER_SPEED * sin(map->angle);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		target_y += PLAYER_SPEED * cos(map->angle);
		target_x -= PLAYER_SPEED * sin(map->angle);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->angle += deg2rad(2.5);
	else if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT)) 
		map->angle -= deg2rad(2.5);
	if (map->angle >= 2 * M_PI)
		map->angle -= 2 * M_PI;
	else if (map->angle < 0)
		map->angle += 2 * M_PI;
	int map_x = target_x / TILE_SIZE;
	int map_y = target_y / TILE_SIZE;
	if (map->map[map_y][map_x] == '0')
	{
		// Draw line from player to target
		// Update player's position
		map->player_x = target_x;
		map->player_y = target_y;
	}
	// printf("error\n");
	draw_map(map);
	float xf, yf;
	map->angle_fov = map->angle - deg2rad(FOV / 2);
	// map->angle -= deg2rad(FOV / 2);
	// printf("the angele is == %f\n", map->angle);

	t_cord inter;
	double i = 0;
	double disrays = deg2rad(FOV)/ map->width;
	// printf("dis ===> %f\n", disrays);
	// int fov = map->viewangle / map->width;
	while(i <= map->width)
	{
		// map->angle_fov += deg2rad(1);
		if (map->angle_fov > 2 * M_PI)
			map->angle_fov -= 2 * M_PI;
		if (map->angle_fov < 0)
			map->angle_fov +=  2 * M_PI;
		// printf("angle: %f\n", map->angle_fov);
		t_cord h =  horizontal_intersection(map, map->angle_fov);
		h.is_vertical = false;
		t_cord v = vertical_intersection(map, map->angle_fov);
		v.is_vertical = true;
		inter = smallest(map, h, v);
		drawline(map, map->player_x, map->player_y, 
			inter.xstep, inter.ystep, 0xFF0000FF);
		map->angle_fov += disrays;
		i++;
	}
	xf = cos(map->angle) * inter.xstep;
	yf = sin(map->angle) * inter.ystep;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	(void)param;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE 
		&& keydata.modifier == MLX_CONTROL)
		puts("Gotta grab it all!");
}

int	get_height(void)
{
	int	i;

	i = 0;
	while (info_path->info->map[i])
		i++;
	return (i);
}

int	get_width(void)
{
	int	i;
	int	j;
	int	max_width;

	i = 0;
	max_width = 0;
	while (info_path->info->map[i])
	{
		j = 0;
		while (info_path->info->map[i][j])
			j++;
		if (j > max_width)
			max_width = j;
		i++;
	}
	return (max_width);
}

void	draw_map(void *param)
{
	t_info *info = (t_info *)param;
	int x, y, i, j;
	int pixel_x, pixel_y;
	int width = get_width();
	int height = get_height();

	if (!info || !info->map || !info->img)
		throw_err_2("Invalid parameters or uninitialized map/image\n");
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			char tile = info->map[i][j];
			uint32_t color;
			if (tile == '1')
				color = 0x000000FF; // Black color
			else 
				color = 0xFFFFFFFF; // White color
			y = 0;
			while (y < TILE_SIZE)
			{
				x = 0;
				while (x < TILE_SIZE)
				{
					pixel_x = j * TILE_SIZE + x;
					pixel_y = i * TILE_SIZE + y;
					if (x == 0 || x == TILE_SIZE - 1 
						|| y == 0 || y == TILE_SIZE - 1)
						mlx_put_pixel(info->img, pixel_x, pixel_y, 0x00FF00FF);
					else
						mlx_put_pixel(info->img, pixel_x, pixel_y, color);
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < TILE_PLAYER_SIZE)
	{
		j = 0;
		while (j < TILE_PLAYER_SIZE)
		{
			double x = info->player_x + i;
			double y = info->player_y + j;
			mlx_put_pixel(info->img, x, y, 0x0000FFFF);
			j++;
		}
		i++;
	}
}


