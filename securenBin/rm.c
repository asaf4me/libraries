#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>

#define LENGTH 39

const char* const blackList[] = {"/", "/aquota.group", "/aquota.user", "/backup", "/backups-test", "/bash", "/boot", "/daniel", "/dev",
										"/dumps", "/eli_install", "/error_log", "/etc", "/home", "/home2", "/idan", "/iscsi", "/logs", "/media",
										"/mnt", "/ofir", "/opt", "/proc", "/quota.group", "/quota.user", "/razor-agent.log", "/root", "/run", "/srv",
										"/svvedice.tar.gz", "/sys", "/tmp", "/usr", "/usr/bin", "/usr/lib", "/usr/lib64", "/usr/local/cpanel/scripts",
										"/usr/sbin", "/var"};

int startsWith(char *a, const char *b){
	if(strncmp(a, b, strlen(b)) == 0) return 1;
	return 0;
}

int forceFlagCheck(int argc, char *argv[])
{
	for(int i = 1 ; i < argc ; i++)
	{
		if(strcmp(argv[i], "-rf") == 0 || strcmp(argv[i], "-f") == 0)
			return 1;
	}
	return -1;
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

// Check for depth 1 permission
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
			continue;
		// Searching for argv[i] in the blacklist
		if(binarySearch(argv[i]) == 1)
		{
			printf("%s %s Permission denied\n", argv[0], argv[i]);
			return -1;
		}
		// Searching for blacklist folders in depth 1
		for(int j = 0 ; j < LENGTH ; j++)
		{
			if(startsWith(argv[i], blackList[j]) == 1)
			{
				if(recursivePermission(++argv[i]) == -1)
				{
					printf("%s %s Permission denied\n", argv[0], --argv[i]);
					return -1;
				}
				--argv[i];
			}
		}
		printf("%s\n", argv[i]);
	}
	return 1;
}

int main(int argc, char* argv[])
{
	if(forceFlagCheck(argc, argv) == 1)
	{
		if(validatePath(argc, argv) == -1)
			return -1;
	}
	// Plug and play, just change the core command
	execvp("/usr/bin/jet/rm", argv);
	return 1;
}
