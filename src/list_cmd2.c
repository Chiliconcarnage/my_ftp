/*
** list_cmd2.c for list_cmd in /home/oem/home/PSU_2016_myftp/src
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Sun May 21 15:02:26 2017 maxence.lauque
** Last update Sun May 21 18:27:20 2017 maxence.lauque
*/

#include "server.h"

void	help_cmd(char *buffer, t_server *server)
{
  (void)buffer;
  write(server->client_fd, HELP, strlen(HELP));
}

void	quit_cmd(char *buffer, t_server *server)
{
  (void)buffer;
  (void)server;
  server->quit = 1;
  write(server->client_fd, "221 Goodbye.\r\n", strlen("221 Goodbye.\r\n"));
  close(server->fd);
  close(server->client_fd);
}


void	pwd_cmd(char *buffer, t_server *server)
{
  char  pwd[4096];

  getcwd(pwd, sizeof(pwd));
  dprintf(server->client_fd, "257 \"%s\"\r\n", pwd);
  (void)buffer;
  (void)server;
}

void	pasv_cmd(char *buffer, t_server *server)
{
  (void)buffer;
  (void)server;
}

void	port_cmd(char *buffer, t_server *server)
{
  (void)buffer;
  (void)server;
}
