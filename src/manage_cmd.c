/*
** manage_cmd.c for manage_cmd in /home/oem/home/PSU_2016_myftp/src
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Sun May 21 14:52:50 2017 maxence.lauque
** Last update Sun May 21 18:51:43 2017 maxence.lauque
*/

#include "server.h"

int	not_log_yet(char *buffer, t_server *server, \
		    void(*tab_cmd[14])(char *buffer, t_server *server), char *finder[14])
{
  int   chose_func;
  (void)tab_cmd;

  chose_func = 0;
  if (server->already_conn == 1)
    return (0);
  if (server->needed_pass == 1 && server->needed_pass != 1)
    pass_cmd(buffer, server);
  while (chose_func < 2)
    {
      if ((strncmp(to_lower(buffer), finder[chose_func], 3)) == 0)
        return (0);
      chose_func++;
    }
  return (1);
}

void	init_tab_finder(char *finder[14])
{
  finder[0] = "user";
  finder[1] = "pass";
  finder[2] = "cwd";
  finder[3] = "cdup";
  finder[4] = "quit";
  finder[5] = "dele";
  finder[6] = "pwd";
  finder[7] = "pasv";
  finder[8] = "port";
  finder[9] = "help";
  finder[10] = "noop";
  finder[11] = "retr";
  finder[12] = "stor";
  finder[13] = "list";
}

void	init_tab_pointer(char *finder[14], \
			 void (*tab_cmd[14])(char *, t_server *))
{
  init_tab_finder(finder);
  tab_cmd[0] = &username_cmd;
  tab_cmd[1] = &pass_cmd;
  tab_cmd[2] = &cwd_cmd;
  tab_cmd[3] = &cdup_cmd;
  tab_cmd[4] = &quit_cmd;
  tab_cmd[5] = &dele_cmd;
  tab_cmd[6] = &pwd_cmd;
  tab_cmd[7] = &pasv_cmd;
  tab_cmd[8] = &port_cmd;
  tab_cmd[9] = &help_cmd;
  tab_cmd[10] = &noop_cmd;
  tab_cmd[11] = &retr_cmd;
  tab_cmd[12] = &stor_cmd;
  tab_cmd[13] = &list_cmd;
}

void	exec_client_cmd(t_server *server, char *first_arg, \
			void    (*tab_cmd[14])(char *, t_server *), char *buffer)
{
  char  *finder[14];

  init_tab_pointer(finder, tab_cmd);
  if ((strncmp(to_lower(first_arg), finder[4], 4)) == 0)
    quit_cmd(buffer, server);
  else if ((not_log_yet(buffer, server, tab_cmd, finder)) == 0)
    {
      while (server->chose_func < 14)
        {
          if ((strncmp(to_lower(first_arg), \
	     finder[server->chose_func], 3)) == 0)
            {
              (*tab_cmd[server->chose_func])(buffer, server);
              server->inc++;
            }
          server->chose_func++;
        }
      if (server->inc == 0)
        write(server->client_fd, UNK_CMD, strlen(UNK_CMD));
    }
  else
    write(server->client_fd, LOG_WITH, strlen(LOG_WITH));
}
