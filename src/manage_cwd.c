/*
** manage_cwd.c for manage_cwd in /home/oem/home/PSU_2016_myftp/src
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Sun May 21 15:04:55 2017 maxence.lauque
** Last update Sun May 21 17:51:44 2017 maxence.lauque
*/

#include "server.h"

void	cwd_from_parent(char *new_path, t_server *server, char *original_path)
{
  char  cwd[4096];

  if ((chdir(new_path)) == -1)
    write(server->client_fd, FAIL_CHDIR, strlen(FAIL_CHDIR));
  else
    {
      getcwd(cwd, sizeof(cwd));
      if (strlen(cwd) >= strlen(original_path))
        write(server->client_fd, GOOD_CHDIR, strlen(GOOD_CHDIR));
      else
        {
          chdir(original_path);
          write(server->client_fd, GOOD_CHDIR, strlen(GOOD_CHDIR));
        }
    }
}

void	cwd_from_curr_dir(t_server *server, char **tab_buff)
{
  char  actual_pwd[4096];
  char  new_pwd[4096];
  char  *cat_slash;
  char  *cat_new_path;

  getcwd(actual_pwd, sizeof(actual_pwd));
  cat_slash = strcat(actual_pwd, "/");
  cat_new_path = cat_path(cat_slash, tab_buff[1]);
  if ((chdir(cat_new_path)) == -1)
    write(server->client_fd, FAIL_CHDIR, strlen(FAIL_CHDIR));
  else
    {
      getcwd(new_pwd, sizeof(new_pwd));
      if (strlen(new_pwd) >= strlen(actual_pwd))
        write(server->client_fd, GOOD_CHDIR, strlen(GOOD_CHDIR));
      else
        {
          chdir(actual_pwd);
          write(server->client_fd, GOOD_CHDIR, strlen(GOOD_CHDIR));
        }
    }
}

void	cwd_cmd(char *buffer, t_server *server)
{
  char  **tab_buff;
  char  *new_path;
  char  *original_path;

  new_path = NULL;
  tab_buff = NULL;
  tab_buff = str_2_wordtab(tab_buff, buffer, ' ');
  original_path = server->original_path;
  if (tab_buff[1] != NULL && strlen(tab_buff[1]) > 1)
    {
      new_path = malloc(sizeof(char) * strlen(tab_buff[1])	\
                        + strlen(original_path) + 1);
      new_path = cat_path(original_path, tab_buff[1]);
      if (tab_buff[1][0] == '/')
        cwd_from_parent(new_path, server, original_path);
      else
        cwd_from_curr_dir(server, tab_buff);
    }
  else
    write(server->client_fd, FAIL_CHDIR, strlen(FAIL_CHDIR));
}
