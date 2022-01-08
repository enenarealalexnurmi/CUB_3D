/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_settings_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:34:35 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 18:43:39 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization_bonus.h"

static int	restr_value(long long int value)
{
	if (value > INT_MAX || value == -1)
		return (INT_MAX);
	else
		return ((int)value);
}

t_bool	set_resolution(void *plink, char **tab)
{
	t_setting_link	*link;
	long long int	width;
	long long int	height;

	link = plink;
	if (ft_tab_size(tab) != link->cnt_fields)
		return (setting_error(link->idntf, err_wrong_count_fields));
	if (!(ft_isanum(tab[1])) || !(ft_isanum(tab[2])))
		return (setting_error(link->idntf, err_wrong_information));
	if (tab[1][0] == '-' || tab[2][0] == '-')
		return (setting_error(link->idntf, err_wrong_information));
	width = ft_atoll(tab[1]);
	height = ft_atoll(tab[2]);
	link->get = malloc(sizeof(t_res));
	if (!(link->get))
		return (error_handler(err_alloc_fail));
	((t_res *)link->get)->width = restr_value(width);
	((t_res *)link->get)->height = restr_value(height);
	link->destroy = &free_resolution;
	return (link->is_set = true);
}

t_bool	set_texture(void *plink, char **tab)
{
	t_setting_link	*link;
	t_bool			is_png;
	void			*img_ptr;
	int				width;
	int				height;

	link = plink;
	if (ft_tab_size(tab) != link->cnt_fields)
		return (setting_error(link->idntf, err_wrong_count_fields));
	is_png = ft_check_extention(tab[1], TEXTURE_PNG_EXTN);
	if (!((ft_check_extention(tab[1], TEXTURE_XPM_EXTN)) || (is_png)))
		return (setting_error(link->idntf, err_bad_extention_texture));
	if (is_png)
		img_ptr = mlx_png_file_to_image(((t_game_master *)link->backlink)->mlx,
				tab[1], &width, &height);
	else
		img_ptr = mlx_xpm_file_to_image(((t_game_master *)link->backlink)->mlx,
				tab[1], &width, &height);
	if (!(img_ptr))
		return (setting_error(link->idntf, err_convert_texture));
	link->get = get_image(img_ptr, width, height);
	if (!(link->get))
		return (error_handler(err_alloc_fail));
	link->destroy = &free_image;
	return (link->is_set = true);
}

static t_bool	take_rgb(t_uint *rgb, char **rgbt)
{
	rgb[0] = ft_atoi(rgbt[0]);
	rgb[1] = ft_atoi(rgbt[1]);
	rgb[2] = ft_atoi(rgbt[2]);
	if (((rgb[0] > 255) || (rgb[0] < 0)) || ((rgb[1] > 255) || (rgb[1] < 0))
		|| ((rgb[2] > 255) || (rgb[2] < 0)))
		return (false);
	else
		return (true);
}

t_bool	set_color(void *plink, char **tab)
{
	t_setting_link	*link;
	char			**rgbt;
	t_uint			rgb[3];

	link = plink;
	if (ft_tab_size(tab) != link->cnt_fields)
		return (setting_error(link->idntf, err_wrong_count_fields));
	if (ft_charcount(tab[1], ',') != 2)
		return (setting_error(link->idntf, err_wrong_count_comma_color));
	rgbt = ft_split(tab[1], ',');
	if (!(rgbt))
		return (error_handler(err_alloc_fail));
	if (!(ft_isanum(rgbt[0])) || !(ft_isanum(rgbt[1])) || !(ft_isanum(rgbt[2])))
		return (setting_error(link->idntf, err_wrong_information));
	if (!(take_rgb(&(rgb[0]), rgbt)))
		return (setting_error(link->idntf, err_wrong_information));
	rgbt = ft_free_tab(rgbt);
	link->get = malloc(sizeof(t_uint));
	if (!(link->get))
		return (error_handler(err_alloc_fail));
	*((t_uint *)link->get) = ((rgb[0] << 16) & 0x00FF0000)
		| ((rgb[1] << 8) & 0x0000FF00) | (rgb[2] & 0x000000FF);
	link->destroy = &free_color;
	return (link->is_set = true);
}
