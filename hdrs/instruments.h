/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruments.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:50:09 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 16:15:57 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUMENTS_H
# define INSTRUMENTS_H
# include "libft.h"
# include "defines.h"
# include "structs.h"
# include "error_handling.h"
# include <math.h>

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

#endif
