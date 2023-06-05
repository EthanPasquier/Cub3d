/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:41:56 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/01 10:16:21 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	ft_count_unrecognize_char(char *str)
{
	int		i;
	size_t	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (ft_strchr(" \n\t", str[i]) != NULL)
			count++;
	}
	if (ft_strlen(str) == count)
		return (false);
	return (true);
}

bool	ft_check_line(t_map *game, int i, int *player_count)
{
	int	j;

	j = 0;
	while (game->map[i][j])
	{
		if (ft_strchr("NSWE10 \n", game->map[i][j]) == NULL)
			return (ft_error_character(game->map[i][j], i));
		if (ft_strchr("NSWE", game->map[i][j]) != NULL)
		{
			game->player.direction = game->map[i][j];
			game->player.x_pos += j;
			game->player.y_pos += (i - game->index_start_map);
			*player_count += 1;
		}
		j++;
	}
	return (true);
}

bool	ft_is_one_player(t_map *game)
{
	int	player_count;
	int	i;

	i = game->index_start_map;
	player_count = 0;
	while (game->map[i])
	{
		if (ft_count_unrecognize_char(game->map[i]) == false)
			return (ft_error("Newline in map design.\n"));
		if (ft_check_line(game, i, &player_count) == false)
			return (false);
		i++;
	}
	if ((i - game->index_start_map) == 0)
		return (ft_error("Problem with map design (non-existent or other)\n"));
	else if ((i - game->index_start_map) < 3)
		return (ft_error("Map design is not playable.\n"));
	else if (player_count > 1)
		return (ft_error("Too many player on map.\n"));
	else if (player_count < 1)
		return (ft_error("There is no player on map.\n"));
	return (true);
}

bool	ft_load_xpm(t_map *game)
{
	ft_remove_newline(game);
	game->texture->all_xpm[NORTH] = mlx_load_xpm42(game->north_string);
	if (!game->texture->all_xpm[NORTH])
		return (ft_error("Can't load north texture.\n"));
	game->texture->all_xpm[SOUTH] = mlx_load_xpm42(game->south_string);
	if (!game->texture->all_xpm[SOUTH])
		return (ft_error("Can't load south texture.\n"));
	game->texture->all_xpm[EAST] = mlx_load_xpm42(game->east_string);
	if (!game->texture->all_xpm[EAST])
		return (ft_error("Can't load east texture.\n"));
	game->texture->all_xpm[WEST] = mlx_load_xpm42(game->west_string);
	if (!game->texture->all_xpm[WEST])
		return (ft_error("Can't load west texture.\n"));
	return (true);
}

void	ft_parsing(t_map *game, char **av)
{
	game->map = ft_copy_map(av[1]);
	if (!game->map)
	{
		free(game->texture);
		free(game->mlx);
		free(game);
		exit(EXIT_SUCCESS);
	}
	if (ft_check_map(game) == false)
		free_n_exit(game);
	if (ft_load_xpm(game) == false)
		free_n_exit(game);
	if (ft_color_texture(game, 0) == false)
		free_n_exit(game);
}
