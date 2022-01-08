/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anime_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enena <enena@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:57:40 by enena             #+#    #+#             */
/*   Updated: 2022/01/08 17:35:28 by enena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization_bonus.h"

static t_image	*get_anime_frame(char *text_name, t_setting_link *link)
{
	t_bool	is_png;
	void	*img_ptr;
	int		width;
	int		height;

	is_png = ft_check_extention(text_name, TEXTURE_PNG_EXTN);
	if (!((ft_check_extention(text_name, TEXTURE_XPM_EXTN)) || (is_png)))
	{
		setting_error(link->idntf, err_bad_extention_texture);
		return (NULL);
	}
	if (is_png)
		img_ptr = mlx_png_file_to_image(((t_game_master *)link->backlink)->mlx,
				text_name, &width, &height);
	else
		img_ptr = mlx_xpm_file_to_image(((t_game_master *)link->backlink)->mlx,
				text_name, &width, &height);
	if (!(img_ptr))
	{
		setting_error(link->idntf, err_convert_texture);
		return (NULL);
	}
	return (get_image(img_ptr, width, height));
}

static t_bool	fill_anime(t_anime *an, char *name_fold, char *extn,
			t_setting_link *link)
{
	size_t	i;
	char	*tmp;
	char	*text_name;

	i = 0;
	while (i < an->count)
	{
		tmp = ft_itoa((int)i);
		text_name = ft_strjoin(tmp, extn);
		tmp = ft_sec_free(tmp);
		tmp = text_name;
		text_name = ft_strjoin(name_fold, tmp);
		tmp = ft_sec_free(tmp);
		an->anime[i] = get_anime_frame(text_name, link);
		if (!(an->anime[i]))
			return (false);
		i++;
	}
	return (true);
}

t_bool	set_anime(void *plink, char **tab)
{
	t_setting_link	*link;
	t_anime			*an;

	link = plink;
	if (ft_tab_size(tab) != link->cnt_fields)
		return (setting_error(link->idntf, err_wrong_count_fields));
	if (!(ft_isanum(tab[1])) || !(ft_isanum(tab[1]))
		|| tab[1][0] == '-' || tab[4][0] == '-')
		return (setting_error(link->idntf, err_wrong_information));
	an = malloc(sizeof(t_anime));
	if (!(an))
		return (error_handler(err_alloc_fail));
	an->count = (size_t)ft_atoll(tab[1]);
	an->cur_frame = 0;
	an->speed = (size_t)ft_atoll(tab[4]);
	an->anime = malloc(sizeof(t_image *) * an->count);
	if (!(an->anime))
		return (error_handler(err_alloc_fail));
	if (!(fill_anime(an, tab[2], tab[3], link)))
		return (false);
	link->get = an;
	link->destroy = &free_anime;
	return (link->is_set = true);
}

t_image	*get_anime(t_anime *an)
{
	t_image			*ret;
	static size_t	upd = 0;

	upd++;
	ret = an->anime[an->cur_frame];
	if (upd == an->speed)
	{
		an->cur_frame++;
		if (an->cur_frame == an->count)
			an->cur_frame = 0;
		upd = 0;
	}
	return (ret);
}
