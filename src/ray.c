/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatbir <aatbir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:10:04 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/05/28 17:50:43 by aatbir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void	pos_player(t_info *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (ft_strchr("NSWE", map->map[i][j]))
			{
				map->player_x = (j + 0.5) * TILE_SIZE - TILE_PLAYER_SIZE / 2;
				map->player_y = (i + 0.5) * TILE_SIZE - TILE_PLAYER_SIZE / 2;
				map->map[i][j] = '0';
				return ;
			}
			j++;
		}
	}
}

void	var_init(t_info *info)
{
	info->viewangle = FOV * (M_PI / 180);
	info->player.speedretate = SPEED_R * (M_PI / 180);
	info->player.speedmove = (CUBE * SPEED_M) / 20 ;
	info->player.dirturn = 0;
	info->player.dirwalk = 0;
	info->rad = M_PI / 180;
}

void	check_dir_angle(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == 'W')
				info->angle = M_PI;
			if (info->map[i][j] == 'E')
				info->angle = 0;
			if (info->map[i][j] == 'S')
				info->angle = M_PI / 2;
			if (info->map[i][j] == 'N')
				info->angle = 3 * M_PI / 2;
			j++;
		}
		i++;
	}
}

int	lenofmap(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
//mo3adalat vitafors

t_cord	smallest(t_info *mlx, t_cord c1, t_cord c2)
{
	float	d1;
	float	d2;

	d1 = sqrt((c1.xstep - mlx->player_x) * (c1.xstep - mlx->player_x) + \
				(c1.ystep - mlx->player_y) * (c1.ystep - mlx->player_y));
	d2 = sqrt((c2.xstep - mlx->player_x) * (c2.xstep - mlx->player_x) + \
				(c2.ystep - mlx->player_y) * (c2.ystep - mlx->player_y));
	if (d1 < d2)
	{
		c1.is_vertical = false;
		return (c1);
	}
	c2.is_vertical = true;
	return (c2);
}
