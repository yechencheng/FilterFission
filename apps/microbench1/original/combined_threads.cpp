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

void __declare_sockets_0();
thread_info *__get_thread_info_0();
void run_0();
pthread_attr_t __pthread_attr_0;
pthread_t __pthread_0;
static void *run_thread_0(void *param) {
  run_0();
}
void __declare_sockets_1();
thread_info *__get_thread_info_1();
void run_1();
pthread_attr_t __pthread_attr_1;
pthread_t __pthread_1;
static void *run_thread_1(void *param) {
  run_1();
}
void __declare_sockets_2();
thread_info *__get_thread_info_2();
void run_2();
pthread_attr_t __pthread_attr_2;
pthread_t __pthread_2;
static void *run_thread_2(void *param) {
  run_2();
}
void __declare_sockets_3();
thread_info *__get_thread_info_3();
void run_3();
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
    pthread_attr_setstacksize(&__pthread_attr_0, PTHREAD_STACK_MIN+14889810);
    pthread_create(&__pthread_0, &__pthread_attr_0, run_thread_0, (void*)"thread0");
    info->set_pthread(__pthread_0);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(1)) {
    thread_info *info = __get_thread_info_1();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_1, PTHREAD_STACK_MIN+10276062);
    pthread_create(&__pthread_1, &__pthread_attr_1, run_thread_1, (void*)"thread1");
    info->set_pthread(__pthread_1);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(2)) {
    thread_info *info = __get_thread_info_2();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_2, PTHREAD_STACK_MIN+10276062);
    pthread_create(&__pthread_2, &__pthread_attr_2, run_thread_2, (void*)"thread2");
    info->set_pthread(__pthread_2);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(3)) {
    thread_info *info = __get_thread_info_3();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_3, PTHREAD_STACK_MIN+14889810);
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

// moved or inserted by concat_cluster_threads.pl
void __push_2_3(int);
void __push_1_2(int);
message *__msg_stack_1;
void __push_0_1(int);
message *__msg_stack_3;
message *__msg_stack_0;
message *__msg_stack_2;

// end of moved or inserted by concat_cluster_threads.pl

#include <math.h>

void __global__init() { }
// peek: 0 pop: 0 push 1048576
// init counts: 0 steady counts: 1

// ClusterFusion isEliminated: false


#include <mysocket.h>
#include <sdep.h>
#include <timer.h>
#include <thread_info.h>
#include <consumer2.h>
#include <consumer2p.h>
#include <producer2.h>
#include "cluster.h"
#include "fusion.h"

int __number_of_iterations_0;
int __counter_0 = 0;
int __steady_0 = 0;
int __tmp_0 = 0;
int __tmp2_0 = 0;
int *__state_flag_0 = NULL;
thread_info *__thread_0 = NULL;

producer2<int> __producer_0_1;
    // this-part:1 dst-part:2


void save_file_pointer__0(object_write_buffer *buf);
void load_file_pointer__0(object_write_buffer *buf);

void __write_thread__0(object_write_buffer *buf) {
  save_file_pointer__0(buf);
  __producer_0_1.write_object(buf);
}

void __read_thread__0(object_write_buffer *buf) {
  load_file_pointer__0(buf);
  __producer_0_1.read_object(buf);
}

inline void check_status__0() {
  check_thread_status(__state_flag_0, __thread_0);
}

void check_status_during_io__0() {
  check_thread_status_during_io(__state_flag_0, __thread_0);
}

void __init_thread_info_0(thread_info *info) {
  info->add_outgoing_data_connection(new connection_info(0,1,&__producer_0_1));
  __state_flag_0 = info->get_state_flag();
}

thread_info *__get_thread_info_0() {
  if (__thread_0 != NULL) return __thread_0;
  __thread_0 = new thread_info(0, check_status_during_io__0);
  __init_thread_info_0(__thread_0);
  return __thread_0;
}

void __declare_sockets_0() {
  init_instance::add_outgoing(0,1, DATA_SOCKET);
}

void __init_sockets_0(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_outgoing_socket(0,1,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __producer_0_1.set_socket(sock);
  __producer_0_1.init();

}

void __flush_sockets_0() {
  __producer_0_1.flush();
  __producer_0_1.get_socket()->close();
  __producer_0_1.delete_socket_obj();
}

void __peek_sockets_0() {
}

 
void init__57__0(); 
void init__1__44__0(); 
void init__5__48__0();
inline void check_status__0();

void work__56__0(int);

// upstreamDeclarationExtern cluster_0_1
// upstreamDeclaration cluster_0_1
int __pop_buffer_0_1[10240];
int __pop_index_0_1 = 0;
inline void __push_0_1(int data) {
__producer_0_1.push(data);
}

 
void init__57__0(){
  init__1__44__0();
  init__5__48__0();
}
 
void init__1__44__0(){
}
 
void init__5__48__0(){
}
void save_file_pointer__0(object_write_buffer *buf) {}
void load_file_pointer__0(object_write_buffer *buf) {}
 
void work__56__0(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[1048576] = {0};/* int[1048576] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int i__2__45 = 0;/* int */
      int tmp1__6__49[1048576] = {0};/* int[1048576] */
      int tmp2__7__50[1048576] = {0};/* int[1048576] */
      int i__conflict__2__8__51 = 0;/* int */
      int i__conflict__1__9__52 = 0;/* int */
      int i__conflict__0__10__53 = 0;/* int */
      int i__11__54 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      // mark begin: SIRFilter source

      for ((i__2__45 = 0)/*int*/; (i__2__45 < 1048576); (i__2__45++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = 1048576)/*int*/;
      }
      // mark end: SIRFilter source

      // mark begin: SIRFilter process

      for ((i__conflict__2__8__51 = 0)/*int*/; (i__conflict__2__8__51 < 1048576); (i__conflict__2__8__51++)) {((tmp1__6__49[(int)i__conflict__2__8__51]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
      }
      for ((i__conflict__1__9__52 = 0)/*int*/; (i__conflict__1__9__52 < 1048576); (i__conflict__1__9__52++)) {((tmp1__6__49[(int)i__conflict__1__9__52])++);
      }
      for ((i__conflict__0__10__53 = 0)/*int*/; (i__conflict__0__10__53 < 1048576); (i__conflict__0__10__53++)) {((tmp2__7__50[(int)i__conflict__0__10__53]) = ((tmp1__6__49[(int)i__conflict__0__10__53]) + 1))/*int*/;
      }
      for ((i__11__54 = 0)/*int*/; (i__11__54 < 1048576); (i__11__54++)) {__push_0_1((tmp2__7__50[(int)i__11__54]));
      }
      // mark end: SIRFilter process

    }
  }
}

void __init_state_0() {
  init__57__0();
  if (save_state::load_state(0, &__steady_0, __read_thread__0) == -1) pthread_exit(NULL);
}

static void __main__0() {
  int _tmp; // modified
  int _steady = __steady_0;
  int _number = __max_iteration;

  if (_steady == 0) {
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__0();
      if (*__state_flag_0 == EXIT_THREAD) exit_thread(__thread_0);
      work__56__0(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_0, _steady, __write_thread__0);
#endif // __CHECKPOINT_FREQ
  }
}

void run_0() {
  __init_sockets_0(check_status_during_io__0);
  __init_state_0();

  timer t1;
  __peek_sockets_0();
  t1.start();
  __main__0();
  t1.stop();
  if (__timer_enabled) t1.output(stderr);

  __flush_sockets_0();
  pthread_exit(NULL);
}
// peek: 1048576 pop: 1048576 push 1048576
// init counts: 0 steady counts: 1

// ClusterFusion isEliminated: false



int __number_of_iterations_1;
int __counter_1 = 0;
int __steady_1 = 0;
int __tmp_1 = 0;
int __tmp2_1 = 0;
int *__state_flag_1 = NULL;
thread_info *__thread_1 = NULL;

consumer2<int> __consumer_0_1;
producer2<int> __producer_1_2;
    // this-part:2 dst-part:3


void save_peek_buffer__1(object_write_buffer *buf);
void load_peek_buffer__1(object_write_buffer *buf);
void save_file_pointer__1(object_write_buffer *buf);
void load_file_pointer__1(object_write_buffer *buf);

void __write_thread__1(object_write_buffer *buf) {
  __consumer_0_1.write_object(buf);
  save_peek_buffer__1(buf);
  save_file_pointer__1(buf);
  __producer_1_2.write_object(buf);
}

void __read_thread__1(object_write_buffer *buf) {
  __consumer_0_1.read_object(buf);
  load_peek_buffer__1(buf);
  load_file_pointer__1(buf);
  __producer_1_2.read_object(buf);
}

inline void check_status__1() {
  check_thread_status(__state_flag_1, __thread_1);
}

void check_status_during_io__1() {
  check_thread_status_during_io(__state_flag_1, __thread_1);
}

void __init_thread_info_1(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(0,1,&__consumer_0_1));
  info->add_outgoing_data_connection(new connection_info(1,2,&__producer_1_2));
  __state_flag_1 = info->get_state_flag();
}

thread_info *__get_thread_info_1() {
  if (__thread_1 != NULL) return __thread_1;
  __thread_1 = new thread_info(1, check_status_during_io__1);
  __init_thread_info_1(__thread_1);
  return __thread_1;
}

void __declare_sockets_1() {
  init_instance::add_incoming(0,1, DATA_SOCKET);
  init_instance::add_outgoing(1,2, DATA_SOCKET);
}

void __init_sockets_1(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(0,1,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_0_1.set_socket(sock);
  __consumer_0_1.init();

  sock = init_instance::get_outgoing_socket(1,2,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __producer_1_2.set_socket(sock);
  __producer_1_2.init();

}

void __flush_sockets_1() {
  __producer_1_2.flush();
  __producer_1_2.get_socket()->close();
  __producer_1_2.delete_socket_obj();
  __consumer_0_1.delete_socket_obj();
}

void __peek_sockets_1() {
  __consumer_0_1.peek(0);
}

 
void init__14__1();
inline void check_status__1();

void work__13__1(int);

// downstreamDeclarationExtern cluster_0_1
// downstreamDeclaration cluster_0_1:
int __pop_buf__1[1048576];
int __head__1;
int __tail__1;

inline void __init_pop_buf__1() {
  __tail__1=0;
  __head__1=0;
}

void save_peek_buffer__1(object_write_buffer *buf) {
  int i = 0, offs = __tail__1;
  while (offs != __head__1) {
    buf->write(&__pop_buf__1[offs], sizeof(int ));
    offs++;
    offs&=1048575;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__1(object_write_buffer *buf) {
  __tail__1=0;
  __head__1=0;
}

inline void __update_pop_buf__1() {
for (int i = 0; i < 1048576; i++) {
  __pop_buf__1[i]=__consumer_0_1.pop();
}
  __tail__1 = 0;
  __head__1 = 1048576;
}


inline int __pop_0_1() {
return __pop_buf__1[__tail__1++];
}

inline void __pop_0_1(int n) {
__tail__1+=n;
return;
}

inline int __peek_0_1(int offs) {
return __pop_buf__1[(__tail__1+offs)];
  }


// upstreamDeclarationExtern cluster_1_2
// upstreamDeclaration cluster_1_2
int __pop_buffer_1_2[10240];
int __pop_index_1_2 = 0;
inline void __push_1_2(int data) {
__producer_1_2.push(data);
}

 
void init__14__1(){
}
void save_file_pointer__1(object_write_buffer *buf) {}
void load_file_pointer__1(object_write_buffer *buf) {}
 
void work__13__1(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int tmp1__15[1048576] = {0};/* int[1048576] */
      int tmp2__16[1048576] = {0};/* int[1048576] */
      int i__conflict__2__17 = 0;/* int */
      int i__conflict__1__18 = 0;/* int */
      int i__conflict__0__19 = 0;/* int */
      int i__20 = 0;/* int */

      // mark begin: SIRFilter process

      for ((i__conflict__2__17 = 0)/*int*/; (i__conflict__2__17 < 1048576); (i__conflict__2__17++)) {(tmp1__15[(int)i__conflict__2__17]) = __pop_0_1();
;
      }
      for ((i__conflict__1__18 = 0)/*int*/; (i__conflict__1__18 < 1048576); (i__conflict__1__18++)) {((tmp1__15[(int)i__conflict__1__18])++);
      }
      for ((i__conflict__0__19 = 0)/*int*/; (i__conflict__0__19 < 1048576); (i__conflict__0__19++)) {((tmp2__16[(int)i__conflict__0__19]) = ((tmp1__15[(int)i__conflict__0__19]) + 1))/*int*/;
      }
      for ((i__20 = 0)/*int*/; (i__20 < 1048576); (i__20++)) {__push_1_2((tmp2__16[(int)i__20]));
      }
      // mark end: SIRFilter process

    }
  }
}

void __init_state_1() {
  init__14__1();
  if (save_state::load_state(1, &__steady_1, __read_thread__1) == -1) pthread_exit(NULL);
}

static void __main__1() {
  int _tmp; // modified
  int _steady = __steady_1;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__1();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__1();
      if (*__state_flag_1 == EXIT_THREAD) exit_thread(__thread_1);
      __update_pop_buf__1();
      work__13__1(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_1, _steady, __write_thread__1);
#endif // __CHECKPOINT_FREQ
  }
}

void run_1() {
  __init_sockets_1(check_status_during_io__1);
  __init_state_1();

  timer t1;
  __peek_sockets_1();
  t1.start();
  __main__1();
  t1.stop();
  if (__timer_enabled) t1.output(stderr);

  __flush_sockets_1();
  pthread_exit(NULL);
}
// peek: 1048576 pop: 1048576 push 1048576
// init counts: 0 steady counts: 1

// ClusterFusion isEliminated: false



int __number_of_iterations_2;
int __counter_2 = 0;
int __steady_2 = 0;
int __tmp_2 = 0;
int __tmp2_2 = 0;
int *__state_flag_2 = NULL;
thread_info *__thread_2 = NULL;

consumer2<int> __consumer_1_2;
producer2<int> __producer_2_3;
    // this-part:3 dst-part:4


void save_peek_buffer__2(object_write_buffer *buf);
void load_peek_buffer__2(object_write_buffer *buf);
void save_file_pointer__2(object_write_buffer *buf);
void load_file_pointer__2(object_write_buffer *buf);

void __write_thread__2(object_write_buffer *buf) {
  __consumer_1_2.write_object(buf);
  save_peek_buffer__2(buf);
  save_file_pointer__2(buf);
  __producer_2_3.write_object(buf);
}

void __read_thread__2(object_write_buffer *buf) {
  __consumer_1_2.read_object(buf);
  load_peek_buffer__2(buf);
  load_file_pointer__2(buf);
  __producer_2_3.read_object(buf);
}

inline void check_status__2() {
  check_thread_status(__state_flag_2, __thread_2);
}

void check_status_during_io__2() {
  check_thread_status_during_io(__state_flag_2, __thread_2);
}

void __init_thread_info_2(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(1,2,&__consumer_1_2));
  info->add_outgoing_data_connection(new connection_info(2,3,&__producer_2_3));
  __state_flag_2 = info->get_state_flag();
}

thread_info *__get_thread_info_2() {
  if (__thread_2 != NULL) return __thread_2;
  __thread_2 = new thread_info(2, check_status_during_io__2);
  __init_thread_info_2(__thread_2);
  return __thread_2;
}

void __declare_sockets_2() {
  init_instance::add_incoming(1,2, DATA_SOCKET);
  init_instance::add_outgoing(2,3, DATA_SOCKET);
}

void __init_sockets_2(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(1,2,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_1_2.set_socket(sock);
  __consumer_1_2.init();

  sock = init_instance::get_outgoing_socket(2,3,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __producer_2_3.set_socket(sock);
  __producer_2_3.init();

}

void __flush_sockets_2() {
  __producer_2_3.flush();
  __producer_2_3.get_socket()->close();
  __producer_2_3.delete_socket_obj();
  __consumer_1_2.delete_socket_obj();
}

void __peek_sockets_2() {
  __consumer_1_2.peek(0);
}

 
void init__23__2();
inline void check_status__2();

void work__22__2(int);

// downstreamDeclarationExtern cluster_1_2
// downstreamDeclaration cluster_1_2:
int __pop_buf__2[1048576];
int __head__2;
int __tail__2;

inline void __init_pop_buf__2() {
  __tail__2=0;
  __head__2=0;
}

void save_peek_buffer__2(object_write_buffer *buf) {
  int i = 0, offs = __tail__2;
  while (offs != __head__2) {
    buf->write(&__pop_buf__2[offs], sizeof(int ));
    offs++;
    offs&=1048575;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__2(object_write_buffer *buf) {
  __tail__2=0;
  __head__2=0;
}

inline void __update_pop_buf__2() {
for (int i = 0; i < 1048576; i++) {
  __pop_buf__2[i]=__consumer_1_2.pop();
}
  __tail__2 = 0;
  __head__2 = 1048576;
}


inline int __pop_1_2() {
return __pop_buf__2[__tail__2++];
}

inline void __pop_1_2(int n) {
__tail__2+=n;
return;
}

inline int __peek_1_2(int offs) {
return __pop_buf__2[(__tail__2+offs)];
  }


// upstreamDeclarationExtern cluster_2_3
// upstreamDeclaration cluster_2_3
int __pop_buffer_2_3[10240];
int __pop_index_2_3 = 0;
inline void __push_2_3(int data) {
__producer_2_3.push(data);
}

 
void init__23__2(){
}
void save_file_pointer__2(object_write_buffer *buf) {}
void load_file_pointer__2(object_write_buffer *buf) {}
 
void work__22__2(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int tmp1__24[1048576] = {0};/* int[1048576] */
      int tmp2__25[1048576] = {0};/* int[1048576] */
      int i__conflict__2__26 = 0;/* int */
      int i__conflict__1__27 = 0;/* int */
      int i__conflict__0__28 = 0;/* int */
      int i__29 = 0;/* int */

      // mark begin: SIRFilter process

      for ((i__conflict__2__26 = 0)/*int*/; (i__conflict__2__26 < 1048576); (i__conflict__2__26++)) {(tmp1__24[(int)i__conflict__2__26]) = __pop_1_2();
;
      }
      for ((i__conflict__1__27 = 0)/*int*/; (i__conflict__1__27 < 1048576); (i__conflict__1__27++)) {((tmp1__24[(int)i__conflict__1__27])++);
      }
      for ((i__conflict__0__28 = 0)/*int*/; (i__conflict__0__28 < 1048576); (i__conflict__0__28++)) {((tmp2__25[(int)i__conflict__0__28]) = ((tmp1__24[(int)i__conflict__0__28]) + 1))/*int*/;
      }
      for ((i__29 = 0)/*int*/; (i__29 < 1048576); (i__29++)) {__push_2_3((tmp2__25[(int)i__29]));
      }
      // mark end: SIRFilter process

    }
  }
}

void __init_state_2() {
  init__23__2();
  if (save_state::load_state(2, &__steady_2, __read_thread__2) == -1) pthread_exit(NULL);
}

static void __main__2() {
  int _tmp; // modified
  int _steady = __steady_2;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__2();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__2();
      if (*__state_flag_2 == EXIT_THREAD) exit_thread(__thread_2);
      __update_pop_buf__2();
      work__22__2(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_2, _steady, __write_thread__2);
#endif // __CHECKPOINT_FREQ
  }
}

void run_2() {
  __init_sockets_2(check_status_during_io__2);
  __init_state_2();

  timer t1;
  __peek_sockets_2();
  t1.start();
  __main__2();
  t1.stop();
  if (__timer_enabled) t1.output(stderr);

  __flush_sockets_2();
  pthread_exit(NULL);
}
// peek: 1048576 pop: 1048576 push 0
// init counts: 0 steady counts: 1

// ClusterFusion isEliminated: false



int __number_of_iterations_3;
int __counter_3 = 0;
int __steady_3 = 0;
int __tmp_3 = 0;
int __tmp2_3 = 0;
int *__state_flag_3 = NULL;
thread_info *__thread_3 = NULL;

consumer2<int> __consumer_2_3;


void save_peek_buffer__3(object_write_buffer *buf);
void load_peek_buffer__3(object_write_buffer *buf);
void save_file_pointer__3(object_write_buffer *buf);
void load_file_pointer__3(object_write_buffer *buf);

void __write_thread__3(object_write_buffer *buf) {
  __consumer_2_3.write_object(buf);
  save_peek_buffer__3(buf);
  save_file_pointer__3(buf);
}

void __read_thread__3(object_write_buffer *buf) {
  __consumer_2_3.read_object(buf);
  load_peek_buffer__3(buf);
  load_file_pointer__3(buf);
}

inline void check_status__3() {
  check_thread_status(__state_flag_3, __thread_3);
}

void check_status_during_io__3() {
  check_thread_status_during_io(__state_flag_3, __thread_3);
}

void __init_thread_info_3(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(2,3,&__consumer_2_3));
  __state_flag_3 = info->get_state_flag();
}

thread_info *__get_thread_info_3() {
  if (__thread_3 != NULL) return __thread_3;
  __thread_3 = new thread_info(3, check_status_during_io__3);
  __init_thread_info_3(__thread_3);
  return __thread_3;
}

void __declare_sockets_3() {
  init_instance::add_incoming(2,3, DATA_SOCKET);
}

void __init_sockets_3(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(2,3,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_2_3.set_socket(sock);
  __consumer_2_3.init();

}

void __flush_sockets_3() {
  __consumer_2_3.delete_socket_obj();
}

void __peek_sockets_3() {
  __consumer_2_3.peek(0);
}

 
void init__71__3(); 
void init__32__59__3(); 
void init__41__68__3();
inline void check_status__3();

void work__70__3(int);

// downstreamDeclarationExtern cluster_2_3
// downstreamDeclaration cluster_2_3:
int __pop_buf__3[1048576];
int __head__3;
int __tail__3;

inline void __init_pop_buf__3() {
  __tail__3=0;
  __head__3=0;
}

void save_peek_buffer__3(object_write_buffer *buf) {
  int i = 0, offs = __tail__3;
  while (offs != __head__3) {
    buf->write(&__pop_buf__3[offs], sizeof(int ));
    offs++;
    offs&=1048575;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__3(object_write_buffer *buf) {
  __tail__3=0;
  __head__3=0;
}

inline void __update_pop_buf__3() {
for (int i = 0; i < 1048576; i++) {
  __pop_buf__3[i]=__consumer_2_3.pop();
}
  __tail__3 = 0;
  __head__3 = 1048576;
}


inline int __pop_2_3() {
return __pop_buf__3[__tail__3++];
}

inline void __pop_2_3(int n) {
__tail__3+=n;
return;
}

inline int __peek_2_3(int offs) {
return __pop_buf__3[(__tail__3+offs)];
  }



 
void init__71__3(){
  init__32__59__3();
  init__41__68__3();
}
 
void init__32__59__3(){
}
 
void init__41__68__3(){
}
void save_file_pointer__3(object_write_buffer *buf) {}
void load_file_pointer__3(object_write_buffer *buf) {}
 
void work__70__3(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[1048576] = {0};/* int[1048576] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___COUNTER_WORK_1_1 = 0;/* int */
      int tmp1__33__60[1048576] = {0};/* int[1048576] */
      int tmp2__34__61[1048576] = {0};/* int[1048576] */
      int i__conflict__2__35__62 = 0;/* int */
      int i__conflict__1__36__63 = 0;/* int */
      int i__conflict__0__37__64 = 0;/* int */
      int i__38__65 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      // mark begin: SIRFilter process

      for ((i__conflict__2__35__62 = 0)/*int*/; (i__conflict__2__35__62 < 1048576); (i__conflict__2__35__62++)) {(tmp1__33__60[(int)i__conflict__2__35__62]) = __pop_2_3();
;
      }
      for ((i__conflict__1__36__63 = 0)/*int*/; (i__conflict__1__36__63 < 1048576); (i__conflict__1__36__63++)) {((tmp1__33__60[(int)i__conflict__1__36__63])++);
      }
      for ((i__conflict__0__37__64 = 0)/*int*/; (i__conflict__0__37__64 < 1048576); (i__conflict__0__37__64++)) {((tmp2__34__61[(int)i__conflict__0__37__64]) = ((tmp1__33__60[(int)i__conflict__0__37__64]) + 1))/*int*/;
      }
      for ((i__38__65 = 0)/*int*/; (i__38__65 < 1048576); (i__38__65++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp2__34__61[(int)i__38__65]))/*int*/;
      }
      // mark end: SIRFilter process

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_1 = 0)/*int*/; (___COUNTER_WORK_1_1 < 1048576); (___COUNTER_WORK_1_1++)) {{
          (___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_3() {
  init__71__3();
  if (save_state::load_state(3, &__steady_3, __read_thread__3) == -1) pthread_exit(NULL);
}

static void __main__3() {
  int _tmp; // modified
  int _steady = __steady_3;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__3();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__3();
      if (*__state_flag_3 == EXIT_THREAD) exit_thread(__thread_3);
      __update_pop_buf__3();
      work__70__3(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_3, _steady, __write_thread__3);
#endif // __CHECKPOINT_FREQ
  }
}

void run_3() {
  __init_sockets_3(check_status_during_io__3);
  __init_state_3();

  __main__3();

  __flush_sockets_3();
  pthread_exit(NULL);
}
