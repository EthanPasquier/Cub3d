/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:08:53 by jalevesq          #+#    #+#             */
/*   Updated: 2023/06/01 10:55:37 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_background(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->size.screen_height / 2)
	{
		j = 0;
		while (j < game->size.screen_width)
		{
			mlx_put_pixel(game->mlx->background, j, i, game->rgb_ceilling);
			j++;
		}
		i++;
	}
	while (i < game->size.screen_height)
	{
		j = 0;
		while (j < game->size.screen_width)
		{
			mlx_put_pixel(game->mlx->background, j, i, game->rgb_floor);
			j++;
		}
		i++;
	}
}

void	ft_change_draw(t_map *game)
{
	if (game->mlx->drawstart < game->mlx->drawend)
		game->mlx->drawstart++;
	else if (game->mlx->drawstart > game->mlx->drawend)
		game->mlx->drawstart--;
}

void	ft_put_pixel(t_map *game, int mode, int texx, int x)
{
	int		color;
	int		texy;
	double	texpos;
	double	step;

	step = 1.0 * game->texture->all_xpm[mode]->texture.height
		/ game->mlx->lineheight;
	texpos = (game->mlx->drawstart - game->size.screen_height / 2
			+ game->mlx->lineheight / 2) * step;
	while (game->mlx->drawstart != game->mlx->drawend)
	{
		ft_change_draw(game);
		texy = (int)texpos & (game->texture->all_xpm[mode]->texture.width - 1);
		texpos += step;
		if (texy >= 0 && texy < (int)game->texture->all_xpm[mode]->texture.width
			&& texx >= 0
			&& texx < (int)game->texture->all_xpm[mode]->texture.height)
		{
			color = game->texture->get_pixel[mode].tab[texy][texx];
			mlx_put_pixel(game->mlx->image, x, game->mlx->drawstart, color);
		}
	}
}

void	ft_drawline(int x, t_map *game, int mode)
{
	int		texx;
	double	wallx;

	if (game->mlx->side == 0)
		wallx = game->player.y_pos + game->mlx->perpwalldist
			* game->mlx->raydiry;
	else
		wallx = game->player.x_pos + game->mlx->perpwalldist
			* game->mlx->raydirx;
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)game->texture->all_xpm[mode]->texture.width);
	if (game->mlx->side == 0 && game->mlx->raydirx > 0)
		texx = game->texture->all_xpm[mode]->texture.width - texx - 1;
	if (game->mlx->side == 1 && game->mlx->raydiry < 0)
		texx = game->texture->all_xpm[mode]->texture.width - texx - 1;
	ft_put_pixel(game, mode, texx, x);
}

void	ft_wich_side(int x, t_map *game)
{
	if (game->mlx->side == 0)
	{
		if (game->mlx->stepx == -1)
			ft_drawline(x, game, EAST);
		else
			ft_drawline(x, game, WEST);
	}
	else if (game->mlx->side == 1)
	{
		if (game->mlx->stepy == -1)
			ft_drawline(x, game, NORTH);
		else
			ft_drawline(x, game, SOUTH);
	}
}
