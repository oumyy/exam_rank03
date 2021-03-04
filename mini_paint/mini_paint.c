#include "mini_paint.h"

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int     error(FILE *fp, char *str)
{
	write(1, str, ft_strlen(str));
	if (fp)
		fclose(fp);
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

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!(file = fopen(argv[1], "r")))
		return (error(file, "Error: Operation file corrupted\n"));
	if (fscanf(file, "%d %d%c %c \n", &background.wi, &background.he, &background.space, &background.c) != 4)
		return (error(file, "Operation file corrupted\n"));
	if (background.wi <= 0 || background.wi > 300 || background.he <= 0 || background.he > 300 || background.space != ' ')
		return (error(file, "Operation file corrupted\n"));
	memset(result, background.c, background.he * background.wi);
	while ((ret = fscanf(file, "%c%c %f %f %f%c %c\n", &cir.type, &cir.sp1, &cir.x, &cir.y, &cir.rad, &cir.sp2, &cir.c)) == 7)
	{
		if (cir.rad <= 0 || cir.sp1 != ' ' || cir.sp2 != ' ' || (cir.type != 'c' && cir.type != 'C'))
			return (error(file, "Error: Operation file corrupted\n"));
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
		return(error(file, "Error: Operation file corrupted\n"));
	for (int i = 0; i < background.wi; i++)
	{
		write(1, result + background.wi * i, background.wi);
		write(1, "\n", 1);
	}
	 fclose(file);
	return (0);
}
