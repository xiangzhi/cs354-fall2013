#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    if (argc != 3) {
	fprintf(stderr, "usage: intrev <inputfile> <outputfile>\n");
	exit(1);
    }

    char *infile; 
    char *outfile;
    infile = argv[1];
    outfile = argv[2];

    int fd = open(infile, O_RDONLY);
    int ofd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

    assert(fd > -1);

    struct stat* info;
    int check = fstat(fd, info);
    assert(check == 0);

    int size = info->st_size;
    //printf("%d", size);
    int *p = malloc(size);

    int count;
    int buf;
    int i = 0;
    int j = 0;
    count = read(fd,&buf,4);
    while(count == 4)
    {
        p[i] = buf;
        i++;
        printf("%d\n",buf);
        count = read(fd, &buf, 4);
    }

    for(j = i - 1; j >= 0;j--)
    {
        int rc = write(ofd, &(p[j]), sizeof(int));
        assert(rc == sizeof(int));
    }

    close(ofd);
    close(fd);
    return 0;
}

