/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:29:36 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/15 15:41:36 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_surrounded_by_walls(t_map *game, int x, int y, char **map)
{
	bool	surrounded;

	if (x < 0 || y < 0 || x >= game->size.width || y >= game->size.height)
		return (false);
	if (map[y][x] == '1')
		return (true);
	else
		map[y][x] = '1';
	surrounded = true;
	surrounded &= is_surrounded_by_walls(game, x - 1, y, map);
	surrounded &= is_surrounded_by_walls(game, x + 1, y, map);
	surrounded &= is_surrounded_by_walls(game, x, y - 1, map);
	surrounded &= is_surrounded_by_walls(game, x, y + 1, map);
	return (surrounded);
}

bool	ft_is_close_with_one(t_map *game)
{
	char	**map;
	int		i;

	i = -1;
	map = (char **)malloc(sizeof(char *) * (game->size.height + 1));
	if (!map)
		return (ft_error("Malloc error in ft_is_close_with_one.\n"));
	map[game->size.height] = NULL;
	while (++i < game->size.height)
		map[i] = ft_strdup(game->map[i]);
	if (is_surrounded_by_walls(game, game->player.x_pos,
			game->player.y_pos, map) == false)
	{
		ft_free_double(map);
		return (ft_error("Map is not closed with one.\n"));
	}
	ft_free_double(map);
	return (true);
}
