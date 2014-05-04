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
message *__msg_stack_5;
int __number_of_iterations_5;
int __counter_5 = 0;
int __steady_5 = 0;
int __tmp_5 = 0;
int __tmp2_5 = 0;
int *__state_flag_5 = NULL;
thread_info *__thread_5 = NULL;

consumer2<int> __consumer_4_5;
extern int __pop_4_5();
producer2<int> __producer_5_6;
extern void __push_5_6(int);
    // this-part:6 dst-part:7


void save_peek_buffer__5(object_write_buffer *buf);
void load_peek_buffer__5(object_write_buffer *buf);
void save_file_pointer__5(object_write_buffer *buf);
void load_file_pointer__5(object_write_buffer *buf);

void __write_thread__5(object_write_buffer *buf) {
  __consumer_4_5.write_object(buf);
  save_peek_buffer__5(buf);
  save_file_pointer__5(buf);
  __producer_5_6.write_object(buf);
}

void __read_thread__5(object_write_buffer *buf) {
  __consumer_4_5.read_object(buf);
  load_peek_buffer__5(buf);
  load_file_pointer__5(buf);
  __producer_5_6.read_object(buf);
}

inline void check_status__5() {
  check_thread_status(__state_flag_5, __thread_5);
}

void check_status_during_io__5() {
  check_thread_status_during_io(__state_flag_5, __thread_5);
}

void __init_thread_info_5(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(4,5,&__consumer_4_5));
  info->add_outgoing_data_connection(new connection_info(5,6,&__producer_5_6));
  __state_flag_5 = info->get_state_flag();
}

thread_info *__get_thread_info_5() {
  if (__thread_5 != NULL) return __thread_5;
  __thread_5 = new thread_info(5, check_status_during_io__5);
  __init_thread_info_5(__thread_5);
  return __thread_5;
}

void __declare_sockets_5() {
  init_instance::add_incoming(4,5, DATA_SOCKET);
  init_instance::add_outgoing(5,6, DATA_SOCKET);
}

void __init_sockets_5(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(4,5,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_4_5.set_socket(sock);
  __consumer_4_5.init();

  sock = init_instance::get_outgoing_socket(5,6,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __producer_5_6.set_socket(sock);
  __producer_5_6.init();

}

void __flush_sockets_5() {
  __producer_5_6.flush();
  __producer_5_6.get_socket()->close();
  __producer_5_6.delete_socket_obj();
  __consumer_4_5.delete_socket_obj();
}

void __peek_sockets_5() {
  __consumer_4_5.peek(0);
}

 
void init__55__5();
inline void check_status__5();

void work__54__5(int);

// downstreamDeclarationExtern cluster_4_5
// downstreamDeclaration cluster_4_5:
int __pop_buf__5[8388608];
int __head__5;
int __tail__5;

inline void __init_pop_buf__5() {
  __tail__5=0;
  __head__5=0;
}

void save_peek_buffer__5(object_write_buffer *buf) {
  int i = 0, offs = __tail__5;
  while (offs != __head__5) {
    buf->write(&__pop_buf__5[offs], sizeof(int ));
    offs++;
    offs&=8388607;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__5(object_write_buffer *buf) {
  __tail__5=0;
  __head__5=0;
}

inline void __update_pop_buf__5() {
for (int i = 0; i < 8388608; i++) {
  __pop_buf__5[i]=__consumer_4_5.pop();
}
  __tail__5 = 0;
  __head__5 = 8388608;
}


inline int __pop_4_5() {
return __pop_buf__5[__tail__5++];
}

inline void __pop_4_5(int n) {
__tail__5+=n;
return;
}

inline int __peek_4_5(int offs) {
return __pop_buf__5[(__tail__5+offs)];
  }


// upstreamDeclarationExtern cluster_5_6
// upstreamDeclaration cluster_5_6
int __pop_buffer_5_6[10240];
int __pop_index_5_6 = 0;
inline void __push_5_6(int data) {
__producer_5_6.push(data);
}

 
void init__55__5(){
}
void save_file_pointer__5(object_write_buffer *buf) {}
void load_file_pointer__5(object_write_buffer *buf) {}
 
void work__54__5(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int tmp1__56[8388608] = {0};/* int[8388608] */
      int tmp2__57[8388608] = {0};/* int[8388608] */
      int tmp3__58[8388608] = {0};/* int[8388608] */
      int i__conflict__2__59 = 0;/* int */
      int i__conflict__1__60 = 0;/* int */
      int i__conflict__0__61 = 0;/* int */
      int i__62 = 0;/* int */

      // mark begin: SIRFilter process1

      for ((i__conflict__2__59 = 0)/*int*/; (i__conflict__2__59 < 8388608); (i__conflict__2__59++)) {(tmp1__56[(int)i__conflict__2__59]) = __pop_4_5();
;
      }
      for ((i__conflict__1__60 = 0)/*int*/; (i__conflict__1__60 < 4194304); (i__conflict__1__60++)) {{
          ((tmp2__57[(int)i__conflict__1__60]) = (tmp1__56[(int)i__conflict__1__60]))/*int*/;
          ((tmp2__57[(int)(i__conflict__1__60 + 4194304)]) = (tmp1__56[(int)(i__conflict__1__60 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__61 = 0)/*int*/; (i__conflict__0__61 < 8388608); (i__conflict__0__61++)) {((tmp3__58[(int)i__conflict__0__61]) = (tmp2__57[(int)i__conflict__0__61]))/*int*/;
      }
      for ((i__62 = 0)/*int*/; (i__62 < 8388608); (i__62++)) {__push_5_6((tmp3__58[(int)i__62]));
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_5() {
  init__55__5();
  if (save_state::load_state(5, &__steady_5, __read_thread__5) == -1) pthread_exit(NULL);
}

static void __main__5() {
  int _tmp; // modified
  int _steady = __steady_5;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__5();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__5();
      if (*__state_flag_5 == EXIT_THREAD) exit_thread(__thread_5);
      __update_pop_buf__5();
      work__54__5(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_5, _steady, __write_thread__5);
#endif // __CHECKPOINT_FREQ
  }
}

void run_5() {
  __init_sockets_5(check_status_during_io__5);
  __init_state_5();

  timer t1;
  __peek_sockets_5();
  t1.start();
  __main__5();
  t1.stop();
  if (__timer_enabled) t1.output(stderr);

  __flush_sockets_5();
  pthread_exit(NULL);
}
