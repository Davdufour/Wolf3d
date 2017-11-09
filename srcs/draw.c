/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:26:34 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/12 15:58:40 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

static	int		wall_tex(t_w *w, int y, t_thrd *thrd)
{
	int		texw;
	int		texh;

	if (thrd->side == 0)
		thrd->wallx = w->e->posy + thrd->perpwalldist * thrd->raydiry;
	else
		thrd->wallx = w->e->posx + thrd->perpwalldist * thrd->raydirx;
	thrd->wallx -= floor(thrd->wallx);
	texw = (int)(thrd->wallx * (double)(w->e->tex));
	if ((thrd->side == 0 && thrd->raydirx > 0) ||
		(thrd->side == 1 && thrd->raydiry < 0))
		texw = (w->e->tex - texw - 1);
	texh = (y * 2 - HEIGHT + thrd->lineheight) *
			(w->e->tex / 2) / thrd->lineheight;
	return (mlx_get_pixel_clr(w->e->wall, texw, texh));
}

static	void	ft_floor_calc_dir(t_thrd *thrd)
{
	if (thrd->side == 0 && thrd->raydirx > 0)
	{
		thrd->floor_wall_x = thrd->mapx;
		thrd->floor_wall_y = thrd->mapy + thrd->wallx;
	}
	else if (thrd->side == 0 && thrd->raydirx < 0)
	{
		thrd->floor_wall_x = thrd->mapx + 1.0;
		thrd->floor_wall_y = thrd->mapy + thrd->wallx;
	}
	else if (thrd->side == 1 && thrd->raydiry > 0)
	{
		thrd->floor_wall_x = thrd->mapx + thrd->wallx;
		thrd->floor_wall_y = thrd->mapy;
	}
	else
	{
		thrd->floor_wall_x = thrd->mapx + thrd->wallx;
		thrd->floor_wall_y = thrd->mapy + 1.0;
	}
}

static	int		floor_tex(t_w *w, int y, void *img, t_thrd *thrd)
{
	double		i;

	if (thrd->side == 0)
		thrd->wallx = w->e->posy + thrd->perpwalldist * thrd->raydiry;
	else
		thrd->wallx = w->e->posx + thrd->perpwalldist * thrd->raydirx;
	thrd->wallx -= floor(thrd->wallx);
	ft_floor_calc_dir(thrd);
	if (y < HEIGHT)
	{
		thrd->dist_draw = HEIGHT / (2.0 * y - HEIGHT);
		i = (thrd->dist_draw - 0.0) / (thrd->perpwalldist - 0.0);
		thrd->floor_x_draw = i * thrd->floor_wall_x + (1.0 - i) * w->e->posx;
		thrd->floor_y_draw = i * thrd->floor_wall_y + (1.0 - i) * w->e->posy;
		thrd->floor_tex_x = (int)(thrd->floor_x_draw * w->e->ftex) % w->e->ftex;
		thrd->floor_tex_y = (int)(thrd->floor_y_draw * w->e->ftex) % w->e->ftex;
	}
	return (mlx_get_pixel_clr(img, thrd->floor_tex_y, thrd->floor_tex_x));
}

void			texture_on(t_w *w, int x, t_thrd *thrd)
{
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < thrd->drawstart)
			mlx_put_pixel(w->m->image, x, y, ft_add_color(
						floor_tex(w, HEIGHT - y, w->e->sky, thrd),
						0x000000, get_alpha(w->e->shadow, thrd->dist_draw)));
		else if (y > thrd->drawend)
			mlx_put_pixel(w->m->image, x, y, ft_add_color(
						floor_tex(w, y, w->e->floor, thrd),
						0x000000, get_alpha(w->e->shadow, thrd->dist_draw)));
		else
			mlx_put_pixel(w->m->image, x, y, ft_add_color(wall_tex(w, y, thrd),
						0x000000, get_alpha(w->e->shadow, thrd->perpwalldist)));
	}
}

void			texture_off(t_w *w, int x, t_thrd *thrd, int y)
{
	while (++y < HEIGHT)
	{
		if (y < thrd->drawstart)
			mlx_put_pixel(w->m->image, x, y, 0x000000);
		else if (y > thrd->drawend)
			mlx_put_pixel(w->m->image, x, y, 0x000000);
		else
			cardinal_points(w, x, thrd, y);
	}
}
