#include "micro_paint.h"

int		check_corr(float x, float y, float rec_x, float rec_y, float width, float height)
{
	if (x < rec_x || x > rec_x + width || y < rec_y || y > rec_y + height)
		return (0);
	else if (x - rec_x < 1 || (rec_x + width) - x < 1 || 
			y - rec_y < 1 || (rec_y + height) - y < 1)
			return (1);
	return (2);
}

int     error(FILE *file, int i)
{
    if (i == 1)
        write(1, "Error: argument\n", 16);
    else if (i ==  2)
	{
        write(1, "Error: Operation file corrupted\n", 32);
    	if (file)
        	fclose(file);
	}
    return (1);
}

int     main(int argc, char **argv)
{
	char	result[90000]; // 300 * 300
	t_rect	rect;
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
	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.wi, &rect.he, &rect.c)) == 6)
	{
		if (rect.wi <= 0 || rect.he <= 0 || (rect.type != 'r' && rect.type != 'R'))
			return (error(file, 2));
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
		return (error(file, 2));
	for (int i = 0; i < background.he; i++)
	{
		write(1, result + background.wi * i, background.wi);
		write(1, "\n", 1);
	}
	fclose(file);
	return (0);
}
