// peek: 0 pop: 0 push 8388608
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
message *__msg_stack_0;
int __number_of_iterations_0;
int __counter_0 = 0;
int __steady_0 = 0;
int __tmp_0 = 0;
int __tmp2_0 = 0;
int *__state_flag_0 = NULL;
thread_info *__thread_0 = NULL;

producer2<int> __producer_0_1;
extern void __push_0_1(int);
    // this-part:1 dst-part:2


void save_file_pointer__0(object_write_buffer *buf);
void load_file_pointer__0(object_write_buffer *buf);

void __write_thread__0(object_write_buffer *buf) {
  save_file_pointer__0(buf);
  __producer_0_1.write_object(buf);
}

void __read_thread__0(object_write_buffer *buf) {
  load_file_pointer__0(buf);
  __producer_0_1.read_object(buf);
}

inline void check_status__0() {
  check_thread_status(__state_flag_0, __thread_0);
}

void check_status_during_io__0() {
  check_thread_status_during_io(__state_flag_0, __thread_0);
}

void __init_thread_info_0(thread_info *info) {
  info->add_outgoing_data_connection(new connection_info(0,1,&__producer_0_1));
  __state_flag_0 = info->get_state_flag();
}

thread_info *__get_thread_info_0() {
  if (__thread_0 != NULL) return __thread_0;
  __thread_0 = new thread_info(0, check_status_during_io__0);
  __init_thread_info_0(__thread_0);
  return __thread_0;
}

void __declare_sockets_0() {
  init_instance::add_outgoing(0,1, DATA_SOCKET);
}

void __init_sockets_0(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_outgoing_socket(0,1,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __producer_0_1.set_socket(sock);
  __producer_0_1.init();

}

void __flush_sockets_0() {
  __producer_0_1.flush();
  __producer_0_1.get_socket()->close();
  __producer_0_1.delete_socket_obj();
}

void __peek_sockets_0() {
}

 
void init__317__0(); 
void init__1__262__0(); 
void init__5__266__0(); 
void init__14__275__0(); 
void init__24__285__0(); 
void init__46__307__0();
inline void check_status__0();

void work__316__0(int);

// upstreamDeclarationExtern cluster_0_1
// upstreamDeclaration cluster_0_1
int __pop_buffer_0_1[10240];
int __pop_index_0_1 = 0;
inline void __push_0_1(int data) {
__producer_0_1.push(data);
}

 
void init__317__0(){
  init__1__262__0();
  init__5__266__0();
  init__14__275__0();
  init__24__285__0();
  init__46__307__0();
}
 
void init__1__262__0(){
}
 
void init__5__266__0(){
}
 
void init__14__275__0(){
}
 
void init__24__285__0(){
}
 
void init__46__307__0(){
}
void save_file_pointer__0(object_write_buffer *buf) {}
void load_file_pointer__0(object_write_buffer *buf) {}
 
void work__316__0(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int ___COUNTER_WORK_1_2 = 0;/* int */
      int ___POP_BUFFER_3_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_3 = 0;/* int */
      int ___PUSH_INDEX_1_3 = 0;/* int */
      int ___POP_BUFFER_4_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_4 = 0;/* int */
      int ___PUSH_INDEX_1_4 = 0;/* int */
      int ___COUNTER_WORK_1_4 = 0;/* int */
      int i__2__263 = 0;/* int */
      int tmp__6__267[512] = {0};/* int[512] */
      int __tmp2__7__268 = 0;/* int */
      int j__conflict__1__8__269 = 0;/* int */
      int j__9__270 = 0;/* int */
      int i__conflict__0__10__271 = 0;/* int */
      int i__11__272 = 0;/* int */
      int tmp1__15__276[1024] = {0};/* int[1024] */
      int tmp2__16__277[1024] = {0};/* int[1024] */
      int tmp3__17__278[1024] = {0};/* int[1024] */
      int i__conflict__2__18__279 = 0;/* int */
      int i__conflict__1__19__280 = 0;/* int */
      int i__conflict__0__20__281 = 0;/* int */
      int i__21__282 = 0;/* int */
      int id__25__286 = 0;/* int */
      int tmp__26__287[4194304] = {0};/* int[4194304] */
      int __tmp3__27__288 = 0;/* int */
      int k__conflict__8__28__289 = 0;/* int */
      int __tmp4__29__290 = 0;/* int */
      int __tmp5__30__291 = 0;/* int */
      int k__conflict__7__31__292 = 0;/* int */
      int k__conflict__6__32__293 = 0;/* int */
      int j__conflict__5__33__294 = 0;/* int */
      int k__conflict__4__34__295 = 0;/* int */
      int k__conflict__3__35__296 = 0;/* int */
      int j__conflict__2__36__297 = 0;/* int */
      int i__conflict__1__37__298 = 0;/* int */
      int __tmp6__38__299 = 0;/* int */
      int j__conflict__0__39__300 = 0;/* int */
      int __tmp7__40__301 = 0;/* int */
      int j__41__302 = 0;/* int */
      int i__42__303 = 0;/* int */
      int k__43__304 = 0;/* int */
      int tmp1__47__308[1024] = {0};/* int[1024] */
      int tmp2__48__309[1024] = {0};/* int[1024] */
      int tmp3__49__310[1024] = {0};/* int[1024] */
      int i__conflict__2__50__311 = 0;/* int */
      int i__conflict__1__51__312 = 0;/* int */
      int i__conflict__0__52__313 = 0;/* int */
      int i__53__314 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      (___POP_INDEX_1_3 = -1)/*int*/;
      (___PUSH_INDEX_1_3 = -1)/*int*/;
      (___POP_INDEX_1_4 = -1)/*int*/;
      (___PUSH_INDEX_1_4 = -1)/*int*/;
      // mark begin: SIRFilter source

      for ((i__2__263 = 0)/*int*/; (i__2__263 < 8388608); (i__2__263++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = i__2__263)/*int*/;
      }
      // mark end: SIRFilter source

      // mark begin: SIRFilter MySplit

      for ((i__conflict__0__10__271 = 0)/*int*/; (i__conflict__0__10__271 < 8192); (i__conflict__0__10__271++)) {{
          for ((j__conflict__1__8__269 = 0)/*int*/; (j__conflict__1__8__269 < 512); (j__conflict__1__8__269++)) {{
              ((tmp__6__267[(int)j__conflict__1__8__269]) = (___POP_BUFFER_1_1[(int)((1 + ___POP_INDEX_1_1) + 4194304)]))/*int*/;
              (__tmp2__7__268 = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
              ((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = __tmp2__7__268)/*int*/;
            }
          }
          for ((j__9__270 = 0)/*int*/; (j__9__270 < 512); (j__9__270++)) {((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = (tmp__6__267[(int)j__9__270]))/*int*/;
          }
        }
      }
      for ((i__11__272 = 0)/*int*/; (i__11__272 < 4194304); (i__11__272++)) {(___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
      }
      // mark end: SIRFilter MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_2 = 0)/*int*/; (___COUNTER_WORK_1_2 < 8192); (___COUNTER_WORK_1_2++)) {{
          for ((i__conflict__2__18__279 = 0)/*int*/; (i__conflict__2__18__279 < 1024); (i__conflict__2__18__279++)) {((tmp1__15__276[(int)i__conflict__2__18__279]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
          }
          for ((i__conflict__1__19__280 = 0)/*int*/; (i__conflict__1__19__280 < 512); (i__conflict__1__19__280++)) {{
              ((tmp2__16__277[(int)i__conflict__1__19__280]) = (tmp1__15__276[(int)i__conflict__1__19__280]))/*int*/;
              ((tmp2__16__277[(int)(i__conflict__1__19__280 + 512)]) = (tmp1__15__276[(int)(i__conflict__1__19__280 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__20__281 = 0)/*int*/; (i__conflict__0__20__281 < 1024); (i__conflict__0__20__281++)) {((tmp3__17__278[(int)i__conflict__0__20__281]) = (tmp2__16__277[(int)i__conflict__0__20__281]))/*int*/;
          }
          for ((i__21__282 = 0)/*int*/; (i__21__282 < 1024); (i__21__282++)) {((___POP_BUFFER_3_1[(int)(++___PUSH_INDEX_1_3)]) = (tmp3__17__278[(int)i__21__282]))/*int*/;
          }
        }
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter Fused_MyJoin_MySplit

      (id__25__286 = 0)/*int*/;
      for ((i__conflict__1__37__298 = 0)/*int*/; (i__conflict__1__37__298 < 1); (i__conflict__1__37__298++)) {{
          for ((j__conflict__5__33__294 = 0)/*int*/; (j__conflict__5__33__294 < 4096); (j__conflict__5__33__294++)) {{
              for ((k__conflict__8__28__289 = 0)/*int*/; (k__conflict__8__28__289 < 512); (k__conflict__8__28__289++)) {{
                  (__tmp3__27__288 = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp3__27__288)/*int*/;
                }
              }
              for ((k__conflict__7__31__292 = 0)/*int*/; (k__conflict__7__31__292 < 512); (k__conflict__7__31__292++)) {{
                  (__tmp5__30__291 = ((k__conflict__7__31__292 + 4194304) - 512))/*int*/;
                  (__tmp4__29__290 = (___POP_BUFFER_3_1[(int)((1 + ___POP_INDEX_1_3) + __tmp5__30__291)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp4__29__290)/*int*/;
                }
              }
              for ((k__conflict__6__32__293 = 0)/*int*/; (k__conflict__6__32__293 < 512); (k__conflict__6__32__293++)) {((tmp__26__287[(int)(id__25__286++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
              }
            }
          }
          for ((j__conflict__2__36__297 = 0)/*int*/; (j__conflict__2__36__297 < 4096); (j__conflict__2__36__297++)) {{
              for ((k__conflict__4__34__295 = 0)/*int*/; (k__conflict__4__34__295 < 512); (k__conflict__4__34__295++)) {(___POP_INDEX_1_3 = (___POP_INDEX_1_3 + 1))/*int*/;
              }
              for ((k__conflict__3__35__296 = 0)/*int*/; (k__conflict__3__35__296 < 512); (k__conflict__3__35__296++)) {((tmp__26__287[(int)(id__25__286++)]) = (___POP_BUFFER_3_1[(int)(++___POP_INDEX_1_3)]))/*int*/;
              }
            }
          }
        }
      }
      (id__25__286 = 0)/*int*/;
      for ((k__43__304 = 0)/*int*/; (k__43__304 < 1); (k__43__304++)) {{
          for ((i__42__303 = 0)/*int*/; (i__42__303 < 4096); (i__42__303++)) {{
              for ((j__conflict__0__39__300 = 0)/*int*/; (j__conflict__0__39__300 < 512); (j__conflict__0__39__300++)) {{
                  (__tmp6__38__299 = (tmp__26__287[(int)(id__25__286++)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp6__38__299)/*int*/;
                }
              }
              (id__25__286 = (id__25__286 - 512))/*int*/;
              for ((j__41__302 = 0)/*int*/; (j__41__302 < 512); (j__41__302++)) {{
                  (__tmp7__40__301 = (tmp__26__287[(int)((id__25__286++) + 2097152)]))/*int*/;
                  ((___POP_BUFFER_4_1[(int)(++___PUSH_INDEX_1_4)]) = __tmp7__40__301)/*int*/;
                }
              }
            }
          }
          (id__25__286 = (id__25__286 + 2097152))/*int*/;
        }
      }
      // mark end: SIRFilter Fused_MyJoin_MySplit

      // mark begin: SIRFilter process1

      for ((___COUNTER_WORK_1_4 = 0)/*int*/; (___COUNTER_WORK_1_4 < 8192); (___COUNTER_WORK_1_4++)) {{
          for ((i__conflict__2__50__311 = 0)/*int*/; (i__conflict__2__50__311 < 1024); (i__conflict__2__50__311++)) {((tmp1__47__308[(int)i__conflict__2__50__311]) = (___POP_BUFFER_4_1[(int)(++___POP_INDEX_1_4)]))/*int*/;
          }
          for ((i__conflict__1__51__312 = 0)/*int*/; (i__conflict__1__51__312 < 512); (i__conflict__1__51__312++)) {{
              ((tmp2__48__309[(int)i__conflict__1__51__312]) = (tmp1__47__308[(int)i__conflict__1__51__312]))/*int*/;
              ((tmp2__48__309[(int)(i__conflict__1__51__312 + 512)]) = (tmp1__47__308[(int)(i__conflict__1__51__312 + 512)]))/*int*/;
            }
          }
          for ((i__conflict__0__52__313 = 0)/*int*/; (i__conflict__0__52__313 < 1024); (i__conflict__0__52__313++)) {((tmp3__49__310[(int)i__conflict__0__52__313]) = (tmp2__48__309[(int)i__conflict__0__52__313]))/*int*/;
          }
          for ((i__53__314 = 0)/*int*/; (i__53__314 < 1024); (i__53__314++)) {__push_0_1((tmp3__49__310[(int)i__53__314]));
          }
        }
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_0() {
  init__317__0();
  if (save_state::load_state(0, &__steady_0, __read_thread__0) == -1) pthread_exit(NULL);
}

static void __main__0() {
  int _tmp; // modified
  int _steady = __steady_0;
  int _number = __max_iteration;

  if (_steady == 0) {
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
      //check_status__0();
      if (*__state_flag_0 == EXIT_THREAD) exit_thread(__thread_0);
      work__316__0(1);
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_0, _steady, __write_thread__0);
#endif // __CHECKPOINT_FREQ
  }
}

void run_0() {
  __init_sockets_0(check_status_during_io__0);
  __init_state_0();

  timer t1;
  __peek_sockets_0();
  t1.start();
  __main__0();
  t1.stop();
  if (__timer_enabled) t1.output(stderr);

  __flush_sockets_0();
  pthread_exit(NULL);
}
