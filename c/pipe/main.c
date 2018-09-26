
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char** argv)
{
    int rc;
    int parent_to_child[2]; // parent writes, child reads
    int child_to_parent[2]; // parent reads, child writes
    int flags = 0;
    pid_t pid;


    rc = pipe2(parent_to_child, flags);
    if (rc < 0) {
        perror("pipe2(parent_to_child)");
        goto EXIT;
    }

    rc = pipe2(child_to_parent, flags);
    if (rc < 0) {
        perror("pipe2(child_to_parent)");
        goto EXIT;
    }


    pid = fork();

    if (pid < 0) {
        perror("fork");
        goto EXIT;
    }

    if (0 == pid) {
        // this is the child process. 

        char buf[64];
        int bufsize = sizeof buf;
        int byte_count;

        close(child_to_parent[0]); // close the read end of this channel
        close(parent_to_child[1]); // close the write end of this channel

        memset(&buf[0], 0, bufsize);


        while (0 < (byte_count = read(parent_to_child[0], buf, bufsize))) {
            printf("%s\n", buf);
        }
        close(parent_to_child[0]);

        write(child_to_parent[1], "he told me you killed him!", 26);
        close(child_to_parent[1]);

    }
    
    else {
        // this is the parent process. 

        char buf[64];
        int bufsize = sizeof buf;
        int byte_count;
        
        close(child_to_parent[1]); // close the write end of this channel
        close(parent_to_child[0]); // close the read end of this channel

        memset(&buf[0], 0, bufsize);

        write(parent_to_child[1], "Obi-Wan never told you about your father",40);
        close(parent_to_child[1]); // this will let the child drop out of the read loop

        while (0 < (byte_count = read(child_to_parent[0], buf, bufsize))) {
            printf("%s\n", buf);
        }
        close(child_to_parent[0]);

        wait(0); // wait for a child 

    }



EXIT:
    return 0;
}

