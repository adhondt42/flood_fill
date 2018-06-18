/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhondt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 17:04:13 by adhondt           #+#    #+#             */
/*   Updated: 2018/06/18 18:35:20 by adhondt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "stdio.h"
#include "t_point.h"

void	ft_puttab(char **tab)
{
	int i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = -1;
		while (tab[i][++j])
			write(1, &tab[i][j], 1);
		write(1, "\n", 1);
		i++;
	}
}

void	fill(char **tab, int x, int y, char f, int ymax)
{
	if (x < 0 || y < 0 || f == 'F')
		return ;
	if (tab[y][x] == f)
		tab[y][x] = 'F';
	if (tab[y][x + 1] == f)
		fill(tab, x + 1, y, f, ymax);
	if (x - 1 >= 0 && tab[y][x - 1] == f)
		fill(tab, x - 1, y, f, ymax);
	if (y + 1 != ymax && tab[y + 1][x] == f)
		fill(tab, x, y + 1, f, ymax);
	if (y - 1 >= 0 && tab[y - 1][x] == f)
		fill(tab, x, y - 1, f, ymax);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	int	x;
	int	y;
	char f;

	if (begin.y < 0 || begin.x < 0)
		return ;
	if (begin.y > size.y || begin.x > size.x)
		return ;
	x = begin.x;
	y = begin.y;
	f = tab[y][x];
	fill(tab, x, y, f, size.y);
	return ;
}

char	**make_area(char **zone, int x, int y)
{
	int	i;
	int j;
	char	**area;

	area = (char **)malloc(sizeof(char *) * (y + 1));
	area[y] = NULL;
	i = -1;
	while (++i < y)
	{
		j = -1;
		area[i] = (char *)malloc(sizeof(char) * (x + 1));
		area[i][x] = '\0';
		while(zone[i][++j])
			area[i][j] = zone[i][j];
	}
	return (area);
}

int main(void)
{
	char **area;
/*
	t_point size = { 8, 5 };
	t_point begin = { 2, 4 };
	char *zone[] = {
		"11111111",
		"10001001",
		"10010001",
		"10110001",
		"11100001"
	};
*/
	t_point size = { 7, 5 };
	t_point begin = { 1, 0};
	char *zone[] = {
		"0400040",
		"0404040",
		"0404040",
		"0404040",
		"0404040"
	};
	area = make_area(zone, size.x, size.y);
	ft_puttab(area);
	flood_fill(area, size, begin);
	write(1, "\n", 1);
	ft_puttab(area);
	t_point begin2 = { 2, 4};
	flood_fill(area, size, begin2);
	write(1, "\n", 1);
	ft_puttab(area);
	t_point begin3 = { 6, 4};
	flood_fill(area, size, begin3);
	write(1, "\n", 1);
	ft_puttab(area);
	return (0);
}
