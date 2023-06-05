/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:03 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/01 10:16:36 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	ft_check_rgb_color(t_map *game)
{
	if (!game->string_ceilling_color || game->string_ceilling_color[0] == '\n')
		return (ft_error("No RGB color for C.\n"));
	if (!game->string_floor_color || game->string_floor_color[0] == '\n')
		return (ft_error("No RGB color for F.\n"));
	return (true);
}

bool	ft_check_all_texture(t_map *game)
{
	if (!game->north_string || game->north_string[0] == '\n')
		return (ft_error("Did not find texture for: NO.\n"));
	if (!game->south_string || game->south_string[0] == '\n')
		return (ft_error("Did not find texture for: SO.\n"));
	if (!game->west_string || game->west_string[0] == '\n')
		return (ft_error("Did not find texture for: WE.\n"));
	if (!game->east_string || game->east_string[0] == '\n')
		return (ft_error("Did not find texture for: EA.\n"));
	return (true);
}

void	ft_assign(t_map *game, int index, char direction)
{
	int	space;

	space = ft_strlen_space(game->map[index]);
	if (direction == 'N')
		game->north_string = ft_strdup(game->map[index] + 3 + space);
	else if (direction == 'S')
		game->south_string = ft_strdup(game->map[index] + 3 + space);
	else if (direction == 'E')
		game->east_string = ft_strdup(game->map[index] + 3 + space);
	else if (direction == 'W')
		game->west_string = ft_strdup(game->map[index] + 3 + space);
	else if (direction == 'F')
		game->string_floor_color = ft_strdup(game->map[index] + 2 + space);
	else if (direction == 'C')
		game->string_ceilling_color = ft_strdup(game->map[index] + 2 + space);
}

bool	ft_is_texture_info(t_map *game, char *direction)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (game->map[i] && game->map[i][0] != '1')
	{
		if (ft_strncmp(direction, game->map[i] + ft_strlen_space(game->map[i]),
				ft_strlen(direction)) == 0
			&& game->map[i][ft_strlen_space(game->map[i])
			+ ft_strlen(direction)] == ' ')
		{
			count++;
			if (count == 1)
				ft_assign(game, i, direction[0]);
		}
		i++;
	}
	if (count == 1)
		return (true);
	ft_error_texture(count, direction);
	return (false);
}

bool	ft_is_map_info(t_map *game)
{
	if (ft_is_texture_info(game, "NO") == false
		|| ft_is_texture_info(game, "SO") == false
		|| ft_is_texture_info(game, "EA") == false
		|| ft_is_texture_info(game, "WE") == false
		|| ft_is_texture_info(game, "F") == false
		|| ft_is_texture_info(game, "C") == false)
		return (false);
	if (ft_check_all_texture(game) == false)
		return (false);
	if (ft_check_rgb_color(game) == false)
		return (false);
	return (true);
}
