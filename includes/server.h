/*
** server.h for server in /home/oem/home/PSU_2016_myftp/includes
** 
** Made by maxence.lauque
** Login   <lauque_m@epitech.net>
** 
** Started on  Wed May 10 14:07:15 2017 maxence.lauque
** Last update Sun May 21 19:16:46 2017 maxence.lauque
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>
#include "get_next_line.h"

#ifndef MY_H_
#define MY_H_

#define USAGE "Usage : ./server port path\n"
#define DELE "250 Requested file action okay, completed.\r\n"
#define BAD_DELE "450 File unavailable (e.g., file busy).\r\n"
#define GOOD_CHDIR "250 Directory successfully changed.\r\n"
#define FAIL_CHDIR "550 Failed to change directory.\r\n"
#define LOG_WITH "530 Please login with USER and PASS.\r\n"
#define UNK_CMD "500 Unknown command.\r\n"
#define BAD_LOG "530 Login incorrect.\r\n"
#define GOOD_LOG "230 Login successful.\r\n"
#define LOG_FIRST "503 Login with USER first.\r\n"
#define ALR_LOG "230 Already Logged in.\r\n"
#define PASS "331 Please specify the password.\r\n"
#define DENIED "530 Permission denied.\r\n"
#define GUEST "530 Can't change from guest user.\r\n"
#define HELP "214-The following commands are recognized.\r\n ABOR\
 ACCT ALLO APPE CDUP CWD DELE EPRT EPSV  FEAT HELP LIST MDTM MKD\r\n\
 MODE NLST NOOP OPTS PASS PASV PORT PWD  QUIT REIN REST RETR RMD  RNFR\r\n\
 RNTO SITE SIZE SMNT STAT STOR STOU STRU SYST TYPE USER XCUP XCWD XMKD\r\n\
 XPWD XRMD\r\n\
214 Help OK.\r\n"
#define NOOP "200 NOOP ok.\r\n"

typedef struct	s_server
{
  struct protoent       *pe;
  char			*original_path;
  int			chose_func;
  int			quit;
  int			inc;
  int                   fd;
  int			needed_pass;
  int			login_succ;
  int			bad_user;
  int			bad_cmd;
  int			already_conn;
  struct sockaddr_in    s_in;
  int                   port;
  struct sockaddr_in    s_in_client;
  socklen_t             s_in_size;
  int                   client_fd;
  int                   reuse;
  char                  *client_ip;
  pid_t                 pid;
}		t_server;

int	check_existing_dir(char *);
int	while_client(t_server *, int);
char	*to_lower(char *);
char	*cat_path(char *, char *);
int	my_strlen(char *);
void	list_cmd(char *, t_server *);
int	handle_client(int);
void	exec_client_cmd(t_server *, char *, \
			void (*tab_cmd[14])(char *, t_server *), char *);
int	listen_serv(t_server *, char *);
int	wait_client_cmd(t_server *);
int	init_socket(t_server *, char **);
char	**str_2_wordtab(char **, char *, char);
void    help_cmd(char *, t_server *);
void    username_cmd(char *, t_server *);
void    pass_cmd(char *, t_server *);
void    cwd_cmd(char *, t_server *);
void    cdup_cmd(char *, t_server *);
void    quit_cmd(char *, t_server *);
void    pwd_cmd(char *, t_server *);
void    pasv_cmd(char *, t_server *);
void    port_cmd(char *, t_server *);
void    noop_cmd(char *, t_server *);
void    retr_cmd(char *, t_server *);
void    stor_cmd(char *, t_server *);
void    list_cmd(char *, t_server *);
void    dele_cmd(char *, t_server *);

#endif
