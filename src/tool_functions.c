/*
** tool_functions.c for tool_functions in /home/oem/home/PSU_2016_myftp/src
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Sun May 21 15:09:02 2017 maxence.lauque
** Last update Sun May 21 18:56:55 2017 maxence.lauque
*/

#include "server.h"

char	*cat_path(char *original_path, char *new_path)
{
  int   i;
  int   a;
  char *new_tab;

  i = 0;
  a = 0;
  new_tab = malloc(sizeof(char) * (strlen(original_path)\
                                   + strlen(new_path) + 1));
  memset(new_tab, '\0', strlen(new_tab));
  while (original_path[i] != '\0')
    {
      new_tab[a] = original_path[i];
      a++;
      i++;
    }
  i = 0;
  while (new_path[i] != '\0')
    {
      new_tab[a] = new_path[i];
      a++;
      i++;
    }
  new_tab[a - 1] = '\0';
  return (new_tab);
}

char	*to_lower(char *str)
{
  int   i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] >= 65 && str[i] <= 90)
        str[i] = tolower(str[i]);
      i++;
    }
  return (str);
}

int	my_strlen(char *str)
{
  int   i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

int	check_existing_dir(char *str)
{
  if ((access(str, F_OK)) == 0)
    {
      if ((chdir(str)) == -1)
        return (-1);
      return (0);
    }
  return (-1);
}
