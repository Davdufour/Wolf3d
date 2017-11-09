/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 13:50:42 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/13 16:17:43 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

static	void	init_var(t_w *w, t_thrd *thrd)
{
	double raydiry2;
	double raydirx2;

	thrd->camerax = 2 * thrd->x / (double)WIDTH - 1;
	thrd->raydirx = w->e->dirx + w->e->planx * thrd->camerax;
	thrd->raydiry = w->e->diry + w->e->plany * thrd->camerax;
	thrd->mapx = (int)w->e->posx;
	thrd->mapy = (int)w->e->posy;
	raydirx2 = thrd->raydirx * thrd->raydirx;
	raydiry2 = thrd->raydiry * thrd->raydiry;
	thrd->deltadistx = sqrt(1 + (raydiry2) / (raydirx2));
	thrd->deltadisty = sqrt(1 + (raydirx2) / (raydiry2));
}

static	void	calc_side(t_w *w, t_thrd *thrd)
{
	if (thrd->raydirx < 0)
	{
		thrd->stepx = -1;
		thrd->sidedistx = (w->e->posx - thrd->mapx) * thrd->deltadistx;
	}
	else
	{
		thrd->stepx = 1;
		thrd->sidedistx = (thrd->mapx + 1 - w->e->posx) * thrd->deltadistx;
	}
	if (thrd->raydiry < 0)
	{
		thrd->stepy = -1;
		thrd->sidedisty = (w->e->posy - thrd->mapy) * thrd->deltadisty;
	}
	else
	{
		thrd->stepy = 1;
		thrd->sidedisty = (thrd->mapy + 1 - w->e->posy) * thrd->deltadisty;
	}
}

static	void	detect_wall(t_w *w, t_thrd *thrd)
{
	thrd->hit = 0;
	while (thrd->hit == 0)
	{
		if (thrd->sidedistx < thrd->sidedisty)
		{
			thrd->sidedistx += thrd->deltadistx;
			thrd->mapx += thrd->stepx;
			thrd->side = 0;
		}
		else
		{
			thrd->sidedisty += thrd->deltadisty;
			thrd->mapy += thrd->stepy;
			thrd->side = 1;
		}
		(iswall(w->m->map[thrd->mapx][thrd->mapy]) != 0) ? thrd->hit = 1 : 0;
	}
	thrd->perpwalldist = (thrd->side == 0)
		? (thrd->mapx - w->e->posx + (1 - thrd->stepx) / 2) / thrd->raydirx
		: (thrd->mapy - w->e->posy + (1 - thrd->stepy) / 2) / thrd->raydiry;
	thrd->lineheight = (int)(HEIGHT / thrd->perpwalldist);
	(thrd->drawstart = -thrd->lineheight / 2 + HEIGHT / 2) < 0 ?
		thrd->drawstart = 0 : 0;
	(thrd->drawend = thrd->lineheight / 2 + HEIGHT / 2) >= HEIGHT ?
		thrd->drawend = HEIGHT - 1 : 0;
}

static	void	*algo(void *arg)
{
	t_thrd	*thrd;
	t_w		*w;

	thrd = (t_thrd*)arg;
	w = (t_w*)thrd->w;
	thrd->x = thrd->i * (WIDTH / NB_TH) - 1;
	while (++thrd->x < ((double)WIDTH / (double)NB_TH) * (thrd->i + 1))
	{
		init_var(w, thrd);
		calc_side(w, thrd);
		detect_wall(w, thrd);
		if (w->e->puttext == 1)
			texture_on(w, thrd->x, thrd);
		else
			texture_off(w, thrd->x, thrd, -1);
	}
	pthread_exit(0);
}

int				thread_algo(t_w *w)
{
	int i;

	i = -1;
	while (++i < NB_TH)
		pthread_create(&w->thrd[i]->thread[i], NULL, &algo, w->thrd[i]);
	i = -1;
	while (++i < NB_TH)
		(void)pthread_join(w->thrd[i]->thread[i], NULL);
	mlx_put_image_to_window(w->m->mlx, w->m->window, w->m->image, 0, 0);
	return (0);
}
