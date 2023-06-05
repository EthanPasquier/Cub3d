/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:43:50 by jalevesq          #+#    #+#             */
/*   Updated: 2023/05/31 11:13:36 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_error_texture(int count, char *direction)
{
	if (count == 0)
		write(2, "Error\nDid not find texture for: ", 32);
	else if (count > 1)
		write(2, "Error\nFound more than one texture for: ", 39);
	write(2, direction, ft_strlen(direction));
	write(2, ".\n", 2);
}

bool	ft_error_rgb(char check)
{
	write(2, "Error in RGB number of: ", 24);
	write(2, &check, 1);
	write(2, ".\n", 2);
	return (false);
}

bool	ft_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	return (false);
}

bool	ft_error_character(char c, int i)
{
	char	*nbr;

	nbr = ft_itoa(i + 1);
	write(2, "Error\nCharacter (", 17);
	write(2, &c, 1);
	write(2, ") not recognize at line ", 24);
	write(2, nbr, ft_strlen(nbr));
	write(2, ".\n", 2);
	free(nbr);
	return (false);
}
