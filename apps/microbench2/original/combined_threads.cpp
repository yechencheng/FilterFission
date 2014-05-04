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
    pthread_attr_setstacksize(&__pthread_attr_0, PTHREAD_STACK_MIN+296327648);
    pthread_create(&__pthread_0, &__pthread_attr_0, run_thread_0, (void*)"thread0");
    info->set_pthread(__pthread_0);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(1)) {
    thread_info *info = __get_thread_info_1();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_1, PTHREAD_STACK_MIN+259417737);
    pthread_create(&__pthread_1, &__pthread_attr_1, run_thread_1, (void*)"thread1");
    info->set_pthread(__pthread_1);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(2)) {
    thread_info *info = __get_thread_info_2();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_2, PTHREAD_STACK_MIN+259417737);
    pthread_create(&__pthread_2, &__pthread_attr_2, run_thread_2, (void*)"thread2");
    info->set_pthread(__pthread_2);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(3)) {
    thread_info *info = __get_thread_info_3();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_3, PTHREAD_STACK_MIN+296327648);
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
// peek: 0 pop: 0 push 8388608
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

 
void init__113__0(); 
void init__1__89__0(); 
void init__5__93__0(); 
void init__15__103__0();
inline void check_status__0();

void work__112__0(int);

// upstreamDeclarationExtern cluster_0_1
// upstreamDeclaration cluster_0_1
int __pop_buffer_0_1[10240];
int __pop_index_0_1 = 0;
inline void __push_0_1(int data) {
__producer_0_1.push(data);
}

 
void init__113__0(){
  init__1__89__0();
  init__5__93__0();
  init__15__103__0();
}
 
void init__1__89__0(){
}
 
void init__5__93__0(){
}
 
void init__15__103__0(){
}
void save_file_pointer__0(object_write_buffer *buf) {}
void load_file_pointer__0(object_write_buffer *buf) {}
 
void work__112__0(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int i__2__90 = 0;/* int */
      int tmp1__6__94[8388608] = {0};/* int[8388608] */
      int tmp2__7__95[8388608] = {0};/* int[8388608] */
      int tmp3__8__96[8388608] = {0};/* int[8388608] */
      int i__conflict__2__9__97 = 0;/* int */
      int i__conflict__1__10__98 = 0;/* int */
      int i__conflict__0__11__99 = 0;/* int */
      int i__12__100 = 0;/* int */
      int tmp1__16__104[8388608] = {0};/* int[8388608] */
      int tmp2__17__105[8388608] = {0};/* int[8388608] */
      int tmp3__18__106[8388608] = {0};/* int[8388608] */
      int i__conflict__2__19__107 = 0;/* int */
      int i__conflict__1__20__108 = 0;/* int */
      int i__conflict__0__21__109 = 0;/* int */
      int i__22__110 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      // mark begin: SIRFilter source

      for ((i__2__90 = 0)/*int*/; (i__2__90 < 8388608); (i__2__90++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = i__2__90)/*int*/;
      }
      // mark end: SIRFilter source

      // mark begin: SIRFilter process1

      for ((i__conflict__2__9__97 = 0)/*int*/; (i__conflict__2__9__97 < 8388608); (i__conflict__2__9__97++)) {((tmp1__6__94[(int)i__conflict__2__9__97]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
      }
      for ((i__conflict__1__10__98 = 0)/*int*/; (i__conflict__1__10__98 < 4194304); (i__conflict__1__10__98++)) {{
          ((tmp2__7__95[(int)i__conflict__1__10__98]) = (tmp1__6__94[(int)i__conflict__1__10__98]))/*int*/;
          ((tmp2__7__95[(int)(i__conflict__1__10__98 + 4194304)]) = (tmp1__6__94[(int)(i__conflict__1__10__98 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__11__99 = 0)/*int*/; (i__conflict__0__11__99 < 8388608); (i__conflict__0__11__99++)) {((tmp3__8__96[(int)i__conflict__0__11__99]) = (tmp2__7__95[(int)i__conflict__0__11__99]))/*int*/;
      }
      for ((i__12__100 = 0)/*int*/; (i__12__100 < 8388608); (i__12__100++)) {((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = (tmp3__8__96[(int)i__12__100]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter process1

      for ((i__conflict__2__19__107 = 0)/*int*/; (i__conflict__2__19__107 < 8388608); (i__conflict__2__19__107++)) {((tmp1__16__104[(int)i__conflict__2__19__107]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
      }
      for ((i__conflict__1__20__108 = 0)/*int*/; (i__conflict__1__20__108 < 4194304); (i__conflict__1__20__108++)) {{
          ((tmp2__17__105[(int)i__conflict__1__20__108]) = (tmp1__16__104[(int)i__conflict__1__20__108]))/*int*/;
          ((tmp2__17__105[(int)(i__conflict__1__20__108 + 4194304)]) = (tmp1__16__104[(int)(i__conflict__1__20__108 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__21__109 = 0)/*int*/; (i__conflict__0__21__109 < 8388608); (i__conflict__0__21__109++)) {((tmp3__18__106[(int)i__conflict__0__21__109]) = (tmp2__17__105[(int)i__conflict__0__21__109]))/*int*/;
      }
      for ((i__22__110 = 0)/*int*/; (i__22__110 < 8388608); (i__22__110++)) {__push_0_1((tmp3__18__106[(int)i__22__110]));
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_0() {
  init__113__0();
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
      work__112__0(1);
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
// peek: 8388608 pop: 8388608 push 8388608
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

 
void init__135__1(); 
void init__25__115__1(); 
void init__35__125__1();
inline void check_status__1();

void work__134__1(int);

// downstreamDeclarationExtern cluster_0_1
// downstreamDeclaration cluster_0_1:
int __pop_buf__1[8388608];
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
    offs&=8388607;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__1(object_write_buffer *buf) {
  __tail__1=0;
  __head__1=0;
}

inline void __update_pop_buf__1() {
for (int i = 0; i < 8388608; i++) {
  __pop_buf__1[i]=__consumer_0_1.pop();
}
  __tail__1 = 0;
  __head__1 = 8388608;
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

 
void init__135__1(){
  init__25__115__1();
  init__35__125__1();
}
 
void init__25__115__1(){
}
 
void init__35__125__1(){
}
void save_file_pointer__1(object_write_buffer *buf) {}
void load_file_pointer__1(object_write_buffer *buf) {}
 
void work__134__1(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int tmp1__26__116[8388608] = {0};/* int[8388608] */
      int tmp2__27__117[8388608] = {0};/* int[8388608] */
      int tmp3__28__118[8388608] = {0};/* int[8388608] */
      int i__conflict__2__29__119 = 0;/* int */
      int i__conflict__1__30__120 = 0;/* int */
      int i__conflict__0__31__121 = 0;/* int */
      int i__32__122 = 0;/* int */
      int tmp1__36__126[8388608] = {0};/* int[8388608] */
      int tmp2__37__127[8388608] = {0};/* int[8388608] */
      int tmp3__38__128[8388608] = {0};/* int[8388608] */
      int i__conflict__2__39__129 = 0;/* int */
      int i__conflict__1__40__130 = 0;/* int */
      int i__conflict__0__41__131 = 0;/* int */
      int i__42__132 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((i__conflict__2__29__119 = 0)/*int*/; (i__conflict__2__29__119 < 8388608); (i__conflict__2__29__119++)) {(tmp1__26__116[(int)i__conflict__2__29__119]) = __pop_0_1();
;
      }
      for ((i__conflict__1__30__120 = 0)/*int*/; (i__conflict__1__30__120 < 4194304); (i__conflict__1__30__120++)) {{
          ((tmp2__27__117[(int)i__conflict__1__30__120]) = (tmp1__26__116[(int)i__conflict__1__30__120]))/*int*/;
          ((tmp2__27__117[(int)(i__conflict__1__30__120 + 4194304)]) = (tmp1__26__116[(int)(i__conflict__1__30__120 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__31__121 = 0)/*int*/; (i__conflict__0__31__121 < 8388608); (i__conflict__0__31__121++)) {((tmp3__28__118[(int)i__conflict__0__31__121]) = (tmp2__27__117[(int)i__conflict__0__31__121]))/*int*/;
      }
      for ((i__32__122 = 0)/*int*/; (i__32__122 < 8388608); (i__32__122++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__28__118[(int)i__32__122]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter process1

      for ((i__conflict__2__39__129 = 0)/*int*/; (i__conflict__2__39__129 < 8388608); (i__conflict__2__39__129++)) {((tmp1__36__126[(int)i__conflict__2__39__129]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
      }
      for ((i__conflict__1__40__130 = 0)/*int*/; (i__conflict__1__40__130 < 4194304); (i__conflict__1__40__130++)) {{
          ((tmp2__37__127[(int)i__conflict__1__40__130]) = (tmp1__36__126[(int)i__conflict__1__40__130]))/*int*/;
          ((tmp2__37__127[(int)(i__conflict__1__40__130 + 4194304)]) = (tmp1__36__126[(int)(i__conflict__1__40__130 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__41__131 = 0)/*int*/; (i__conflict__0__41__131 < 8388608); (i__conflict__0__41__131++)) {((tmp3__38__128[(int)i__conflict__0__41__131]) = (tmp2__37__127[(int)i__conflict__0__41__131]))/*int*/;
      }
      for ((i__42__132 = 0)/*int*/; (i__42__132 < 8388608); (i__42__132++)) {__push_1_2((tmp3__38__128[(int)i__42__132]));
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_1() {
  init__135__1();
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
      work__134__1(1);
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
// peek: 8388608 pop: 8388608 push 8388608
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

 
void init__157__2(); 
void init__45__137__2(); 
void init__55__147__2();
inline void check_status__2();

void work__156__2(int);

// downstreamDeclarationExtern cluster_1_2
// downstreamDeclaration cluster_1_2:
int __pop_buf__2[8388608];
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
    offs&=8388607;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__2(object_write_buffer *buf) {
  __tail__2=0;
  __head__2=0;
}

inline void __update_pop_buf__2() {
for (int i = 0; i < 8388608; i++) {
  __pop_buf__2[i]=__consumer_1_2.pop();
}
  __tail__2 = 0;
  __head__2 = 8388608;
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

 
void init__157__2(){
  init__45__137__2();
  init__55__147__2();
}
 
void init__45__137__2(){
}
 
void init__55__147__2(){
}
void save_file_pointer__2(object_write_buffer *buf) {}
void load_file_pointer__2(object_write_buffer *buf) {}
 
void work__156__2(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int tmp1__46__138[8388608] = {0};/* int[8388608] */
      int tmp2__47__139[8388608] = {0};/* int[8388608] */
      int tmp3__48__140[8388608] = {0};/* int[8388608] */
      int i__conflict__2__49__141 = 0;/* int */
      int i__conflict__1__50__142 = 0;/* int */
      int i__conflict__0__51__143 = 0;/* int */
      int i__52__144 = 0;/* int */
      int tmp1__56__148[8388608] = {0};/* int[8388608] */
      int tmp2__57__149[8388608] = {0};/* int[8388608] */
      int tmp3__58__150[8388608] = {0};/* int[8388608] */
      int i__conflict__2__59__151 = 0;/* int */
      int i__conflict__1__60__152 = 0;/* int */
      int i__conflict__0__61__153 = 0;/* int */
      int i__62__154 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((i__conflict__2__49__141 = 0)/*int*/; (i__conflict__2__49__141 < 8388608); (i__conflict__2__49__141++)) {(tmp1__46__138[(int)i__conflict__2__49__141]) = __pop_1_2();
;
      }
      for ((i__conflict__1__50__142 = 0)/*int*/; (i__conflict__1__50__142 < 4194304); (i__conflict__1__50__142++)) {{
          ((tmp2__47__139[(int)i__conflict__1__50__142]) = (tmp1__46__138[(int)i__conflict__1__50__142]))/*int*/;
          ((tmp2__47__139[(int)(i__conflict__1__50__142 + 4194304)]) = (tmp1__46__138[(int)(i__conflict__1__50__142 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__51__143 = 0)/*int*/; (i__conflict__0__51__143 < 8388608); (i__conflict__0__51__143++)) {((tmp3__48__140[(int)i__conflict__0__51__143]) = (tmp2__47__139[(int)i__conflict__0__51__143]))/*int*/;
      }
      for ((i__52__144 = 0)/*int*/; (i__52__144 < 8388608); (i__52__144++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__48__140[(int)i__52__144]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter process1

      for ((i__conflict__2__59__151 = 0)/*int*/; (i__conflict__2__59__151 < 8388608); (i__conflict__2__59__151++)) {((tmp1__56__148[(int)i__conflict__2__59__151]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
      }
      for ((i__conflict__1__60__152 = 0)/*int*/; (i__conflict__1__60__152 < 4194304); (i__conflict__1__60__152++)) {{
          ((tmp2__57__149[(int)i__conflict__1__60__152]) = (tmp1__56__148[(int)i__conflict__1__60__152]))/*int*/;
          ((tmp2__57__149[(int)(i__conflict__1__60__152 + 4194304)]) = (tmp1__56__148[(int)(i__conflict__1__60__152 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__61__153 = 0)/*int*/; (i__conflict__0__61__153 < 8388608); (i__conflict__0__61__153++)) {((tmp3__58__150[(int)i__conflict__0__61__153]) = (tmp2__57__149[(int)i__conflict__0__61__153]))/*int*/;
      }
      for ((i__62__154 = 0)/*int*/; (i__62__154 < 8388608); (i__62__154++)) {__push_2_3((tmp3__58__150[(int)i__62__154]));
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_2() {
  init__157__2();
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
      work__156__2(1);
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
// peek: 8388608 pop: 8388608 push 0
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

 
void init__183__3(); 
void init__65__159__3(); 
void init__75__169__3(); 
void init__85__179__3();
inline void check_status__3();

void work__182__3(int);

// downstreamDeclarationExtern cluster_2_3
// downstreamDeclaration cluster_2_3:
int __pop_buf__3[8388608];
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
    offs&=8388607;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__3(object_write_buffer *buf) {
  __tail__3=0;
  __head__3=0;
}

inline void __update_pop_buf__3() {
for (int i = 0; i < 8388608; i++) {
  __pop_buf__3[i]=__consumer_2_3.pop();
}
  __tail__3 = 0;
  __head__3 = 8388608;
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



 
void init__183__3(){
  init__65__159__3();
  init__75__169__3();
  init__85__179__3();
}
 
void init__65__159__3(){
}
 
void init__75__169__3(){
}
 
void init__85__179__3(){
}
void save_file_pointer__3(object_write_buffer *buf) {}
void load_file_pointer__3(object_write_buffer *buf) {}
 
void work__182__3(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int tmp1__66__160[8388608] = {0};/* int[8388608] */
      int tmp2__67__161[8388608] = {0};/* int[8388608] */
      int tmp3__68__162[8388608] = {0};/* int[8388608] */
      int i__conflict__2__69__163 = 0;/* int */
      int i__conflict__1__70__164 = 0;/* int */
      int i__conflict__0__71__165 = 0;/* int */
      int i__72__166 = 0;/* int */
      int tmp1__76__170[8388608] = {0};/* int[8388608] */
      int tmp2__77__171[8388608] = {0};/* int[8388608] */
      int tmp3__78__172[8388608] = {0};/* int[8388608] */
      int i__conflict__2__79__173 = 0;/* int */
      int i__conflict__1__80__174 = 0;/* int */
      int i__conflict__0__81__175 = 0;/* int */
      int i__82__176 = 0;/* int */
      int __tmp2__86__180 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((i__conflict__2__69__163 = 0)/*int*/; (i__conflict__2__69__163 < 8388608); (i__conflict__2__69__163++)) {(tmp1__66__160[(int)i__conflict__2__69__163]) = __pop_2_3();
;
      }
      for ((i__conflict__1__70__164 = 0)/*int*/; (i__conflict__1__70__164 < 4194304); (i__conflict__1__70__164++)) {{
          ((tmp2__67__161[(int)i__conflict__1__70__164]) = (tmp1__66__160[(int)i__conflict__1__70__164]))/*int*/;
          ((tmp2__67__161[(int)(i__conflict__1__70__164 + 4194304)]) = (tmp1__66__160[(int)(i__conflict__1__70__164 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__71__165 = 0)/*int*/; (i__conflict__0__71__165 < 8388608); (i__conflict__0__71__165++)) {((tmp3__68__162[(int)i__conflict__0__71__165]) = (tmp2__67__161[(int)i__conflict__0__71__165]))/*int*/;
      }
      for ((i__72__166 = 0)/*int*/; (i__72__166 < 8388608); (i__72__166++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__68__162[(int)i__72__166]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter process1

      for ((i__conflict__2__79__173 = 0)/*int*/; (i__conflict__2__79__173 < 8388608); (i__conflict__2__79__173++)) {((tmp1__76__170[(int)i__conflict__2__79__173]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
      }
      for ((i__conflict__1__80__174 = 0)/*int*/; (i__conflict__1__80__174 < 4194304); (i__conflict__1__80__174++)) {{
          ((tmp2__77__171[(int)i__conflict__1__80__174]) = (tmp1__76__170[(int)i__conflict__1__80__174]))/*int*/;
          ((tmp2__77__171[(int)(i__conflict__1__80__174 + 4194304)]) = (tmp1__76__170[(int)(i__conflict__1__80__174 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__81__175 = 0)/*int*/; (i__conflict__0__81__175 < 8388608); (i__conflict__0__81__175++)) {((tmp3__78__172[(int)i__conflict__0__81__175]) = (tmp2__77__171[(int)i__conflict__0__81__175]))/*int*/;
      }
      for ((i__82__176 = 0)/*int*/; (i__82__176 < 8388608); (i__82__176++)) {((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = (tmp3__78__172[(int)i__82__176]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 8388608); (___COUNTER_WORK_1_2++)) {{
          (__tmp2__86__180 = (___POP_BUFFER_2_1[(int)((1 + ___POP_INDEX_1_2) + 0)]))/*int*/;

          // TIMER_PRINT_CODE: __print_sink__ += (int)(__tmp2__86__180); 
          printf( "%d", __tmp2__86__180); printf("\n");

          (___POP_INDEX_1_2 = (___POP_INDEX_1_2 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_3() {
  init__183__3();
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
      work__182__3(1);
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
