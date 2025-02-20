/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:55:06 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/10 11:14:28 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_map_exetension(char *map_file)
{
	char *start;

	start = &map_file[ft_strlen(map_file) - 4];
	if ((ft_strncmp(start, ".ber", 4) != 0))
	{
		ft_error("Error\nMap not found dummy 🌍");
		exit(EXIT_FAILURE);
	}
}

