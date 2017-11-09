/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:59:06 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/14 11:00:47 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

void	rotation(void *s, int keycode)
{
	t_w		*w;
	double	rotattmp;

	w = s;
	rotattmp = (keycode == 14) ? -w->e->rotat : w->e->rotat;
	w->e->olddirx = w->e->dirx;
	w->e->dirx = w->e->dirx * cos(rotattmp) - w->e->diry * sin(rotattmp);
	w->e->diry = w->e->olddirx * sin(rotattmp) + w->e->diry * cos(rotattmp);
	w->e->oldplanex = w->e->planx;
	w->e->planx = w->e->planx * cos(rotattmp) - w->e->plany * sin(rotattmp);
	w->e->plany = w->e->oldplanex * sin(rotattmp) + w->e->plany * cos(rotattmp);
}

int		motion_mouse(int x, int y, t_w *w)
{
	double rotattmp;

	(void)y;
	if (w->e->active == 1)
	{
		rotattmp = 0.0;
		lockcursor(1);
		if (x > (WIDTH / 2))
			rotattmp = -w->e->rotat;
		else if (x < (WIDTH / 2))
			rotattmp = w->e->rotat;
		w->e->olddirx = w->e->dirx;
		w->e->dirx = w->e->dirx * cos(rotattmp) - w->e->diry * sin(rotattmp);
		w->e->diry = w->e->olddirx * sin(rotattmp) + w->e->diry * cos(rotattmp);
		w->e->oldplanex = w->e->planx;
		w->e->planx = w->e->planx * cos(rotattmp) - w->e->plany * sin(rotattmp);
		w->e->plany = w->e->oldplanex * sin(rotattmp) + w->e->plany *
						cos(rotattmp);
	}
	return (1);
}

void	updown(void *s, int keycode)
{
	t_w *w;

	w = s;
	(!(iswall(w->m->map[(int)(w->e->posx + w->e->dirx * w->e->speed)]
	[(int)w->e->posy])) && keycode == 13) ?
	w->e->posx += w->e->dirx * w->e->speed : 0;
	(!(iswall(w->m->map[(int)w->e->posx][(int)(w->e->posy + w->e->diry *
	w->e->speed)])) && keycode == 13) ? w->e->posy += w->e->diry *
	w->e->speed : 0;
	(!(iswall(w->m->map[(int)(w->e->posx - w->e->dirx * w->e->speed)]
	[(int)w->e->posy])) && keycode == 1) ? w->e->posx -= w->e->dirx *
	w->e->speed : 0;
	(!(iswall(w->m->map[(int)w->e->posx][(int)(w->e->posy - w->e->diry *
	w->e->speed)])) && keycode == 1) ? w->e->posy -= w->e->diry *
	w->e->speed : 0;
}

void	leftright(void *s, int keycode)
{
	t_w *w;

	w = s;
	(!(iswall(w->m->map[(int)(w->e->posx + w->e->planx * w->e->speed)]
	[(int)w->e->posy])) && keycode == 2) ? w->e->posx += w->e->planx *
	w->e->speed : 0;
	(!(iswall(w->m->map[(int)w->e->posx][(int)(w->e->posy + w->e->plany *
	w->e->speed)])) && keycode == 2) ? w->e->posy += w->e->plany *
	w->e->speed : 0;
	(!(iswall(w->m->map[(int)(w->e->posx - w->e->planx * w->e->speed)]
	[(int)w->e->posy])) && keycode == 0) ? w->e->posx -= w->e->planx *
	w->e->speed : 0;
	(!(iswall(w->m->map[(int)w->e->posx][(int)(w->e->posy - w->e->plany *
	w->e->speed)])) && keycode == 0) ? w->e->posy -= w->e->plany *
	w->e->speed : 0;
}
