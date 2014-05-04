// peek: 0 pop: 0 push 1048576
// init counts: 0 steady counts: 1

// ClusterFusion isEliminated: false

#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <init_instance.h>
#include <mysocket.h>
#include <object_write_buffer.h>
#include <save_state.h>
#include <sdep.h>
#include <message.h>
#include <timer.h>
#include <thread_info.h>
#include <consumer2.h>
#include <consumer2p.h>
#include <producer2.h>
#include "cluster.h"
#include "fusion.h"
#include "global.h"

extern int __max_iteration;
extern int __init_iter;
extern int __timer_enabled;
extern int __frequency_of_chkpts;
extern volatile int __vol;
message *__msg_stack_0;
int __number_of_iterations_0;
int __counter_0 = 0;
int __steady_0 = 0;
int __tmp_0 = 0;
int __tmp2_0 = 0;
int *__state_flag_0 = NULL;
thread_info *__thread_0 = NULL;

producer2<int> __producer_0_1;
extern void __push_0_1(int);
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
      int ___COUNTER_WORK_1_1 = 0;/* int */
      int i__2__45 = 0;/* int */
      int tmp1__6__49[1024] = {0};/* int[1024] */
      int tmp2__7__50[1024] = {0};/* int[1024] */
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

      for ((___COUNTER_WORK_1_1 = 0)/*int*/; (___COUNTER_WORK_1_1 < 1024); (___COUNTER_WORK_1_1++)) {{
          for ((i__conflict__2__8__51 = 0)/*int*/; (i__conflict__2__8__51 < 1024); (i__conflict__2__8__51++)) {((tmp1__6__49[(int)i__conflict__2__8__51]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
          }
          for ((i__conflict__1__9__52 = 0)/*int*/; (i__conflict__1__9__52 < 1024); (i__conflict__1__9__52++)) {((tmp1__6__49[(int)i__conflict__1__9__52])++);
          }
          for ((i__conflict__0__10__53 = 0)/*int*/; (i__conflict__0__10__53 < 1024); (i__conflict__0__10__53++)) {((tmp2__7__50[(int)i__conflict__0__10__53]) = ((tmp1__6__49[(int)i__conflict__0__10__53]) + 1))/*int*/;
          }
          for ((i__11__54 = 0)/*int*/; (i__11__54 < 1024); (i__11__54++)) {__push_0_1((tmp2__7__50[(int)i__11__54]));
          }
        }
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
