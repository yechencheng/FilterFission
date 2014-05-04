// peek: 524288 pop: 524288 push 524288
// init counts: 0 steady counts: 16

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

 
void init__471__2(); 
void init__142__407__2(); 
void init__152__417__2(); 
void init__174__439__2(); 
void init__184__449__2();
inline void check_status__2();

void work__470__2(int);

// downstreamDeclarationExtern cluster_1_2
// downstreamDeclaration cluster_1_2:
int __pop_buf__2[524288];
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
    offs&=524287;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__2(object_write_buffer *buf) {
  __tail__2=0;
  __head__2=0;
}

inline void __update_pop_buf__2() {
for (int i = 0; i < 524288; i++) {
  __pop_buf__2[i]=__consumer_1_2.pop();
}
  __tail__2 = 0;
  __head__2 = 524288;
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
int __pop_index_2_3 = 0;
inline void __push_2_3(int data) {
__producer_2_3.push(data);
}

 
void init__471__2(){
  init__142__407__2();
  init__152__417__2();
  init__174__439__2();
  init__184__449__2();
}
 
void init__142__407__2(){
}
 
void init__152__417__2(){
}
 
void init__174__439__2(){
}
 
void init__184__449__2(){
}
void save_file_pointer__2(object_write_buffer *buf) {}
void load_file_pointer__2(object_write_buffer *buf) {}
 
void work__470__2(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___COUNTER_WORK_1_0 = 0;/* int */
      int ___POP_BUFFER_1_1[524288] = {0};/* int[524288] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[524288] = {0};/* int[524288] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int ___POP_BUFFER_3_1[524288] = {0};/* int[524288] */
      int ___POP_INDEX_1_3 = 0;/* int */
      int ___PUSH_INDEX_1_3 = 0;/* int */
      int ___COUNTER_WORK_1_3 = 0;/* int */
      int tmp1__143__408[1024] = {0};/* int[1024] */
      int tmp2__144__409[1024] = {0};/* int[1024] */
      int tmp3__145__410[1024] = {0};/* int[1024] */
      int i__conflict__2__146__411 = 0;/* int */
      int i__conflict__1__147__412 = 0;/* int */
      int i__conflict__0__148__413 = 0;/* int */
      int i__149__414 = 0;/* int */
      int id__153__418 = 0;/* int */
      int tmp__154__419[262144] = {0};/* int[262144] */
      int __tmp3__155__420 = 0;/* int */
      int k__conflict__8__156__421 = 0;/* int */
      int __tmp4__157__422 = 0;/* int */
      int __tmp5__158__423 = 0;/* int */
      int k__conflict__7__159__424 = 0;/* int */
      int k__conflict__6__160__425 = 0;/* int */
      int j__conflict__5__161__426 = 0;/* int */
      int k__conflict__4__162__427 = 0;/* int */
      int k__conflict__3__163__428 = 0;/* int */
      int j__conflict__2__164__429 = 0;/* int */
      int i__conflict__1__165__430 = 0;/* int */
      int __tmp6__166__431 = 0;/* int */
      int j__conflict__0__167__432 = 0;/* int */
      int __tmp7__168__433 = 0;/* int */
      int j__169__434 = 0;/* int */
      int i__170__435 = 0;/* int */
      int k__171__436 = 0;/* int */
      int tmp1__175__440[1024] = {0};/* int[1024] */
      int tmp2__176__441[1024] = {0};/* int[1024] */
      int tmp3__177__442[1024] = {0};/* int[1024] */
      int i__conflict__2__178__443 = 0;/* int */
      int i__conflict__1__179__444 = 0;/* int */
      int i__conflict__0__180__445 = 0;/* int */
      int i__181__446 = 0;/* int */
      int id__185__450 = 0;/* int */
      int tmp__186__451[131072] = {0};/* int[131072] */
      int __tmp3__187__452 = 0;/* int */
      int k__conflict__8__188__453 = 0;/* int */
      int __tmp4__189__454 = 0;/* int */
      int __tmp5__190__455 = 0;/* int */
      int k__conflict__7__191__456 = 0;/* int */
      int k__conflict__6__192__457 = 0;/* int */
      int j__conflict__5__193__458 = 0;/* int */
      int k__conflict__4__194__459 = 0;/* int */
      int k__conflict__3__195__460 = 0;/* int */
      int j__conflict__2__196__461 = 0;/* int */
      int i__conflict__1__197__462 = 0;/* int */
      int __tmp6__198__463 = 0;/* int */
      int j__conflict__0__199__464 = 0;/* int */
      int __tmp7__200__465 = 0;/* int */
      int j__201__466 = 0;/* int */
      int i__202__467 = 0;/* int */
      int k__203__468 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      (___POP_INDEX_1_3 = -1)/*int*/;
      (___PUSH_INDEX_1_3 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_0 = 0)/*int*/; (___COUNTER_WORK_1_0 < 512); (___COUNTER_WORK_1_0++)) {{
          for ((i__conflict__2__146__411 = 0)/*int*/; (i__conflict__2__146__411 < 1024); (i__conflict__2__146__411++)) {(tmp1__143__408[(int)i__conflict__2__146__411]) = __pop_1_2();
;
          }
          for ((i__conflict__1__147__412 = 0)/*int*/; (i__conflict__1__147__412 < 512); (i__conflict__1__147__412++)) {{
              ((tmp2__144__409[(int)i__conflict__1__147__412]) = (tmp1__143__408[(int)i__conflict__1__147__412]))/*int*/;
              ((tmp2__144__409[(int)(i__conflict__1__147__412 + 512)]) = (tmp1__143__408[(int)(i__conflict__1__147__412 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__148__413 = 0)/*int*/; (i__conflict__0__148__413 < 1024); (i__conflict__0__148__413++)) {((tmp3__145__410[(int)i__conflict__0__148__413]) = (tmp2__144__409[(int)i__conflict__0__148__413]))/*int*/;
          }
          for ((i__149__414 = 0)/*int*/; (i__149__414 < 1024); (i__149__414++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__145__410[(int)i__149__414]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      (id__153__418 = 0)/*int*/;
      for ((i__conflict__1__165__430 = 0)/*int*/; (i__conflict__1__165__430 < 1); (i__conflict__1__165__430++)) {{
          for ((j__conflict__5__161__426 = 0)/*int*/; (j__conflict__5__161__426 < 256); (j__conflict__5__161__426++)) {{
              for ((k__conflict__8__156__421 = 0)/*int*/; (k__conflict__8__156__421 < 512); (k__conflict__8__156__421++)) {{
                  (__tmp3__155__420 = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp3__155__420)/*int*/;
                }
              }
              for ((k__conflict__7__159__424 = 0)/*int*/; (k__conflict__7__159__424 < 512); (k__conflict__7__159__424++)) {{
                  (__tmp5__158__423 = ((k__conflict__7__159__424 + 262144) - 512))/*int*/;
                  (__tmp4__157__422 = (___POP_BUFFER_1_1[(int)((1 + ___POP_INDEX_1_1) + __tmp5__158__423)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp4__157__422)/*int*/;
                }
              }
              for ((k__conflict__6__160__425 = 0)/*int*/; (k__conflict__6__160__425 < 512); (k__conflict__6__160__425++)) {((tmp__154__419[(int)(id__153__418++)]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              }
            }
          }
          for ((j__conflict__2__164__429 = 0)/*int*/; (j__conflict__2__164__429 < 256); (j__conflict__2__164__429++)) {{
              for ((k__conflict__4__162__427 = 0)/*int*/; (k__conflict__4__162__427 < 512); (k__conflict__4__162__427++)) {(___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
              }
              for ((k__conflict__3__163__428 = 0)/*int*/; (k__conflict__3__163__428 < 512); (k__conflict__3__163__428++)) {((tmp__154__419[(int)(id__153__418++)]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              }
            }
          }
        }
      }
      (id__153__418 = 0)/*int*/;
      for ((k__171__436 = 0)/*int*/; (k__171__436 < 1); (k__171__436++)) {{
          for ((i__170__435 = 0)/*int*/; (i__170__435 < 256); (i__170__435++)) {{
              for ((j__conflict__0__167__432 = 0)/*int*/; (j__conflict__0__167__432 < 512); (j__conflict__0__167__432++)) {{
                  (__tmp6__166__431 = (tmp__154__419[(int)(id__153__418++)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp6__166__431)/*int*/;
                }
              }
              (id__153__418 = (id__153__418 - 512))/*int*/;
              for ((j__169__434 = 0)/*int*/; (j__169__434 < 512); (j__169__434++)) {{
                  (__tmp7__168__433 = (tmp__154__419[(int)((id__153__418++) + 131072)]))/*int*/;
                  ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp7__168__433)/*int*/;
                }
              }
            }
          }
          (id__153__418 = (id__153__418 + 131072))/*int*/;
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 512); (___COUNTER_WORK_1_2++)) {{
          for ((i__conflict__2__178__443 = 0)/*int*/; (i__conflict__2__178__443 < 1024); (i__conflict__2__178__443++)) {((tmp1__175__440[(int)i__conflict__2__178__443]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
          }
          for ((i__conflict__1__179__444 = 0)/*int*/; (i__conflict__1__179__444 < 512); (i__conflict__1__179__444++)) {{
              ((tmp2__176__441[(int)i__conflict__1__179__444]) = (tmp1__175__440[(int)i__conflict__1__179__444]))/*int*/;
              ((tmp2__176__441[(int)(i__conflict__1__179__444 + 512)]) = (tmp1__175__440[(int)(i__conflict__1__179__444 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__180__445 = 0)/*int*/; (i__conflict__0__180__445 < 1024); (i__conflict__0__180__445++)) {((tmp3__177__442[(int)i__conflict__0__180__445]) = (tmp2__176__441[(int)i__conflict__0__180__445]))/*int*/;
          }
          for ((i__181__446 = 0)/*int*/; (i__181__446 < 1024); (i__181__446++)) {((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = (tmp3__177__442[(int)i__181__446]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      for ((___COUNTER_WORK_1_3 = 0)/*int*/; (___COUNTER_WORK_1_3 < 2); (___COUNTER_WORK_1_3++)) {{
          (id__185__450 = 0)/*int*/;
          for ((i__conflict__1__197__462 = 0)/*int*/; (i__conflict__1__197__462 < 1); (i__conflict__1__197__462++)) {{
              for ((j__conflict__5__193__458 = 0)/*int*/; (j__conflict__5__193__458 < 128); (j__conflict__5__193__458++)) {{
                  for ((k__conflict__8__188__453 = 0)/*int*/; (k__conflict__8__188__453 < 512); (k__conflict__8__188__453++)) {{
                      (__tmp3__187__452 = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                      __push_2_3(__tmp3__187__452);
                    }
                  }
                  for ((k__conflict__7__191__456 = 0)/*int*/; (k__conflict__7__191__456 < 512); (k__conflict__7__191__456++)) {{
                      (__tmp5__190__455 = ((k__conflict__7__191__456 + 131072) - 512))/*int*/;
                      (__tmp4__189__454 = (___POP_BUFFER_3_1[(int)((1 + ___POP_INDEX_1_3) + __tmp5__190__455)]))/*int*/;
                      __push_2_3(__tmp4__189__454);
                    }
                  }
                  for ((k__conflict__6__192__457 = 0)/*int*/; (k__conflict__6__192__457 < 512); (k__conflict__6__192__457++)) {((tmp__186__451[(int)(id__185__450++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                  }
                }
              }
              for ((j__conflict__2__196__461 = 0)/*int*/; (j__conflict__2__196__461 < 128); (j__conflict__2__196__461++)) {{
                  for ((k__conflict__4__194__459 = 0)/*int*/; (k__conflict__4__194__459 < 512); (k__conflict__4__194__459++)) {(___POP_INDEX_1_3 = (___POP_INDEX_1_3 + 1))/*int*/;
                  }
                  for ((k__conflict__3__195__460 = 0)/*int*/; (k__conflict__3__195__460 < 512); (k__conflict__3__195__460++)) {((tmp__186__451[(int)(id__185__450++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                  }
                }
              }
            }
          }
          (id__185__450 = 0)/*int*/;
          for ((k__203__468 = 0)/*int*/; (k__203__468 < 1); (k__203__468++)) {{
              for ((i__202__467 = 0)/*int*/; (i__202__467 < 128); (i__202__467++)) {{
                  for ((j__conflict__0__199__464 = 0)/*int*/; (j__conflict__0__199__464 < 512); (j__conflict__0__199__464++)) {{
                      (__tmp6__198__463 = (tmp__186__451[(int)(id__185__450++)]))/*int*/;
                      __push_2_3(__tmp6__198__463);
                    }
                  }
                  (id__185__450 = (id__185__450 - 512))/*int*/;
                  for ((j__201__466 = 0)/*int*/; (j__201__466 < 512); (j__201__466++)) {{
                      (__tmp7__200__465 = (tmp__186__451[(int)((id__185__450++) + 65536)]))/*int*/;
                      __push_2_3(__tmp7__200__465);
                    }
                  }
                }
              }
              (id__185__450 = (id__185__450 + 65536))/*int*/;
            }
          }
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

    }
  }
}

void __init_state_2() {
  init__471__2();
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
    for (_tmp = 0; _tmp < 16; _tmp++) {
      //check_status__2();
      if (*__state_flag_2 == EXIT_THREAD) exit_thread(__thread_2);
      __update_pop_buf__2();
      work__470__2(1);
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
