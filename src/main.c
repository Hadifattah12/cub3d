/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfattah <hfattah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:24:39 by pkahil            #+#    #+#             */
/*   Updated: 2025/01/09 10:13:25 by hfattah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_test_extension(char *argv)
{
	int	i;
	int	j;

	i = ft_strlen(argv);
	j = 0;
	i -= 4;
	while (argv[i] != '\0')
	{
		if (j == 0 && argv[i] != '.')
			return (0);
		if (j == 1 && argv[i] != 'c')
			return (0);
		if (j == 2 && argv[i] != 'u')
			return (0);
		if (j == 3 && argv[i] != 'b')
			return (0);
		i++;
		j++;
	}
	return (1);
}

int	ft_test_file(char *argv)
{
	int		fd;
	int		result;
	char	test[1];

	if (!ft_test_extension(argv))
	{
		ft_printf("Error\nBad extension\n");
		return (0);
	}
	fd = open(argv, O_RDONLY);
	result = read(fd, test, 1);
	if (result <= 0)
	{
		if (result == 0)
			ft_printf("Error\nEmpty file\n");
		else if (result < 0)
			ft_printf("Error\nInvalid entry\n");
		return (0);
	}
	close(fd);
	return (1);
}

void	bzero_struct(t_map *map)
{
	int	i;

	i = 0;
	map->map_tab = NULL;
	map->width_map = 0;
	map->height_map = 0;
	map->rgb_floor[0] = -1;
	map->rgb_floor[1] = -1;
	map->rgb_floor[2] = -1;
	map->rgb_sky[0] = -1;
	map->rgb_sky[1] = -1;
	map->rgb_sky[2] = -1;
	map->line = NULL;
	map->map_line = NULL;
	while (i < 5)
	{
		map->img[i].mlx_img = NULL;
		map->img[i].path = NULL;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_map	map;
	int		fd;

	bzero_struct(&map);
	if (ac != 2)
		parse_error(&map, "Error\nOne argument required\n");
	if (!ft_test_file(av[1]))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("Error\nFailed to open file\n");
		return (1);
	}
	if (!ft_parse_map(&map, fd))
	{
		free_double_array(map.map_tab);
		return (1);
	}
	ft_init_game(&map);
	return (0);
}
