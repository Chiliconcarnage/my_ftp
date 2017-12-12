/*
** main.c for main in /home/oem/home/PSU_2016_myftp/src
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Wed May 10 14:06:03 2017 maxence.lauque
** Last update Sun May 21 18:40:44 2017 maxence.lauque
*/

#include "server.h"

int	main(int ac, char **av)
{
  t_server	server;

  server.reuse = 1;
  if (ac != 3)
    {
      write(2, USAGE, strlen(USAGE));
      return (84);
    }
  if ((init_socket(&server, av)) == 1)
    return (1);
  server.s_in.sin_family = AF_INET;
  server.s_in.sin_port = htons(server.port);
  server.s_in.sin_addr.s_addr = INADDR_ANY;
  setsockopt(server.fd, SOL_SOCKET, SO_REUSEADDR, \
	     (const char*)&server.reuse, sizeof(server.reuse));
  if ((listen_serv(&server, av[2])) == 1)
    return (1);
  if ((wait_client_cmd(&server)) == 1)
    return (1);
  if (close(server.fd) == -1)
    return (1);
  return (0);
}
