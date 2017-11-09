/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:32:36 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/14 12:35:34 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

int		key_fonc(int keycode, void *s)
{
	t_w *w;

	w = s;
	w->m->ptrfonct_eventkey[keycode](w, keycode);
	return (0);
}

int		button_fonc(int button, int x, int y, t_w *w)
{
	(void)w;
	(void)x;
	(void)y;
	(void)button;
	return (1);
}

void	active_texture(void *s, int keycode)
{
	t_w *w;

	w = s;
	(void)keycode;
	w->e->puttext = (w->e->puttext == 1) ? 0 : 1;
}

void	active_mouse(void *s, int keycode)
{
	t_w *w;

	w = s;
	(void)keycode;
	w->e->active = (w->e->active == 1) ? 0 : 1;
	w->e->active == 1 ? hidecursor(1) : hidecursor(0);
}

void	shadow(void *s, int keycode)
{
	t_w *w;

	w = s;
	(void)keycode;
	w->e->shadow = (w->e->shadow == 1) ? 0 : 1;
}
