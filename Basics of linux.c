#include <stdio.h>
#include <dirent.h>

int main() {
  DIR *dir;
  struct dirent *ent;
  dir = opendir(".");  // Open current directory

  if (dir != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      printf("%s\n", ent->d_name);
    }
    closedir(dir);
  } else {
    perror("opendir");
  }

  return 0;
}
