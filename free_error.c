/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:37:23 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/08 15:27:20 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	free_map(s_info **data)
{
	int	i;

	i = 0;
	while (i < (*data)->column)
	{
		free((*data)->map[i]);
		i++;
	}
	free((*data)->map);
}

void free_error(s_info *data, char *msg)
{
	free(data);
	write(2, "Error\n", 6);
	ft_error(msg);
}

