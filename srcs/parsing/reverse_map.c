/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:06:04 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/05 11:11:08 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_find_player(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (ft_strchr("NSWE", game->map[i][j]) != NULL)
			{
				game->player.x_pos = j + 0.5;
				game->player.y_pos = i + 0.5;
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_reverse_map(t_map *game)
{
	int		i;
	int		j;
	int		k;
	char	tmp;

	i = 0;
	while (game->map[i])
	{
		k = ft_strlen(game->map[i]) - 1;
		j = 0;
		while (j < k)
		{
			tmp = game->map[i][j];
			game->map[i][j] = game->map[i][k];
			game->map[i][k] = tmp;
			j++;
			k--;
		}
		i++;
	}
	ft_find_player(game);
}

void	ft_set_ns(t_map *game)
{
	if (game->player.direction == 'E')
	{
		game->mlx->dirx = -1.0;
		game->mlx->diry = 0.0;
		game->mlx->planex = 0.0;
		game->mlx->planey = 0.66;
	}
	else if (game->player.direction == 'W')
	{
		game->mlx->dirx = 1.0;
		game->mlx->diry = 0.0;
		game->mlx->planex = 0.0;
		game->mlx->planey = -0.66;
	}
}

void	ft_set_dir_spawn(t_map *game)
{
	if (game->player.direction == 'N')
	{
		game->mlx->dirx = 0.0;
		game->mlx->diry = -1.0;
		game->mlx->planex = -0.66;
		game->mlx->planey = 0.0;
	}
	else if (game->player.direction == 'S')
	{
		game->mlx->dirx = 0.0;
		game->mlx->diry = 1.0;
		game->mlx->planex = 0.66;
		game->mlx->planey = 0.0;
	}
	else
		ft_set_ns(game);
}
