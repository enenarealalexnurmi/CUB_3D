/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruments_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:50:09 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 17:43:29 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUMENTS_BONUS_H
# define INSTRUMENTS_BONUS_H
# include <math.h>
# include "libft.h"
# include "defines_bonus.h"
# include "structs_bonus.h"
# include "error_handling_bonus.h"

/*
** common_things_part_1
*/

void	put_pxl_to_img(t_image *data, int x, int y, t_uint clr);
t_uint	get_color_from_img(t_image *data, int x, int y);
void	calculate_edge_wall(t_ray *ray, t_game_master *gm);

t_bool	get_table(float ***table);
void	rotate(float *x, float *y, float *table);
void	rotate_ninety(float *x, float *y, t_dir_rotate dir);

void	draw_ceil(t_ray *ray, t_uint *color, t_image *frame);
void	draw_floor(t_ray *ray, t_uint *color, t_image *frame);
void	draw_wall(t_ray *ray, t_wall *wall, t_image *frame);
void	calculate_wall(t_ray *ray, t_game_master *gm);
void	mouse_view(t_game_master *gm);
t_bool	prepare_map_image(t_game_master *gm);
void	map_draw(t_game_master *gm);
void	collision(t_game_master *gm);
t_image	*get_anime(t_anime *an);
void	draw_circle(t_image *data, t_circle *circle);
void	draw_cell(t_game_master *gm, int size, ssize_t y, ssize_t x);

#endif
