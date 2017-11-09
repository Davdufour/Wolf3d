/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:22:34 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/14 12:54:47 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

void	cardinal_points(t_w *w, int x, t_thrd *thrd, int y)
{
	if (thrd->side == 0)
	{
		if ((thrd->raydirx >= 0.0 && thrd->raydiry < 0.0) ||
			(thrd->raydirx >= 0.0 && thrd->raydiry >= 0.0))
			mlx_put_pixel(w->m->image, x, y, ft_add_color(0xFFFF00,
			0x000000, get_alpha(w->e->shadow, thrd->perpwalldist)));
		else
			mlx_put_pixel(w->m->image, x, y, ft_add_color(0xCC00FF,
			0x000000, get_alpha(w->e->shadow, thrd->perpwalldist)));
	}
	else
	{
		if ((thrd->raydirx >= 0.0 && thrd->raydiry < 0.0) ||
			(thrd->raydirx < 0.0 && thrd->raydiry < 0.0))
			mlx_put_pixel(w->m->image, x, y, ft_add_color(0x33CC00,
			0x000000, get_alpha(w->e->shadow, thrd->perpwalldist)));
		else
			mlx_put_pixel(w->m->image, x, y, ft_add_color(0xFF6633,
			0x000000, get_alpha(w->e->shadow, thrd->perpwalldist)));
	}
}

void	init_text(t_w *w)
{
	w->e->sky = mlx_xpm_file_to_image(w->m->mlx, "texture/trapdoor.xpm",
										&w->e->ftex, &w->e->ftex);
	w->e->floor = mlx_xpm_file_to_image(w->m->mlx,
			"texture/wool_colored_silver.xpm", &w->e->ftex, &w->e->ftex);
	w->e->wall = mlx_xpm_file_to_image(w->m->mlx, "texture/glass_cyan.xpm",
										&w->e->tex, &w->e->tex);
}

void	foncnull(void *s, int keycode)
{
	(void)s;
	(void)keycode;
}

void	echap(void *s, int keycode)
{
	(void)s;
	(void)keycode;
	ft_exit(0, "lol");
}

int		exit_prog(t_w *w)
{
	(void)w;
	ft_exit(0, "lol");
	return (1);
}
