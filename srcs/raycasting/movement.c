/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:03:51 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/01 12:20:47 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_wich_key(t_map *game, double *newplayerx, double *newplayery)
{
	if (mlx_is_key_down(game->mlx->main, MLX_KEY_W))
	{
		*newplayerx += game->mlx->dirx * 0.1;
		*newplayery += game->mlx->diry * 0.1;
	}
	if (mlx_is_key_down(game->mlx->main, MLX_KEY_S))
	{
		*newplayerx -= game->mlx->dirx * 0.1;
		*newplayery -= game->mlx->diry * 0.1;
	}
	if (mlx_is_key_down(game->mlx->main, MLX_KEY_D))
	{
		*newplayerx += game->mlx->diry * 0.1;
		*newplayery -= game->mlx->dirx * 0.1;
	}
	if (mlx_is_key_down(game->mlx->main, MLX_KEY_A))
	{
		*newplayerx -= game->mlx->diry * 0.1;
		*newplayery += game->mlx->dirx * 0.1;
	}
}

void	ft_movement(t_map *game)
{
	int		newmapx;
	int		newmapy;
	double	newplayerx;
	double	newplayery;

	newplayerx = game->player.x_pos;
	newplayery = game->player.y_pos;
	ft_wich_key(game, &newplayerx, &newplayery);
	newmapx = (int)(newplayerx);
	newmapy = (int)(newplayery);
	if (game->map[newmapy][newmapx] != '1'
		&& game->map[newmapy][newmapx] != '2')
	{
		game->player.x_pos = newplayerx;
		game->player.y_pos = newplayery;
	}
}

void	ft_turn_head_left(t_map *game)
{
	double	olddirx;
	double	oldplanex;

	if (mlx_is_key_down(game->mlx->main, MLX_KEY_LEFT))
	{
		olddirx = game->mlx->dirx;
		game->mlx->dirx = game->mlx->dirx * cos(game->mlx->rotspeed)
			- game->mlx->diry * sin(game->mlx->rotspeed);
		game->mlx->diry = olddirx * sin(game->mlx->rotspeed) + game->mlx->diry
			* cos(game->mlx->rotspeed);
		oldplanex = game->mlx->planex;
		game->mlx->planex = game->mlx->planex * cos(game->mlx->rotspeed)
			- game->mlx->planey * sin(game->mlx->rotspeed);
		game->mlx->planey = oldplanex * sin(game->mlx->rotspeed)
			+ game->mlx->planey * cos(game->mlx->rotspeed);
	}
}

void	ft_turn_head_right(t_map *game)
{
	double	olddirx;
	double	oldplanex;

	if (mlx_is_key_down(game->mlx->main, MLX_KEY_RIGHT))
	{
		olddirx = game->mlx->dirx;
		game->mlx->dirx = game->mlx->dirx * cos(-game->mlx->rotspeed)
			- game->mlx->diry * sin(-game->mlx->rotspeed);
		game->mlx->diry = olddirx * sin(-game->mlx->rotspeed) + game->mlx->diry
			* cos(-game->mlx->rotspeed);
		oldplanex = game->mlx->planex;
		game->mlx->planex = game->mlx->planex * cos(-game->mlx->rotspeed)
			- game->mlx->planey * sin(-game->mlx->rotspeed);
		game->mlx->planey = oldplanex * sin(-game->mlx->rotspeed)
			+ game->mlx->planey * cos(-game->mlx->rotspeed);
	}
}

void	ft_hook(void *param)
{
	t_map	*game;

	game = (t_map *)param;
	if (mlx_is_key_down(game->mlx->main, MLX_KEY_ESCAPE))
	{
		free_mlx(game);
		free_n_exit(game);
	}
	ft_movement(game);
	ft_turn_head_left(game);
	ft_turn_head_right(game);
	mlx_delete_image(game->mlx->main, game->mlx->image);
	game->mlx->image = mlx_new_image(game->mlx->main, game->size.screen_width,
			game->size.screen_height);
	mlx_image_to_window(game->mlx->main, game->mlx->image, 0, 0);
	ft_affichage(game);
}
