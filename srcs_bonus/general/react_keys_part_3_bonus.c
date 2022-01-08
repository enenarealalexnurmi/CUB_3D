/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   react_keys_part_3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 02:23:41 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 21:24:04 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_bonus.h"

int	look_up(void *pgm)
{
	t_game_master	*gm;

	gm = pgm;
	gm->render->horizon -= 10;
	if (gm->render->horizon < 0)
		gm->render->horizon = 0;
	gm->render->need = true;
	return (0);
}

int	look_down(void *pgm)
{
	t_game_master	*gm;

	gm = pgm;
	gm->render->horizon += 10;
	if (gm->render->horizon > gm->frame->height)
		gm->render->horizon = gm->frame->height;
	gm->render->need = true;
	return (0);
}

int	use_map(void *pgm)
{
	t_game_master		*gm;

	gm = pgm;
	if (gm->map->map_on == off)
	{
		gm->map->map_on = mini;
		gm->map->prev = off;
	}
	else if (gm->map->map_on == mini && gm->map->prev == off)
		gm->map->map_on = on;
	else if (gm->map->map_on == mini && gm->map->prev == on)
		gm->map->map_on = off;
	else if (gm->map->map_on == on)
	{
		gm->map->map_on = mini;
		gm->map->prev = on;
	}
	gm->render->need = true;
	return (0);
}

int	action(void *pgm)
{
	t_game_master	*gm;
	int				look_y;
	int				look_x;
	char			*look;

	gm = pgm;
	look_y = (int)(gm->pl->y + gm->pl->dir_y);
	look_x = (int)(gm->pl->x + gm->pl->dir_x);
	look = &(gm->map->yx[look_y][look_x]);
	if (*look == 'D')
		*look = 'd';
	else if (*look == 'd')
		*look = 'D';
	draw_cell(gm, gm->map->size, look_y, look_x);
	gm->render->need = true;
	return (0);
}
