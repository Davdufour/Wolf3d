/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:56:14 by ddufour           #+#    #+#             */
/*   Updated: 2017/10/17 14:48:39 by ddufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx_macos/mlx.h"
# include <math.h>
# include <pthread.h>
# include </System/Library/Frameworks/TK.framework/Versions/8.5/Headers/X11/X.h>

# define WIDTH 1680
# define HEIGHT 1050
# define NB_TH 16

typedef struct		s_thrd
{
	int				i;
	int				x;
	double			camerax;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			wallx;
	double			floor_wall_x;
	double			floor_wall_y;
	double			dist_draw;
	double			dist_playeur;
	double			floor_x_draw;
	double			floor_y_draw;
	int				floor_tex_x;
	int				floor_tex_y;
	pthread_t		thread[NB_TH];
	void			*w;
}					t_thrd;

typedef struct		s_e
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			speed;
	double			rotat;
	double			olddirx;
	double			oldplanex;
	void			*floor;
	void			*sky;
	void			*wall;
	int				ftex;
	int				tex;
	int				puttext;
	int				shadow;
	int				active;
}					t_e;

typedef struct		s_m
{
	void			*mlx;
	void			*image;
	void			*window;
	char			*data;
	char			**map;
	int				xmax;
	int				ymax;
	void			(*ptrfonct_eventkey[281])(void *, int);
}					t_m;

typedef struct		s_w
{
	t_m				*m;
	t_e				*e;
	t_thrd			**thrd;
}					t_w;

/*
**main.c
*/

/*
**draw.c
*/
void				texture_on(t_w *w, int x, t_thrd *thrd);
void				texture_off(t_w *w, int x, t_thrd *thrd, int y);

/*
**parsing.c
*/
void				parsing(t_w *w, char *av);

/*
**raycasting.c
*/
int					thread_algo(t_w *w);

/*
**moving.c
*/
void				rotation(void *s, int keycode);
int					motion_mouse(int x, int y, t_w *w);
void				updown(void *s, int keycode);
void				leftright(void *s, int keycode);

/*
**ptrfonc.c
*/
void				init_ptrfonc(t_w *w);

/*
**useless.c
*/
void				foncnull(void *s, int keycode);
void				echap(void *s, int keycode);
int					exit_prog(t_w *w);
void				cardinal_points(t_w *w, int x, t_thrd *thrd, int y);
void				init_text(t_w *w);

/*
**event.c
*/
int					key_fonc(int keycode, void *s);
int					button_fonc(int button, int x, int y, t_w *w);
void				active_texture(void *s, int keycode);
void				active_mouse(void *s, int keycode);
void				shadow(void *s, int keycode);

#endif
