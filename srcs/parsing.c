/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:42:51 by ddufour           #+#    #+#             */
/*   Updated: 2017/04/20 11:55:38 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Wolf3d.h"

static	void	check_wall(t_w *w)
{
	int a;

	a = -1;
	while (w->m->map[0][++a])
		if (!(iswall(w->m->map[0][a])))
			ft_exit(2, "Error: Use a valid map\n");
	a = -1;
	while (w->m->map[w->m->ymax - 1][++a])
		if (!(iswall(w->m->map[w->m->ymax - 1][a])))
			ft_exit(2, "Error: Use a valid map\n");
	a = -1;
	while (w->m->map[++a])
	{
		if (!(iswall(w->m->map[a][0])))
			ft_exit(2, "Error: Use a valid map\n");
		if (!(iswall(w->m->map[a][w->m->xmax - 1])))
			ft_exit(2, "Error: Use a valid map\n");
	}
}

void			start(t_w *w)
{
	int a;
	int b;
	int c;

	c = 0;
	a = -1;
	while (w->m->map[++a])
	{
		b = -1;
		while (w->m->map[a][++b])
		{
			if (w->m->map[a][b] == 'S')
			{
				w->e->posx = a + 0.5;
				w->e->posy = b + 0.5;
				c++;
				(c <= 1) ? w->m->map[a][b] = '0' :
					ft_exit(2, "Error: Use a valid map\n");
			}
		}
	}
	if (!c)
		ft_exit(2, "Error: Use a valid map\n");
}

void			parsing(t_w *w, char *av)
{
	char	*buff;
	int		a;

	if (!(buff = ft_read_file(av)))
		ft_exit(2, "Error: Use a valid map\n");
	if (!(w->m->map = ft_strsplit(buff, '\n')))
		ft_exit(2, "Error: Use a valid map\n");
	(w->m->xmax = ft_strlen(w->m->map[0])) >= 3 ? 0 :
		ft_exit(2, "Error: Use a valid map\n");
	free(buff);
	a = -1;
	while (w->m->map[++a])
		w->m->xmax == (int)ft_strlen(w->m->map[a]) ?
		checkisvalid(w->m->map[a]) : ft_exit(2, "Error: Use a valid map\n");
	(w->m->ymax = a) >= 3 ? 0 : ft_exit(2, "Error: Use a valid map\n");
	check_wall(w);
	start(w);
}
