#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <message.h>
#include <netsocket.h>
#include <node_server.h>
#include <init_instance.h>
#include <master_server.h>
#include <save_state.h>
#include <save_manager.h>
#include <delete_chkpts.h>
#include <object_write_buffer.h>
#include <read_setup.h>
#include <ccp.h>
#include <streamit_random.h>
#include "global.h"
#include <limits.h>
int __max_iteration;
int __timer_enabled = 0;
int __frequency_of_chkpts;
int __out_data_buffer;
vector <thread_info*> thread_list;
netsocket *server = NULL;
unsigned __ccp_ip = 0;
int __init_iter = 0;

unsigned myip;

extern void __declare_sockets_0();
extern thread_info *__get_thread_info_0();
extern void run_0();
pthread_attr_t __pthread_attr_0;
pthread_t __pthread_0;
static void *run_thread_0(void *param) {
  run_0();
}
extern void __declare_sockets_1();
extern thread_info *__get_thread_info_1();
extern void run_1();
pthread_attr_t __pthread_attr_1;
pthread_t __pthread_1;
static void *run_thread_1(void *param) {
  run_1();
}
extern void __declare_sockets_2();
extern thread_info *__get_thread_info_2();
extern void run_2();
pthread_attr_t __pthread_attr_2;
pthread_t __pthread_2;
static void *run_thread_2(void *param) {
  run_2();
}
extern void __declare_sockets_3();
extern thread_info *__get_thread_info_3();
extern void run_3();
pthread_attr_t __pthread_attr_3;
pthread_t __pthread_3;
static void *run_thread_3(void *param) {
  run_3();
}

static void *run_join(void *param) {
  if (myip == init_instance::get_thread_ip(0)) {
    pthread_join(__pthread_0, NULL);
    __get_thread_info_0()->set_active(false);
  }
  if (myip == init_instance::get_thread_ip(1)) {
    pthread_join(__pthread_1, NULL);
    __get_thread_info_1()->set_active(false);
  }
  if (myip == init_instance::get_thread_ip(2)) {
    pthread_join(__pthread_2, NULL);
    __get_thread_info_2()->set_active(false);
  }
  if (myip == init_instance::get_thread_ip(3)) {
    pthread_join(__pthread_3, NULL);
    __get_thread_info_3()->set_active(false);
  }
  sleep(1);
  if (__ccp_ip != 0) for(;;) sleep(1);
  exit(0);
}

int master_pid;

void init() {
  if (myip == init_instance::get_thread_ip(0)) {
    __declare_sockets_0();
  }
  if (myip == init_instance::get_thread_ip(1)) {
    __declare_sockets_1();
  }
  if (myip == init_instance::get_thread_ip(2)) {
    __declare_sockets_2();
  }
  if (myip == init_instance::get_thread_ip(3)) {
    __declare_sockets_3();
  }
  init_instance::initialize_sockets();
  if (myip == init_instance::get_thread_ip(0)) {
    thread_info *info = __get_thread_info_0();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_0, PTHREAD_STACK_MIN+5671356);
    pthread_create(&__pthread_0, &__pthread_attr_0, run_thread_0, (void*)"thread0");
    info->set_pthread(__pthread_0);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(1)) {
    thread_info *info = __get_thread_info_1();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_1, PTHREAD_STACK_MIN+1057604);
    pthread_create(&__pthread_1, &__pthread_attr_1, run_thread_1, (void*)"thread1");
    info->set_pthread(__pthread_1);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(2)) {
    thread_info *info = __get_thread_info_2();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_2, PTHREAD_STACK_MIN+1057604);
    pthread_create(&__pthread_2, &__pthread_attr_2, run_thread_2, (void*)"thread2");
    info->set_pthread(__pthread_2);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(3)) {
    thread_info *info = __get_thread_info_3();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_3, PTHREAD_STACK_MIN+1062123);
    pthread_create(&__pthread_3, &__pthread_attr_3, run_thread_3, (void*)"thread3");
    info->set_pthread(__pthread_3);
    info->set_active(true);
  }
  pthread_t id;
  pthread_create(&id, NULL, run_join, NULL);
}

int main(int argc, char **argv) {
  thread_info *t_info;
  t_info = __get_thread_info_0();
  thread_list.push_back(t_info);
  t_info = __get_thread_info_1();
  thread_list.push_back(t_info);
  t_info = __get_thread_info_2();
  thread_list.push_back(t_info);
  t_info = __get_thread_info_3();
  thread_list.push_back(t_info);

  myip = get_myip();
  read_setup::read_setup_file();
  __frequency_of_chkpts = read_setup::freq_of_chkpts;
  __out_data_buffer = read_setup::out_data_buffer;
  __max_iteration = read_setup::max_iteration;
  master_pid = getpid();
  for (int a = 1; a < argc; a++) {
    if (argc > a + 1 && strcmp(argv[a], "-init") == 0) {
       int tmp;
       sscanf(argv[a + 1], "%d", &tmp);
#ifdef VERBOSE
       fprintf(stderr,"Initial Iteration: %d\n", tmp);
#endif
       __init_iter = tmp;       init_instance::set_start_iter(__init_iter);    }
    if (argc > a + 1 && strcmp(argv[a], "-i") == 0) {
       int tmp;
       sscanf(argv[a + 1], "%d", &tmp);
#ifdef VERBOSE
       fprintf(stderr,"Number of Iterations: %d\n", tmp);
#endif
       __max_iteration = tmp;    }
    if (strcmp(argv[a], "-t") == 0) {
#ifdef VERBOSE
       fprintf(stderr,"Timer enabled.\n");
#endif
       __timer_enabled = 1;    }
    if (argc > a + 1 && strcmp(argv[a], "-ccp") == 0) {
#ifdef VERBOSE
       fprintf(stderr,"CCP address: %s\n", argv[a + 1]);
#endif
       __ccp_ip = lookup_ip(argv[a + 1]);
    }
    if (strcmp(argv[a], "-runccp") == 0) {
      int tmp = 1;
      if (argc > a + 1 && argv[a+1][0] >= '1' &&  argv[a+1][0] <= '9' ) {
        sscanf(argv[a + 1], "%d", &tmp);
      }
#ifdef VERBOSE
      fprintf(stderr,"RUNCCP number of init nodes is: %d\n", tmp);
#endif
      ccp c(thread_list, tmp);
      if (__init_iter > 0) c.set_init_iter(__init_iter);
      (new delete_chkpts())->start();
      c.run_ccp();
    }
    if (strcmp(argv[a], "-console") == 0) {
      char line[256], tmp;
      master_server *m = new master_server();
      m->print_commands();
      for (;;) {
        fprintf(stderr,"master> ");fflush(stdout);
        line[0] = 0;
        scanf("%[^\n]", line);scanf("%c", &tmp);
        m->process_command(line);
      }
    }
  }

  __global__init();

  (new save_manager())->start();
  node_server *node = new node_server(thread_list, init);

  node->run(__ccp_ip);
}
