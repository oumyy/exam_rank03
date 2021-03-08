#ifndef MINI_PAINT_H
# define MINI_PAINT_H

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
}				t_bg;

typedef	struct s_cir
{
	char	type;
	float	x;
	float	y;
	float	rad;
	char	c;
}				t_cir;

int main(int argc, char **argv);


#endif
