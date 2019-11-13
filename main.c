#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int dev_rand() {
    int file, buffer;
    if ((file = open("/dev/random", O_RDONLY)) < 0) {
        printf("Error %d: %s\n", errno, strerror(errno));
    }
    if ((read(file, &buffer, sizeof(int))) < 0) {
        printf("Error %d: %s\n", errno, strerror(errno));
    }
    close(file);
    return buffer;
}

int main() {

    //POPULATION
    int randarr[10];
    printf("Populating array...\n");
    for (int i = 0; i < 10; i++) {
        randarr[i] = dev_rand();
    }
    printf("Printing array of 10 random ints:\n");
    for (int i = 0; i < 10; i++) {
        printf("Random int at index %d: %d\n", i, randarr[i]);
    }

    //WRITING
    int write_target;
    if ((write_target = open("nums", O_RDWR | O_CREAT)) < 0) {
        printf("Error %d: %s\n", errno, strerror(errno));
    }
    printf("Writing random array...");
    write(write_target, randarr, sizeof(randarr));
    close(write_target);

    //READING
    int read_target;
    if ((read_target = open("nums", O_RDONLY)) < 0) {
        printf("Error %d: %s\n", errno, strerror(errno));
    }
    int read_ints[10];
    if (read(read_target, read_ints, sizeof(read_ints)) < 0) {
        printf("Error %d: %s\n", errno, strerror(errno));
    }
    printf("Printing array read from file:\n");
    for (int i = 0; i < 10; i++) {
        printf("Int at index %d: %d\n", i, read_ints[i]);
    }

}