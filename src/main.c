/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatbir <aatbir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:58:34 by aatbir            #+#    #+#             */
/*   Updated: 2024/05/28 18:03:54 by aatbir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

typedef struct key_value
{
	char	*key;
	char	*value;
}	t_kv;

void init(t_info *map)
{
	map->width = get_width() * TILE_SIZE;
	map->height = get_height() * TILE_SIZE;
	map->mlx = mlx_init(map->width, map->height, "CUB3D", 0);
	if (!map->mlx)
		throw_err_2("Failed to initialize MLX\n");
	map->img = mlx_new_image(map->mlx, map->width, map->height);
	if (!map->img)
	{
		fprintf(stderr, "Failed to create new image\n");
		mlx_terminate(map->mlx);
		return ;
	}
	if (mlx_image_to_window(map->mlx, map->img, 0, 0) < 0)
	{
		fprintf(stderr, "Failed to put image to window\n");
		mlx_delete_image(map->mlx, map->img);
		mlx_terminate(map->mlx);
		return ;
	}
	map->rows = ft_strlen(map->map[0]);
	map->cols = lenofmap(map->map);
	check_dir_angle(map);
	mlx_loop_hook(map->mlx, hook_key, map);
	mlx_loop(map->mlx);
}

int	main(int ac, char **av)
{
	t_info	*info ;
	char	**str;
	// t_info  map;
	// char	*take;
	int		i;

	i = 0;
	info = malloc(sizeof(t_info));
	info_path = (t_map*)ft_calloc(sizeof(t_map), 1);
	info_path->info = info;
	(void)ac;
	if (!av[1])
		return (printf("Error\n"), -1);
	str = store_get_info_in_array(info, av[1]);
	// while(str[i])
	// 	printf("%s\n", str[i++]);
	// printf ("%c\n", info_path->info->pos);
	// info->first_color = 0;
	// info->first_info = 0;
	// info
	// info = get_info(info, av[1]);
	// while (str[i])
	// {
	// 	printf("str[%d] => %s\n", i +1, str[i]);
	// 	i++;
	// }
	// check_get_info(info, av[1]);
	// printf("+first : %s\n", info->first_info);
	// printf("+second : %s\n", info->second_info);
	// printf("+third : %s\n", info->third_info);
	// printf("+fourth : %s\n", info->fourth_info);
	// printf("+color 1 : %s\n", info->first_color);
	// printf("+color 2 : %s\n", info->second_color);
	parsing(info, av[1]);
	pos_player(info);
	init(info);
	// run_game();
	arr_free(str);
	// system("leaks cub3D");
	return (0);
}
