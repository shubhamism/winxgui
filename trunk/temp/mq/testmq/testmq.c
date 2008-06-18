#include <pthread.h>
#include <mqueue.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define die(msg) { perror(msg); exit(EXIT_FAILURE); }

static void                     /* Thread start function */
tfunc(union sigval sv)
{
   struct mq_attr attr;
   ssize_t nr;
   void *buf;
   mqd_t mqdes = *((mqd_t *) sv.sival_ptr);

   /* Determine max. msg size; allocate buffer to receive msg */

   if (mq_getattr(mqdes, &attr) == -1) die("mq_getattr");
   buf = malloc(attr.mq_msgsize);
   if (buf == NULL) die("malloc");

   nr = mq_receive(mqdes, buf, attr.mq_msgsize, NULL);
   if (nr == -1) die("mq_receive");

   printf("Read %ld bytes from MQ\n", (long)nr);
   free(buf);
   exit(EXIT_SUCCESS);         /* Terminate the process */
}

int
main(int argc, char *argv[])
{
   mqd_t mqdes;
   struct sigevent not;

   if (argc != 2) {
     printf("usage: testmq <MQ>\n");
     return;
   }
   
   mqdes = mq_open(argv[1], O_RDONLY);
   if (mqdes == (mqd_t) -1) die("mq_open");

   not.sigev_notify = SIGEV_THREAD;
   not.sigev_notify_function = tfunc;
   not.sigev_notify_attributes = NULL;
   not.sigev_value.sival_ptr = &mqdes;   /* Arg. to thread func. */
   if (mq_notify(mqdes, &not) == -1) die("mq_notify");

   pause();    /* Process will be terminated by thread function */
}

