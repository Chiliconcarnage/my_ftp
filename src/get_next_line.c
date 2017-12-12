/*
** get_next_line.c for gnl in /home/oem/home/PSU_2016_myftp
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Wed May 17 20:26:15 2017 maxence.lauque
** Last update Wed May 17 20:26:20 2017 maxence.lauque
*/

#include "get_next_line.h"

char	*my_realloc(char *str, int size, char *newstr)
{
  char	*tmp;
  int	i;
  int	j;

  j = i = 0;
  if ((tmp = malloc(size + 1)) == NULL)
    return (NULL);
  while (i <= size)
    tmp[i++] = 0;
  i = 0;
  if (str != NULL)
    {
      while (str[i] != 0)
	{
	  tmp[i] = str[i];
	  i++;
	}
      free(str);
    }
  i = j = 0;
  while (tmp[i] != 0)
    i++;
  while ((newstr[j] != 0) && (newstr[j] != '\n'))
    tmp[i++] = newstr[j++];
  return (tmp);
}

int	is_b_slash_n(char *buffer)
{
  int	i;
  int	j;

  j =  i = 0;
  while (buffer[i] != 0)
    {
      if (buffer[i] == '\n')
	j++;
      i++;
    }
  return (j);
}

char	*maj_buffer(char *buffer)
{
  int	i;
  int	j;

  i = 0;
  j = -2;
 while (buffer[i] != 0)
   {
     if (buffer[i] == '\n' && j < 0)
       j = i;
     i++;
   }
 j = j + 1;
 if (j > 0)
   {
     i = 0;
     while (buffer[j] != 0)
       buffer[i++] = buffer[j++];
     buffer[i] = 0;
   }
 return (buffer);
}

char	*xbuffer(char *buffer, char *stock)
{
  if (is_b_slash_n(buffer) <= 0)
    return (NULL);
  buffer = maj_buffer(buffer);
  if ((stock = my_realloc(stock, READ_SIZE, buffer)) == NULL)
    return (NULL);
  if (is_b_slash_n(buffer) > 0)
    return (stock);
  return (stock);
}

char	*get_next_line(int fd)
{
  static char	buffer[READ_SIZE + 1];
  char		*stock;
  int		ret;
  int		mal_size;

  mal_size = 0;
  stock = NULL;
  if (fd == -1)
    return (NULL);
  stock = xbuffer(buffer, stock);
  if (is_b_slash_n(buffer) > 0)
    return (stock);
  while ((ret = read(fd, buffer, READ_SIZE)) > 0)
    {
      buffer[ret] = 0;
      mal_size = mal_size + ret + READ_SIZE;
      if ((stock = my_realloc(stock, mal_size, buffer)) == NULL)
	return (NULL);
      if (is_b_slash_n(buffer) > 0)
	return (stock);
    }
  if (buffer[0] != 0)
    return (stock);
  free(stock);
  return (NULL);
}
