/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:47:31 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/17 16:18:09 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 250);
}

bool	ft_check_split(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		i++;
	}
	if (ft_strlen(str) >= 10)
		return (false);
	return (true);
}

bool	ft_convert_number(char **split, t_map *game, char check)
{
	if ((ft_atoi(split[0]) > 255 || ft_atoi(split[0]) < 0)
		|| (ft_atoi(split[1]) > 255 || ft_atoi(split[1]) < 0)
		|| (ft_atoi(split[2]) > 255 || ft_atoi(split[2]) < 0))
	{
		ft_free_double(split);
		return (false);
	}
	if (check == 'C')
	{
		game->rgb_ceilling = rgb_to_int(ft_atoi(split[0]), ft_atoi(split[1]),
				ft_atoi(split[2]));
	}
	else if (check == 'F')
	{
		game->rgb_floor = rgb_to_int(ft_atoi(split[0]), ft_atoi(split[1]),
				ft_atoi(split[2]));
	}
	return (true);
}

bool	ft_check_number(char *str, char check, t_map *game)
{
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	if (!split)
		return (ft_error_rgb(check));
	while (split[i])
	{
		tmp = ft_strtrim(split[i], " \n\t");
		free(split[i]);
		split[i] = ft_strdup(tmp);
		free(tmp);
		if (ft_check_split(split[i]) == false)
		{
			ft_free_double(split);
			return (ft_error_rgb(check));
		}
		i++;
	}
	if (ft_convert_number(split, game, check) == false)
		return (ft_error_rgb(check));
	ft_free_double(split);
	return (true);
}

bool	ft_check_comma(char *str, char check)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		if (check == 'F')
			write(2, "Error\nProblem with RGB color of F.\n", 35);
		else if (check == 'C')
			write(2, "Error\nProblem with RGB color of C.\n", 35);
		return (false);
	}
	return (true);
}
