/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calculate_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:15:16 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 17:35:03 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite_bonus.h"

static void	calc_sprite(t_sprite *sp, t_player *pl, t_image *frame)
{
	float	sprite_x;
	float	sprite_y;
	float	inv_det;
	float	x_offset;

	sprite_x = sp->x - pl->x;
	sprite_y = sp->y - pl->y;
	inv_det = 1.0 / (pl->pln_x * pl->dir_y - pl->dir_x * pl->pln_y);
	x_offset = inv_det * (pl->dir_y * sprite_x - pl->dir_x * sprite_y)
		* 2.0 / FOV;
	sp->perp_dist = inv_det * (-pl->pln_y * sprite_x + pl->pln_x * sprite_y);
	sp->cntr = (int)((frame->width / 2) * (1 + x_offset / sp->perp_dist));
	sp->height = (int)(fabs(frame->width / FOV / sp->perp_dist));
	calculate_edge_sprite(sp, frame->height, sp->height);
	sp->width = (int)(fabs(frame->width / FOV / sp->perp_dist));
	sp->x_draw_begin = sp->cntr - sp->width / 2;
	if (sp->x_draw_begin < 0)
		sp->x_draw_begin = 0;
	sp->x_draw_end = sp->cntr + sp->width / 2;
	if (sp->x_draw_end >= frame->width)
		sp->x_draw_end = frame->width;
}

void	calculate_sprites(t_sprite ***arr, t_player *pl,
			ssize_t count_s, t_image *frame)
{
	ssize_t			i;
	static float	sort_prev_x = -1.0;
	static float	sort_prev_y = -1.0;

	if (fabs(sort_prev_x - pl->x) >= 0.5 || fabs(sort_prev_y - pl->y) >= 0.5)
	{
		i = -1;
		while (++i < count_s)
			(*arr)[i]->dist_pow2 = pow((pl->x - (*arr)[i]->x), 2)
				+ pow((pl->y - (*arr)[i]->y), 2);
		improve_quick_sort(arr, 0, count_s - 1);
		sort_prev_x = pl->x;
		sort_prev_y = pl->y;
	}
	i = -1;
	while (++i < count_s)
		calc_sprite((*arr)[i], pl, frame);
}

void	calculate_edge_sprite(t_sprite *sp, int max, int value)
{
	int	half_value;

	half_value = value / 2;
	sp->y_draw_begin = *(sp->horizon) - half_value;
	if (sp->y_draw_begin < 0)
		sp->y_draw_begin = 0;
	sp->y_draw_end = *(sp->horizon) + half_value;
	if (sp->y_draw_end > max)
		sp->y_draw_end = max;
}

void	draw_sprite(t_sprite *sprt, t_ray *rays, t_image *texture,
			t_image *frame)
{
	ssize_t	yx[2];
	int		tex_yx[2];
	int		d;
	t_uint	color;

	yx[1] = sprt->x_draw_begin - 1;
	while (++yx[1] < sprt->x_draw_end)
	{
		tex_yx[1] = (int)(yx[1] - (sprt->cntr - sprt->width / 2));
		tex_yx[1] = tex_yx[1] * texture->width / sprt->width;
		if (sprt->perp_dist > 0.1 && sprt->perp_dist < rays[yx[1]].perp_dist)
		{
			yx[0] = sprt->y_draw_begin - 1;
			while (++yx[0] < sprt->y_draw_end + 0)
			{
				d = 2 * yx[0] + sprt->height - 2 * (*(sprt->horizon));
				tex_yx[0] = ((d * texture->height) / (sprt->height)) / 2;
				color = get_color_from_img(texture, tex_yx[1], tex_yx[0]);
				if ((color & 0xFF000000) == 0)
					put_pxl_to_img(frame, yx[1], yx[0], color);
			}
		}
	}
}
