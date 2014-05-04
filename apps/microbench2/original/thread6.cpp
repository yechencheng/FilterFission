// peek: 8388608 pop: 8388608 push 8388608
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
message *__msg_stack_6;
int __number_of_iterations_6;
int __counter_6 = 0;
int __steady_6 = 0;
int __tmp_6 = 0;
int __tmp2_6 = 0;
int *__state_flag_6 = NULL;
thread_info *__thread_6 = NULL;

consumer2<int> __consumer_5_6;
extern int __pop_5_6();
producer2<int> __producer_6_7;
extern void __push_6_7(int);
    // this-part:7 dst-part:8


void save_peek_buffer__6(object_write_buffer *buf);
void load_peek_buffer__6(object_write_buffer *buf);
void save_file_pointer__6(object_write_buffer *buf);
void load_file_pointer__6(object_write_buffer *buf);

void __write_thread__6(object_write_buffer *buf) {
  __consumer_5_6.write_object(buf);
  save_peek_buffer__6(buf);
  save_file_pointer__6(buf);
  __producer_6_7.write_object(buf);
}

void __read_thread__6(object_write_buffer *buf) {
  __consumer_5_6.read_object(buf);
  load_peek_buffer__6(buf);
  load_file_pointer__6(buf);
  __producer_6_7.read_object(buf);
}

inline void check_status__6() {
  check_thread_status(__state_flag_6, __thread_6);
}

void check_status_during_io__6() {
  check_thread_status_during_io(__state_flag_6, __thread_6);
}

void __init_thread_info_6(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(5,6,&__consumer_5_6));
  info->add_outgoing_data_connection(new connection_info(6,7,&__producer_6_7));
  __state_flag_6 = info->get_state_flag();
}

thread_info *__get_thread_info_6() {
  if (__thread_6 != NULL) return __thread_6;
  __thread_6 = new thread_info(6, check_status_during_io__6);
  __init_thread_info_6(__thread_6);
  return __thread_6;
}

void __declare_sockets_6() {
  init_instance::add_incoming(5,6, DATA_SOCKET);
  init_instance::add_outgoing(6,7, DATA_SOCKET);
}

void __init_sockets_6(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(5,6,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_5_6.set_socket(sock);
  __consumer_5_6.init();

  sock = init_instance::get_outgoing_socket(6,7,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __producer_6_7.set_socket(sock);
  __producer_6_7.init();

}

void __flush_sockets_6() {
  __producer_6_7.flush();
  __producer_6_7.get_socket()->close();
  __producer_6_7.delete_socket_obj();
  __consumer_5_6.delete_socket_obj();
}

void __peek_sockets_6() {
  __consumer_5_6.peek(0);
}

 
void init__65__6();
inline void check_status__6();

void work__64__6(int);

// downstreamDeclarationExtern cluster_5_6
// downstreamDeclaration cluster_5_6:
int __pop_buf__6[8388608];
int __head__6;
int __tail__6;

inline void __init_pop_buf__6() {
  __tail__6=0;
  __head__6=0;
}

void save_peek_buffer__6(object_write_buffer *buf) {
  int i = 0, offs = __tail__6;
  while (offs != __head__6) {
    buf->write(&__pop_buf__6[offs], sizeof(int ));
    offs++;
    offs&=8388607;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__6(object_write_buffer *buf) {
  __tail__6=0;
  __head__6=0;
}

inline void __update_pop_buf__6() {
for (int i = 0; i < 8388608; i++) {
  __pop_buf__6[i]=__consumer_5_6.pop();
}
  __tail__6 = 0;
  __head__6 = 8388608;
}


inline int __pop_5_6() {
return __pop_buf__6[__tail__6++];
}

inline void __pop_5_6(int n) {
__tail__6+=n;
return;
}

inline int __peek_5_6(int offs) {
return __pop_buf__6[(__tail__6+offs)];
  }


// upstreamDeclarationExtern cluster_6_7
// upstreamDeclaration cluster_6_7
int __pop_buffer_6_7[10240];
int __pop_index_6_7 = 0;
inline void __push_6_7(int data) {
__producer_6_7.push(data);
}

 
void init__65__6(){
}
void save_file_pointer__6(object_write_buffer *buf) {}
void load_file_pointer__6(object_write_buffer *buf) {}
 
void work__64__6(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int tmp1__66[8388608] = {0};/* int[8388608] */
      int tmp2__67[8388608] = {0};/* int[8388608] */
      int tmp3__68[8388608] = {0};/* int[8388608] */
      int i__conflict__2__69 = 0;/* int */
      int i__conflict__1__70 = 0;/* int */
      int i__conflict__0__71 = 0;/* int */
      int i__72 = 0;/* int */

      // mark begin: SIRFilter process1

      for ((i__conflict__2__69 = 0)/*int*/; (i__conflict__2__69 < 8388608); (i__conflict__2__69++)) {(tmp1__66[(int)i__conflict__2__69]) = __pop_5_6();
;
      }
      for ((i__conflict__1__70 = 0)/*int*/; (i__conflict__1__70 < 4194304); (i__conflict__1__70++)) {{
          ((tmp2__67[(int)i__conflict__1__70]) = (tmp1__66[(int)i__conflict__1__70]))/*int*/;
          ((tmp2__67[(int)(i__conflict__1__70 + 4194304)]) = (tmp1__66[(int)(i__conflict__1__70 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__71 = 0)/*int*/; (i__conflict__0__71 < 8388608); (i__conflict__0__71++)) {((tmp3__68[(int)i__conflict__0__71]) = (tmp2__67[(int)i__conflict__0__71]))/*int*/;
      }
      for ((i__72 = 0)/*int*/; (i__72 < 8388608); (i__72++)) {__push_6_7((tmp3__68[(int)i__72]));
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_6() {
  init__65__6();
  if (save_state::load_state(6, &__steady_6, __read_thread__6) == -1) pthread_exit(NULL);
}

static void __main__6() {
  int _tmp; // modified
  int _steady = __steady_6;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__6();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__6();
      if (*__state_flag_6 == EXIT_THREAD) exit_thread(__thread_6);
      __update_pop_buf__6();
      work__64__6(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_6, _steady, __write_thread__6);
#endif // __CHECKPOINT_FREQ
  }
}

void run_6() {
  __init_sockets_6(check_status_during_io__6);
  __init_state_6();

  timer t1;
  __peek_sockets_6();
  t1.start();
  __main__6();
  t1.stop();
  if (__timer_enabled) t1.output(stderr);

  __flush_sockets_6();
  pthread_exit(NULL);
}
