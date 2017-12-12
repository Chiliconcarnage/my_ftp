/*
** usr_pass.c for usr_pass in /home/oem/home/PSU_2016_myftp/src
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Sun May 21 15:14:19 2017 maxence.lauque
** Last update Sun May 21 15:35:45 2017 maxence.lauque
*/

#include "server.h"

void	username_cmd(char *buffer, t_server *server)
{
  char  **tab_buff;

  tab_buff = NULL;
  tab_buff = str_2_wordtab(tab_buff, buffer, ' ');
  if (server->already_conn == 1)
    write(server->client_fd, GUEST, strlen(GUEST));
  else if (tab_buff[1] == NULL)
    {
      write(server->client_fd, DENIED, strlen(DENIED));
      server->needed_pass = 0;
    }
  else if (server->login_succ == 0 &&
           ((strncmp(tab_buff[1], "anonymous", 9) == 0))
	   && (tab_buff[2] == NULL))
    {
      write(server->client_fd, PASS, strlen(PASS));
      server->needed_pass = 1;
      server->bad_user = 0;
    }
  else if (server->login_succ == 0 && tab_buff[1] != NULL)
    {
      write(server->client_fd, PASS, strlen(PASS));
      server->needed_pass = 1;
      server->bad_user = 1;
    }
}

void	pass_cmd(char *buffer, t_server *server)
{
  char  **tab_buff;

  tab_buff = NULL;
  tab_buff = str_2_wordtab(tab_buff, buffer, ' ');
  if (server->bad_user == 0)
    {
      if ((server->login_succ == 1 && server->needed_pass == 1)
          || server->already_conn == 1)
        write(server->client_fd, ALR_LOG, strlen(ALR_LOG));
      else if (server->needed_pass == 0)
        write(server->client_fd, LOG_FIRST, strlen(LOG_FIRST));
      else if (server->needed_pass == 1 &&
               (strncmp(tab_buff[0], "pass", 4) == 0) &&
               ((strlen(tab_buff[0]) == 5) || (strlen(tab_buff[0]) == 4)))
        {
          write(server->client_fd, GOOD_LOG, strlen(GOOD_LOG));
          server->already_conn = 1;
        }
      else
        write(server->client_fd, LOG_WITH, strlen(LOG_WITH));
    }
  else if (strlen(tab_buff[0]) == 4 || strlen(tab_buff[0]) == 5)
    write(server->client_fd, BAD_LOG, strlen(BAD_LOG));
  else
    write(server->client_fd, LOG_WITH, strlen(LOG_WITH));
}

void	cdup_cmd(char *buffer, t_server *server)
{
  (void)buffer;
  if ((chdir(server->original_path)) == -1)
    write(server->client_fd, FAIL_CHDIR, strlen(FAIL_CHDIR));
  else
    write(server->client_fd, GOOD_CHDIR, strlen(GOOD_CHDIR));
}
