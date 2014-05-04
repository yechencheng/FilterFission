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
message *__msg_stack_4;
int __number_of_iterations_4;
int __counter_4 = 0;
int __steady_4 = 0;
int __tmp_4 = 0;
int __tmp2_4 = 0;
int *__state_flag_4 = NULL;
thread_info *__thread_4 = NULL;

consumer2<int> __consumer_3_4;
extern int __pop_3_4();
producer2<int> __producer_4_5;
extern void __push_4_5(int);
    // this-part:5 dst-part:6


void save_peek_buffer__4(object_write_buffer *buf);
void load_peek_buffer__4(object_write_buffer *buf);
void save_file_pointer__4(object_write_buffer *buf);
void load_file_pointer__4(object_write_buffer *buf);

void __write_thread__4(object_write_buffer *buf) {
  __consumer_3_4.write_object(buf);
  save_peek_buffer__4(buf);
  save_file_pointer__4(buf);
  __producer_4_5.write_object(buf);
}

void __read_thread__4(object_write_buffer *buf) {
  __consumer_3_4.read_object(buf);
  load_peek_buffer__4(buf);
  load_file_pointer__4(buf);
  __producer_4_5.read_object(buf);
}

inline void check_status__4() {
  check_thread_status(__state_flag_4, __thread_4);
}

void check_status_during_io__4() {
  check_thread_status_during_io(__state_flag_4, __thread_4);
}

void __init_thread_info_4(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(3,4,&__consumer_3_4));
  info->add_outgoing_data_connection(new connection_info(4,5,&__producer_4_5));
  __state_flag_4 = info->get_state_flag();
}

thread_info *__get_thread_info_4() {
  if (__thread_4 != NULL) return __thread_4;
  __thread_4 = new thread_info(4, check_status_during_io__4);
  __init_thread_info_4(__thread_4);
  return __thread_4;
}

void __declare_sockets_4() {
  init_instance::add_incoming(3,4, DATA_SOCKET);
  init_instance::add_outgoing(4,5, DATA_SOCKET);
}

void __init_sockets_4(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(3,4,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_3_4.set_socket(sock);
  __consumer_3_4.init();

  sock = init_instance::get_outgoing_socket(4,5,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __producer_4_5.set_socket(sock);
  __producer_4_5.init();

}

void __flush_sockets_4() {
  __producer_4_5.flush();
  __producer_4_5.get_socket()->close();
  __producer_4_5.delete_socket_obj();
  __consumer_3_4.delete_socket_obj();
}

void __peek_sockets_4() {
  __consumer_3_4.peek(0);
}

 
void init__45__4();
inline void check_status__4();

void work__44__4(int);

// downstreamDeclarationExtern cluster_3_4
// downstreamDeclaration cluster_3_4:
int __pop_buf__4[8388608];
int __head__4;
int __tail__4;

inline void __init_pop_buf__4() {
  __tail__4=0;
  __head__4=0;
}

void save_peek_buffer__4(object_write_buffer *buf) {
  int i = 0, offs = __tail__4;
  while (offs != __head__4) {
    buf->write(&__pop_buf__4[offs], sizeof(int ));
    offs++;
    offs&=8388607;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__4(object_write_buffer *buf) {
  __tail__4=0;
  __head__4=0;
}

inline void __update_pop_buf__4() {
for (int i = 0; i < 8388608; i++) {
  __pop_buf__4[i]=__consumer_3_4.pop();
}
  __tail__4 = 0;
  __head__4 = 8388608;
}


inline int __pop_3_4() {
return __pop_buf__4[__tail__4++];
}

inline void __pop_3_4(int n) {
__tail__4+=n;
return;
}

inline int __peek_3_4(int offs) {
return __pop_buf__4[(__tail__4+offs)];
  }


// upstreamDeclarationExtern cluster_4_5
// upstreamDeclaration cluster_4_5
int __pop_buffer_4_5[10240];
int __pop_index_4_5 = 0;
inline void __push_4_5(int data) {
__producer_4_5.push(data);
}

 
void init__45__4(){
}
void save_file_pointer__4(object_write_buffer *buf) {}
void load_file_pointer__4(object_write_buffer *buf) {}
 
void work__44__4(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int tmp1__46[8388608] = {0};/* int[8388608] */
      int tmp2__47[8388608] = {0};/* int[8388608] */
      int tmp3__48[8388608] = {0};/* int[8388608] */
      int i__conflict__2__49 = 0;/* int */
      int i__conflict__1__50 = 0;/* int */
      int i__conflict__0__51 = 0;/* int */
      int i__52 = 0;/* int */

      // mark begin: SIRFilter process1

      for ((i__conflict__2__49 = 0)/*int*/; (i__conflict__2__49 < 8388608); (i__conflict__2__49++)) {(tmp1__46[(int)i__conflict__2__49]) = __pop_3_4();
;
      }
      for ((i__conflict__1__50 = 0)/*int*/; (i__conflict__1__50 < 4194304); (i__conflict__1__50++)) {{
          ((tmp2__47[(int)i__conflict__1__50]) = (tmp1__46[(int)i__conflict__1__50]))/*int*/;
          ((tmp2__47[(int)(i__conflict__1__50 + 4194304)]) = (tmp1__46[(int)(i__conflict__1__50 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__51 = 0)/*int*/; (i__conflict__0__51 < 8388608); (i__conflict__0__51++)) {((tmp3__48[(int)i__conflict__0__51]) = (tmp2__47[(int)i__conflict__0__51]))/*int*/;
      }
      for ((i__52 = 0)/*int*/; (i__52 < 8388608); (i__52++)) {__push_4_5((tmp3__48[(int)i__52]));
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_4() {
  init__45__4();
  if (save_state::load_state(4, &__steady_4, __read_thread__4) == -1) pthread_exit(NULL);
}

static void __main__4() {
  int _tmp; // modified
  int _steady = __steady_4;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__4();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__4();
      if (*__state_flag_4 == EXIT_THREAD) exit_thread(__thread_4);
      __update_pop_buf__4();
      work__44__4(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_4, _steady, __write_thread__4);
#endif // __CHECKPOINT_FREQ
  }
}

void run_4() {
  __init_sockets_4(check_status_during_io__4);
  __init_state_4();

  timer t1;
  __peek_sockets_4();
  t1.start();
  __main__4();
  t1.stop();
  if (__timer_enabled) t1.output(stderr);

  __flush_sockets_4();
  pthread_exit(NULL);
}
