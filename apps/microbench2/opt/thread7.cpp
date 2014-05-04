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

 
void init__423__7(); 
void init__168__386__7(); 
void init__182__400__7(); 
void init__192__410__7(); 
void init__202__420__7();
inline void check_status__7();

void work__422__7(int);

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



 
void init__423__7(){
  init__168__386__7();
  init__182__400__7();
  init__192__410__7();
  init__202__420__7();
}
 
void init__168__386__7(){
}
 
void init__182__400__7(){
}
 
void init__192__410__7(){
}
 
void init__202__420__7(){
}
void save_file_pointer__7(object_write_buffer *buf) {}
void load_file_pointer__7(object_write_buffer *buf) {}
 
void work__422__7(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___COUNTER_WORK_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int ___POP_BUFFER_3_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_3 = 0;/* int */
      int ___PUSH_INDEX_1_3 = 0;/* int */
      int ___COUNTER_WORK_1_3 = 0;/* int */
      int tmp__169__387[8388608] = {0};/* int[8388608] */
      int id__170__388 = 0;/* int */
      int j__conflict__3__171__389 = 0;/* int */
      int j__conflict__2__172__390 = 0;/* int */
      int i__conflict__1__173__391 = 0;/* int */
      int __tmp3__174__392 = 0;/* int */
      int j__conflict__0__175__393 = 0;/* int */
      int __tmp4__176__394 = 0;/* int */
      int j__177__395 = 0;/* int */
      int i__178__396 = 0;/* int */
      int k__179__397 = 0;/* int */
      int tmp1__183__401[2048] = {0};/* int[2048] */
      int tmp2__184__402[2048] = {0};/* int[2048] */
      int tmp3__185__403[2048] = {0};/* int[2048] */
      int i__conflict__2__186__404 = 0;/* int */
      int i__conflict__1__187__405 = 0;/* int */
      int i__conflict__0__188__406 = 0;/* int */
      int i__189__407 = 0;/* int */
      int tmp__193__411[32768] = {0};/* int[32768] */
      int id__194__412 = 0;/* int */
      int __tmp5__195__413 = 0;/* int */
      int j__conflict__1__196__414 = 0;/* int */
      int j__197__415 = 0;/* int */
      int i__conflict__0__198__416 = 0;/* int */
      int i__199__417 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      (___POP_INDEX_1_3 = -1)/*int*/;
      (___PUSH_INDEX_1_3 = -1)/*int*/;
      // mark begin: SIRFilter Fused_MyJoin_MySplit

      (id__170__388 = 0)/*int*/;
      for ((i__conflict__1__173__391 = 0)/*int*/; (i__conflict__1__173__391 < 4096); (i__conflict__1__173__391++)) {{
          for ((j__conflict__3__171__389 = 0)/*int*/; (j__conflict__3__171__389 < 1024); (j__conflict__3__171__389++)) {(tmp__169__387[(int)(id__170__388++)]) = __pop_6_7();
;
          }
          (id__170__388 = (id__170__388 - 1024))/*int*/;
          for ((j__conflict__2__172__390 = 0)/*int*/; (j__conflict__2__172__390 < 1024); (j__conflict__2__172__390++)) {(tmp__169__387[(int)((id__170__388++) + 4194304)]) = __pop_6_7();
;
          }
        }
      }
      (id__170__388 = 0)/*int*/;
      for ((k__179__397 = 0)/*int*/; (k__179__397 < 128); (k__179__397++)) {{
          for ((i__178__396 = 0)/*int*/; (i__178__396 < 32); (i__178__396++)) {{
              for ((j__conflict__0__175__393 = 0)/*int*/; (j__conflict__0__175__393 < 1024); (j__conflict__0__175__393++)) {{
                  (__tmp3__174__392 = (tmp__169__387[(int)(id__170__388++)]))/*int*/;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp3__174__392)/*int*/;
                }
              }
              (id__170__388 = (id__170__388 - 1024))/*int*/;
              for ((j__177__395 = 0)/*int*/; (j__177__395 < 1024); (j__177__395++)) {{
                  (__tmp4__176__394 = (tmp__169__387[(int)((id__170__388++) + 32768)]))/*int*/;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp4__176__394)/*int*/;
                }
              }
            }
          }
          (id__170__388 = (id__170__388 + 32768))/*int*/;
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_1 = 0)/*int*/; (___COUNTER_WORK_1_1 < 4096); (___COUNTER_WORK_1_1++)) {{
          for ((i__conflict__2__186__404 = 0)/*int*/; (i__conflict__2__186__404 < 2048); (i__conflict__2__186__404++)) {((tmp1__183__401[(int)i__conflict__2__186__404]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
          }
          for ((i__conflict__1__187__405 = 0)/*int*/; (i__conflict__1__187__405 < 1024); (i__conflict__1__187__405++)) {{
              ((tmp2__184__402[(int)i__conflict__1__187__405]) = (tmp1__183__401[(int)i__conflict__1__187__405]))/*int*/;
              ((tmp2__184__402[(int)(i__conflict__1__187__405 + 1024)]) = (tmp1__183__401[(int)(i__conflict__1__187__405 + 1024)]))/*int*/;
            }
          }
          for ((i__conflict__0__188__406 = 0)/*int*/; (i__conflict__0__188__406 < 2048); (i__conflict__0__188__406++)) {((tmp3__185__403[(int)i__conflict__0__188__406]) = (tmp2__184__402[(int)i__conflict__0__188__406]))/*int*/;
          }
          for ((i__189__407 = 0)/*int*/; (i__189__407 < 2048); (i__189__407++)) {((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = (tmp3__185__403[(int)i__189__407]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter MyJoin

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 128); (___COUNTER_WORK_1_2++)) {{
          (id__194__412 = 0)/*int*/;
          for ((i__conflict__0__198__416 = 0)/*int*/; (i__conflict__0__198__416 < 32); (i__conflict__0__198__416++)) {{
              for ((j__conflict__1__196__414 = 0)/*int*/; (j__conflict__1__196__414 < 1024); (j__conflict__1__196__414++)) {{
                  (__tmp5__195__413 = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
                  ((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = __tmp5__195__413)/*int*/;
                }
              }
              for ((j__197__415 = 0)/*int*/; (j__197__415 < 1024); (j__197__415++)) {((tmp__193__411[(int)(id__194__412++)]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
              }
            }
          }
          for ((i__199__417 = 0)/*int*/; (i__199__417 < 32768); (i__199__417++)) {((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = (tmp__193__411[(int)i__199__417]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter MyJoin

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_3 = 0)/*int*/; (___COUNTER_WORK_1_3 < 8388608); (___COUNTER_WORK_1_3++)) {{
          (___POP_INDEX_1_3 = (___POP_INDEX_1_3 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_7() {
  init__423__7();
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
      work__422__7(1);
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
