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
message *__msg_stack_2;
int __number_of_iterations_2;
int __counter_2 = 0;
int __steady_2 = 0;
int __tmp_2 = 0;
int __tmp2_2 = 0;
int *__state_flag_2 = NULL;
thread_info *__thread_2 = NULL;

consumer2<int> __consumer_1_2;
extern int __pop_1_2();
producer2<int> __producer_2_3;
extern void __push_2_3(int);
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
int __pop_buf__2[1024];
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
    offs&=1023;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__2(object_write_buffer *buf) {
  __tail__2=0;
  __head__2=0;
}

inline void __update_pop_buf__2() {
for (int i = 0; i < 1024; i++) {
  __pop_buf__2[i]=__consumer_1_2.pop();
}
  __tail__2 = 0;
  __head__2 = 1024;
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
int __pop_index_2_3 = 10240;
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
      int tmp1__24[1024] = {0};/* int[1024] */
      int tmp2__25[1024] = {0};/* int[1024] */
      int i__conflict__2__26 = 0;/* int */
      int i__conflict__1__27 = 0;/* int */
      int i__conflict__0__28 = 0;/* int */
      int i__29 = 0;/* int */

      // mark begin: SIRFilter process

      for ((i__conflict__2__26 = 0)/*int*/; (i__conflict__2__26 < 1024); (i__conflict__2__26++)) {(tmp1__24[(int)i__conflict__2__26]) = __pop_1_2();
;
      }
      for ((i__conflict__1__27 = 0)/*int*/; (i__conflict__1__27 < 1024); (i__conflict__1__27++)) {((tmp1__24[(int)i__conflict__1__27])++);
      }
      for ((i__conflict__0__28 = 0)/*int*/; (i__conflict__0__28 < 1024); (i__conflict__0__28++)) {((tmp2__25[(int)i__conflict__0__28]) = ((tmp1__24[(int)i__conflict__0__28]) + 1))/*int*/;
      }
      for ((i__29 = 0)/*int*/; (i__29 < 1024); (i__29++)) {__push_2_3((tmp2__25[(int)i__29]));
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
    for (_tmp = 0; _tmp < 1024; _tmp++) {
      //check_status__2();
      if (*__state_flag_2 == EXIT_THREAD) exit_thread(__thread_2);
      __update_pop_buf__2();
      work__22__2(1);
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
