// peek: 1048576 pop: 1048576 push 0
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
message *__msg_stack_3;
int __number_of_iterations_3;
int __counter_3 = 0;
int __steady_3 = 0;
int __tmp_3 = 0;
int __tmp2_3 = 0;
int *__state_flag_3 = NULL;
thread_info *__thread_3 = NULL;

consumer2<int> __consumer_2_3;
extern int __pop_2_3();


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

 
void init__71__3(); 
void init__32__59__3(); 
void init__41__68__3();
inline void check_status__3();

void work__70__3(int);

// downstreamDeclarationExtern cluster_2_3
// downstreamDeclaration cluster_2_3:
int __pop_buf__3[1048576];
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
    offs&=1048575;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__3(object_write_buffer *buf) {
  __tail__3=0;
  __head__3=0;
}

inline void __update_pop_buf__3() {
for (int i = 0; i < 1048576; i++) {
  __pop_buf__3[i]=__consumer_2_3.pop();
}
  __tail__3 = 0;
  __head__3 = 1048576;
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



 
void init__71__3(){
  init__32__59__3();
  init__41__68__3();
}
 
void init__32__59__3(){
}
 
void init__41__68__3(){
}
void save_file_pointer__3(object_write_buffer *buf) {}
void load_file_pointer__3(object_write_buffer *buf) {}
 
void work__70__3(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[1048576] = {0};/* int[1048576] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___COUNTER_WORK_1_1 = 0;/* int */
      int tmp1__33__60[1048576] = {0};/* int[1048576] */
      int tmp2__34__61[1048576] = {0};/* int[1048576] */
      int i__conflict__2__35__62 = 0;/* int */
      int i__conflict__1__36__63 = 0;/* int */
      int i__conflict__0__37__64 = 0;/* int */
      int i__38__65 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      // mark begin: SIRFilter process

      for ((i__conflict__2__35__62 = 0)/*int*/; (i__conflict__2__35__62 < 1048576); (i__conflict__2__35__62++)) {(tmp1__33__60[(int)i__conflict__2__35__62]) = __pop_2_3();
;
      }
      for ((i__conflict__1__36__63 = 0)/*int*/; (i__conflict__1__36__63 < 1048576); (i__conflict__1__36__63++)) {((tmp1__33__60[(int)i__conflict__1__36__63])++);
      }
      for ((i__conflict__0__37__64 = 0)/*int*/; (i__conflict__0__37__64 < 1048576); (i__conflict__0__37__64++)) {((tmp2__34__61[(int)i__conflict__0__37__64]) = ((tmp1__33__60[(int)i__conflict__0__37__64]) + 1))/*int*/;
      }
      for ((i__38__65 = 0)/*int*/; (i__38__65 < 1048576); (i__38__65++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp2__34__61[(int)i__38__65]))/*int*/;
      }
      // mark end: SIRFilter process

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_1 = 0)/*int*/; (___COUNTER_WORK_1_1 < 1048576); (___COUNTER_WORK_1_1++)) {{
          (___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_3() {
  init__71__3();
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
      work__70__3(1);
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
