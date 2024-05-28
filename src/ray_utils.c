/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatbir <aatbir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:35:14 by aatbir            #+#    #+#             */
/*   Updated: 2024/05/28 18:10:33 by aatbir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

bool	has_wall(t_info *mlx, int x, int y)
{
	x /= TILE_SIZE;
	y /= TILE_SIZE;
	if (x < 0 || x >= mlx->rows || y < 0 || y >= mlx->cols)
		return (true);
	if (mlx->map[(int)y][(int)x] == '1')
		return (true);
	return (false);
}

t_cord	horizontal_intersection(t_info *mlx, float ray_angle)
{
	t_cord	cord;
	int		sign;
	bool	is_ray_facing_up;

	is_ray_facing_up = ray_angle > M_PI;
	sign = 1;
	if (is_ray_facing_up)
		sign = -1;
	cord.ystep = (int)(mlx->player_y / TILE_SIZE) * TILE_SIZE;
	if (!is_ray_facing_up)
		cord.ystep += TILE_SIZE;
	cord.xstep = mlx->player_x + (cord.ystep - mlx->player_y) / tan(ray_angle);
	const float dx = sign * TILE_SIZE / tan(ray_angle);
	const float dy = sign * TILE_SIZE;
	while (true)
	{
		if ((is_ray_facing_up && \
				has_wall(mlx, cord.xstep, cord.ystep - TILE_SIZE)) || \
			(!is_ray_facing_up && \
				has_wall(mlx, cord.xstep, cord.ystep)))
			break ;
		cord.xstep += dx;
		cord.ystep += dy ;
		if (cord.xstep > mlx->width || cord.xstep < 0) 
			break ;
	}
	return (cord);
}

t_cord	vertical_intersection(t_info *mlx, float ray_angle)
{
	t_cord		cord;
	int			sign;
	bool		is_ray_facing_left;


	is_ray_facing_left = ray_angle > M_PI / 2 && ray_angle < 1.5 * M_PI;
	sign = 1;
	cord.xstep = (int)(1 + mlx->player_x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_left)
	{
		cord.xstep -= TILE_SIZE;
		sign = -1;
	}
	cord.ystep = mlx->player_y - (mlx->player_x - cord.xstep) * tan(ray_angle);
	const float	dx = sign * TILE_SIZE;
	const float dy = sign * TILE_SIZE * tan(ray_angle);
	while (true)
	{
		if ((is_ray_facing_left && \
				has_wall(mlx, cord.xstep - TILE_SIZE, cord.ystep)) || \
			(!is_ray_facing_left && \
				has_wall(mlx, cord.xstep, cord.ystep)))
			break ;
		cord.xstep += dx;
		cord.ystep += dy; 
	}
	return (cord);
}


void drawline(t_info *map, int x1, int y1, int x2, int y2, uint32_t color)
{
	float dx, dy, step, x, y;
	int i;

	dx = x2 - x1;
	dy = y2 - y1;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);

	dx = dx / step;
	dy = dy / step;
	x = x1;
	y = y1;
	i = 0;
	while (i <= step)
	{
		if (x > 0 && x < map->width && y > 0 && y < map->height)
			mlx_put_pixel(map->img, (int)x, (int)y, color);
		x += dx;
		y += dy;
		i++;
	}
}

double	deg2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}
