//  mlx_init_loop.m
// By Ol

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl3.h>
#import <AppKit/NSOpenGLView.h>

#include "mlx_int.h"
#include "mlx_new_window.h"

#include "font.c"



void	do_loop_hook2(CFRunLoopTimerRef observer, void * info)
{
  ((mlx_ptr_t *)info)->loop_hook(((mlx_ptr_t *)info)->loop_hook_data);
}


void do_loop_flush(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void * info)
{
  mlx_ptr_t	*mlx_ptr;
  mlx_win_list_t *win;

  mlx_ptr = (mlx_ptr_t *)info;
  win = mlx_ptr->win_list;
  while (win)
    {
      if (win->nb_flush > 0 && win->pixmgt)
	{
	  [(id)win->winid selectGLContext];
	  [(id)win->winid mlx_gl_draw];
	  glFlush();
	  win->nb_flush = 0;
	}
      win = win->next;
    }
}

void *mlx_init()
{
  mlx_ptr_t	*new_mlx;
  int		bidon;
  int		i;

  if ((new_mlx = malloc(sizeof(*new_mlx))) == NULL)
    return ((void *)0);
  new_mlx->win_list = NULL;
  new_mlx->img_list = NULL;
  new_mlx->loop_hook = NULL;
  new_mlx->loop_hook_data = NULL;
  new_mlx->main_loop_active = 0;


  new_mlx->appid = [NSApplication sharedApplication];

  // super magic trick to detach app from terminal, get menubar & key input events
  for (NSRunningApplication * app in [NSRunningApplication runningApplicationsWithBundleIdentifier:@"com.apple.finder"])
    {
      [app activateWithOptions:NSApplicationActivateIgnoringOtherApps];
      break;
    }
  usleep(100000);
  ProcessSerialNumber psn = { 0, kCurrentProcess };
  (void) TransformProcessType(&psn, kProcessTransformToForegroundApplication);
  usleep(100000);
  [[NSRunningApplication currentApplication] activateWithOptions:NSApplicationActivateIgnoringOtherApps];

  // load font
  new_mlx->font = mlx_new_image(new_mlx, (FONT_WIDTH+2)*95, FONT_HEIGHT);
  i = 0;
  while (i < 4*(FONT_WIDTH+2)*95*FONT_HEIGHT)
    {
      new_mlx->font->buffer[i+0] = font_atlas.pixel_data[i+2];
      new_mlx->font->buffer[i+1] = font_atlas.pixel_data[i+1];
      new_mlx->font->buffer[i+2] = font_atlas.pixel_data[i+0];
      ((unsigned char *)new_mlx->font->buffer)[i+3] = 0xFF-font_atlas.pixel_data[i+3];
      i += 4;
    }

  new_mlx->font->vertexes[2] = FONT_WIDTH;
  new_mlx->font->vertexes[4] = FONT_WIDTH;
  new_mlx->font->vertexes[5] = -FONT_HEIGHT-1;
  new_mlx->font->vertexes[7] = -FONT_HEIGHT-1;

  return ((void *)new_mlx);
}


void mlx_loop(mlx_ptr_t *mlx_ptr)
{
  CFRunLoopObserverRef observer;
  CFRunLoopObserverContext ocontext = {.version = 0, .info = mlx_ptr, .retain = NULL, .release = NULL, .copyDescription = NULL};

  mlx_ptr->main_loop_active = 1;

  observer = CFRunLoopObserverCreate(NULL, kCFRunLoopBeforeTimers, true, 0, do_loop_flush, &ocontext);
  CFRunLoopAddObserver(CFRunLoopGetMain(), observer, kCFRunLoopCommonModes);

  //  [[[MlxLoopHookObj alloc] initWithPtr:mlx_ptr] performSelector:@selector(do_loop_hook) withObject:nil afterDelay:0.0];

  [NSApp run];
}

int     ft_add_color(int old_clr, int add_clr, double alpha)
{
    int r;
    int g;
    int b;

    r = floor((double)(((old_clr >> 16) & 0xFF) * alpha) - (double)(((add_clr >> 16) & 0xFF) * alpha));
    g = floor((double)(((old_clr >> 8) & 0xFF) * alpha) - (double)(((add_clr >> 8) & 0xFF) * alpha));
    b = floor((double)(((old_clr) & 0xFF) * alpha) - (double)(((add_clr) & 0xFF) * alpha));
	return (((0 & 0xff) << 24)  + ((r & 0xff) << 16) + ((g & 0xff) << 8)  + (b & 0xff));
}

t_rec *init_data_rect(int x, int y, int width, int height)
{
	t_rec *rec;

	if (!(rec = (t_rec*)malloc(sizeof(t_rec))))
		exit(0);
	rec->x = x;
	rec->y = y;
	rec->width = width;
	rec->height = height;
	return (rec);
}


void	ft_draw_rec(mlx_img_list_t *img, int clr, t_rec *rec)
{
	int tmpx;
	int tmpy;
	int a;

	tmpx = rec->x;
	tmpy = rec->y;
	a = -1;
	while (++a <= rec->height)
	{
		*((int *)&img->buffer[(tmpx * UNIQ_BPP) + (tmpy * (img->width * UNIQ_BPP))]) = clr;
		*((int *)&img->buffer[((tmpx + rec->width) * UNIQ_BPP) + (tmpy * (img->width * UNIQ_BPP))]) = clr;
		tmpy++;
	}
	a = -1;
	while (++a <= rec->width)
	{
		*((int *)&img->buffer[(tmpx * UNIQ_BPP) + (rec->y * (img->width * UNIQ_BPP))]) = clr;
		*((int *)&img->buffer[(tmpx * UNIQ_BPP) + ((rec->y + rec->height) * (img->width * UNIQ_BPP))]) = clr;
		tmpx++;
	}
	free(rec);
}


int     mlx_put_pixel(mlx_img_list_t *img, int x, int y, int clr)
{
    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return (0);
    *((int *)&img->buffer[(x * UNIQ_BPP) + (y * (img->width * UNIQ_BPP))]) = clr;

	return (0);
}

void mlx_pixel_put(mlx_ptr_t *mlx_ptr, mlx_win_list_t *win_ptr, int x, int y, int color)
{

  if (!win_ptr->pixmgt)
    return ;
  [(id)(win_ptr->winid) selectGLContext];
  [(id)(win_ptr->winid) pixelPutColor:color X:x Y:y];
  win_ptr->nb_flush ++;
}

int     mlx_get_pixel_clr(mlx_img_list_t *img, int x, int y)
{
    int             r;
    int             g;
    int             b;
    unsigned int    p;

    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return (0);
    p = (x * UNIQ_BPP) + (y * (img->width * UNIQ_BPP));
    r = img->buffer[p + 2];
    g = img->buffer[p + 1];
    b = img->buffer[p];
    return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF));
}

void	draw_fill_rec(mlx_img_list_t *img, int clr, t_rec *rec, double alpha)
{
	int a;
	int b;
	int tmpx;

	a = -1;
	while (++a <= rec->height - 2)
	{
		tmpx = rec->x;
		b = -1;
		++rec->y;
		while (++b <= rec->width - 2)
			*((int *)&img->buffer[(++tmpx * UNIQ_BPP) + (rec->y * (img->width * UNIQ_BPP))]) = ft_add_color(mlx_get_pixel_clr(img, rec->x, rec->y), clr, alpha);
	}
	free(rec);
}

void hidecursor(int hide)
{
	if (hide > 0)
		[NSCursor hide];
	else if (!hide)
		[NSCursor unhide];
}

void lockcursor(int lock)
{
	NSRect screenRect;
	screenRect = [ [NSScreen mainScreen] frame];

	if (lock > 0)
	{
		NSRect window;
		window = [ [NSApp mainWindow] frame];
		CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
		CGEventRef mouse = CGEventCreateMouseEvent (NULL, kCGEventMouseMoved, CGPointMake(window.origin.x + ((int)window.size.width >> 1), ((screenRect.size.height - (window.size.height + window.origin.y)) + ((int)window.size.height >> 1))), 0);
		CGEventPost(kCGHIDEventTap, mouse);
		CFRelease(mouse);
		CFRelease(source);
	}
}

void	mlx_int_loop_once()
{
  NSEvent *event;
  NSDate  *thedate;

  thedate = [NSDate dateWithTimeIntervalSinceNow:0.1];
  while (42)
    {
      event = [NSApp nextEventMatchingMask:NSAnyEventMask
		     untilDate:thedate
		     inMode:NSDefaultRunLoopMode
		     dequeue:YES];
      if (event == nil)
	{
	  [thedate release];
	  return ;
	}
      [NSApp sendEvent:event];
      [NSApp updateWindows];
    }
}


int     mlx_do_sync(mlx_ptr_t *mlx_ptr)
{
  mlx_win_list_t *win;

  win = mlx_ptr->win_list;
  while (win)
    {
      if (win->pixmgt)
	{
	  [(id)(win->winid) selectGLContext];
	  [(id)(win->winid) mlx_gl_draw];
	  glFlush();
	  if (!mlx_ptr->main_loop_active)
	    mlx_int_loop_once();
	}
      win = win->next;
    }
  return (0);
}


int mlx_loop_hook(mlx_ptr_t *mlx_ptr, void (*fct)(void *), void *param)
{
  CFRunLoopTimerContext	tcontext = {0, mlx_ptr, NULL, NULL, NULL};
  CFRunLoopTimerRef	timer;

  if (mlx_ptr->loop_hook != NULL)
    {
      CFRunLoopTimerInvalidate(mlx_ptr->loop_timer);
      [(id)(mlx_ptr->loop_timer) release];
    }

  mlx_ptr->loop_hook = fct;
  mlx_ptr->loop_hook_data = param;

  if (fct)
    {
      timer = CFRunLoopTimerCreate(kCFAllocatorDefault, 0.0, 0.0001, 0, 0, &do_loop_hook2, &tcontext);
      mlx_ptr->loop_timer = timer;
      CFRunLoopAddTimer(CFRunLoopGetMain(), timer, kCFRunLoopCommonModes);
    }

  return (0);
}
