#include "cube_test.h"

// Global variable to store child PID for signal handling
pid_t child_pid = -1;

void signal_handler(int sig)
{
	(void)sig;
	if (child_pid > 0)
	{
		kill(child_pid, SIGTERM);
		waitpid(child_pid, NULL, 0);
	}
}

void free_files(file_list_t *filestruct)
{
	for (int i = 0; i < filestruct->count; i++)
	{
		if (filestruct->files[i])
		{
			free(filestruct->files[i]);
			filestruct->files[i] = NULL;
		}
	}
	filestruct->count = 0;
}

int scan_directory(const char *dir_path, file_list_t *files)
{
	DIR *dir;
	struct dirent *entry;

	if (!files || !files->files)
	{
		printf(RED "Error: Invalid file list structure\n" RESET);
		return -1;
	}

	dir = opendir(dir_path);
	if (!dir)
	{
		printf(RED "Error: Cannot open directory %s\n" RESET, dir_path);
		return -1;
	}

	files->count = 0;

	// Initialize all pointers to NULL for safety
	for (int i = 0; i < MAX_FILES; i++)
		files->files[i] = NULL;

	while ((entry = readdir(dir)) != NULL && files->count < MAX_FILES - 1)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		// Only include .cub files and .txt files (for wrong extension test)
		char *ext = strrchr(entry->d_name, '.');
		if (ext && (strcmp(ext, ".cub") == 0 || strcmp(ext, ".txt") == 0))
		{
			files->files[files->count] = strdup(entry->d_name);
			if (!files->files[files->count])
			{
				printf(RED "Error: Memory allocation failed for filename\n" RESET);
				closedir(dir);
				return -1;
			}
			files->count++;
		}
	}

	closedir(dir);
	return files->count;
}

int test_bad_file(const char *filepath)
{
	char command[1024];
	snprintf(command, sizeof(command), "cd .. && timeout 2s ./cub3D '%s' >/dev/null 2>&1", filepath);

	int result = system(command);
	int exit_code = WEXITSTATUS(result);

	// If exit code is 1-127, it's an error (good for bad files)
	// If exit code is 124, it's a timeout (bad for bad files - means program started)
	if (exit_code >= 1 && exit_code <= 127 && exit_code != 124) {
		return 1; // PASS - program exited with error
	}
	return 0; // FAIL - program either timed out or exited normally
}

int test_good_file(const char *filepath)
{
	char command[1024];
	snprintf(command, sizeof(command), "cd .. && timeout 2s ./cub3D '%s' >/dev/null 2>&1", filepath);

	int result = system(command);
	int exit_code = WEXITSTATUS(result);

	// If exit code is 124, it's a timeout (good for good files - means program started)
	if (exit_code == 124) {
		return 1; // PASS - program started and was killed by timeout
	}
	return 0; // FAIL - program exited immediately (probably error)
}

void print_header(const char *title)
{
	printf("\n" BLUE "================================\n");
	printf("  %s\n", title);
	printf("================================\n" RESET);
}

void print_test_result(const char *filename, int passed, const char *type)
{
	const char *basename = strrchr(filename, '/');
	basename = basename ? basename + 1 : filename;

	if (passed) {
		printf(GREEN "✓ PASS" RESET " - %s: %s\n", type, basename);
	} else {
		printf(RED "✗ FAIL" RESET " - %s: %s\n", type, basename);
	}
}
