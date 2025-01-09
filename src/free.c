/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:24:34 by pkahil            #+#    #+#             */
/*   Updated: 2025/01/07 10:33:44 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	destroy_image(t_map *map)
{
	int	i;

	i = 0;
	if (map->mlx)
	{
		while (i < 5)
		{
			if (map->img[i].mlx_img)
				mlx_destroy_image(map->mlx, map->img[i].mlx_img);
			i++;
		}
	}
}

void	free_rgb_texture(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->img[i].path)
			free(map->img[i].path);
		i++;
	}
}

void	free_double_array(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

int	close_game(t_map *map)
{
	free_rgb_texture(map);
	free_double_array(map->map_tab);
	destroy_image(map);
	mlx_destroy_window(map->mlx, map->mlx_win);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	exit (0);
}
