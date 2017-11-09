/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrfonc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 14:15:53 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/14 10:41:48 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

void	init_ptrfonc(t_w *w)
{
	int a;

	a = -1;
	while (++a <= 280)
	{
		w->m->ptrfonct_eventkey[a] = &foncnull;
	}
	w->m->ptrfonct_eventkey[53] = &echap;
	w->m->ptrfonct_eventkey[13] = &updown;
	w->m->ptrfonct_eventkey[1] = &updown;
	w->m->ptrfonct_eventkey[0] = &leftright;
	w->m->ptrfonct_eventkey[2] = &leftright;
	w->m->ptrfonct_eventkey[12] = &rotation;
	w->m->ptrfonct_eventkey[14] = &rotation;
	w->m->ptrfonct_eventkey[48] = &active_texture;
	w->m->ptrfonct_eventkey[15] = &shadow;
	w->m->ptrfonct_eventkey[3] = &active_mouse;
}
