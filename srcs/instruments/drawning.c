/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 06:09:48 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 16:16:22 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruments.h"

void	draw_ceil(t_ray *ray, t_uint *color, t_image *frame)
{
	ssize_t	y;
	t_uint	ceil;

	y = -1;
	ceil = *color;
	while (++y < ray->wall_top)
		put_pxl_to_img(frame, ray->ind, y, ceil);
}

void	draw_floor(t_ray *ray, t_uint *color, t_image *frame)
{
	ssize_t	y;
	t_uint	floor;

	y = ray->wall_bot - 1;
	floor = *color;
	while (++y < frame->height)
		put_pxl_to_img(frame, ray->ind, y, floor);
}

void	draw_wall(t_ray *ray, t_wall *wall, t_image *frame)
{
	ssize_t	y;
	t_uint	color;

	y = ray->wall_top - 1;
	while (++y < ray->wall_bot)
	{
		wall->texture_y = (int)wall->y;
		wall->y += wall->step_y;
		color = 0x00FFFFFF
			& get_color_from_img(wall->texture, wall->texture_x,
				wall->texture_y);
		put_pxl_to_img(frame, ray->ind, y, color);
	}
}
