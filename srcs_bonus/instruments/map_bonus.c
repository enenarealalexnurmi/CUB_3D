/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 22:18:40 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 21:27:17 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruments_bonus.h"
#include "initialization_bonus.h"

static t_uint	took_color(t_game_master *gm, ssize_t y, ssize_t x)
{
	t_uint	clr;

	clr = 0x44000000;
	if (gm->map->yx[y][x] == '1')
		clr = 0x44FFFFFF;
	if (gm->map->yx[y][x] == '2')
		clr = 0x44F000FF;
	if (gm->map->yx[y][x] == 'd')
		clr = 0x4400FF00;
	if (gm->map->yx[y][x] == 'D')
		clr = 0x44FF0000;
	return (clr);
}

void	draw_cell(t_game_master *gm, int size, ssize_t y, ssize_t x)
{
	t_uint	fill_clr;
	t_uint	clr;
	int		y_l;
	int		x_l;

	fill_clr = took_color(gm, y, x);
	if (fill_clr != 0x44000000)
	{
		y_l = 0;
		while (y_l < size)
		{
			x_l = 0;
			while (x_l < size)
			{
				clr = fill_clr & ~(0xFF444444 * (y_l == 0 || x_l == 0
							|| y_l == size || x_l == size));
				put_pxl_to_img(gm->map->big, x * size + y_l,
					y * size + x_l, clr);
				put_pxl_to_img(gm->map->mini, x * size / MNMAP + y_l / MNMAP,
					y * size / MNMAP + x_l / MNMAP, clr);
				x_l++;
			}
			y_l++;
		}
	}
}

static t_bool	adding_player_dot(t_game_master *gm, int size)
{
	void		*img_ptr;
	t_circle	mini;
	t_circle	big;

	img_ptr = mlx_new_image(gm->mlx, size, size, 0xFF000000);
	if (!(img_ptr))
		return (error_handler(err_new_image_fail));
	gm->map->bigdot = get_image(img_ptr, size, size);
	img_ptr = mlx_new_image(gm->mlx, size / MNMAP, size / MNMAP, 0xFF000000);
	if (!(img_ptr))
		return (error_handler(err_new_image_fail));
	gm->map->minidot = get_image(img_ptr, size / MNMAP, size / MNMAP);
	mini.clr = 0x000000FF;
	big.clr = 0x000000FF;
	mini.x = size / MNMAP / 2;
	big.x = size / 2;
	mini.y = size / MNMAP / 2;
	big.y = size / 2;
	mini.r = size / MNMAP / 2;
	big.r = size / 2;
	draw_circle(gm->map->bigdot, &big);
	draw_circle(gm->map->minidot, &mini);
	return (true);
}

static t_bool	finish_prepare_map(t_game_master *gm)
{
	int		c_h;
	int		c_w;
	ssize_t	i_h;
	ssize_t	i_w;

	c_h = (((t_res *)gm->sl->link[resolution].get)->height - (2 * BRD))
		/ (gm->map->mx_y + 1);
	c_w = (((t_res *)gm->sl->link[resolution].get)->width - (2 * BRD))
		/ (gm->map->mx_x + 1);
	if (c_w < c_h)
		gm->map->size = c_w;
	else
		gm->map->size = c_w;
	gm->map->size -= gm->map->size % 2;
	i_h = -1;
	i_w = -1;
	if (!(adding_player_dot(gm, gm->map->size)))
		return (false);
	while (++i_h <= gm->map->mx_y)
	{
		while (++i_w <= gm->map->mx_x)
			draw_cell(gm, gm->map->size, i_h, i_w);
		i_w = -1;
	}
	return (true);
}

t_bool	prepare_map_image(t_game_master *gm)
{
	void	*img_ptr;

	img_ptr = mlx_new_image(gm->mlx,
			((t_res *)gm->sl->link[resolution].get)->width - (2 * BRD),
			((t_res *)gm->sl->link[resolution].get)->height - (2 * BRD),
			0x44000000);
	if (!(img_ptr))
		return (error_handler(err_new_image_fail));
	gm->map->big = get_image(img_ptr,
			((t_res *)gm->sl->link[resolution].get)->width - (2 * BRD),
			((t_res *)gm->sl->link[resolution].get)->height - (2 * BRD));
	img_ptr = mlx_new_image(gm->mlx,
			(((t_res *)gm->sl->link[resolution].get)->width
				- (2 * BRD)) / MNMAP,
			(((t_res *)gm->sl->link[resolution].get)->height
				- (2 * BRD)) / MNMAP,
			0x44000000);
	if (!(img_ptr))
		return (error_handler(err_new_image_fail));
	gm->map->mini = get_image(img_ptr,
			(((t_res *)gm->sl->link[resolution].get)->width
				- (2 * BRD)) / MNMAP,
			(((t_res *)gm->sl->link[resolution].get)->height
				- (2 * BRD)) / MNMAP);
	return (finish_prepare_map(gm));
}
