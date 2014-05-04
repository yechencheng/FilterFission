// peek: 2097152 pop: 2097152 push 0
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
message *__msg_stack_8;
int __number_of_iterations_8;
int __counter_8 = 0;
int __steady_8 = 0;
int __tmp_8 = 0;
int __tmp2_8 = 0;
int *__state_flag_8 = NULL;
thread_info *__thread_8 = NULL;

consumer2<int> __consumer_7_8;
extern int __pop_7_8();


void save_peek_buffer__8(object_write_buffer *buf);
void load_peek_buffer__8(object_write_buffer *buf);
void save_file_pointer__8(object_write_buffer *buf);
void load_file_pointer__8(object_write_buffer *buf);

void __write_thread__8(object_write_buffer *buf) {
  __consumer_7_8.write_object(buf);
  save_peek_buffer__8(buf);
  save_file_pointer__8(buf);
}

void __read_thread__8(object_write_buffer *buf) {
  __consumer_7_8.read_object(buf);
  load_peek_buffer__8(buf);
  load_file_pointer__8(buf);
}

inline void check_status__8() {
  check_thread_status(__state_flag_8, __thread_8);
}

void check_status_during_io__8() {
  check_thread_status_during_io(__state_flag_8, __thread_8);
}

void __init_thread_info_8(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(7,8,&__consumer_7_8));
  __state_flag_8 = info->get_state_flag();
}

thread_info *__get_thread_info_8() {
  if (__thread_8 != NULL) return __thread_8;
  __thread_8 = new thread_info(8, check_status_during_io__8);
  __init_thread_info_8(__thread_8);
  return __thread_8;
}

void __declare_sockets_8() {
  init_instance::add_incoming(7,8, DATA_SOCKET);
}

void __init_sockets_8(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(7,8,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_7_8.set_socket(sock);
  __consumer_7_8.init();

}

void __flush_sockets_8() {
  __consumer_7_8.delete_socket_obj();
}

void __peek_sockets_8() {
  __consumer_7_8.peek(0);
}

 
void init__199__8(); 
void init__99__186__8(); 
void init__109__196__8();
inline void check_status__8();

void work__198__8(int);

// downstreamDeclarationExtern cluster_7_8
// downstreamDeclaration cluster_7_8:
int __pop_buf__8[2097152];
int __head__8;
int __tail__8;

inline void __init_pop_buf__8() {
  __tail__8=0;
  __head__8=0;
}

void save_peek_buffer__8(object_write_buffer *buf) {
  int i = 0, offs = __tail__8;
  while (offs != __head__8) {
    buf->write(&__pop_buf__8[offs], sizeof(int ));
    offs++;
    offs&=2097151;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__8(object_write_buffer *buf) {
  __tail__8=0;
  __head__8=0;
}

inline void __update_pop_buf__8() {
for (int i = 0; i < 2097152; i++) {
  __pop_buf__8[i]=__consumer_7_8.pop();
}
  __tail__8 = 0;
  __head__8 = 2097152;
}


inline int __pop_7_8() {
return __pop_buf__8[__tail__8++];
}

inline void __pop_7_8(int n) {
__tail__8+=n;
return;
}

inline int __peek_7_8(int offs) {
return __pop_buf__8[(__tail__8+offs)];
  }



 
void init__199__8(){
  init__99__186__8();
  init__109__196__8();
}
 
void init__99__186__8(){
}
 
void init__109__196__8(){
}
void save_file_pointer__8(object_write_buffer *buf) {}
void load_file_pointer__8(object_write_buffer *buf) {}
 
void work__198__8(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[2097152] = {0};/* int[2097152] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___COUNTER_WORK_1_1 = 0;/* int */
      int tmp__100__187[1048576] = {0};/* int[1048576] */
      int id__101__188 = 0;/* int */
      int __tmp4__102__189 = 0;/* int */
      int j__conflict__1__103__190 = 0;/* int */
      int j__104__191 = 0;/* int */
      int i__conflict__0__105__192 = 0;/* int */
      int i__106__193 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      // mark begin: SIRFilter MyJoin

      (id__101__188 = 0)/*int*/;
      for ((i__conflict__0__105__192 = 0)/*int*/; (i__conflict__0__105__192 < 1024); (i__conflict__0__105__192++)) {{
          for ((j__conflict__1__103__190 = 0)/*int*/; (j__conflict__1__103__190 < 1024); (j__conflict__1__103__190++)) {{
              __tmp4__102__189 = __pop_7_8();
;
              ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp4__102__189)/*int*/;
            }
          }
          for ((j__104__191 = 0)/*int*/; (j__104__191 < 1024); (j__104__191++)) {(tmp__100__187[(int)(id__101__188++)]) = __pop_7_8();
;
          }
        }
      }
      for ((i__106__193 = 0)/*int*/; (i__106__193 < 1048576); (i__106__193++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp__100__187[(int)i__106__193]))/*int*/;
      }
      // mark end: SIRFilter MyJoin

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_1 = 0)/*int*/; (___COUNTER_WORK_1_1 < 2097152); (___COUNTER_WORK_1_1++)) {{
          (___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_8() {
  init__199__8();
  if (save_state::load_state(8, &__steady_8, __read_thread__8) == -1) pthread_exit(NULL);
}

static void __main__8() {
  int _tmp; // modified
  int _steady = __steady_8;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__8();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__8();
      if (*__state_flag_8 == EXIT_THREAD) exit_thread(__thread_8);
      __update_pop_buf__8();
      work__198__8(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_8, _steady, __write_thread__8);
#endif // __CHECKPOINT_FREQ
  }
}

void run_8() {
  __init_sockets_8(check_status_during_io__8);
  __init_state_8();

  __main__8();

  __flush_sockets_8();
  pthread_exit(NULL);
}
