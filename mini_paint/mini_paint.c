#include "mini_paint.h"

int     error(FILE *fp, int i)
{
	if (i == 1)
		write(1, "Error: argument\n", 16);
	else if (i == 2)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		if (fp)
			fclose(fp);
	}
	return (1);
}

int		fill_circle(int x, int y, t_cir *cir)
{
	float x1 = x;
	float y1 = y;
	float x2 = cir->x;
	float y2 = cir->y;
	float dist;

	dist = sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if (dist > cir->rad)
		return (0);
	if (cir->rad - dist < 1)
		return (1);
	if (cir->type == 'C')
		return (1);
	return (0);
}
int     main(int argc, char **argv)
{
	char	result[90000]; // 300 * 300
	t_cir	cir;
	t_bg	background;
	FILE	*file;
	int		ret;

	file = NULL;
	if (argc != 2)
		return (error(file, 1));
	if (!(file = fopen(argv[1], "r")))
		return (error(file, 2));
	if (fscanf(file, "%d %d %c \n", &background.wi, &background.he, &background.c) != 3)
		return (error(file, 2));
	if (background.wi <= 0 || background.wi > 300 || background.he <= 0 || background.he > 300)
		return (error(file, 2));
	memset(result, background.c, background.he * background.wi);
	while ((ret = fscanf(file, "%c %f %f %f %c\n", &cir.type, &cir.x, &cir.y, &cir.rad, &cir.c)) == 5)
	{
		if (cir.rad <= 0 || (cir.type != 'c' && cir.type != 'C'))
			return (error(file, 2));
		for (int y = 0; y < background.he; y++)
		{
			for (int x = 0; x < background.wi; x++)
			{
				if (fill_circle(x, y, &cir))
					result[y * background.wi + x] = cir.c;
			}
		}
	}
	if (ret !=  EOF)
		return(error(file, 2));
	for (int i = 0; i < background.he; i++)
	{
		write(1, result + background.wi * i, background.wi);
		write(1, "\n", 1);
	}
	fclose(file);
	return (0);
}
