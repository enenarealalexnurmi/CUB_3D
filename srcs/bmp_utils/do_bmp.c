/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 23:04:27 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 21:13:27 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"
#include "bmp_utils.h"

void	do_bmp_from_frame(t_game_master *gm, const char *map_name)
{
	const int	width = ((t_res *)gm->sl->link[resolution].get)->width;
	const int	height = ((t_res *)gm->sl->link[resolution].get)->height;
	char		*filename;
	char		*real_name;
	char		*tmp;

	if ((width > BMP_MAX_DIMENSION) || (height > BMP_MAX_DIMENSION))
	{
		error_handler(err_too_big_save_bmp);
		escape_deal(gm);
	}
	render_frame(gm);
	tmp = ft_strrchr(map_name, '/');
	if (tmp)
	{
		tmp++;
		real_name = ft_substr(map_name, tmp - map_name, ft_strlen(tmp));
	}
	else
		real_name = ft_strdup(map_name);
	if (!(put_name_screenshot(&filename, real_name, gm->frame))
		|| !(save_image_as_bmp(gm->frame, filename)))
		escape_deal(gm);
	real_name = ft_sec_free(real_name);
	exit_ok(gm);
}
