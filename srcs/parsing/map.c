/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:53:32 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/30 11:12:23 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_set_width_height_and_1(t_map *game)
{
	int	i;
	int	a;

	i = game->index_start_map;
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) > (size_t)game->size.width)
			game->size.width = (int)ft_strlen(game->map[i]);
		a = -1;
		while (game->map[i][++a])
		{
			if (game->map[i][a] == ' ')
				game->map[i][a] = '2';
		}
		i++;
	}
	game->size.height = (i - game->index_start_map);
}

char	**copy_map_and_set_1(t_map *game)
{
	char	**tmp_map;

	ft_set_width_height_and_1(game);
	tmp_map = (char **)malloc(sizeof(char *) * (game->size.height + 1));
	if (!tmp_map)
	{
		write (2, "Error\nMalloc Error in fill map\n", 31);
		free_n_exit(game);
	}
	tmp_map[game->size.height] = NULL;
	return (tmp_map);
}

char	*ft_copy_line(t_map *game, int j)
{
	char	*tmp_map;

	tmp_map = (char *)malloc(sizeof(char) * (game->size.width + 1));
	if (!tmp_map)
	{
		write(2, "Error\nMalloc tmp_map[i] in ft_fill_map..\n", 41);
		free_n_exit(game);
	}
	tmp_map[game->size.width] = '\0';
	ft_strlcpy(tmp_map, game->map[j], ft_strlen(game->map[j]));
	return (tmp_map);
}

void	ft_copy(t_map *game, char **tmp_map)
{
	int	i;

	i = 0;
	ft_free_double(game->map);
	game->map = (char **)malloc(sizeof(char *) * (game->size.height + 1));
	if (!game->map)
	{
		write(2, "Error\nMalloc in copy_map failed\n", 32);
		free_n_exit(game);
	}
	game->map[game->size.height] = NULL;
	while (tmp_map[i])
	{
		game->map[i] = ft_strdup(tmp_map[i]);
		i++;
	}
	ft_free_double(tmp_map);
}

void	ft_fill_map(t_map *game)
{
	char	**tmp_map;
	int		i;
	int		j;

	i = 0;
	j = game->index_start_map;
	tmp_map = copy_map_and_set_1(game);
	while (game->map[j])
	{
		tmp_map[i] = ft_copy_line(game, j);
		ft_set_1(tmp_map, game->map[j],
			(game->size.width - (int)ft_strlen(game->map[j])), i);
		i++;
		j++;
	}
	ft_copy(game, tmp_map);
}
