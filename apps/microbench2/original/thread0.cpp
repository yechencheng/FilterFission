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

 
void init__113__0(); 
void init__1__89__0(); 
void init__5__93__0(); 
void init__15__103__0();
inline void check_status__0();

void work__112__0(int);

// upstreamDeclarationExtern cluster_0_1
// upstreamDeclaration cluster_0_1
int __pop_buffer_0_1[10240];
int __pop_index_0_1 = 0;
inline void __push_0_1(int data) {
__producer_0_1.push(data);
}

 
void init__113__0(){
  init__1__89__0();
  init__5__93__0();
  init__15__103__0();
}
 
void init__1__89__0(){
}
 
void init__5__93__0(){
}
 
void init__15__103__0(){
}
void save_file_pointer__0(object_write_buffer *buf) {}
void load_file_pointer__0(object_write_buffer *buf) {}
 
void work__112__0(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___POP_BUFFER_2_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_2 = 0;/* int */
      int ___PUSH_INDEX_1_2 = 0;/* int */
      int i__2__90 = 0;/* int */
      int tmp1__6__94[8388608] = {0};/* int[8388608] */
      int tmp2__7__95[8388608] = {0};/* int[8388608] */
      int tmp3__8__96[8388608] = {0};/* int[8388608] */
      int i__conflict__2__9__97 = 0;/* int */
      int i__conflict__1__10__98 = 0;/* int */
      int i__conflict__0__11__99 = 0;/* int */
      int i__12__100 = 0;/* int */
      int tmp1__16__104[8388608] = {0};/* int[8388608] */
      int tmp2__17__105[8388608] = {0};/* int[8388608] */
      int tmp3__18__106[8388608] = {0};/* int[8388608] */
      int i__conflict__2__19__107 = 0;/* int */
      int i__conflict__1__20__108 = 0;/* int */
      int i__conflict__0__21__109 = 0;/* int */
      int i__22__110 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      (___POP_INDEX_1_2 = -1)/*int*/;
      (___PUSH_INDEX_1_2 = -1)/*int*/;
      // mark begin: SIRFilter source

      for ((i__2__90 = 0)/*int*/; (i__2__90 < 8388608); (i__2__90++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = i__2__90)/*int*/;
      }
      // mark end: SIRFilter source

      // mark begin: SIRFilter process1

      for ((i__conflict__2__9__97 = 0)/*int*/; (i__conflict__2__9__97 < 8388608); (i__conflict__2__9__97++)) {((tmp1__6__94[(int)i__conflict__2__9__97]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
      }
      for ((i__conflict__1__10__98 = 0)/*int*/; (i__conflict__1__10__98 < 4194304); (i__conflict__1__10__98++)) {{
          ((tmp2__7__95[(int)i__conflict__1__10__98]) = (tmp1__6__94[(int)i__conflict__1__10__98]))/*int*/;
          ((tmp2__7__95[(int)(i__conflict__1__10__98 + 4194304)]) = (tmp1__6__94[(int)(i__conflict__1__10__98 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__11__99 = 0)/*int*/; (i__conflict__0__11__99 < 8388608); (i__conflict__0__11__99++)) {((tmp3__8__96[(int)i__conflict__0__11__99]) = (tmp2__7__95[(int)i__conflict__0__11__99]))/*int*/;
      }
      for ((i__12__100 = 0)/*int*/; (i__12__100 < 8388608); (i__12__100++)) {((___POP_BUFFER_2_1[(int)(++___PUSH_INDEX_1_2)]) = (tmp3__8__96[(int)i__12__100]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter process1

      for ((i__conflict__2__19__107 = 0)/*int*/; (i__conflict__2__19__107 < 8388608); (i__conflict__2__19__107++)) {((tmp1__16__104[(int)i__conflict__2__19__107]) = (___POP_BUFFER_2_1[(int)(++___POP_INDEX_1_2)]))/*int*/;
      }
      for ((i__conflict__1__20__108 = 0)/*int*/; (i__conflict__1__20__108 < 4194304); (i__conflict__1__20__108++)) {{
          ((tmp2__17__105[(int)i__conflict__1__20__108]) = (tmp1__16__104[(int)i__conflict__1__20__108]))/*int*/;
          ((tmp2__17__105[(int)(i__conflict__1__20__108 + 4194304)]) = (tmp1__16__104[(int)(i__conflict__1__20__108 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__21__109 = 0)/*int*/; (i__conflict__0__21__109 < 8388608); (i__conflict__0__21__109++)) {((tmp3__18__106[(int)i__conflict__0__21__109]) = (tmp2__17__105[(int)i__conflict__0__21__109]))/*int*/;
      }
      for ((i__22__110 = 0)/*int*/; (i__22__110 < 8388608); (i__22__110++)) {__push_0_1((tmp3__18__106[(int)i__22__110]));
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_0() {
  init__113__0();
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
      work__112__0(1);
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
