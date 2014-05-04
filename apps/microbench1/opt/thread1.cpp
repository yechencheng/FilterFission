// peek: 1024 pop: 1024 push 1024
// init counts: 0 steady counts: 1024

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
message *__msg_stack_1;
int __number_of_iterations_1;
int __counter_1 = 0;
int __steady_1 = 0;
int __tmp_1 = 0;
int __tmp2_1 = 0;
int *__state_flag_1 = NULL;
thread_info *__thread_1 = NULL;

consumer2<int> __consumer_0_1;
extern int __pop_0_1();
producer2<int> __producer_1_2;
extern void __push_1_2(int);
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
int __pop_buf__1[1024];
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
    offs&=1023;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__1(object_write_buffer *buf) {
  __tail__1=0;
  __head__1=0;
}

inline void __update_pop_buf__1() {
for (int i = 0; i < 1024; i++) {
  __pop_buf__1[i]=__consumer_0_1.pop();
}
  __tail__1 = 0;
  __head__1 = 1024;
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
int __pop_index_1_2 = 10240;
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
      int tmp1__15[1024] = {0};/* int[1024] */
      int tmp2__16[1024] = {0};/* int[1024] */
      int i__conflict__2__17 = 0;/* int */
      int i__conflict__1__18 = 0;/* int */
      int i__conflict__0__19 = 0;/* int */
      int i__20 = 0;/* int */

      // mark begin: SIRFilter process

      for ((i__conflict__2__17 = 0)/*int*/; (i__conflict__2__17 < 1024); (i__conflict__2__17++)) {(tmp1__15[(int)i__conflict__2__17]) = __pop_0_1();
;
      }
      for ((i__conflict__1__18 = 0)/*int*/; (i__conflict__1__18 < 1024); (i__conflict__1__18++)) {((tmp1__15[(int)i__conflict__1__18])++);
      }
      for ((i__conflict__0__19 = 0)/*int*/; (i__conflict__0__19 < 1024); (i__conflict__0__19++)) {((tmp2__16[(int)i__conflict__0__19]) = ((tmp1__15[(int)i__conflict__0__19]) + 1))/*int*/;
      }
      for ((i__20 = 0)/*int*/; (i__20 < 1024); (i__20++)) {__push_1_2((tmp2__16[(int)i__20]));
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
    for (_tmp = 0; _tmp < 1024; _tmp++) {
      //check_status__1();
      if (*__state_flag_1 == EXIT_THREAD) exit_thread(__thread_1);
      __update_pop_buf__1();
      work__13__1(1);
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
