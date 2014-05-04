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

 
void init__183__3(); 
void init__65__159__3(); 
void init__75__169__3(); 
void init__85__179__3();
inline void check_status__3();

void work__182__3(int);

// downstreamDeclarationExtern cluster_2_3
// downstreamDeclaration cluster_2_3:
int __pop_buf__3[8388608];
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
    offs&=8388607;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__3(object_write_buffer *buf) {
  __tail__3=0;
  __head__3=0;
}

inline void __update_pop_buf__3() {
for (int i = 0; i < 8388608; i++) {
  __pop_buf__3[i]=__consumer_2_3.pop();
}
  __tail__3 = 0;
  __head__3 = 8388608;
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



 
void init__183__3(){
  init__65__159__3();
  init__75__169__3();
  init__85__179__3();
}
 
void init__65__159__3(){
}
 
void init__75__169__3(){
}
 
void init__85__179__3(){
}
void save_file_pointer__3(object_write_buffer *buf) {}
void load_file_pointer__3(object_write_buffer *buf) {}
 
void work__182__3(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int tmp1__66__160[8388608] = {0};/* int[8388608] */
      int tmp2__67__161[8388608] = {0};/* int[8388608] */
      int tmp3__68__162[8388608] = {0};/* int[8388608] */
      int i__conflict__2__69__163 = 0;/* int */
      int i__conflict__1__70__164 = 0;/* int */
      int i__conflict__0__71__165 = 0;/* int */
      int i__72__166 = 0;/* int */
      int tmp1__76__170[8388608] = {0};/* int[8388608] */
      int tmp2__77__171[8388608] = {0};/* int[8388608] */
      int tmp3__78__172[8388608] = {0};/* int[8388608] */
      int i__conflict__2__79__173 = 0;/* int */
      int i__conflict__1__80__174 = 0;/* int */
      int i__conflict__0__81__175 = 0;/* int */
      int i__82__176 = 0;/* int */
      int __tmp2__86__180 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((i__conflict__2__69__163 = 0)/*int*/; (i__conflict__2__69__163 < 8388608); (i__conflict__2__69__163++)) {(tmp1__66__160[(int)i__conflict__2__69__163]) = __pop_2_3();
;
      }
      for ((i__conflict__1__70__164 = 0)/*int*/; (i__conflict__1__70__164 < 4194304); (i__conflict__1__70__164++)) {{
          ((tmp2__67__161[(int)i__conflict__1__70__164]) = (tmp1__66__160[(int)i__conflict__1__70__164]))/*int*/;
          ((tmp2__67__161[(int)(i__conflict__1__70__164 + 4194304)]) = (tmp1__66__160[(int)(i__conflict__1__70__164 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__71__165 = 0)/*int*/; (i__conflict__0__71__165 < 8388608); (i__conflict__0__71__165++)) {((tmp3__68__162[(int)i__conflict__0__71__165]) = (tmp2__67__161[(int)i__conflict__0__71__165]))/*int*/;
      }
      for ((i__72__166 = 0)/*int*/; (i__72__166 < 8388608); (i__72__166++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__68__162[(int)i__72__166]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter process1

      for ((i__conflict__2__79__173 = 0)/*int*/; (i__conflict__2__79__173 < 8388608); (i__conflict__2__79__173++)) {((tmp1__76__170[(int)i__conflict__2__79__173]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
      }
      for ((i__conflict__1__80__174 = 0)/*int*/; (i__conflict__1__80__174 < 4194304); (i__conflict__1__80__174++)) {{
          ((tmp2__77__171[(int)i__conflict__1__80__174]) = (tmp1__76__170[(int)i__conflict__1__80__174]))/*int*/;
          ((tmp2__77__171[(int)(i__conflict__1__80__174 + 4194304)]) = (tmp1__76__170[(int)(i__conflict__1__80__174 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__81__175 = 0)/*int*/; (i__conflict__0__81__175 < 8388608); (i__conflict__0__81__175++)) {((tmp3__78__172[(int)i__conflict__0__81__175]) = (tmp2__77__171[(int)i__conflict__0__81__175]))/*int*/;
      }
      for ((i__82__176 = 0)/*int*/; (i__82__176 < 8388608); (i__82__176++)) {((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = (tmp3__78__172[(int)i__82__176]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 8388608); (___COUNTER_WORK_1_2++)) {{
          (__tmp2__86__180 = (___POP_BUFFER_2_1[(int)((1 + ___POP_INDEX_1_2) + 0)]))/*int*/;

          // TIMER_PRINT_CODE: __print_sink__ += (int)(__tmp2__86__180); 
          printf( "%d", __tmp2__86__180); printf("\n");

          (___POP_INDEX_1_2 = (___POP_INDEX_1_2 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_3() {
  init__183__3();
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
      work__182__3(1);
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
