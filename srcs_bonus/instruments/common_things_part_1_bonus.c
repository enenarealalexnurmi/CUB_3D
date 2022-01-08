/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_things_part_1_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 23:51:22 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 21:27:02 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruments_bonus.h"

/*
** Puting clr to [x,y] image data
*/

void	put_pxl_to_img(t_image *data, int x, int y, t_uint clr)
{
	char	*dst;
	int		offset;

	offset = y * data->len_line + x * data->bytepp;
	dst = data->addr + offset;
	*(t_uint *)dst = clr;
}

void	draw_circle(t_image *data, t_circle *circle)
{
	int	i_x;
	int	i_y;

	i_x = 0;
	while (i_x < data->width)
	{
		i_y = 0;
		while (i_y < data->height)
		{
			if ((i_x - circle->x) * (i_x - circle->x) + (i_y - circle->y)
				* (i_y - circle->y) < (circle->r * circle->r))
				put_pxl_to_img(data, i_x, i_y, circle->clr);
			i_y++;
		}
		i_x++;
	}
}

t_uint	get_color_from_img(t_image *data, int x, int y)
{
	char	*dst;
	int		offset;

	offset = y * data->len_line + x * data->bytepp;
	dst = data->addr + offset;
	return (*(t_uint *)dst);
}

void	calculate_edge_wall(t_ray *ray, t_game_master *gm)
{
	int	half_value;

	half_value = gm->render->wall->height / 2;
	ray->wall_top = -half_value + gm->render->horizon;
	if (ray->wall_top < 0)
		ray->wall_top = 0;
	ray->wall_bot = half_value + gm->render->horizon;
	if (ray->wall_bot > gm->frame->height)
		ray->wall_bot = gm->frame->height;
}		
