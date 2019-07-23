#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
  if(argc < 3) {
    errx(EXIT_FAILURE, "Usage: %s <src_file> <dst_file>", argv[0]);
  } 
  int src;
  if((src = open(argv[1], O_RDONLY)) == -1) {
    err(EXIT_FAILURE, "Failed to open src file %s", argv[1]);
  }
  int dst;
  if((dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    close(src);
    err(EXIT_FAILURE, "Failed to open dst file %s", argv[1]);
  }
  char buf[4096];
  int ret;
  while((ret = read(src, buf, sizeof(buf))) > 0)
    write(dst, buf, ret);
  if(ret == -1)
    warn("copy failed");
  close(src);
  close(dst);
  return 0;
}
