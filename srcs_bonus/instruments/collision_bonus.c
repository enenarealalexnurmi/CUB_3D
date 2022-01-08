/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 07:55:51 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 18:39:39 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruments_bonus.h"

void	collision(t_game_master *gm)
{
	static float	old_x;
	static float	old_y;
	static t_bool	check = false;

	if (!(check))
	{
		old_x = gm->pl->x;
		old_y = gm->pl->y;
		check = true;
	}
	else
	{
		if (ft_strchr(SOLID_CHAR,
				gm->map->yx[(int)(gm->pl->y)][(int)(gm->pl->x)]))
		{
			gm->pl->x = old_x;
			gm->pl->y = old_y;
		}
		check = false;
	}
}
