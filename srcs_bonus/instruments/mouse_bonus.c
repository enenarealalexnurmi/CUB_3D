/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:34:12 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 18:38:55 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruments_bonus.h"
#include "general_bonus.h"

void	mouse_view(t_game_master *gm)
{
	mlx_mouse_get_pos(gm->win, &(gm->mouse_x), &(gm->mouse_y));
	if (gm->mouse_x != gm->frame->width / 2)
	{
		if (((gm->frame->width / 2) - gm->mouse_x) < 0)
			rotate_clockwise(gm);
		else
			rotate_counter_clock(gm);
		mlx_mouse_move(gm->win, gm->frame->width / 2, gm->mouse_y);
	}
	if (gm->mouse_y != gm->frame->height / 2)
	{
		if (((gm->frame->height / 2) - gm->mouse_y) < 0)
			look_up(gm);
		else
			look_down(gm);
	}
	mlx_mouse_move(gm->win, gm->frame->width / 2, gm->frame->height / 2);
	mlx_mouse_hide();
}
