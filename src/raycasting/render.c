/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkahil <pkahil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:24:24 by pkahil            #+#    #+#             */
/*   Updated: 2025/01/02 15:24:25 by pkahil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	render_background(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->display_width)
	{
		y = 0;
		while (y < map->display_height)
		{
			if (y < map->display_height / 2)
				img_pix_put(map, x, y, create_trgb(0, map->rgb_sky[0],
						map->rgb_sky[1], map->rgb_sky[2]));
			else
				img_pix_put(map, x, y, create_trgb(0, map->rgb_floor[0],
						map->rgb_floor[1], map->rgb_floor[2]));
			y++;
		}
		++x;
	}
}

int	render(t_map *map)
{
	render_background(map);
	raycasting(map);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img[4].mlx_img, 0, 0);
	return (0);
}
