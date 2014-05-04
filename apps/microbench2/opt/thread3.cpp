// peek: 131072 pop: 131072 push 0
// init counts: 0 steady counts: 64

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

 
void init__529__3(); 
void init__206__473__3(); 
void init__216__483__3(); 
void init__238__505__3(); 
void init__248__515__3(); 
void init__258__525__3();
inline void check_status__3();

void work__528__3(int);

// downstreamDeclarationExtern cluster_2_3
// downstreamDeclaration cluster_2_3:
int __pop_buf__3[131072];
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
    offs&=131071;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__3(object_write_buffer *buf) {
  __tail__3=0;
  __head__3=0;
}

inline void __update_pop_buf__3() {
for (int i = 0; i < 131072; i++) {
  __pop_buf__3[i]=__consumer_2_3.pop();
}
  __tail__3 = 0;
  __head__3 = 131072;
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



 
void init__529__3(){
  init__206__473__3();
  init__216__483__3();
  init__238__505__3();
  init__248__515__3();
  init__258__525__3();
}
 
void init__206__473__3(){
}
 
void init__216__483__3(){
}
 
void init__238__505__3(){
}
 
void init__248__515__3(){
}
 
void init__258__525__3(){
}
void save_file_pointer__3(object_write_buffer *buf) {}
void load_file_pointer__3(object_write_buffer *buf) {}
 
void work__528__3(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___COUNTER_WORK_1_0 = 0;/* int */
      int ___POP_BUFFER_1_1[131072] = {0};/* int[131072] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[131072] = {0};/* int[131072] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int ___POP_BUFFER_3_1[131072] = {0};/* int[131072] */
      int ___POP_INDEX_1_3 = 0;/* int */
      int ___PUSH_INDEX_1_3 = 0;/* int */
      int ___COUNTER_WORK_1_3 = 0;/* int */
      int ___POP_BUFFER_4_1[131072] = {0};/* int[131072] */
      int ___POP_INDEX_1_4 = 0;/* int */
      int ___PUSH_INDEX_1_4 = 0;/* int */
      int ___COUNTER_WORK_1_4 = 0;/* int */
      int tmp1__207__474[1024] = {0};/* int[1024] */
      int tmp2__208__475[1024] = {0};/* int[1024] */
      int tmp3__209__476[1024] = {0};/* int[1024] */
      int i__conflict__2__210__477 = 0;/* int */
      int i__conflict__1__211__478 = 0;/* int */
      int i__conflict__0__212__479 = 0;/* int */
      int i__213__480 = 0;/* int */
      int id__217__484 = 0;/* int */
      int tmp__218__485[65536] = {0};/* int[65536] */
      int __tmp3__219__486 = 0;/* int */
      int k__conflict__8__220__487 = 0;/* int */
      int __tmp4__221__488 = 0;/* int */
      int __tmp5__222__489 = 0;/* int */
      int k__conflict__7__223__490 = 0;/* int */
      int k__conflict__6__224__491 = 0;/* int */
      int j__conflict__5__225__492 = 0;/* int */
      int k__conflict__4__226__493 = 0;/* int */
      int k__conflict__3__227__494 = 0;/* int */
      int j__conflict__2__228__495 = 0;/* int */
      int i__conflict__1__229__496 = 0;/* int */
      int __tmp6__230__497 = 0;/* int */
      int j__conflict__0__231__498 = 0;/* int */
      int __tmp7__232__499 = 0;/* int */
      int j__233__500 = 0;/* int */
      int i__234__501 = 0;/* int */
      int k__235__502 = 0;/* int */
      int tmp1__239__506[1024] = {0};/* int[1024] */
      int tmp2__240__507[1024] = {0};/* int[1024] */
      int tmp3__241__508[1024] = {0};/* int[1024] */
      int i__conflict__2__242__509 = 0;/* int */
      int i__conflict__1__243__510 = 0;/* int */
      int i__conflict__0__244__511 = 0;/* int */
      int i__245__512 = 0;/* int */
      int tmp__249__516[32768] = {0};/* int[32768] */
      int id__250__517 = 0;/* int */
      int __tmp8__251__518 = 0;/* int */
      int j__conflict__1__252__519 = 0;/* int */
      int j__253__520 = 0;/* int */
      int i__conflict__0__254__521 = 0;/* int */
      int i__255__522 = 0;/* int */
      int __tmp9__259__526 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      (___POP_INDEX_1_3 = -1)/*int*/;
      (___PUSH_INDEX_1_3 = -1)/*int*/;
      (___POP_INDEX_1_4 = -1)/*int*/;
      (___PUSH_INDEX_1_4 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_0 = 0)/*int*/; (___COUNTER_WORK_1_0 < 128); (___COUNTER_WORK_1_0++)) {{
          for ((i__conflict__2__210__477 = 0)/*int*/; (i__conflict__2__210__477 < 1024); (i__conflict__2__210__477++)) {(tmp1__207__474[(int)i__conflict__2__210__477]) = __pop_2_3();
;
          }
          for ((i__conflict__1__211__478 = 0)/*int*/; (i__conflict__1__211__478 < 512); (i__conflict__1__211__478++)) {{
              ((tmp2__208__475[(int)i__conflict__1__211__478]) = (tmp1__207__474[(int)i__conflict__1__211__478]))/*int*/;
              ((tmp2__208__475[(int)(i__conflict__1__211__478 + 512)]) = (tmp1__207__474[(int)(i__conflict__1__211__478 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__212__479 = 0)/*int*/; (i__conflict__0__212__479 < 1024); (i__conflict__0__212__479++)) {((tmp3__209__476[(int)i__conflict__0__212__479]) = (tmp2__208__475[(int)i__conflict__0__212__479]))/*int*/;
          }
          for ((i__213__480 = 0)/*int*/; (i__213__480 < 1024); (i__213__480++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__209__476[(int)i__213__480]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      (id__217__484 = 0)/*int*/;
      for ((i__conflict__1__229__496 = 0)/*int*/; (i__conflict__1__229__496 < 1); (i__conflict__1__229__496++)) {{
          for ((j__conflict__5__225__492 = 0)/*int*/; (j__conflict__5__225__492 < 64); (j__conflict__5__225__492++)) {{
              for ((k__conflict__8__220__487 = 0)/*int*/; (k__conflict__8__220__487 < 512); (k__conflict__8__220__487++)) {{
                  (__tmp3__219__486 = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp3__219__486)/*int*/;
                }
              }
              for ((k__conflict__7__223__490 = 0)/*int*/; (k__conflict__7__223__490 < 512); (k__conflict__7__223__490++)) {{
                  (__tmp5__222__489 = ((k__conflict__7__223__490 + 65536) - 512))/*int*/;
                  (__tmp4__221__488 = (___POP_BUFFER_1_1[(int)((1 + ___POP_INDEX_1_1) + __tmp5__222__489)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp4__221__488)/*int*/;
                }
              }
              for ((k__conflict__6__224__491 = 0)/*int*/; (k__conflict__6__224__491 < 512); (k__conflict__6__224__491++)) {((tmp__218__485[(int)(id__217__484++)]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              }
            }
          }
          for ((j__conflict__2__228__495 = 0)/*int*/; (j__conflict__2__228__495 < 64); (j__conflict__2__228__495++)) {{
              for ((k__conflict__4__226__493 = 0)/*int*/; (k__conflict__4__226__493 < 512); (k__conflict__4__226__493++)) {(___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
              }
              for ((k__conflict__3__227__494 = 0)/*int*/; (k__conflict__3__227__494 < 512); (k__conflict__3__227__494++)) {((tmp__218__485[(int)(id__217__484++)]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              }
            }
          }
        }
      }
      (id__217__484 = 0)/*int*/;
      for ((k__235__502 = 0)/*int*/; (k__235__502 < 1); (k__235__502++)) {{
          for ((i__234__501 = 0)/*int*/; (i__234__501 < 64); (i__234__501++)) {{
              for ((j__conflict__0__231__498 = 0)/*int*/; (j__conflict__0__231__498 < 512); (j__conflict__0__231__498++)) {{
                  (__tmp6__230__497 = (tmp__218__485[(int)(id__217__484++)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp6__230__497)/*int*/;
                }
              }
              (id__217__484 = (id__217__484 - 512))/*int*/;
              for ((j__233__500 = 0)/*int*/; (j__233__500 < 512); (j__233__500++)) {{
                  (__tmp7__232__499 = (tmp__218__485[(int)((id__217__484++) + 32768)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp7__232__499)/*int*/;
                }
              }
            }
          }
          (id__217__484 = (id__217__484 + 32768))/*int*/;
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 128); (___COUNTER_WORK_1_2++)) {{
          for ((i__conflict__2__242__509 = 0)/*int*/; (i__conflict__2__242__509 < 1024); (i__conflict__2__242__509++)) {((tmp1__239__506[(int)i__conflict__2__242__509]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
          }
          for ((i__conflict__1__243__510 = 0)/*int*/; (i__conflict__1__243__510 < 512); (i__conflict__1__243__510++)) {{
              ((tmp2__240__507[(int)i__conflict__1__243__510]) = (tmp1__239__506[(int)i__conflict__1__243__510]))/*int*/;
              ((tmp2__240__507[(int)(i__conflict__1__243__510 + 512)]) = (tmp1__239__506[(int)(i__conflict__1__243__510 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__244__511 = 0)/*int*/; (i__conflict__0__244__511 < 1024); (i__conflict__0__244__511++)) {((tmp3__241__508[(int)i__conflict__0__244__511]) = (tmp2__240__507[(int)i__conflict__0__244__511]))/*int*/;
          }
          for ((i__245__512 = 0)/*int*/; (i__245__512 < 1024); (i__245__512++)) {((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = (tmp3__241__508[(int)i__245__512]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter MyJoin

      for ((___COUNTER_WORK_1_3 = 0)/*int*/; (___COUNTER_WORK_1_3 < 2); (___COUNTER_WORK_1_3++)) {{
          (id__250__517 = 0)/*int*/;
          for ((i__conflict__0__254__521 = 0)/*int*/; (i__conflict__0__254__521 < 64); (i__conflict__0__254__521++)) {{
              for ((j__conflict__1__252__519 = 0)/*int*/; (j__conflict__1__252__519 < 512); (j__conflict__1__252__519++)) {{
                  (__tmp8__251__518 = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp8__251__518)/*int*/;
                }
              }
              for ((j__253__520 = 0)/*int*/; (j__253__520 < 512); (j__253__520++)) {((tmp__249__516[(int)(id__250__517++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
              }
            }
          }
          for ((i__255__522 = 0)/*int*/; (i__255__522 < 32768); (i__255__522++)) {((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = (tmp__249__516[(int)i__255__522]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter MyJoin

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_4 = 0)/*int*/; (___COUNTER_WORK_1_4 < 131072); (___COUNTER_WORK_1_4++)) {{
          (__tmp9__259__526 = (___POP_BUFFER_4_1[(int)((1 + ___POP_INDEX_1_4) + 0)]))/*int*/;

          // TIMER_PRINT_CODE: __print_sink__ += (int)(__tmp9__259__526); 
          printf( "%d", __tmp9__259__526); printf("\n");

          (___POP_INDEX_1_4 = (___POP_INDEX_1_4 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_3() {
  init__529__3();
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
    for (_tmp = 0; _tmp < 64; _tmp++) {
      //check_status__3();
      if (*__state_flag_3 == EXIT_THREAD) exit_thread(__thread_3);
      __update_pop_buf__3();
      work__528__3(1);
    }
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
