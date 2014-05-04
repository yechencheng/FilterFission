// peek: 8 pop: 8 push 0
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
message *__msg_stack_4;
int __number_of_iterations_4;
int __counter_4 = 0;
int __steady_4 = 0;
int __tmp_4 = 0;
int __tmp2_4 = 0;
int *__state_flag_4 = NULL;
thread_info *__thread_4 = NULL;

consumer2<int> __consumer_3_4;
extern int __pop_3_4();


void save_peek_buffer__4(object_write_buffer *buf);
void load_peek_buffer__4(object_write_buffer *buf);
void save_file_pointer__4(object_write_buffer *buf);
void load_file_pointer__4(object_write_buffer *buf);

void __write_thread__4(object_write_buffer *buf) {
  __consumer_3_4.write_object(buf);
  save_peek_buffer__4(buf);
  save_file_pointer__4(buf);
}

void __read_thread__4(object_write_buffer *buf) {
  __consumer_3_4.read_object(buf);
  load_peek_buffer__4(buf);
  load_file_pointer__4(buf);
}

inline void check_status__4() {
  check_thread_status(__state_flag_4, __thread_4);
}

void check_status_during_io__4() {
  check_thread_status_during_io(__state_flag_4, __thread_4);
}

void __init_thread_info_4(thread_info *info) {
  info->add_incoming_data_connection(new connection_info(3,4,&__consumer_3_4));
  __state_flag_4 = info->get_state_flag();
}

thread_info *__get_thread_info_4() {
  if (__thread_4 != NULL) return __thread_4;
  __thread_4 = new thread_info(4, check_status_during_io__4);
  __init_thread_info_4(__thread_4);
  return __thread_4;
}

void __declare_sockets_4() {
  init_instance::add_incoming(3,4, DATA_SOCKET);
}

void __init_sockets_4(void (*cs_fptr)()) {
  mysocket *sock;

  sock = init_instance::get_incoming_socket(3,4,DATA_SOCKET);
  sock->set_check_thread_status(cs_fptr);
  __consumer_3_4.set_socket(sock);
  __consumer_3_4.init();

}

void __flush_sockets_4() {
  __consumer_3_4.delete_socket_obj();
}

void __peek_sockets_4() {
  __consumer_3_4.peek(0);
}

 
void init__91__4(); 
void init__48__77__4(); 
void init__58__87__4();
inline void check_status__4();

void work__90__4(int);

// downstreamDeclarationExtern cluster_3_4
// downstreamDeclaration cluster_3_4:
int __pop_buf__4[8];
int __head__4;
int __tail__4;

inline void __init_pop_buf__4() {
  __tail__4=0;
  __head__4=0;
}

void save_peek_buffer__4(object_write_buffer *buf) {
  int i = 0, offs = __tail__4;
  while (offs != __head__4) {
    buf->write(&__pop_buf__4[offs], sizeof(int ));
    offs++;
    offs&=7;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__4(object_write_buffer *buf) {
  __tail__4=0;
  __head__4=0;
}

inline void __update_pop_buf__4() {
for (int i = 0; i < 8; i++) {
  __pop_buf__4[i]=__consumer_3_4.pop();
}
  __tail__4 = 0;
  __head__4 = 8;
}


inline int __pop_3_4() {
return __pop_buf__4[__tail__4++];
}

inline void __pop_3_4(int n) {
__tail__4+=n;
return;
}

inline int __peek_3_4(int offs) {
return __pop_buf__4[(__tail__4+offs)];
  }



 
void init__91__4(){
  init__48__77__4();
  init__58__87__4();
}
 
void init__48__77__4(){
}
 
void init__58__87__4(){
}
void save_file_pointer__4(object_write_buffer *buf) {}
void load_file_pointer__4(object_write_buffer *buf) {}
 
void work__90__4(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8] = {0};/* int[8] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int ___COUNTER_WORK_1_1 = 0;/* int */
      int tmp__49__78[4] = {0};/* int[4] */
      int id__50__79 = 0;/* int */
      int __tmp5__51__80 = 0;/* int */
      int j__conflict__1__52__81 = 0;/* int */
      int j__53__82 = 0;/* int */
      int i__conflict__0__54__83 = 0;/* int */
      int i__55__84 = 0;/* int */
      int __tmp6__59__88 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      // mark begin: SIRFilter MyJoin

      (id__50__79 = 0)/*int*/;
      for ((i__conflict__0__54__83 = 0)/*int*/; (i__conflict__0__54__83 < 2); (i__conflict__0__54__83++)) {{
          for ((j__conflict__1__52__81 = 0)/*int*/; (j__conflict__1__52__81 < 2); (j__conflict__1__52__81++)) {{
              __tmp5__51__80 = __pop_3_4();
;
              ((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = __tmp5__51__80)/*int*/;
            }
          }
          for ((j__53__82 = 0)/*int*/; (j__53__82 < 2); (j__53__82++)) {(tmp__49__78[(int)(id__50__79++)]) = __pop_3_4();
;
          }
        }
      }
      for ((i__55__84 = 0)/*int*/; (i__55__84 < 4); (i__55__84++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp__49__78[(int)i__55__84]))/*int*/;
      }
      // mark end: SIRFilter MyJoin

      // mark begin: SIRFilter print

      for ((___COUNTER_WORK_1_1 = 0)/*int*/; (___COUNTER_WORK_1_1 < 8); (___COUNTER_WORK_1_1++)) {{
          (__tmp6__59__88 = (___POP_BUFFER_1_1[(int)((1 + ___POP_INDEX_1_1) + 0)]))/*int*/;

          // TIMER_PRINT_CODE: __print_sink__ += (int)(__tmp6__59__88); 
          printf( "%d", __tmp6__59__88); printf("\n");

          (___POP_INDEX_1_1 = (___POP_INDEX_1_1 + 1))/*int*/;
        }
      }
      // mark end: SIRFilter print

    }
  }
}

void __init_state_4() {
  init__91__4();
  if (save_state::load_state(4, &__steady_4, __read_thread__4) == -1) pthread_exit(NULL);
}

static void __main__4() {
  int _tmp; // modified
  int _steady = __steady_4;
  int _number = __max_iteration;

  if (_steady == 0) {
  __init_pop_buf__4();
  }
  _steady++;
  for (; _steady <= _number; _steady++) {
    for (_tmp = 0; _tmp < 2; _tmp++) {
      //check_status__4();
      if (*__state_flag_4 == EXIT_THREAD) exit_thread(__thread_4);
      __update_pop_buf__4();
      work__90__4(1);
    }
#ifdef __CHECKPOINT_FREQ
    if (_steady % __CHECKPOINT_FREQ == 0)
      save_state::save_to_file(__thread_4, _steady, __write_thread__4);
#endif // __CHECKPOINT_FREQ
  }
}

void run_4() {
  __init_sockets_4(check_status_during_io__4);
  __init_state_4();

  __main__4();

  __flush_sockets_4();
  pthread_exit(NULL);
}
