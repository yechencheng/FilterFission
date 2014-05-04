// peek: 8388608 pop: 8388608 push 0
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
message *__msg_stack_7;
int __number_of_iterations_7;
int __counter_7 = 0;
int __steady_7 = 0;
int __tmp_7 = 0;
int __tmp2_7 = 0;
int *__state_flag_7 = NULL;
thread_info *__thread_7 = NULL;

consumer2<int> __consumer_6_7;
extern int __pop_6_7();


void save_peek_buffer__7(object_write_buffer *buf);
void load_peek_buffer__7(object_write_buffer *buf);
void save_file_pointer__7(object_write_buffer *buf);
void load_file_pointer__7(object_write_buffer *buf);

void __write_thread__7(object_write_buffer *buf) {
  __consumer_6_7.write_object(buf);
  save_peek_buffer__7(buf);
  save_file_pointer__7(buf);
}

void __read_thread__7(object_write_buffer *buf) {
  __consumer_6_7.read_object(buf);
  load_peek_buffer__7(buf);
  load_file_pointer__7(buf);
}

inline void check_status__7() {
  check_thread_status(__state_flag_7, __thread_7);
}

void check_status_during_io__7() {
  check_thread_status_during_io(__state_flag_7, __thread_7);
}

void __init_thread_info_7(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(6,7,&__consumer_6_7));
  __state_flag_7 = info->get_state_flag();
}

thread_info *__get_thread_info_7() {
  if (__thread_7 != NULL) return __thread_7;
  __thread_7 = new thread_info(7, check_status_during_io__7);
  __init_thread_info_7(__thread_7);
  return __thread_7;
}

void __declare_sockets_7() {
  init_instance::add_incoming(6,7, DATA_SOCKET);
}

void __init_sockets_7(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(6,7,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_6_7.set_socket(sock);
  __consumer_6_7.init();

}

void __flush_sockets_7() {
  __consumer_6_7.delete_socket_obj();
}

void __peek_sockets_7() {
  __consumer_6_7.peek(0);
}

 
void init__117__7(); 
void init__75__104__7(); 
void init__85__114__7();
inline void check_status__7();

void work__116__7(int);

// downstreamDeclarationExtern cluster_6_7
// downstreamDeclaration cluster_6_7:
int __pop_buf__7[8388608];
int __head__7;
int __tail__7;

inline void __init_pop_buf__7() {
  __tail__7=0;
  __head__7=0;
}

void save_peek_buffer__7(object_write_buffer *buf) {
  int i = 0, offs = __tail__7;
  while (offs != __head__7) {
    buf->write(&__pop_buf__7[offs], sizeof(int ));
    offs++;
    offs&=8388607;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__7(object_write_buffer *buf) {
  __tail__7=0;
  __head__7=0;
}

inline void __update_pop_buf__7() {
for (int i = 0; i < 8388608; i++) {
  __pop_buf__7[i]=__consumer_6_7.pop();
}
  __tail__7 = 0;
  __head__7 = 8388608;
}


inline int __pop_6_7() {
return __pop_buf__7[__tail__7++];
}

inline void __pop_6_7(int n) {
__tail__7+=n;
return;
}

inline int __peek_6_7(int offs) {
return __pop_buf__7[(__tail__7+offs)];
  }



 
void init__117__7(){
  init__75__104__7();
  init__85__114__7();
}
 
void init__75__104__7(){
}
 
void init__85__114__7(){
}
void save_file_pointer__7(object_write_buffer *buf) {}
void load_file_pointer__7(object_write_buffer *buf) {}
 
void work__116__7(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___COUNTER_WORK_1_1 = 0;/* int */
      int tmp1__76__105[8388608] = {0};/* int[8388608] */
      int tmp2__77__106[8388608] = {0};/* int[8388608] */
      int tmp3__78__107[8388608] = {0};/* int[8388608] */
      int i__conflict__2__79__108 = 0;/* int */
      int i__conflict__1__80__109 = 0;/* int */
      int i__conflict__0__81__110 = 0;/* int */
      int i__82__111 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((i__conflict__2__79__108 = 0)/*int*/; (i__conflict__2__79__108 < 8388608); (i__conflict__2__79__108++)) {(tmp1__76__105[(int)i__conflict__2__79__108]) = __pop_6_7();
;
      }
      for ((i__conflict__1__80__109 = 0)/*int*/; (i__conflict__1__80__109 < 4194304); (i__conflict__1__80__109++)) {{
          ((tmp2__77__106[(int)i__conflict__1__80__109]) = (tmp1__76__105[(int)i__conflict__1__80__109]))/*int*/;
          ((tmp2__77__106[(int)(i__conflict__1__80__109 + 4194304)]) = (tmp1__76__105[(int)(i__conflict__1__80__109 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__81__110 = 0)/*int*/; (i__conflict__0__81__110 < 8388608); (i__conflict__0__81__110++)) {((tmp3__78__107[(int)i__conflict__0__81__110]) = (tmp2__77__106[(int)i__conflict__0__81__110]))/*int*/;
      }
      for ((i__82__111 = 0)/*int*/; (i__82__111 < 8388608); (i__82__111++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__78__107[(int)i__82__111]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_1 = 0)/*int*/; (___COUNTER_WORK_1_1 < 8388608); (___COUNTER_WORK_1_1++)) {{
          (___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_7() {
  init__117__7();
  if (save_state::load_state(7, &__steady_7, __read_thread__7) == -1) pthread_exit(NULL);
}

static void __main__7() {
  int _tmp; // modified
  int _steady = __steady_7;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__7();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__7();
      if (*__state_flag_7 == EXIT_THREAD) exit_thread(__thread_7);
      __update_pop_buf__7();
      work__116__7(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_7, _steady, __write_thread__7);
#endif // __CHECKPOINT_FREQ
  }
}

void run_7() {
  __init_sockets_7(check_status_during_io__7);
  __init_state_7();

  __main__7();

  __flush_sockets_7();
  pthread_exit(NULL);
}
