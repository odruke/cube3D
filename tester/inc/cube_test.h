#ifndef CUBE_TEST_H
# define CUBE_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/select.h>
#include <limits.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
// #include <X11/extensions/XTest.h>

#define MAX_FILES 100
#define MAX_PATH 512
#define BUFFER_SIZE 1024
#define TEST_TIMEOUT_GOOD 4
#define TEST_TIMEOUT_BAD 2
#define CONTINUE 0
#define RESET_GNL 1

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

typedef struct
{
	char	**files;  // Changed to array of pointers (dynamically allocated)
	int		count;
}	file_list_t;

typedef struct s_fd
{
	int		fd;
	char	*filename;
}	t_fd;

// Global variable
extern pid_t child_pid;

// Function declarations
void	signal_handler(int sig);
int		scan_directory(const char *dir_path, file_list_t *files);
int		test_bad_file(const char *filepath);
int		test_good_file(const char *filepath);
void	print_header(const char *title);
void	print_test_result(const char *filename, int passed, const char *type);
char	*get_next_line(t_fd fd, int reset);
int		test_bad_input(void);
void	launch_game(char *full_path, int *pipefd);
int		send_scp(pid_t pid);
int		send_escape_key_x11(pid_t pid);

// Memory management functions
file_list_t* allocate_file_list(void);
void free_file_list(file_list_t *list);

#endif
