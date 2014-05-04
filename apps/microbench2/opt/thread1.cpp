// peek: 4194304 pop: 4194304 push 4194304
// init counts: 0 steady counts: 2

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
message *__msg_stack_1;
int __number_of_iterations_1;
int __counter_1 = 0;
int __steady_1 = 0;
int __tmp_1 = 0;
int __tmp2_1 = 0;
int *__state_flag_1 = NULL;
thread_info *__thread_1 = NULL;

consumer2<int> __consumer_0_1;
extern int __pop_0_1();
producer2<int> __producer_1_2;
extern void __push_1_2(int);
    // this-part:2 dst-part:3


void save_peek_buffer__1(object_write_buffer *buf);
void load_peek_buffer__1(object_write_buffer *buf);
void save_file_pointer__1(object_write_buffer *buf);
void load_file_pointer__1(object_write_buffer *buf);

void __write_thread__1(object_write_buffer *buf) {
  __consumer_0_1.write_object(buf);
  save_peek_buffer__1(buf);
  save_file_pointer__1(buf);
  __producer_1_2.write_object(buf);
}

void __read_thread__1(object_write_buffer *buf) {
  __consumer_0_1.read_object(buf);
  load_peek_buffer__1(buf);
  load_file_pointer__1(buf);
  __producer_1_2.read_object(buf);
}

inline void check_status__1() {
  check_thread_status(__state_flag_1, __thread_1);
}

void check_status_during_io__1() {
  check_thread_status_during_io(__state_flag_1, __thread_1);
}

void __init_thread_info_1(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(0,1,&__consumer_0_1));
  info->add_outgoing_data_connection(new connection_info(1,2,&__producer_1_2));
  __state_flag_1 = info->get_state_flag();
}

thread_info *__get_thread_info_1() {
  if (__thread_1 != NULL) return __thread_1;
  __thread_1 = new thread_info(1, check_status_during_io__1);
  __init_thread_info_1(__thread_1);
  return __thread_1;
}

void __declare_sockets_1() {
  init_instance::add_incoming(0,1, DATA_SOCKET);
  init_instance::add_outgoing(1,2, DATA_SOCKET);
}

void __init_sockets_1(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(0,1,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_0_1.set_socket(sock);
  __consumer_0_1.init();

  sock = init_instance::get_outgoing_socket(1,2,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __producer_1_2.set_socket(sock);
  __producer_1_2.init();

}

void __flush_sockets_1() {
  __producer_1_2.flush();
  __producer_1_2.get_socket()->close();
  __producer_1_2.delete_socket_obj();
  __consumer_0_1.delete_socket_obj();
}

void __peek_sockets_1() {
  __consumer_0_1.peek(0);
}

 
void init__405__1(); 
void init__56__319__1(); 
void init__78__341__1(); 
void init__88__351__1(); 
void init__110__373__1(); 
void init__120__383__1();
inline void check_status__1();

void work__404__1(int);

// downstreamDeclarationExtern cluster_0_1
// downstreamDeclaration cluster_0_1:
int __pop_buf__1[4194304];
int __head__1;
int __tail__1;

inline void __init_pop_buf__1() {
  __tail__1=0;
  __head__1=0;
}

void save_peek_buffer__1(object_write_buffer *buf) {
  int i = 0, offs = __tail__1;
  while (offs != __head__1) {
    buf->write(&__pop_buf__1[offs], sizeof(int ));
    offs++;
    offs&=4194303;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__1(object_write_buffer *buf) {
  __tail__1=0;
  __head__1=0;
}

inline void __update_pop_buf__1() {
for (int i = 0; i < 4194304; i++) {
  __pop_buf__1[i]=__consumer_0_1.pop();
}
  __tail__1 = 0;
  __head__1 = 4194304;
}


inline int __pop_0_1() {
return __pop_buf__1[__tail__1++];
}

inline void __pop_0_1(int n) {
__tail__1+=n;
return;
}

inline int __peek_0_1(int offs) {
return __pop_buf__1[(__tail__1+offs)];
  }


// upstreamDeclarationExtern cluster_1_2
// upstreamDeclaration cluster_1_2
int __pop_buffer_1_2[10240];
int __pop_index_1_2 = 0;
inline void __push_1_2(int data) {
__producer_1_2.push(data);
}

 
void init__405__1(){
  init__56__319__1();
  init__78__341__1();
  init__88__351__1();
  init__110__373__1();
  init__120__383__1();
}
 
void init__56__319__1(){
}
 
void init__78__341__1(){
}
 
void init__88__351__1(){
}
 
void init__110__373__1(){
}
 
void init__120__383__1(){
}
void save_file_pointer__1(object_write_buffer *buf) {}
void load_file_pointer__1(object_write_buffer *buf) {}
 
void work__404__1(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[4194304] = {0};/* int[4194304] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___COUNTER_WORK_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[4194304] = {0};/* int[4194304] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int ___POP_BUFFER_3_1[4194304] = {0};/* int[4194304] */
      int ___POP_INDEX_1_3 = 0;/* int */
      int ___PUSH_INDEX_1_3 = 0;/* int */
      int ___COUNTER_WORK_1_3 = 0;/* int */
      int ___POP_BUFFER_4_1[4194304] = {0};/* int[4194304] */
      int ___POP_INDEX_1_4 = 0;/* int */
      int ___PUSH_INDEX_1_4 = 0;/* int */
      int ___COUNTER_WORK_1_4 = 0;/* int */
      int id__57__320 = 0;/* int */
      int tmp__58__321[2097152] = {0};/* int[2097152] */
      int __tmp3__59__322 = 0;/* int */
      int k__conflict__8__60__323 = 0;/* int */
      int __tmp4__61__324 = 0;/* int */
      int __tmp5__62__325 = 0;/* int */
      int k__conflict__7__63__326 = 0;/* int */
      int k__conflict__6__64__327 = 0;/* int */
      int j__conflict__5__65__328 = 0;/* int */
      int k__conflict__4__66__329 = 0;/* int */
      int k__conflict__3__67__330 = 0;/* int */
      int j__conflict__2__68__331 = 0;/* int */
      int i__conflict__1__69__332 = 0;/* int */
      int __tmp6__70__333 = 0;/* int */
      int j__conflict__0__71__334 = 0;/* int */
      int __tmp7__72__335 = 0;/* int */
      int j__73__336 = 0;/* int */
      int i__74__337 = 0;/* int */
      int k__75__338 = 0;/* int */
      int tmp1__79__342[1024] = {0};/* int[1024] */
      int tmp2__80__343[1024] = {0};/* int[1024] */
      int tmp3__81__344[1024] = {0};/* int[1024] */
      int i__conflict__2__82__345 = 0;/* int */
      int i__conflict__1__83__346 = 0;/* int */
      int i__conflict__0__84__347 = 0;/* int */
      int i__85__348 = 0;/* int */
      int id__89__352 = 0;/* int */
      int tmp__90__353[1048576] = {0};/* int[1048576] */
      int __tmp3__91__354 = 0;/* int */
      int k__conflict__8__92__355 = 0;/* int */
      int __tmp4__93__356 = 0;/* int */
      int __tmp5__94__357 = 0;/* int */
      int k__conflict__7__95__358 = 0;/* int */
      int k__conflict__6__96__359 = 0;/* int */
      int j__conflict__5__97__360 = 0;/* int */
      int k__conflict__4__98__361 = 0;/* int */
      int k__conflict__3__99__362 = 0;/* int */
      int j__conflict__2__100__363 = 0;/* int */
      int i__conflict__1__101__364 = 0;/* int */
      int __tmp6__102__365 = 0;/* int */
      int j__conflict__0__103__366 = 0;/* int */
      int __tmp7__104__367 = 0;/* int */
      int j__105__368 = 0;/* int */
      int i__106__369 = 0;/* int */
      int k__107__370 = 0;/* int */
      int tmp1__111__374[1024] = {0};/* int[1024] */
      int tmp2__112__375[1024] = {0};/* int[1024] */
      int tmp3__113__376[1024] = {0};/* int[1024] */
      int i__conflict__2__114__377 = 0;/* int */
      int i__conflict__1__115__378 = 0;/* int */
      int i__conflict__0__116__379 = 0;/* int */
      int i__117__380 = 0;/* int */
      int id__121__384 = 0;/* int */
      int tmp__122__385[524288] = {0};/* int[524288] */
      int __tmp3__123__386 = 0;/* int */
      int k__conflict__8__124__387 = 0;/* int */
      int __tmp4__125__388 = 0;/* int */
      int __tmp5__126__389 = 0;/* int */
      int k__conflict__7__127__390 = 0;/* int */
      int k__conflict__6__128__391 = 0;/* int */
      int j__conflict__5__129__392 = 0;/* int */
      int k__conflict__4__130__393 = 0;/* int */
      int k__conflict__3__131__394 = 0;/* int */
      int j__conflict__2__132__395 = 0;/* int */
      int i__conflict__1__133__396 = 0;/* int */
      int __tmp6__134__397 = 0;/* int */
      int j__conflict__0__135__398 = 0;/* int */
      int __tmp7__136__399 = 0;/* int */
      int j__137__400 = 0;/* int */
      int i__138__401 = 0;/* int */
      int k__139__402 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      (___POP_INDEX_1_3 = -1)/*int*/;
      (___PUSH_INDEX_1_3 = -1)/*int*/;
      (___POP_INDEX_1_4 = -1)/*int*/;
      (___PUSH_INDEX_1_4 = -1)/*int*/;
      // mark begin: SIRFilter Fused_MyJoin_MySplit

      (id__57__320 = 0)/*int*/;
      for ((i__conflict__1__69__332 = 0)/*int*/; (i__conflict__1__69__332 < 1); (i__conflict__1__69__332++)) {{
          for ((j__conflict__5__65__328 = 0)/*int*/; (j__conflict__5__65__328 < 2048); (j__conflict__5__65__328++)) {{
              for ((k__conflict__8__60__323 = 0)/*int*/; (k__conflict__8__60__323 < 512); (k__conflict__8__60__323++)) {{
                  __tmp3__59__322 = __pop_0_1();
;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp3__59__322)/*int*/;
                }
              }
              for ((k__conflict__7__63__326 = 0)/*int*/; (k__conflict__7__63__326 < 512); (k__conflict__7__63__326++)) {{
                  (__tmp5__62__325 = ((k__conflict__7__63__326 + 2097152) - 512))/*int*/;
                  __tmp4__61__324 = __peek_0_1(__tmp5__62__325);
;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp4__61__324)/*int*/;
                }
              }
              for ((k__conflict__6__64__327 = 0)/*int*/; (k__conflict__6__64__327 < 512); (k__conflict__6__64__327++)) {(tmp__58__321[(int)(id__57__320++)]) = __pop_0_1();
;
              }
            }
          }
          for ((j__conflict__2__68__331 = 0)/*int*/; (j__conflict__2__68__331 < 2048); (j__conflict__2__68__331++)) {{
              for ((k__conflict__4__66__329 = 0)/*int*/; (k__conflict__4__66__329 < 512); (k__conflict__4__66__329++)) {__pop_0_1();
              }
              for ((k__conflict__3__67__330 = 0)/*int*/; (k__conflict__3__67__330 < 512); (k__conflict__3__67__330++)) {(tmp__58__321[(int)(id__57__320++)]) = __pop_0_1();
;
              }
            }
          }
        }
      }
      (id__57__320 = 0)/*int*/;
      for ((k__75__338 = 0)/*int*/; (k__75__338 < 1); (k__75__338++)) {{
          for ((i__74__337 = 0)/*int*/; (i__74__337 < 2048); (i__74__337++)) {{
              for ((j__conflict__0__71__334 = 0)/*int*/; (j__conflict__0__71__334 < 512); (j__conflict__0__71__334++)) {{
                  (__tmp6__70__333 = (tmp__58__321[(int)(id__57__320++)]))/*int*/;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp6__70__333)/*int*/;
                }
              }
              (id__57__320 = (id__57__320 - 512))/*int*/;
              for ((j__73__336 = 0)/*int*/; (j__73__336 < 512); (j__73__336++)) {{
                  (__tmp7__72__335 = (tmp__58__321[(int)((id__57__320++) + 1048576)]))/*int*/;
                  ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp7__72__335)/*int*/;
                }
              }
            }
          }
          (id__57__320 = (id__57__320 + 1048576))/*int*/;
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_1 = 0)/*int*/; (___COUNTER_WORK_1_1 < 4096); (___COUNTER_WORK_1_1++)) {{
          for ((i__conflict__2__82__345 = 0)/*int*/; (i__conflict__2__82__345 < 1024); (i__conflict__2__82__345++)) {((tmp1__79__342[(int)i__conflict__2__82__345]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
          }
          for ((i__conflict__1__83__346 = 0)/*int*/; (i__conflict__1__83__346 < 512); (i__conflict__1__83__346++)) {{
              ((tmp2__80__343[(int)i__conflict__1__83__346]) = (tmp1__79__342[(int)i__conflict__1__83__346]))/*int*/;
              ((tmp2__80__343[(int)(i__conflict__1__83__346 + 512)]) = (tmp1__79__342[(int)(i__conflict__1__83__346 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__84__347 = 0)/*int*/; (i__conflict__0__84__347 < 1024); (i__conflict__0__84__347++)) {((tmp3__81__344[(int)i__conflict__0__84__347]) = (tmp2__80__343[(int)i__conflict__0__84__347]))/*int*/;
          }
          for ((i__85__348 = 0)/*int*/; (i__85__348 < 1024); (i__85__348++)) {((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = (tmp3__81__344[(int)i__85__348]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 2); (___COUNTER_WORK_1_2++)) {{
          (id__89__352 = 0)/*int*/;
          for ((i__conflict__1__101__364 = 0)/*int*/; (i__conflict__1__101__364 < 1); (i__conflict__1__101__364++)) {{
              for ((j__conflict__5__97__360 = 0)/*int*/; (j__conflict__5__97__360 < 1024); (j__conflict__5__97__360++)) {{
                  for ((k__conflict__8__92__355 = 0)/*int*/; (k__conflict__8__92__355 < 512); (k__conflict__8__92__355++)) {{
                      (__tmp3__91__354 = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
                      ((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = __tmp3__91__354)/*int*/;
                    }
                  }
                  for ((k__conflict__7__95__358 = 0)/*int*/; (k__conflict__7__95__358 < 512); (k__conflict__7__95__358++)) {{
                      (__tmp5__94__357 = ((k__conflict__7__95__358 + 1048576) - 512))/*int*/;
                      (__tmp4__93__356 = (___POP_BUFFER_2_1[(int)((1 + ___POP_INDEX_1_2) + __tmp5__94__357)]))/*int*/;
                      ((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = __tmp4__93__356)/*int*/;
                    }
                  }
                  for ((k__conflict__6__96__359 = 0)/*int*/; (k__conflict__6__96__359 < 512); (k__conflict__6__96__359++)) {((tmp__90__353[(int)(id__89__352++)]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
                  }
                }
              }
              for ((j__conflict__2__100__363 = 0)/*int*/; (j__conflict__2__100__363 < 1024); (j__conflict__2__100__363++)) {{
                  for ((k__conflict__4__98__361 = 0)/*int*/; (k__conflict__4__98__361 < 512); (k__conflict__4__98__361++)) {(___POP_INDEX_1_2 = (___POP_INDEX_1_2 + 1))/*int*/;
                  }
                  for ((k__conflict__3__99__362 = 0)/*int*/; (k__conflict__3__99__362 < 512); (k__conflict__3__99__362++)) {((tmp__90__353[(int)(id__89__352++)]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
                  }
                }
              }
            }
          }
          (id__89__352 = 0)/*int*/;
          for ((k__107__370 = 0)/*int*/; (k__107__370 < 1); (k__107__370++)) {{
              for ((i__106__369 = 0)/*int*/; (i__106__369 < 1024); (i__106__369++)) {{
                  for ((j__conflict__0__103__366 = 0)/*int*/; (j__conflict__0__103__366 < 512); (j__conflict__0__103__366++)) {{
                      (__tmp6__102__365 = (tmp__90__353[(int)(id__89__352++)]))/*int*/;
                      ((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = __tmp6__102__365)/*int*/;
                    }
                  }
                  (id__89__352 = (id__89__352 - 512))/*int*/;
                  for ((j__105__368 = 0)/*int*/; (j__105__368 < 512); (j__105__368++)) {{
                      (__tmp7__104__367 = (tmp__90__353[(int)((id__89__352++) + 524288)]))/*int*/;
                      ((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = __tmp7__104__367)/*int*/;
                    }
                  }
                }
              }
              (id__89__352 = (id__89__352 + 524288))/*int*/;
            }
          }
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_3 = 0)/*int*/; (___COUNTER_WORK_1_3 < 4096); (___COUNTER_WORK_1_3++)) {{
          for ((i__conflict__2__114__377 = 0)/*int*/; (i__conflict__2__114__377 < 1024); (i__conflict__2__114__377++)) {((tmp1__111__374[(int)i__conflict__2__114__377]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
          }
          for ((i__conflict__1__115__378 = 0)/*int*/; (i__conflict__1__115__378 < 512); (i__conflict__1__115__378++)) {{
              ((tmp2__112__375[(int)i__conflict__1__115__378]) = (tmp1__111__374[(int)i__conflict__1__115__378]))/*int*/;
              ((tmp2__112__375[(int)(i__conflict__1__115__378 + 512)]) = (tmp1__111__374[(int)(i__conflict__1__115__378 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__116__379 = 0)/*int*/; (i__conflict__0__116__379 < 1024); (i__conflict__0__116__379++)) {((tmp3__113__376[(int)i__conflict__0__116__379]) = (tmp2__112__375[(int)i__conflict__0__116__379]))/*int*/;
          }
          for ((i__117__380 = 0)/*int*/; (i__117__380 < 1024); (i__117__380++)) {((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = (tmp3__113__376[(int)i__117__380]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      for ((___COUNTER_WORK_1_4 = 0)/*int*/; (___COUNTER_WORK_1_4 < 4); (___COUNTER_WORK_1_4++)) {{
          (id__121__384 = 0)/*int*/;
          for ((i__conflict__1__133__396 = 0)/*int*/; (i__conflict__1__133__396 < 1); (i__conflict__1__133__396++)) {{
              for ((j__conflict__5__129__392 = 0)/*int*/; (j__conflict__5__129__392 < 512); (j__conflict__5__129__392++)) {{
                  for ((k__conflict__8__124__387 = 0)/*int*/; (k__conflict__8__124__387 < 512); (k__conflict__8__124__387++)) {{
                      (__tmp3__123__386 = (___POP_BUFFER_4_1[(int)(++___POP_INDEX_1_4)]))/*int*/;
                      __push_1_2(__tmp3__123__386);
                    }
                  }
                  for ((k__conflict__7__127__390 = 0)/*int*/; (k__conflict__7__127__390 < 512); (k__conflict__7__127__390++)) {{
                      (__tmp5__126__389 = ((k__conflict__7__127__390 + 524288) - 512))/*int*/;
                      (__tmp4__125__388 = (___POP_BUFFER_4_1[(int)((1 + ___POP_INDEX_1_4) + __tmp5__126__389)]))/*int*/;
                      __push_1_2(__tmp4__125__388);
                    }
                  }
                  for ((k__conflict__6__128__391 = 0)/*int*/; (k__conflict__6__128__391 < 512); (k__conflict__6__128__391++)) {((tmp__122__385[(int)(id__121__384++)]) = (___POP_BUFFER_4_1[(int)(++___POP_INDEX_1_4)]))/*int*/;
                  }
                }
              }
              for ((j__conflict__2__132__395 = 0)/*int*/; (j__conflict__2__132__395 < 512); (j__conflict__2__132__395++)) {{
                  for ((k__conflict__4__130__393 = 0)/*int*/; (k__conflict__4__130__393 < 512); (k__conflict__4__130__393++)) {(___POP_INDEX_1_4 = (___POP_INDEX_1_4 + 1))/*int*/;
                  }
                  for ((k__conflict__3__131__394 = 0)/*int*/; (k__conflict__3__131__394 < 512); (k__conflict__3__131__394++)) {((tmp__122__385[(int)(id__121__384++)]) = (___POP_BUFFER_4_1[(int)(++___POP_INDEX_1_4)]))/*int*/;
                  }
                }
              }
            }
          }
          (id__121__384 = 0)/*int*/;
          for ((k__139__402 = 0)/*int*/; (k__139__402 < 1); (k__139__402++)) {{
              for ((i__138__401 = 0)/*int*/; (i__138__401 < 512); (i__138__401++)) {{
                  for ((j__conflict__0__135__398 = 0)/*int*/; (j__conflict__0__135__398 < 512); (j__conflict__0__135__398++)) {{
                      (__tmp6__134__397 = (tmp__122__385[(int)(id__121__384++)]))/*int*/;
                      __push_1_2(__tmp6__134__397);
                    }
                  }
                  (id__121__384 = (id__121__384 - 512))/*int*/;
                  for ((j__137__400 = 0)/*int*/; (j__137__400 < 512); (j__137__400++)) {{
                      (__tmp7__136__399 = (tmp__122__385[(int)((id__121__384++) + 262144)]))/*int*/;
                      __push_1_2(__tmp7__136__399);
                    }
                  }
                }
              }
              (id__121__384 = (id__121__384 + 262144))/*int*/;
            }
          }
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

    }
  }
}

void __init_state_1() {
  init__405__1();
  if (save_state::load_state(1, &__steady_1, __read_thread__1) == -1) pthread_exit(NULL);
}

static void __main__1() {
  int _tmp; // modified
  int _steady = __steady_1;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__1();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
    for (_tmp = 0; _tmp < 2; _tmp++) {
      //check_status__1();
      if (*__state_flag_1 == EXIT_THREAD) exit_thread(__thread_1);
      __update_pop_buf__1();
      work__404__1(1);
    }
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_1, _steady, __write_thread__1);
#endif // __CHECKPOINT_FREQ
  }
}

void run_1() {
  __init_sockets_1(check_status_during_io__1);
  __init_state_1();

  timer t1;
  __peek_sockets_1();
  t1.start();
  __main__1();
  t1.stop();
  if (__timer_enabled) t1.output(stderr);

  __flush_sockets_1();
  pthread_exit(NULL);
}
