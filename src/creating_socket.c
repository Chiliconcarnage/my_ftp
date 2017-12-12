/*
** creating_socket.c for creating_socket in /home/oem/home/PSU_2016_myftp/src
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Sun May 21 14:47:24 2017 maxence.lauque
** Last update Sun May 21 18:57:00 2017 maxence.lauque
*/

#include "server.h"

int	manage_client_cmd(char *buffer, t_server *server)
{
  void  (*tab_cmd[14])(char *, t_server *);
  char  **tab_buff;

  tab_buff = NULL;
  tab_buff = str_2_wordtab(tab_buff, buffer, ' ');
  server->chose_func = 0;
  server->inc = 0;
  if (server->needed_pass == 1 && server->needed_pass != 1)
    pass_cmd(buffer, server);
  exec_client_cmd(server, tab_buff[0], tab_cmd, buffer);
  return (0);
}

int	manage_childproc(t_server *server)
{
  char  *buffer;

  handle_client(server->client_fd);
  while ((buffer = get_next_line(server->client_fd)) != 0)
    manage_client_cmd(buffer, server);
  if (close(server->client_fd) == -1)
    return (1);
  return (0);
}

int	while_client(t_server *server, int i)
{
  while (42)
    {
      server->client_fd = accept(server->fd, \
				 (struct sockaddr *)&server->s_in_client, &server->s_in_size);
      if (server->client_fd == -1)
        {
          if (close(server->fd) == -1)
            return (1);
          return (1);
        }
      server->pid = fork();
      if (server->pid == 0)
        {
          if ((manage_childproc(server)) == 1)
            return (1);
          if (waitpid(server->pid, NULL, 0) < 0)
            break ;
        }
      if (server->pid > 0)
	{
	  waitpid(-1, &i, WNOHANG);
	  close(server->client_fd);
	}
    }
  return (0);
}

int	wait_client_cmd(t_server *server)
{
  int	i;

  i = 0;
  server->login_succ = 0;
  server->needed_pass = 0;
  server->bad_user = 0;
  server->already_conn = 0;
  if ((while_client(server, i)) == 1)
    return (1);
  return (0);
}

int	init_socket(t_server *server, char **av)
{
  server->s_in_size = sizeof(server->s_in_client);
  server->port = atoi(av[1]);
  server->pe = getprotobyname("TCP");

  if (!server->pe || ((check_existing_dir(av[2])) == -1))
    return (1);
  server->fd = socket(AF_INET, SOCK_STREAM, server->pe->p_proto);
  if (server->fd == -1)
    return (1);
  return (0);
}
