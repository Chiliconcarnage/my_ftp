/*
** listen_socket.c for listen_socket in /home/oem/home/PSU_2016_myftp/src
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Sun May 21 15:12:28 2017 maxence.lauque
** Last update Sun May 21 15:13:06 2017 maxence.lauque
*/

#include "server.h"

int	handle_client(int client_fd)
{
  static const char * const     welcome = "220 (vsFTPd 3.0.0)\r\n";
  if (write(client_fd, welcome, strlen(welcome)) == -1)
    return (1);
  return (0);
}

int	listen_serv(t_server *server, char *path)
{
  server->original_path = path;
  server->quit = 0;
  if (bind(server->fd, (const struct sockaddr *)&server->s_in,  \
           sizeof(server->s_in)) == -1)
    {
      if (close(server->fd) == -1)
        {
          return (1);
        }
      return (1);
    }
  if (listen(server->fd, 42) == 1)
    {
      if (close(server->fd) == -1)
        {
          return (1);
        }
      return (1);
    }
  return (0);
}
