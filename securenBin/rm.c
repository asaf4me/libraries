#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>

#define LENGTH 0

const char* const blackList[] = {};

int StartsWith(char *a, const char *b){
	if(strncmp(a, b, strlen(b)) == 0) return 1;
	return 0;
}

// Return 1 if the param is found in blacklist
int binarySearch(char* param){
	int i = 0, j = LENGTH - 1;
	while(i <= j){
		int mid = i + (j - i) / 2, res = strcmp(param, blackList[mid]);
		if(res == 0)
			return 1;
		if(res > 0)
			i = mid + 1;
		else
			j = mid - 1;
	}
	return -1;
}

int recursivePermission(char *param){
	char *ptr = strchr(param,'/');
	if(ptr != NULL)
	{
		ptr = strchr(++ptr,'/');
		if(ptr == NULL)
			return -1;
	}
	return 1;
}

// Validating that you can do the command on this argv
int validatePath(int argc, char* argv[]){
	char absulote[PATH_MAX];
	for(int i = 1 ; i < argc ; i++)
	{
		// Get the absolute path instead relative one
		argv[i] = realpath(argv[i], absulote);
		if (argv[i] == NULL)
		{
			perror("realpath() error");
			return -1;
		}
		// Searching for argv[i] in the blacklist
		if(binarySearch(argv[i]) == 1)
		{
			printf("%s %s Permission denied\n", argv[0], argv[i]);
			return -1;
		}
		if(StartsWith(argv[i], "/boot") == 1 || StartsWith(argv[i], "/home2") == 1 || StartsWith(argv[i], "/home") == 1 || StartsWith(argv[i], "/etc") == 1 || StartsWith(argv[i], "/usr") == 1 || StartsWith(argv[i], "/root") == 1 || StartsWith(argv[i], "/run") == 1)
		{
			if(recursivePermission(++argv[i]) == -1){
				printf("%s %s Permission denied\n", argv[0], --argv[i]);
				return -1;
			}
			--argv[i];
		}
		printf("%s\n", argv[i]);
	}
	return 1;
}

int main(int argc, char* argv[])
{
	if(validatePath(argc, argv) == -1)
		return -1;
	// Plug and play, just change the core command
	// execvp("/usr/bin/rm", argv);
	return 1;
}
