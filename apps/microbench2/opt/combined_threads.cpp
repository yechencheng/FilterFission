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
    pthread_attr_setstacksize(&__pthread_attr_0, PTHREAD_STACK_MIN+167172476);
    pthread_create(&__pthread_0, &__pthread_attr_0, run_thread_0, (void*)"thread0");
    info->set_pthread(__pthread_0);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(1)) {
    thread_info *info = __get_thread_info_1();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_1, PTHREAD_STACK_MIN+91043756);
    pthread_create(&__pthread_1, &__pthread_attr_1, run_thread_1, (void*)"thread1");
    info->set_pthread(__pthread_1);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(2)) {
    thread_info *info = __get_thread_info_2();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_2, PTHREAD_STACK_MIN+9726594);
    pthread_create(&__pthread_2, &__pthread_attr_2, run_thread_2, (void*)"thread2");
    info->set_pthread(__pthread_2);
    info->set_active(true);
  }
  if (myip == init_instance::get_thread_ip(3)) {
    thread_info *info = __get_thread_info_3();
    int *state = info->get_state_flag();
    *state = RUN_STATE;
    pthread_attr_setstacksize(&__pthread_attr_3, PTHREAD_STACK_MIN+3815212);
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

 
void init__317__0(); 
void init__1__262__0(); 
void init__5__266__0(); 
void init__14__275__0(); 
void init__24__285__0(); 
void init__46__307__0();
inline void check_status__0();

void work__316__0(int);

// upstreamDeclarationExtern cluster_0_1
// upstreamDeclaration cluster_0_1
int __pop_buffer_0_1[10240];
int __pop_index_0_1 = 0;
inline void __push_0_1(int data) {
__producer_0_1.push(data);
}

 
void init__317__0(){
  init__1__262__0();
  init__5__266__0();
  init__14__275__0();
  init__24__285__0();
  init__46__307__0();
}
 
void init__1__262__0(){
}
 
void init__5__266__0(){
}
 
void init__14__275__0(){
}
 
void init__24__285__0(){
}
 
void init__46__307__0(){
}
void save_file_pointer__0(object_write_buffer *buf) {}
void load_file_pointer__0(object_write_buffer *buf) {}
 
void work__316__0(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int ___POP_BUFFER_3_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_3 = 0;/* int */
      int ___PUSH_INDEX_1_3 = 0;/* int */
      int ___POP_BUFFER_4_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_4 = 0;/* int */
      int ___PUSH_INDEX_1_4 = 0;/* int */
      int ___COUNTER_WORK_1_4 = 0;/* int */
      int i__2__263 = 0;/* int */
      int tmp__6__267[512] = {0};/* int[512] */
      int __tmp2__7__268 = 0;/* int */
      int j__conflict__1__8__269 = 0;/* int */
      int j__9__270 = 0;/* int */
      int i__conflict__0__10__271 = 0;/* int */
      int i__11__272 = 0;/* int */
      int tmp1__15__276[1024] = {0};/* int[1024] */
      int tmp2__16__277[1024] = {0};/* int[1024] */
      int tmp3__17__278[1024] = {0};/* int[1024] */
      int i__conflict__2__18__279 = 0;/* int */
      int i__conflict__1__19__280 = 0;/* int */
      int i__conflict__0__20__281 = 0;/* int */
      int i__21__282 = 0;/* int */
      int id__25__286 = 0;/* int */
      int tmp__26__287[4194304] = {0};/* int[4194304] */
      int __tmp3__27__288 = 0;/* int */
      int k__conflict__8__28__289 = 0;/* int */
      int __tmp4__29__290 = 0;/* int */
      int __tmp5__30__291 = 0;/* int */
      int k__conflict__7__31__292 = 0;/* int */
      int k__conflict__6__32__293 = 0;/* int */
      int j__conflict__5__33__294 = 0;/* int */
      int k__conflict__4__34__295 = 0;/* int */
      int k__conflict__3__35__296 = 0;/* int */
      int j__conflict__2__36__297 = 0;/* int */
      int i__conflict__1__37__298 = 0;/* int */
      int __tmp6__38__299 = 0;/* int */
      int j__conflict__0__39__300 = 0;/* int */
      int __tmp7__40__301 = 0;/* int */
      int j__41__302 = 0;/* int */
      int i__42__303 = 0;/* int */
      int k__43__304 = 0;/* int */
      int tmp1__47__308[1024] = {0};/* int[1024] */
      int tmp2__48__309[1024] = {0};/* int[1024] */
      int tmp3__49__310[1024] = {0};/* int[1024] */
      int i__conflict__2__50__311 = 0;/* int */
      int i__conflict__1__51__312 = 0;/* int */
      int i__conflict__0__52__313 = 0;/* int */
      int i__53__314 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      (___POP_INDEX_1_3 = -1)/*int*/;
      (___PUSH_INDEX_1_3 = -1)/*int*/;
      (___POP_INDEX_1_4 = -1)/*int*/;
      (___PUSH_INDEX_1_4 = -1)/*int*/;
      // mark begin: SIRFilter source

      for ((i__2__263 = 0)/*int*/; (i__2__263 < 8388608); (i__2__263++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = i__2__263)/*int*/;
      }
      // mark end: SIRFilter source

      // mark begin: SIRFilter MySplit

      for ((i__conflict__0__10__271 = 0)/*int*/; (i__conflict__0__10__271 < 8192); (i__conflict__0__10__271++)) {{
          for ((j__conflict__1__8__269 = 0)/*int*/; (j__conflict__1__8__269 < 512); (j__conflict__1__8__269++)) {{
              ((tmp__6__267[(int)j__conflict__1__8__269]) = (___POP_BUFFER_1_1[(int)((1 + ___POP_INDEX_1_1) + 4194304)]))/*int*/;
              (__tmp2__7__268 = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp2__7__268)/*int*/;
            }
          }
          for ((j__9__270 = 0)/*int*/; (j__9__270 < 512); (j__9__270++)) {((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = (tmp__6__267[(int)j__9__270]))/*int*/;
          }
        }
      }
      for ((i__11__272 = 0)/*int*/; (i__11__272 < 4194304); (i__11__272++)) {(___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
      }
      // mark end: SIRFilter MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 8192); (___COUNTER_WORK_1_2++)) {{
          for ((i__conflict__2__18__279 = 0)/*int*/; (i__conflict__2__18__279 < 1024); (i__conflict__2__18__279++)) {((tmp1__15__276[(int)i__conflict__2__18__279]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
          }
          for ((i__conflict__1__19__280 = 0)/*int*/; (i__conflict__1__19__280 < 512); (i__conflict__1__19__280++)) {{
              ((tmp2__16__277[(int)i__conflict__1__19__280]) = (tmp1__15__276[(int)i__conflict__1__19__280]))/*int*/;
              ((tmp2__16__277[(int)(i__conflict__1__19__280 + 512)]) = (tmp1__15__276[(int)(i__conflict__1__19__280 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__20__281 = 0)/*int*/; (i__conflict__0__20__281 < 1024); (i__conflict__0__20__281++)) {((tmp3__17__278[(int)i__conflict__0__20__281]) = (tmp2__16__277[(int)i__conflict__0__20__281]))/*int*/;
          }
          for ((i__21__282 = 0)/*int*/; (i__21__282 < 1024); (i__21__282++)) {((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = (tmp3__17__278[(int)i__21__282]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      (id__25__286 = 0)/*int*/;
      for ((i__conflict__1__37__298 = 0)/*int*/; (i__conflict__1__37__298 < 1); (i__conflict__1__37__298++)) {{
          for ((j__conflict__5__33__294 = 0)/*int*/; (j__conflict__5__33__294 < 4096); (j__conflict__5__33__294++)) {{
              for ((k__conflict__8__28__289 = 0)/*int*/; (k__conflict__8__28__289 < 512); (k__conflict__8__28__289++)) {{
                  (__tmp3__27__288 = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp3__27__288)/*int*/;
                }
              }
              for ((k__conflict__7__31__292 = 0)/*int*/; (k__conflict__7__31__292 < 512); (k__conflict__7__31__292++)) {{
                  (__tmp5__30__291 = ((k__conflict__7__31__292 + 4194304) - 512))/*int*/;
                  (__tmp4__29__290 = (___POP_BUFFER_3_1[(int)((1 + ___POP_INDEX_1_3) + __tmp5__30__291)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp4__29__290)/*int*/;
                }
              }
              for ((k__conflict__6__32__293 = 0)/*int*/; (k__conflict__6__32__293 < 512); (k__conflict__6__32__293++)) {((tmp__26__287[(int)(id__25__286++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
              }
            }
          }
          for ((j__conflict__2__36__297 = 0)/*int*/; (j__conflict__2__36__297 < 4096); (j__conflict__2__36__297++)) {{
              for ((k__conflict__4__34__295 = 0)/*int*/; (k__conflict__4__34__295 < 512); (k__conflict__4__34__295++)) {(___POP_INDEX_1_3 = (___POP_INDEX_1_3 + 1))/*int*/;
              }
              for ((k__conflict__3__35__296 = 0)/*int*/; (k__conflict__3__35__296 < 512); (k__conflict__3__35__296++)) {((tmp__26__287[(int)(id__25__286++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
              }
            }
          }
        }
      }
      (id__25__286 = 0)/*int*/;
      for ((k__43__304 = 0)/*int*/; (k__43__304 < 1); (k__43__304++)) {{
          for ((i__42__303 = 0)/*int*/; (i__42__303 < 4096); (i__42__303++)) {{
              for ((j__conflict__0__39__300 = 0)/*int*/; (j__conflict__0__39__300 < 512); (j__conflict__0__39__300++)) {{
                  (__tmp6__38__299 = (tmp__26__287[(int)(id__25__286++)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp6__38__299)/*int*/;
                }
              }
              (id__25__286 = (id__25__286 - 512))/*int*/;
              for ((j__41__302 = 0)/*int*/; (j__41__302 < 512); (j__41__302++)) {{
                  (__tmp7__40__301 = (tmp__26__287[(int)((id__25__286++) + 2097152)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp7__40__301)/*int*/;
                }
              }
            }
          }
          (id__25__286 = (id__25__286 + 2097152))/*int*/;
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_4 = 0)/*int*/; (___COUNTER_WORK_1_4 < 8192); (___COUNTER_WORK_1_4++)) {{
          for ((i__conflict__2__50__311 = 0)/*int*/; (i__conflict__2__50__311 < 1024); (i__conflict__2__50__311++)) {((tmp1__47__308[(int)i__conflict__2__50__311]) = (___POP_BUFFER_4_1[(int)(++___POP_INDEX_1_4)]))/*int*/;
          }
          for ((i__conflict__1__51__312 = 0)/*int*/; (i__conflict__1__51__312 < 512); (i__conflict__1__51__312++)) {{
              ((tmp2__48__309[(int)i__conflict__1__51__312]) = (tmp1__47__308[(int)i__conflict__1__51__312]))/*int*/;
              ((tmp2__48__309[(int)(i__conflict__1__51__312 + 512)]) = (tmp1__47__308[(int)(i__conflict__1__51__312 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__52__313 = 0)/*int*/; (i__conflict__0__52__313 < 1024); (i__conflict__0__52__313++)) {((tmp3__49__310[(int)i__conflict__0__52__313]) = (tmp2__48__309[(int)i__conflict__0__52__313]))/*int*/;
          }
          for ((i__53__314 = 0)/*int*/; (i__53__314 < 1024); (i__53__314++)) {__push_0_1((tmp3__49__310[(int)i__53__314]));
          }
        }
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_0() {
  init__317__0();
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
      work__316__0(1);
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
// peek: 4194304 pop: 4194304 push 4194304
// init counts: 0 steady counts: 2

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

 
void init__405__1(); 
void init__56__319__1(); 
void init__78__341__1(); 
void init__88__351__1(); 
void init__110__373__1(); 
void init__120__383__1();
inline void check_status__1();

void work__404__1(int);

// downstreamDeclarationExtern cluster_0_1
// downstreamDeclaration cluster_0_1:
int __pop_buf__1[4194304];
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
    offs&=4194303;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__1(object_write_buffer *buf) {
  __tail__1=0;
  __head__1=0;
}

inline void __update_pop_buf__1() {
for (int i = 0; i < 4194304; i++) {
  __pop_buf__1[i]=__consumer_0_1.pop();
}
  __tail__1 = 0;
  __head__1 = 4194304;
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

 
void init__405__1(){
  init__56__319__1();
  init__78__341__1();
  init__88__351__1();
  init__110__373__1();
  init__120__383__1();
}
 
void init__56__319__1(){
}
 
void init__78__341__1(){
}
 
void init__88__351__1(){
}
 
void init__110__373__1(){
}
 
void init__120__383__1(){
}
void save_file_pointer__1(object_write_buffer *buf) {}
void load_file_pointer__1(object_write_buffer *buf) {}
 
void work__404__1(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[4194304] = {0};/* int[4194304] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___COUNTER_WORK_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[4194304] = {0};/* int[4194304] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int ___POP_BUFFER_3_1[4194304] = {0};/* int[4194304] */
      int ___POP_INDEX_1_3 = 0;/* int */
      int ___PUSH_INDEX_1_3 = 0;/* int */
      int ___COUNTER_WORK_1_3 = 0;/* int */
      int ___POP_BUFFER_4_1[4194304] = {0};/* int[4194304] */
      int ___POP_INDEX_1_4 = 0;/* int */
      int ___PUSH_INDEX_1_4 = 0;/* int */
      int ___COUNTER_WORK_1_4 = 0;/* int */
      int id__57__320 = 0;/* int */
      int tmp__58__321[2097152] = {0};/* int[2097152] */
      int __tmp3__59__322 = 0;/* int */
      int k__conflict__8__60__323 = 0;/* int */
      int __tmp4__61__324 = 0;/* int */
      int __tmp5__62__325 = 0;/* int */
      int k__conflict__7__63__326 = 0;/* int */
      int k__conflict__6__64__327 = 0;/* int */
      int j__conflict__5__65__328 = 0;/* int */
      int k__conflict__4__66__329 = 0;/* int */
      int k__conflict__3__67__330 = 0;/* int */
      int j__conflict__2__68__331 = 0;/* int */
      int i__conflict__1__69__332 = 0;/* int */
      int __tmp6__70__333 = 0;/* int */
      int j__conflict__0__71__334 = 0;/* int */
      int __tmp7__72__335 = 0;/* int */
      int j__73__336 = 0;/* int */
      int i__74__337 = 0;/* int */
      int k__75__338 = 0;/* int */
      int tmp1__79__342[1024] = {0};/* int[1024] */
      int tmp2__80__343[1024] = {0};/* int[1024] */
      int tmp3__81__344[1024] = {0};/* int[1024] */
      int i__conflict__2__82__345 = 0;/* int */
      int i__conflict__1__83__346 = 0;/* int */
      int i__conflict__0__84__347 = 0;/* int */
      int i__85__348 = 0;/* int */
      int id__89__352 = 0;/* int */
      int tmp__90__353[1048576] = {0};/* int[1048576] */
      int __tmp3__91__354 = 0;/* int */
      int k__conflict__8__92__355 = 0;/* int */
      int __tmp4__93__356 = 0;/* int */
      int __tmp5__94__357 = 0;/* int */
      int k__conflict__7__95__358 = 0;/* int */
      int k__conflict__6__96__359 = 0;/* int */
      int j__conflict__5__97__360 = 0;/* int */
      int k__conflict__4__98__361 = 0;/* int */
      int k__conflict__3__99__362 = 0;/* int */
      int j__conflict__2__100__363 = 0;/* int */
      int i__conflict__1__101__364 = 0;/* int */
      int __tmp6__102__365 = 0;/* int */
      int j__conflict__0__103__366 = 0;/* int */
      int __tmp7__104__367 = 0;/* int */
      int j__105__368 = 0;/* int */
      int i__106__369 = 0;/* int */
      int k__107__370 = 0;/* int */
      int tmp1__111__374[1024] = {0};/* int[1024] */
      int tmp2__112__375[1024] = {0};/* int[1024] */
      int tmp3__113__376[1024] = {0};/* int[1024] */
      int i__conflict__2__114__377 = 0;/* int */
      int i__conflict__1__115__378 = 0;/* int */
      int i__conflict__0__116__379 = 0;/* int */
      int i__117__380 = 0;/* int */
      int id__121__384 = 0;/* int */
      int tmp__122__385[524288] = {0};/* int[524288] */
      int __tmp3__123__386 = 0;/* int */
      int k__conflict__8__124__387 = 0;/* int */
      int __tmp4__125__388 = 0;/* int */
      int __tmp5__126__389 = 0;/* int */
      int k__conflict__7__127__390 = 0;/* int */
      int k__conflict__6__128__391 = 0;/* int */
      int j__conflict__5__129__392 = 0;/* int */
      int k__conflict__4__130__393 = 0;/* int */
      int k__conflict__3__131__394 = 0;/* int */
      int j__conflict__2__132__395 = 0;/* int */
      int i__conflict__1__133__396 = 0;/* int */
      int __tmp6__134__397 = 0;/* int */
      int j__conflict__0__135__398 = 0;/* int */
      int __tmp7__136__399 = 0;/* int */
      int j__137__400 = 0;/* int */
      int i__138__401 = 0;/* int */
      int k__139__402 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      (___POP_INDEX_1_3 = -1)/*int*/;
      (___PUSH_INDEX_1_3 = -1)/*int*/;
      (___POP_INDEX_1_4 = -1)/*int*/;
      (___PUSH_INDEX_1_4 = -1)/*int*/;
      // mark begin: SIRFilter Fused_MyJoin_MySplit

      (id__57__320 = 0)/*int*/;
      for ((i__conflict__1__69__332 = 0)/*int*/; (i__conflict__1__69__332 < 1); (i__conflict__1__69__332++)) {{
          for ((j__conflict__5__65__328 = 0)/*int*/; (j__conflict__5__65__328 < 2048); (j__conflict__5__65__328++)) {{
              for ((k__conflict__8__60__323 = 0)/*int*/; (k__conflict__8__60__323 < 512); (k__conflict__8__60__323++)) {{
                  __tmp3__59__322 = __pop_0_1();
;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp3__59__322)/*int*/;
                }
              }
              for ((k__conflict__7__63__326 = 0)/*int*/; (k__conflict__7__63__326 < 512); (k__conflict__7__63__326++)) {{
                  (__tmp5__62__325 = ((k__conflict__7__63__326 + 2097152) - 512))/*int*/;
                  __tmp4__61__324 = __peek_0_1(__tmp5__62__325);
;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp4__61__324)/*int*/;
                }
              }
              for ((k__conflict__6__64__327 = 0)/*int*/; (k__conflict__6__64__327 < 512); (k__conflict__6__64__327++)) {(tmp__58__321[(int)(id__57__320++)]) = __pop_0_1();
;
              }
            }
          }
          for ((j__conflict__2__68__331 = 0)/*int*/; (j__conflict__2__68__331 < 2048); (j__conflict__2__68__331++)) {{
              for ((k__conflict__4__66__329 = 0)/*int*/; (k__conflict__4__66__329 < 512); (k__conflict__4__66__329++)) {__pop_0_1();
              }
              for ((k__conflict__3__67__330 = 0)/*int*/; (k__conflict__3__67__330 < 512); (k__conflict__3__67__330++)) {(tmp__58__321[(int)(id__57__320++)]) = __pop_0_1();
;
              }
            }
          }
        }
      }
      (id__57__320 = 0)/*int*/;
      for ((k__75__338 = 0)/*int*/; (k__75__338 < 1); (k__75__338++)) {{
          for ((i__74__337 = 0)/*int*/; (i__74__337 < 2048); (i__74__337++)) {{
              for ((j__conflict__0__71__334 = 0)/*int*/; (j__conflict__0__71__334 < 512); (j__conflict__0__71__334++)) {{
                  (__tmp6__70__333 = (tmp__58__321[(int)(id__57__320++)]))/*int*/;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp6__70__333)/*int*/;
                }
              }
              (id__57__320 = (id__57__320 - 512))/*int*/;
              for ((j__73__336 = 0)/*int*/; (j__73__336 < 512); (j__73__336++)) {{
                  (__tmp7__72__335 = (tmp__58__321[(int)((id__57__320++) + 1048576)]))/*int*/;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp7__72__335)/*int*/;
                }
              }
            }
          }
          (id__57__320 = (id__57__320 + 1048576))/*int*/;
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_1 = 0)/*int*/; (___COUNTER_WORK_1_1 < 4096); (___COUNTER_WORK_1_1++)) {{
          for ((i__conflict__2__82__345 = 0)/*int*/; (i__conflict__2__82__345 < 1024); (i__conflict__2__82__345++)) {((tmp1__79__342[(int)i__conflict__2__82__345]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
          }
          for ((i__conflict__1__83__346 = 0)/*int*/; (i__conflict__1__83__346 < 512); (i__conflict__1__83__346++)) {{
              ((tmp2__80__343[(int)i__conflict__1__83__346]) = (tmp1__79__342[(int)i__conflict__1__83__346]))/*int*/;
              ((tmp2__80__343[(int)(i__conflict__1__83__346 + 512)]) = (tmp1__79__342[(int)(i__conflict__1__83__346 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__84__347 = 0)/*int*/; (i__conflict__0__84__347 < 1024); (i__conflict__0__84__347++)) {((tmp3__81__344[(int)i__conflict__0__84__347]) = (tmp2__80__343[(int)i__conflict__0__84__347]))/*int*/;
          }
          for ((i__85__348 = 0)/*int*/; (i__85__348 < 1024); (i__85__348++)) {((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = (tmp3__81__344[(int)i__85__348]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 2); (___COUNTER_WORK_1_2++)) {{
          (id__89__352 = 0)/*int*/;
          for ((i__conflict__1__101__364 = 0)/*int*/; (i__conflict__1__101__364 < 1); (i__conflict__1__101__364++)) {{
              for ((j__conflict__5__97__360 = 0)/*int*/; (j__conflict__5__97__360 < 1024); (j__conflict__5__97__360++)) {{
                  for ((k__conflict__8__92__355 = 0)/*int*/; (k__conflict__8__92__355 < 512); (k__conflict__8__92__355++)) {{
                      (__tmp3__91__354 = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
                      ((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = __tmp3__91__354)/*int*/;
                    }
                  }
                  for ((k__conflict__7__95__358 = 0)/*int*/; (k__conflict__7__95__358 < 512); (k__conflict__7__95__358++)) {{
                      (__tmp5__94__357 = ((k__conflict__7__95__358 + 1048576) - 512))/*int*/;
                      (__tmp4__93__356 = (___POP_BUFFER_2_1[(int)((1 + ___POP_INDEX_1_2) + __tmp5__94__357)]))/*int*/;
                      ((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = __tmp4__93__356)/*int*/;
                    }
                  }
                  for ((k__conflict__6__96__359 = 0)/*int*/; (k__conflict__6__96__359 < 512); (k__conflict__6__96__359++)) {((tmp__90__353[(int)(id__89__352++)]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
                  }
                }
              }
              for ((j__conflict__2__100__363 = 0)/*int*/; (j__conflict__2__100__363 < 1024); (j__conflict__2__100__363++)) {{
                  for ((k__conflict__4__98__361 = 0)/*int*/; (k__conflict__4__98__361 < 512); (k__conflict__4__98__361++)) {(___POP_INDEX_1_2 = (___POP_INDEX_1_2 + 1))/*int*/;
                  }
                  for ((k__conflict__3__99__362 = 0)/*int*/; (k__conflict__3__99__362 < 512); (k__conflict__3__99__362++)) {((tmp__90__353[(int)(id__89__352++)]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
                  }
                }
              }
            }
          }
          (id__89__352 = 0)/*int*/;
          for ((k__107__370 = 0)/*int*/; (k__107__370 < 1); (k__107__370++)) {{
              for ((i__106__369 = 0)/*int*/; (i__106__369 < 1024); (i__106__369++)) {{
                  for ((j__conflict__0__103__366 = 0)/*int*/; (j__conflict__0__103__366 < 512); (j__conflict__0__103__366++)) {{
                      (__tmp6__102__365 = (tmp__90__353[(int)(id__89__352++)]))/*int*/;
                      ((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = __tmp6__102__365)/*int*/;
                    }
                  }
                  (id__89__352 = (id__89__352 - 512))/*int*/;
                  for ((j__105__368 = 0)/*int*/; (j__105__368 < 512); (j__105__368++)) {{
                      (__tmp7__104__367 = (tmp__90__353[(int)((id__89__352++) + 524288)]))/*int*/;
                      ((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = __tmp7__104__367)/*int*/;
                    }
                  }
                }
              }
              (id__89__352 = (id__89__352 + 524288))/*int*/;
            }
          }
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_3 = 0)/*int*/; (___COUNTER_WORK_1_3 < 4096); (___COUNTER_WORK_1_3++)) {{
          for ((i__conflict__2__114__377 = 0)/*int*/; (i__conflict__2__114__377 < 1024); (i__conflict__2__114__377++)) {((tmp1__111__374[(int)i__conflict__2__114__377]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
          }
          for ((i__conflict__1__115__378 = 0)/*int*/; (i__conflict__1__115__378 < 512); (i__conflict__1__115__378++)) {{
              ((tmp2__112__375[(int)i__conflict__1__115__378]) = (tmp1__111__374[(int)i__conflict__1__115__378]))/*int*/;
              ((tmp2__112__375[(int)(i__conflict__1__115__378 + 512)]) = (tmp1__111__374[(int)(i__conflict__1__115__378 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__116__379 = 0)/*int*/; (i__conflict__0__116__379 < 1024); (i__conflict__0__116__379++)) {((tmp3__113__376[(int)i__conflict__0__116__379]) = (tmp2__112__375[(int)i__conflict__0__116__379]))/*int*/;
          }
          for ((i__117__380 = 0)/*int*/; (i__117__380 < 1024); (i__117__380++)) {((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = (tmp3__113__376[(int)i__117__380]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      for ((___COUNTER_WORK_1_4 = 0)/*int*/; (___COUNTER_WORK_1_4 < 4); (___COUNTER_WORK_1_4++)) {{
          (id__121__384 = 0)/*int*/;
          for ((i__conflict__1__133__396 = 0)/*int*/; (i__conflict__1__133__396 < 1); (i__conflict__1__133__396++)) {{
              for ((j__conflict__5__129__392 = 0)/*int*/; (j__conflict__5__129__392 < 512); (j__conflict__5__129__392++)) {{
                  for ((k__conflict__8__124__387 = 0)/*int*/; (k__conflict__8__124__387 < 512); (k__conflict__8__124__387++)) {{
                      (__tmp3__123__386 = (___POP_BUFFER_4_1[(int)(++___POP_INDEX_1_4)]))/*int*/;
                      __push_1_2(__tmp3__123__386);
                    }
                  }
                  for ((k__conflict__7__127__390 = 0)/*int*/; (k__conflict__7__127__390 < 512); (k__conflict__7__127__390++)) {{
                      (__tmp5__126__389 = ((k__conflict__7__127__390 + 524288) - 512))/*int*/;
                      (__tmp4__125__388 = (___POP_BUFFER_4_1[(int)((1 + ___POP_INDEX_1_4) + __tmp5__126__389)]))/*int*/;
                      __push_1_2(__tmp4__125__388);
                    }
                  }
                  for ((k__conflict__6__128__391 = 0)/*int*/; (k__conflict__6__128__391 < 512); (k__conflict__6__128__391++)) {((tmp__122__385[(int)(id__121__384++)]) = (___POP_BUFFER_4_1[(int)(++___POP_INDEX_1_4)]))/*int*/;
                  }
                }
              }
              for ((j__conflict__2__132__395 = 0)/*int*/; (j__conflict__2__132__395 < 512); (j__conflict__2__132__395++)) {{
                  for ((k__conflict__4__130__393 = 0)/*int*/; (k__conflict__4__130__393 < 512); (k__conflict__4__130__393++)) {(___POP_INDEX_1_4 = (___POP_INDEX_1_4 + 1))/*int*/;
                  }
                  for ((k__conflict__3__131__394 = 0)/*int*/; (k__conflict__3__131__394 < 512); (k__conflict__3__131__394++)) {((tmp__122__385[(int)(id__121__384++)]) = (___POP_BUFFER_4_1[(int)(++___POP_INDEX_1_4)]))/*int*/;
                  }
                }
              }
            }
          }
          (id__121__384 = 0)/*int*/;
          for ((k__139__402 = 0)/*int*/; (k__139__402 < 1); (k__139__402++)) {{
              for ((i__138__401 = 0)/*int*/; (i__138__401 < 512); (i__138__401++)) {{
                  for ((j__conflict__0__135__398 = 0)/*int*/; (j__conflict__0__135__398 < 512); (j__conflict__0__135__398++)) {{
                      (__tmp6__134__397 = (tmp__122__385[(int)(id__121__384++)]))/*int*/;
                      __push_1_2(__tmp6__134__397);
                    }
                  }
                  (id__121__384 = (id__121__384 - 512))/*int*/;
                  for ((j__137__400 = 0)/*int*/; (j__137__400 < 512); (j__137__400++)) {{
                      (__tmp7__136__399 = (tmp__122__385[(int)((id__121__384++) + 262144)]))/*int*/;
                      __push_1_2(__tmp7__136__399);
                    }
                  }
                }
              }
              (id__121__384 = (id__121__384 + 262144))/*int*/;
            }
          }
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

    }
  }
}

void __init_state_1() {
  init__405__1();
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
    for (_tmp = 0; _tmp < 2; _tmp++) {
      //check_status__1();
      if (*__state_flag_1 == EXIT_THREAD) exit_thread(__thread_1);
      __update_pop_buf__1();
      work__404__1(1);
    }
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
// peek: 524288 pop: 524288 push 524288
// init counts: 0 steady counts: 16

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

 
void init__471__2(); 
void init__142__407__2(); 
void init__152__417__2(); 
void init__174__439__2(); 
void init__184__449__2();
inline void check_status__2();

void work__470__2(int);

// downstreamDeclarationExtern cluster_1_2
// downstreamDeclaration cluster_1_2:
int __pop_buf__2[524288];
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
    offs&=524287;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__2(object_write_buffer *buf) {
  __tail__2=0;
  __head__2=0;
}

inline void __update_pop_buf__2() {
for (int i = 0; i < 524288; i++) {
  __pop_buf__2[i]=__consumer_1_2.pop();
}
  __tail__2 = 0;
  __head__2 = 524288;
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

 
void init__471__2(){
  init__142__407__2();
  init__152__417__2();
  init__174__439__2();
  init__184__449__2();
}
 
void init__142__407__2(){
}
 
void init__152__417__2(){
}
 
void init__174__439__2(){
}
 
void init__184__449__2(){
}
void save_file_pointer__2(object_write_buffer *buf) {}
void load_file_pointer__2(object_write_buffer *buf) {}
 
void work__470__2(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___COUNTER_WORK_1_0 = 0;/* int */
      int ___POP_BUFFER_1_1[524288] = {0};/* int[524288] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[524288] = {0};/* int[524288] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int ___POP_BUFFER_3_1[524288] = {0};/* int[524288] */
      int ___POP_INDEX_1_3 = 0;/* int */
      int ___PUSH_INDEX_1_3 = 0;/* int */
      int ___COUNTER_WORK_1_3 = 0;/* int */
      int tmp1__143__408[1024] = {0};/* int[1024] */
      int tmp2__144__409[1024] = {0};/* int[1024] */
      int tmp3__145__410[1024] = {0};/* int[1024] */
      int i__conflict__2__146__411 = 0;/* int */
      int i__conflict__1__147__412 = 0;/* int */
      int i__conflict__0__148__413 = 0;/* int */
      int i__149__414 = 0;/* int */
      int id__153__418 = 0;/* int */
      int tmp__154__419[262144] = {0};/* int[262144] */
      int __tmp3__155__420 = 0;/* int */
      int k__conflict__8__156__421 = 0;/* int */
      int __tmp4__157__422 = 0;/* int */
      int __tmp5__158__423 = 0;/* int */
      int k__conflict__7__159__424 = 0;/* int */
      int k__conflict__6__160__425 = 0;/* int */
      int j__conflict__5__161__426 = 0;/* int */
      int k__conflict__4__162__427 = 0;/* int */
      int k__conflict__3__163__428 = 0;/* int */
      int j__conflict__2__164__429 = 0;/* int */
      int i__conflict__1__165__430 = 0;/* int */
      int __tmp6__166__431 = 0;/* int */
      int j__conflict__0__167__432 = 0;/* int */
      int __tmp7__168__433 = 0;/* int */
      int j__169__434 = 0;/* int */
      int i__170__435 = 0;/* int */
      int k__171__436 = 0;/* int */
      int tmp1__175__440[1024] = {0};/* int[1024] */
      int tmp2__176__441[1024] = {0};/* int[1024] */
      int tmp3__177__442[1024] = {0};/* int[1024] */
      int i__conflict__2__178__443 = 0;/* int */
      int i__conflict__1__179__444 = 0;/* int */
      int i__conflict__0__180__445 = 0;/* int */
      int i__181__446 = 0;/* int */
      int id__185__450 = 0;/* int */
      int tmp__186__451[131072] = {0};/* int[131072] */
      int __tmp3__187__452 = 0;/* int */
      int k__conflict__8__188__453 = 0;/* int */
      int __tmp4__189__454 = 0;/* int */
      int __tmp5__190__455 = 0;/* int */
      int k__conflict__7__191__456 = 0;/* int */
      int k__conflict__6__192__457 = 0;/* int */
      int j__conflict__5__193__458 = 0;/* int */
      int k__conflict__4__194__459 = 0;/* int */
      int k__conflict__3__195__460 = 0;/* int */
      int j__conflict__2__196__461 = 0;/* int */
      int i__conflict__1__197__462 = 0;/* int */
      int __tmp6__198__463 = 0;/* int */
      int j__conflict__0__199__464 = 0;/* int */
      int __tmp7__200__465 = 0;/* int */
      int j__201__466 = 0;/* int */
      int i__202__467 = 0;/* int */
      int k__203__468 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      (___POP_INDEX_1_3 = -1)/*int*/;
      (___PUSH_INDEX_1_3 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_0 = 0)/*int*/; (___COUNTER_WORK_1_0 < 512); (___COUNTER_WORK_1_0++)) {{
          for ((i__conflict__2__146__411 = 0)/*int*/; (i__conflict__2__146__411 < 1024); (i__conflict__2__146__411++)) {(tmp1__143__408[(int)i__conflict__2__146__411]) = __pop_1_2();
;
          }
          for ((i__conflict__1__147__412 = 0)/*int*/; (i__conflict__1__147__412 < 512); (i__conflict__1__147__412++)) {{
              ((tmp2__144__409[(int)i__conflict__1__147__412]) = (tmp1__143__408[(int)i__conflict__1__147__412]))/*int*/;
              ((tmp2__144__409[(int)(i__conflict__1__147__412 + 512)]) = (tmp1__143__408[(int)(i__conflict__1__147__412 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__148__413 = 0)/*int*/; (i__conflict__0__148__413 < 1024); (i__conflict__0__148__413++)) {((tmp3__145__410[(int)i__conflict__0__148__413]) = (tmp2__144__409[(int)i__conflict__0__148__413]))/*int*/;
          }
          for ((i__149__414 = 0)/*int*/; (i__149__414 < 1024); (i__149__414++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__145__410[(int)i__149__414]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      (id__153__418 = 0)/*int*/;
      for ((i__conflict__1__165__430 = 0)/*int*/; (i__conflict__1__165__430 < 1); (i__conflict__1__165__430++)) {{
          for ((j__conflict__5__161__426 = 0)/*int*/; (j__conflict__5__161__426 < 256); (j__conflict__5__161__426++)) {{
              for ((k__conflict__8__156__421 = 0)/*int*/; (k__conflict__8__156__421 < 512); (k__conflict__8__156__421++)) {{
                  (__tmp3__155__420 = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp3__155__420)/*int*/;
                }
              }
              for ((k__conflict__7__159__424 = 0)/*int*/; (k__conflict__7__159__424 < 512); (k__conflict__7__159__424++)) {{
                  (__tmp5__158__423 = ((k__conflict__7__159__424 + 262144) - 512))/*int*/;
                  (__tmp4__157__422 = (___POP_BUFFER_1_1[(int)((1 + ___POP_INDEX_1_1) + __tmp5__158__423)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp4__157__422)/*int*/;
                }
              }
              for ((k__conflict__6__160__425 = 0)/*int*/; (k__conflict__6__160__425 < 512); (k__conflict__6__160__425++)) {((tmp__154__419[(int)(id__153__418++)]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              }
            }
          }
          for ((j__conflict__2__164__429 = 0)/*int*/; (j__conflict__2__164__429 < 256); (j__conflict__2__164__429++)) {{
              for ((k__conflict__4__162__427 = 0)/*int*/; (k__conflict__4__162__427 < 512); (k__conflict__4__162__427++)) {(___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
              }
              for ((k__conflict__3__163__428 = 0)/*int*/; (k__conflict__3__163__428 < 512); (k__conflict__3__163__428++)) {((tmp__154__419[(int)(id__153__418++)]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              }
            }
          }
        }
      }
      (id__153__418 = 0)/*int*/;
      for ((k__171__436 = 0)/*int*/; (k__171__436 < 1); (k__171__436++)) {{
          for ((i__170__435 = 0)/*int*/; (i__170__435 < 256); (i__170__435++)) {{
              for ((j__conflict__0__167__432 = 0)/*int*/; (j__conflict__0__167__432 < 512); (j__conflict__0__167__432++)) {{
                  (__tmp6__166__431 = (tmp__154__419[(int)(id__153__418++)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp6__166__431)/*int*/;
                }
              }
              (id__153__418 = (id__153__418 - 512))/*int*/;
              for ((j__169__434 = 0)/*int*/; (j__169__434 < 512); (j__169__434++)) {{
                  (__tmp7__168__433 = (tmp__154__419[(int)((id__153__418++) + 131072)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp7__168__433)/*int*/;
                }
              }
            }
          }
          (id__153__418 = (id__153__418 + 131072))/*int*/;
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 512); (___COUNTER_WORK_1_2++)) {{
          for ((i__conflict__2__178__443 = 0)/*int*/; (i__conflict__2__178__443 < 1024); (i__conflict__2__178__443++)) {((tmp1__175__440[(int)i__conflict__2__178__443]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
          }
          for ((i__conflict__1__179__444 = 0)/*int*/; (i__conflict__1__179__444 < 512); (i__conflict__1__179__444++)) {{
              ((tmp2__176__441[(int)i__conflict__1__179__444]) = (tmp1__175__440[(int)i__conflict__1__179__444]))/*int*/;
              ((tmp2__176__441[(int)(i__conflict__1__179__444 + 512)]) = (tmp1__175__440[(int)(i__conflict__1__179__444 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__180__445 = 0)/*int*/; (i__conflict__0__180__445 < 1024); (i__conflict__0__180__445++)) {((tmp3__177__442[(int)i__conflict__0__180__445]) = (tmp2__176__441[(int)i__conflict__0__180__445]))/*int*/;
          }
          for ((i__181__446 = 0)/*int*/; (i__181__446 < 1024); (i__181__446++)) {((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = (tmp3__177__442[(int)i__181__446]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      for ((___COUNTER_WORK_1_3 = 0)/*int*/; (___COUNTER_WORK_1_3 < 2); (___COUNTER_WORK_1_3++)) {{
          (id__185__450 = 0)/*int*/;
          for ((i__conflict__1__197__462 = 0)/*int*/; (i__conflict__1__197__462 < 1); (i__conflict__1__197__462++)) {{
              for ((j__conflict__5__193__458 = 0)/*int*/; (j__conflict__5__193__458 < 128); (j__conflict__5__193__458++)) {{
                  for ((k__conflict__8__188__453 = 0)/*int*/; (k__conflict__8__188__453 < 512); (k__conflict__8__188__453++)) {{
                      (__tmp3__187__452 = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                      __push_2_3(__tmp3__187__452);
                    }
                  }
                  for ((k__conflict__7__191__456 = 0)/*int*/; (k__conflict__7__191__456 < 512); (k__conflict__7__191__456++)) {{
                      (__tmp5__190__455 = ((k__conflict__7__191__456 + 131072) - 512))/*int*/;
                      (__tmp4__189__454 = (___POP_BUFFER_3_1[(int)((1 + ___POP_INDEX_1_3) + __tmp5__190__455)]))/*int*/;
                      __push_2_3(__tmp4__189__454);
                    }
                  }
                  for ((k__conflict__6__192__457 = 0)/*int*/; (k__conflict__6__192__457 < 512); (k__conflict__6__192__457++)) {((tmp__186__451[(int)(id__185__450++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                  }
                }
              }
              for ((j__conflict__2__196__461 = 0)/*int*/; (j__conflict__2__196__461 < 128); (j__conflict__2__196__461++)) {{
                  for ((k__conflict__4__194__459 = 0)/*int*/; (k__conflict__4__194__459 < 512); (k__conflict__4__194__459++)) {(___POP_INDEX_1_3 = (___POP_INDEX_1_3 + 1))/*int*/;
                  }
                  for ((k__conflict__3__195__460 = 0)/*int*/; (k__conflict__3__195__460 < 512); (k__conflict__3__195__460++)) {((tmp__186__451[(int)(id__185__450++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                  }
                }
              }
            }
          }
          (id__185__450 = 0)/*int*/;
          for ((k__203__468 = 0)/*int*/; (k__203__468 < 1); (k__203__468++)) {{
              for ((i__202__467 = 0)/*int*/; (i__202__467 < 128); (i__202__467++)) {{
                  for ((j__conflict__0__199__464 = 0)/*int*/; (j__conflict__0__199__464 < 512); (j__conflict__0__199__464++)) {{
                      (__tmp6__198__463 = (tmp__186__451[(int)(id__185__450++)]))/*int*/;
                      __push_2_3(__tmp6__198__463);
                    }
                  }
                  (id__185__450 = (id__185__450 - 512))/*int*/;
                  for ((j__201__466 = 0)/*int*/; (j__201__466 < 512); (j__201__466++)) {{
                      (__tmp7__200__465 = (tmp__186__451[(int)((id__185__450++) + 65536)]))/*int*/;
                      __push_2_3(__tmp7__200__465);
                    }
                  }
                }
              }
              (id__185__450 = (id__185__450 + 65536))/*int*/;
            }
          }
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

    }
  }
}

void __init_state_2() {
  init__471__2();
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
    for (_tmp = 0; _tmp < 16; _tmp++) {
      //check_status__2();
      if (*__state_flag_2 == EXIT_THREAD) exit_thread(__thread_2);
      __update_pop_buf__2();
      work__470__2(1);
    }
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
// peek: 131072 pop: 131072 push 0
// init counts: 0 steady counts: 64

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

 
void init__529__3(); 
void init__206__473__3(); 
void init__216__483__3(); 
void init__238__505__3(); 
void init__248__515__3(); 
void init__258__525__3();
inline void check_status__3();

void work__528__3(int);

// downstreamDeclarationExtern cluster_2_3
// downstreamDeclaration cluster_2_3:
int __pop_buf__3[131072];
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
    offs&=131071;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__3(object_write_buffer *buf) {
  __tail__3=0;
  __head__3=0;
}

inline void __update_pop_buf__3() {
for (int i = 0; i < 131072; i++) {
  __pop_buf__3[i]=__consumer_2_3.pop();
}
  __tail__3 = 0;
  __head__3 = 131072;
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



 
void init__529__3(){
  init__206__473__3();
  init__216__483__3();
  init__238__505__3();
  init__248__515__3();
  init__258__525__3();
}
 
void init__206__473__3(){
}
 
void init__216__483__3(){
}
 
void init__238__505__3(){
}
 
void init__248__515__3(){
}
 
void init__258__525__3(){
}
void save_file_pointer__3(object_write_buffer *buf) {}
void load_file_pointer__3(object_write_buffer *buf) {}
 
void work__528__3(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___COUNTER_WORK_1_0 = 0;/* int */
      int ___POP_BUFFER_1_1[131072] = {0};/* int[131072] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[131072] = {0};/* int[131072] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int ___POP_BUFFER_3_1[131072] = {0};/* int[131072] */
      int ___POP_INDEX_1_3 = 0;/* int */
      int ___PUSH_INDEX_1_3 = 0;/* int */
      int ___COUNTER_WORK_1_3 = 0;/* int */
      int ___POP_BUFFER_4_1[131072] = {0};/* int[131072] */
      int ___POP_INDEX_1_4 = 0;/* int */
      int ___PUSH_INDEX_1_4 = 0;/* int */
      int ___COUNTER_WORK_1_4 = 0;/* int */
      int tmp1__207__474[1024] = {0};/* int[1024] */
      int tmp2__208__475[1024] = {0};/* int[1024] */
      int tmp3__209__476[1024] = {0};/* int[1024] */
      int i__conflict__2__210__477 = 0;/* int */
      int i__conflict__1__211__478 = 0;/* int */
      int i__conflict__0__212__479 = 0;/* int */
      int i__213__480 = 0;/* int */
      int id__217__484 = 0;/* int */
      int tmp__218__485[65536] = {0};/* int[65536] */
      int __tmp3__219__486 = 0;/* int */
      int k__conflict__8__220__487 = 0;/* int */
      int __tmp4__221__488 = 0;/* int */
      int __tmp5__222__489 = 0;/* int */
      int k__conflict__7__223__490 = 0;/* int */
      int k__conflict__6__224__491 = 0;/* int */
      int j__conflict__5__225__492 = 0;/* int */
      int k__conflict__4__226__493 = 0;/* int */
      int k__conflict__3__227__494 = 0;/* int */
      int j__conflict__2__228__495 = 0;/* int */
      int i__conflict__1__229__496 = 0;/* int */
      int __tmp6__230__497 = 0;/* int */
      int j__conflict__0__231__498 = 0;/* int */
      int __tmp7__232__499 = 0;/* int */
      int j__233__500 = 0;/* int */
      int i__234__501 = 0;/* int */
      int k__235__502 = 0;/* int */
      int tmp1__239__506[1024] = {0};/* int[1024] */
      int tmp2__240__507[1024] = {0};/* int[1024] */
      int tmp3__241__508[1024] = {0};/* int[1024] */
      int i__conflict__2__242__509 = 0;/* int */
      int i__conflict__1__243__510 = 0;/* int */
      int i__conflict__0__244__511 = 0;/* int */
      int i__245__512 = 0;/* int */
      int tmp__249__516[32768] = {0};/* int[32768] */
      int id__250__517 = 0;/* int */
      int __tmp8__251__518 = 0;/* int */
      int j__conflict__1__252__519 = 0;/* int */
      int j__253__520 = 0;/* int */
      int i__conflict__0__254__521 = 0;/* int */
      int i__255__522 = 0;/* int */
      int __tmp9__259__526 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      (___POP_INDEX_1_3 = -1)/*int*/;
      (___PUSH_INDEX_1_3 = -1)/*int*/;
      (___POP_INDEX_1_4 = -1)/*int*/;
      (___PUSH_INDEX_1_4 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_0 = 0)/*int*/; (___COUNTER_WORK_1_0 < 128); (___COUNTER_WORK_1_0++)) {{
          for ((i__conflict__2__210__477 = 0)/*int*/; (i__conflict__2__210__477 < 1024); (i__conflict__2__210__477++)) {(tmp1__207__474[(int)i__conflict__2__210__477]) = __pop_2_3();
;
          }
          for ((i__conflict__1__211__478 = 0)/*int*/; (i__conflict__1__211__478 < 512); (i__conflict__1__211__478++)) {{
              ((tmp2__208__475[(int)i__conflict__1__211__478]) = (tmp1__207__474[(int)i__conflict__1__211__478]))/*int*/;
              ((tmp2__208__475[(int)(i__conflict__1__211__478 + 512)]) = (tmp1__207__474[(int)(i__conflict__1__211__478 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__212__479 = 0)/*int*/; (i__conflict__0__212__479 < 1024); (i__conflict__0__212__479++)) {((tmp3__209__476[(int)i__conflict__0__212__479]) = (tmp2__208__475[(int)i__conflict__0__212__479]))/*int*/;
          }
          for ((i__213__480 = 0)/*int*/; (i__213__480 < 1024); (i__213__480++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__209__476[(int)i__213__480]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      (id__217__484 = 0)/*int*/;
      for ((i__conflict__1__229__496 = 0)/*int*/; (i__conflict__1__229__496 < 1); (i__conflict__1__229__496++)) {{
          for ((j__conflict__5__225__492 = 0)/*int*/; (j__conflict__5__225__492 < 64); (j__conflict__5__225__492++)) {{
              for ((k__conflict__8__220__487 = 0)/*int*/; (k__conflict__8__220__487 < 512); (k__conflict__8__220__487++)) {{
                  (__tmp3__219__486 = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp3__219__486)/*int*/;
                }
              }
              for ((k__conflict__7__223__490 = 0)/*int*/; (k__conflict__7__223__490 < 512); (k__conflict__7__223__490++)) {{
                  (__tmp5__222__489 = ((k__conflict__7__223__490 + 65536) - 512))/*int*/;
                  (__tmp4__221__488 = (___POP_BUFFER_1_1[(int)((1 + ___POP_INDEX_1_1) + __tmp5__222__489)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp4__221__488)/*int*/;
                }
              }
              for ((k__conflict__6__224__491 = 0)/*int*/; (k__conflict__6__224__491 < 512); (k__conflict__6__224__491++)) {((tmp__218__485[(int)(id__217__484++)]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              }
            }
          }
          for ((j__conflict__2__228__495 = 0)/*int*/; (j__conflict__2__228__495 < 64); (j__conflict__2__228__495++)) {{
              for ((k__conflict__4__226__493 = 0)/*int*/; (k__conflict__4__226__493 < 512); (k__conflict__4__226__493++)) {(___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
              }
              for ((k__conflict__3__227__494 = 0)/*int*/; (k__conflict__3__227__494 < 512); (k__conflict__3__227__494++)) {((tmp__218__485[(int)(id__217__484++)]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              }
            }
          }
        }
      }
      (id__217__484 = 0)/*int*/;
      for ((k__235__502 = 0)/*int*/; (k__235__502 < 1); (k__235__502++)) {{
          for ((i__234__501 = 0)/*int*/; (i__234__501 < 64); (i__234__501++)) {{
              for ((j__conflict__0__231__498 = 0)/*int*/; (j__conflict__0__231__498 < 512); (j__conflict__0__231__498++)) {{
                  (__tmp6__230__497 = (tmp__218__485[(int)(id__217__484++)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp6__230__497)/*int*/;
                }
              }
              (id__217__484 = (id__217__484 - 512))/*int*/;
              for ((j__233__500 = 0)/*int*/; (j__233__500 < 512); (j__233__500++)) {{
                  (__tmp7__232__499 = (tmp__218__485[(int)((id__217__484++) + 32768)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp7__232__499)/*int*/;
                }
              }
            }
          }
          (id__217__484 = (id__217__484 + 32768))/*int*/;
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 128); (___COUNTER_WORK_1_2++)) {{
          for ((i__conflict__2__242__509 = 0)/*int*/; (i__conflict__2__242__509 < 1024); (i__conflict__2__242__509++)) {((tmp1__239__506[(int)i__conflict__2__242__509]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
          }
          for ((i__conflict__1__243__510 = 0)/*int*/; (i__conflict__1__243__510 < 512); (i__conflict__1__243__510++)) {{
              ((tmp2__240__507[(int)i__conflict__1__243__510]) = (tmp1__239__506[(int)i__conflict__1__243__510]))/*int*/;
              ((tmp2__240__507[(int)(i__conflict__1__243__510 + 512)]) = (tmp1__239__506[(int)(i__conflict__1__243__510 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__244__511 = 0)/*int*/; (i__conflict__0__244__511 < 1024); (i__conflict__0__244__511++)) {((tmp3__241__508[(int)i__conflict__0__244__511]) = (tmp2__240__507[(int)i__conflict__0__244__511]))/*int*/;
          }
          for ((i__245__512 = 0)/*int*/; (i__245__512 < 1024); (i__245__512++)) {((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = (tmp3__241__508[(int)i__245__512]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter MyJoin

      for ((___COUNTER_WORK_1_3 = 0)/*int*/; (___COUNTER_WORK_1_3 < 2); (___COUNTER_WORK_1_3++)) {{
          (id__250__517 = 0)/*int*/;
          for ((i__conflict__0__254__521 = 0)/*int*/; (i__conflict__0__254__521 < 64); (i__conflict__0__254__521++)) {{
              for ((j__conflict__1__252__519 = 0)/*int*/; (j__conflict__1__252__519 < 512); (j__conflict__1__252__519++)) {{
                  (__tmp8__251__518 = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp8__251__518)/*int*/;
                }
              }
              for ((j__253__520 = 0)/*int*/; (j__253__520 < 512); (j__253__520++)) {((tmp__249__516[(int)(id__250__517++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
              }
            }
          }
          for ((i__255__522 = 0)/*int*/; (i__255__522 < 32768); (i__255__522++)) {((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = (tmp__249__516[(int)i__255__522]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter MyJoin

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_4 = 0)/*int*/; (___COUNTER_WORK_1_4 < 131072); (___COUNTER_WORK_1_4++)) {{
          (__tmp9__259__526 = (___POP_BUFFER_4_1[(int)((1 + ___POP_INDEX_1_4) + 0)]))/*int*/;

          // TIMER_PRINT_CODE: __print_sink__ += (int)(__tmp9__259__526); 
          printf( "%d", __tmp9__259__526); printf("\n");

          (___POP_INDEX_1_4 = (___POP_INDEX_1_4 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_3() {
  init__529__3();
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
    for (_tmp = 0; _tmp < 64; _tmp++) {
      //check_status__3();
      if (*__state_flag_3 == EXIT_THREAD) exit_thread(__thread_3);
      __update_pop_buf__3();
      work__528__3(1);
    }
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
