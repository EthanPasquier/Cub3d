/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:05:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/01 12:15:15 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_calculate_camera(t_map *game, int x, double w)
{
	game->mlx->camerax = 2 * x / w - 1;
	game->mlx->raydirx = game->mlx->dirx + game->mlx->planex
		* game->mlx->camerax;
	game->mlx->raydiry = game->mlx->diry + game->mlx->planey
		* game->mlx->camerax;
	game->mlx->mapy = (int)game->player.y_pos;
	game->mlx->mapx = (int)game->player.x_pos;
	if (game->mlx->raydirx == 0)
		game->mlx->deltadistx = 1e30;
	else
		game->mlx->deltadistx = fabs(1 / game->mlx->raydirx);
	if (game->mlx->raydiry == 0)
		game->mlx->deltadisty = 1e30;
	else
		game->mlx->deltadisty = fabs(1 / game->mlx->raydiry);
	game->mlx->hit = 0;
}

void	ft_calculate_raydir(t_map *game)
{
	if (game->mlx->raydirx < 0)
	{
		game->mlx->stepx = -1;
		game->mlx->sidedistx = (game->player.x_pos - game->mlx->mapx)
			* game->mlx->deltadistx;
	}
	else
	{
		game->mlx->stepx = 1;
		game->mlx->sidedistx = (game->mlx->mapx + 1.0 - game->player.x_pos)
			* game->mlx->deltadistx;
	}
	if (game->mlx->raydiry < 0)
	{
		game->mlx->stepy = -1;
		game->mlx->sidedisty = (game->player.y_pos - game->mlx->mapy)
			* game->mlx->deltadisty;
	}
	else
	{
		game->mlx->stepy = 1;
		game->mlx->sidedisty = (game->mlx->mapy + 1.0 - game->player.y_pos)
			* game->mlx->deltadisty;
	}
}

void	ft_calculate_dda(t_map *game)
{
	while (game->mlx->hit == 0)
	{
		if (game->mlx->sidedistx < game->mlx->sidedisty)
		{
			game->mlx->sidedistx += game->mlx->deltadistx;
			game->mlx->mapx += game->mlx->stepx;
			game->mlx->side = 0;
		}
		else
		{
			game->mlx->sidedisty += game->mlx->deltadisty;
			game->mlx->mapy += game->mlx->stepy;
			game->mlx->side = 1;
		}
		if (game->map[game->mlx->mapy][game->mlx->mapx] == '1'
			|| game->map[game->mlx->mapy][game->mlx->mapx] == '2')
			game->mlx->hit = 1;
	}
}

void	ft_calculate_distance(t_map *game)
{
	if (game->mlx->side == 0)
		game->mlx->perpwalldist = (game->mlx->sidedistx
				- game->mlx->deltadistx);
	else
		game->mlx->perpwalldist = (game->mlx->sidedisty
				- game->mlx->deltadisty);
	game->mlx->h = game->size.screen_height;
	game->mlx->lineheight = (int)(game->mlx->h / game->mlx->perpwalldist);
	game->mlx->drawstart = -game->mlx->lineheight / 2 + game->mlx->h / 2;
	if (game->mlx->drawstart < 0)
		game->mlx->drawstart = 0;
	game->mlx->drawend = game->mlx->lineheight / 2 + game->mlx->h / 2;
	if (game->mlx->drawend >= game->mlx->h)
		game->mlx->drawend = game->mlx->h - 1;
}
