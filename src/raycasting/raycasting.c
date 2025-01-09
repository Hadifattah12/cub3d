/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:24:19 by pkahil            #+#    #+#             */
/*   Updated: 2025/01/09 12:00:03 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// The delta distance helps determine how far the ray will travel in
// each direction between grid cells,
//  which is essential for detecting collisions
// with walls and rendering the 3D environment.

void	get_delta_dist(t_map *map)
{	
	if (map->ray_dir_x == 0)
		map->delta_dist_x = INT_MAX;
	else
		map->delta_dist_x = fabs(1 / map->ray_dir_x);
	if (map->ray_dir_y == 0)
		map->delta_dist_y = INT_MAX;
	else
		map->delta_dist_y = fabs(1 / map->ray_dir_y);
}

//  step_x and step_y: These variables determine the direction in 
//  which the ray will move through the grid.
//  If the ray is moving left or up, step_x or step_y will be -1; 
//  if the ray is moving right or down, they 
//  will be 1. These values are used later in the raycasting loop 
//  to update the player's position as the ray
//  steps through the grid.
//  side_dist_x and side_dist_y: These variables store the distance 
//  from the player's current position to
//  the next grid boundary (either vertical or horizontal) along
//  the respective axis. These distances are 
//  updated during the raycasting process as the ray steps through 
//  the grid. The side_dist_x and side_dist_y
//  values are crucial for determining how far the ray travels 
//  before hitting a wall or passing through
//  another grid cell.

void	get_step(t_map *map)
{
	if (map->ray_dir_x < 0)
	{
		map->step_x = -1;
		map->side_dist_x = (map->pos_x - map->map_x) * map->delta_dist_x;
	}
	else
	{
		map->step_x = 1;
		map->side_dist_x = (map->map_x + 1.0 - map->pos_x) * map->delta_dist_x;
	}
	if (map->ray_dir_y < 0)
	{
		map->step_y = -1;
		map->side_dist_y = (map->pos_y - map->map_y) * map->delta_dist_y;
	}
	else
	{
		map->step_y = 1;
		map->side_dist_y = (map->map_y + 1.0 - map->pos_y) * map->delta_dist_y;
	}
}

// side_dist_x / side_dist_y: Tracks the current distance 
//to the next vertical or horizontal grid line.
// delta_dist_x / delta_dist_y: Represents the constant step size along the 
// ray for vertical and horizontal directions.
// step_x / step_y: Indicates the direction of movement along the
// x and y axes (+1 for right/down, -1 for left/up).
// wall_side: Indicates whether the
// ray hit a vertical (0) or horizontal (1) wall.

void	digital_differential_analyser(t_map *map)
{
	int	wall;

	wall = 0;
	while (wall == 0)
	{
		if (map->side_dist_x < map->side_dist_y)
		{
			map->side_dist_x += map->delta_dist_x;
			map->map_x += map->step_x;
			map->wall_side = 0;
		}
		else
		{
			map->side_dist_y += map->delta_dist_y;
			map->map_y += map->step_y;
			map->wall_side = 1;
		}
		if (map->map_tab[map->map_y][map->map_x] == '1')
			wall = 1;
	}
}

// It calculates the ray's direction in both the x and y axes
// based on the player's position, 
// direction, and camera plane .This setup allows 
// for simulating the way rays travel from the 
// player's viewpoint to interact with the map grid, which 
// is essential for rendering the 3D environment.

void	init_raycasting(t_map *map, int x)
{
	map->map_x = map->pos_x;
	map->map_y = map->pos_y;
	map->cam_x = 2 * x / (double)map->display_width - 1;
	map->ray_dir_x = map->dir_x + map->plane_x * map->cam_x;
	map->ray_dir_y = map->dir_y + map->plane_y * map->cam_x;
}

// side_dist_x and side_dist_y represent the accumulated distances
// to the vertical or horizontal grid lines
//  from the player's initial position.
// Subtracting delta_dist_x or delta_dist_y removes the last added increment,
//  giving the exact distance to the wall.

void	raycasting(t_map *map)
{
	int	x;

	x = 0;
	while (x < map->display_width)
	{
		init_raycasting(map, x);
		get_delta_dist(map);
		get_step(map);
		digital_differential_analyser(map);
		if (map->wall_side == 0)
			map->perpwalldist = ((map->side_dist_x - map->delta_dist_x));
		else
			map->perpwalldist = ((map->side_dist_y - map->delta_dist_y));
		draw_column(map, x);
		x++;
	}
}
