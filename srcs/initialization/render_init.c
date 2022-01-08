/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 07:04:13 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 16:12:55 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

static void	ray_init(t_ray *ray)
{
	ray->dir_x = 0.0;
	ray->dir_y = 0.0;
	ray->delt_x = 0.0;
	ray->delt_y = 0.0;
	ray->dist_x = 0.0;
	ray->dist_y = 0.0;
	ray->perp_dist = 0.0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = false;
	ray->side = n_s;
}

static void	wall_init(t_wall *wall)
{
	wall->texture = NULL;
	wall->texture_x = 0;
	wall->texture_y = 0;
	wall->x = 0.0;
	wall->y = 0.0;
	wall->step_y = 0.0;
	wall->height = 0;
}

static t_bool	render_alloc(t_render **prender, const int width)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!(render))
		return (error_handler(err_alloc_fail));
	render->rays = malloc(width * sizeof(t_ray));
	if (!(render->rays))
		return (error_handler(err_alloc_fail));
	render->wall = malloc(sizeof(t_wall));
	if (!(render->wall))
		return (error_handler(err_alloc_fail));
	wall_init(render->wall);
	render->cubed = (float)width / FOV;
	render->need = true;
	*prender = render;
	return (true);
}

t_bool	render_init(t_game_master *gm)
{
	const int	width = ((t_res *)gm->sl->link[resolution].get)->width;
	const int	height = ((t_res *)gm->sl->link[resolution].get)->height;
	ssize_t		i;

	if (!(render_alloc(&gm->render, width)))
		return (false);
	i = -1;
	gm->render->horizon = height / 2;
	while (++i < width)
	{
		ray_init(&gm->render->rays[i]);
		gm->render->rays[i].ind = i;
		gm->render->rays[i].x = (int)gm->pl->x;
		gm->render->rays[i].y = (int)gm->pl->y;
		gm->render->rays[i].sclrcam = ((i + 1) / (float)width - 0.5) * FOV;
		gm->render->rays[i].horizon = &(gm->render->horizon);
		gm->render->rays[i].last_top = 0;
		gm->render->rays[i].last_bot = height;
	}
	return (true);
}
