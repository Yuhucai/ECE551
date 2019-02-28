#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//This function is for Step 1
void step1(char * filename) {
  struct stat sb;
  if (lstat(filename, &sb) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }
  //first line
  if (S_ISLNK(sb.st_mode)) {
    char linktarget[256];
    ssize_t len = readlink(filename, linktarget, 256);
    linktarget[len] = '\0';
    printf("  File: %s -> %s\n", filename, linktarget);
  }
  else {
    printf("  File: %s\n", filename);
  }
  //second line
  printf(
      "  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu ", sb.st_size, sb.st_blocks, sb.st_blksize);
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      printf("block special file\n");
      break;
    case S_IFCHR:
      printf("character special file\n");
      break;
    case S_IFDIR:
      printf("directory\n");
      break;
    case S_IFIFO:
      printf("fifo\n");
      break;
    case S_IFLNK:
      printf("symbolic link\n");
      break;
    case S_IFREG:
      printf("regular file\n");
      break;
    case S_IFSOCK:
      printf("socket\n");
      break;
    default:
      printf("unknown?\n");
      break;
  }
  //third line
  if (S_ISCHR(sb.st_mode) == 1 || S_ISBLK(sb.st_mode) == 1) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink,
           major(sb.st_rdev),
           minor(sb.st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink);
  }
}
//This function is for Step 2&3
void step2(char * filename) {
  struct stat sb;
  if (lstat(filename, &sb) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }
  //fourth line
  char string[11] = {0};
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      string[0] = 'b';
      break;
    case S_IFCHR:
      string[0] = 'c';
      break;
    case S_IFDIR:
      string[0] = 'd';
      break;
    case S_IFIFO:
      string[0] = 'p';
      break;
    case S_IFLNK:
      string[0] = 'l';
      break;
    case S_IFREG:
      string[0] = '-';
      break;
    case S_IFSOCK:
      string[0] = 's';
      break;
  }
  switch (sb.st_mode & S_IRUSR) {
    case 0:
      string[1] = '-';
      break;
    default:
      string[1] = 'r';
      break;
  }
  switch (sb.st_mode & S_IWUSR) {
    case 0:
      string[2] = '-';
      break;
    default:
      string[2] = 'w';
      break;
  }
  switch (sb.st_mode & S_IXUSR) {
    case 0:
      string[3] = '-';
      break;
    default:
      string[3] = 'x';
      break;
  }
  switch (sb.st_mode & S_IRGRP) {
    case 0:
      string[4] = '-';
      break;
    default:
      string[4] = 'r';
      break;
  }
  switch (sb.st_mode & S_IWGRP) {
    case 0:
      string[5] = '-';
      break;
    default:
      string[5] = 'w';
      break;
  }
  switch (sb.st_mode & S_IXGRP) {
    case 0:
      string[6] = '-';
      break;
    default:
      string[6] = 'x';
      break;
  }
  switch (sb.st_mode & S_IROTH) {
    case 0:
      string[7] = '-';
      break;
    default:
      string[7] = 'r';
      break;
  }
  switch (sb.st_mode & S_IWOTH) {
    case 0:
      string[8] = '-';
      break;
    default:
      string[8] = 'w';
      break;
  }
  switch (sb.st_mode & S_IXOTH) {
    case 0:
      string[9] = '-';
      break;
    default:
      string[9] = 'x';
      break;
  }
  //Step 3
  struct passwd * name = getpwuid(sb.st_uid);
  if (name == NULL) {
    fprintf(stderr, "can not find user name\n");
    exit(EXIT_FAILURE);
  }
  char * username = name->pw_name;
  struct group * gname = getgrgid(sb.st_gid);
  if (gname == NULL) {
    fprintf(stderr, "can not find group name\n");
    exit(EXIT_FAILURE);
  }
  char * groupname = gname->gr_name;
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         sb.st_mode & ~S_IFMT,
         string,
         sb.st_uid,
         username,
         sb.st_gid,
         groupname);
}

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

void step4(char * filename) {
  struct stat sb;
  if (lstat(filename, &sb) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }
  char * atimestr = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
  char * mtimestr = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
  char * ctimestr = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
  printf("Access: %s\n", atimestr);
  printf("Modify: %s\n", mtimestr);
  printf("Change: %s\n", ctimestr);
  printf(" Birth: -\n");
  free(atimestr);
  free(mtimestr);
  free(ctimestr);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage:%s <pathname>\n", argv[0]);
    return EXIT_FAILURE;
  }
  for (int i = 1; i < argc; i++) {
    char * filename = argv[i];
    //first three line
    step1(filename);
    //forth line
    step2(filename);
    //last three line
    step4(filename);
  }
  return EXIT_SUCCESS;
}
