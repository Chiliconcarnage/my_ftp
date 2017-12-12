/*
** str_2_wordtab.c for towordtab in /home/oem/home/PSU_2016_myftp
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Tue May 16 18:23:12 2017 maxence.lauque
** Last update Tue May 16 18:27:21 2017 maxence.lauque
*/

#include "server.h"

int	get_width(char	*str, char c)
{
  int	i;
  int	len;
  int	width;

  width = 0;
  len = 0;
  i = 0;
  while (str[i] != 0)
    {
      if (str[i] != c)
	{
	  len++;
	}
      else
	{
	  if (width < len)
	    width = len;
	  len = 0;
	}
      i++;
    }
  if (width < len)
    width = len;
  return (width);
}

int	get_nb_line(char *str, char c)
{
  int	i;
  int	nb;

  nb = 0;
  i = 0;
  while (str[i] != 0)
    {
      if (str[i] == c)
	nb++;
      i++;
    }
  nb = nb + 1;
  return (nb);
}

char	**fill_char_2d(char **dest, char *src, char c)
{
  int	i;
  int	x;
  int	y;

  i = 0;
  x = 0;
  y = 0;
  while (src[i] != 0)
    {
      if (src[i] == c)
	{
	  y++;
	  x = 0;
	}
      else
	{
	  dest[y][x] = src[i];
	  x++;
	}
      i++;
    }
  return (dest);
}

char	**str_2_wordtab(char **dest, char *src, char c)
{
  int	line;
  int	width;
  int	y;

  y = 0;
  width = get_width(src, c) + 1;
  line = get_nb_line(src, c);
  if ((dest = malloc(sizeof(char*) * (line + 1))) == NULL)
    return (NULL);
  dest[line] = NULL;
  while (y < line)
    {
      if ((dest[y] = malloc(sizeof(char) * (width + 1))) == NULL)
	return (NULL);
      memset(dest[y], '\0', width);
      y++;
    }
  dest = fill_char_2d(dest, src, c);
  return (dest);
}
