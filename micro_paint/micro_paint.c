#include "micro_paint.h"

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int		check_corr(float x, float y, float rec_x, float rec_y, float width, float height)
{
	if (x < rec_x || x > rec_x + width || y < rec_y || y > rec_y + height)
		return (0);
	else if (x - rec_x < 1.0 || (rec_x + width) - x < 1.0 || 
			y - rec_y < 1.0 || (rec_y + height) - y < 1.0)
			return (1);
	return (2);
}
int     error(FILE *fp, char *str)
{
	write(1, str, ft_strlen(str));
	if (fp)
		fclose(fp);
	return (1);
}

int     main(int argc, char **argv)
{
	char	result[90000]; // 300 * 300
	t_rect	rect;
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
		return (error(file, "Error: Operation file corrupted\n"));
	if (background.wi <= 0 || background.wi > 300 || background.he <= 0 || background.he > 300 || background.space != ' ')
		return (error(file, "Error: Operation file corrupted\n"));
	memset(result, background.c, background.he * background.wi);
	while ((ret = fscanf(file, "%c%c %f %f %f %f%c %c\n", &rect.type, &rect.sp1, &rect.x, &rect.y, &rect.wi, &rect.he, &rect.sp2, &rect.c)) == 8)
	{
		if (rect.wi <= 0 || rect.he <= 0 || rect.sp1 != ' ' || rect.sp2 != ' ' || (rect.type != 'r' && rect.type != 'R'))
			return (error(file, "Error: Operation file corrupted\n"));
		for (int y = 0; y < background.he; y++)
		{
			for (int x = 0; x < background.wi; x++)
			{
				int i = check_corr((float)x, (float)y, rect.x, rect.y, rect.wi, rect.he);
				if (i == 1 || (i == 2 && rect.type == 'R'))
					result[y * background.wi + x] = rect.c;
			}
		}
	}
	if (ret != EOF)
		return (error(file, "Error: Operation file corrupted\n"));
	for (int i = 0; i < background.he; i++)
	{
		write(1, result + background.wi * i, background.wi);
		write(1, "\n", 1);
	}
	fclose(file);
	return (0);
}