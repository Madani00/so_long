/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:55:06 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/08 11:37:44 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_map_exetension(char *map_file)
{
	if (!(ft_strnstr(map_file, ".ber", ft_strlen(map_file))))
	{
		ft_error("Error\nMap not found dummy 🗾");
		exit(EXIT_FAILURE);
	}
}

