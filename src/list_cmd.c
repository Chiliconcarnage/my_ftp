/*
** list_cmd.c for list_cmd in /home/oem/home/PSU_2016_myftp/src
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Sun May 21 14:58:11 2017 maxence.lauque
** Last update Sun May 21 18:13:00 2017 maxence.lauque
*/

#include "server.h"

void	noop_cmd(char *buffer, t_server *server)
{
  (void)buffer;
  write(server->client_fd, NOOP, strlen(NOOP));
}

void	retr_cmd(char *buffer, t_server *server)
{
  (void)buffer;
  (void)server;
}

void	stor_cmd(char *buffer, t_server *server)
{
  (void)buffer;
  (void)server;
}

void	list_cmd(char *buffer, t_server *server)
{
  (void)buffer;
  (void)server;
}

void	dele_cmd(char *buffer, t_server *server)
{
  char  **tab_buff;
  int   size_arg;

  tab_buff = NULL;
  tab_buff = str_2_wordtab(tab_buff, buffer, ' ');
  if (tab_buff[1] != NULL)
    {
      size_arg = my_strlen(tab_buff[1]);
      tab_buff[1][size_arg - 1] = '\0';
      if ((unlink(tab_buff[1])) == 0)
        write(server->client_fd, DELE, strlen(DELE));
      else
        write(server->client_fd, BAD_DELE, strlen(BAD_DELE));
    }
  else
    write(server->client_fd, BAD_DELE, strlen(BAD_DELE));
}
