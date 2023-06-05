/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:48:54 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/31 12:07:03 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	ft_check_extension(char *av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (ft_strncmp(&av[i - 4], ".cub", 4) == 0 && i - 4 != 0)
		return (true);
	return (false);
}

bool	ft_check_input(int ac, char *av)
{
	int	fd;

	if (ac <= 1)
		return (ft_error("No argument given.\n"));
	if (ac > 2)
		return (ft_error("Too many argument.\n"));
	if (ft_check_extension(av) == false)
		return (ft_error("Map extension is not .cub.\n"));
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_error("Map does not exist or can't be open.\n"));
	close(fd);
	return (true);
}

bool	ft_check_design(t_map *game)
{
	ft_set_index_start(game);
	if (game->index_start_map <= 0)
	{
		write(2, "Error\nMap design error\n", 23);
		return (false);
	}
	if (ft_is_one_player(game) == false)
		return (false);
	ft_fill_map(game);
	if (ft_is_close_with_one(game) == false)
		return (false);
	ft_set_dir_spawn(game);
	return (true);
}

bool	ft_check_rgb(t_map *game)
{
	if (ft_check_comma(game->string_ceilling_color, 'C') == false
		|| (ft_check_comma(game->string_floor_color, 'F') == false))
		return (false);
	if (ft_check_number(game->string_ceilling_color, 'C', game) == false
		|| ft_check_number(game->string_floor_color, 'F', game) == false)
		return (false);
	return (true);
}

bool	ft_check_map(t_map *game)
{
	if (ft_is_map_info(game) == false)
		return (false);
	if (ft_check_rgb(game) == false)
		return (false);
	if (ft_check_design(game) == false)
		return (false);
	if (game->size.width > 520)
		return (ft_error("Map width is too big (more than 520)\n"));
	if (game->size.height > 85)
		return (ft_error("Map Heigh is too big (more than 85)\n"));
	return (true);
}
