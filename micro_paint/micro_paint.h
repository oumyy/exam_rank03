#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h>


typedef	struct	s_bg
{
	int		he;
	int		wi;
	char	c;
	char	space;
}				t_bg;

typedef	struct s_rect
{
	char	type;
	float	x;
	float	y;
	float	wi;
	float	he;
	char	c;
	char	sp1;
	char	sp2;
}				t_rect;

int main(int argc, char **argv);


#endif