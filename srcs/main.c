/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:55:06 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/20 11:54:04 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

static	void	init_pos(t_w *w)
{
	if (!(w->e = (t_e*)malloc(sizeof(t_e))))
		ft_exit(1, "init_pos");
	w->e->dirx = 0.08;
	w->e->diry = 1;
	w->e->planx = 0.6;
	w->e->plany = -0.05;
	w->e->rotat = 0.05;
	w->e->speed = 0.1;
	w->e->puttext = 0;
	w->e->shadow = 1;
	w->e->active = 1;
}

static	void	init_thrd(t_w *w)
{
	int i;

	i = -1;
	while (++i < NB_TH)
	{
		if (!(w->thrd[i] = (t_thrd*)malloc(sizeof(t_thrd))))
			ft_exit(1, "init_thrd");
		w->thrd[i]->i = i;
		w->thrd[i]->w = w;
	}
}

static	t_w		*init_struct(t_w *w, char *av)
{
	if (!(w = (t_w*)malloc(sizeof(t_w))))
		ft_exit(1, "init_struct");
	if (!(w->m = (t_m*)malloc(sizeof(t_m))))
		ft_exit(1, "init_struct");
	if (!(w->thrd = (t_thrd**)malloc(sizeof(t_thrd*) * NB_TH)))
		ft_exit(1, "init_struct");
	init_pos(w);
	parsing(w, av);
	w->m->mlx = mlx_init();
	w->m->window = mlx_new_window(w->m->mlx, -1, -1, WIDTH, HEIGHT, "Wolf3d");
	w->m->image = mlx_new_image(w->m->mlx, WIDTH, HEIGHT, 0xFFFFFFF);
	init_ptrfonc(w);
	init_text(w);
	init_thrd(w);
	hidecursor(1);
	return (w);
}

static	void	ft_wolf3d(char *av)
{
	t_w *w;

	w = init_struct(NULL, av);
	mlx_loop_hook(w->m->mlx, thread_algo, w);
	mlx_hook(w->m->window, KeyPress, KeyPressMask, key_fonc, w);
	mlx_hook(w->m->window, DestroyNotify, Button1MotionMask, exit_prog, w);
	mlx_hook(w->m->window, MotionNotify, ButtonMotionMask, motion_mouse, w);
	mlx_hook(w->m->window, ButtonPress, ButtonPressMask, button_fonc, w);
	mlx_loop(w->m->mlx);
}

int				main(int ac, char **av)
{
	if (ac == 2)
		ft_wolf3d(av[1]);
	else
		ft_exit(2, "usage: ./Wolf3d [map]\n");
	return (0);
}
