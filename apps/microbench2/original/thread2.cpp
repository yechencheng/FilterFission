// peek: 8388608 pop: 8388608 push 8388608
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

 
void init__157__2(); 
void init__45__137__2(); 
void init__55__147__2();
inline void check_status__2();

void work__156__2(int);

// downstreamDeclarationExtern cluster_1_2
// downstreamDeclaration cluster_1_2:
int __pop_buf__2[8388608];
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
    offs&=8388607;
    i++;
  }
  assert(i == 0);
}

void load_peek_buffer__2(object_write_buffer *buf) {
  __tail__2=0;
  __head__2=0;
}

inline void __update_pop_buf__2() {
for (int i = 0; i < 8388608; i++) {
  __pop_buf__2[i]=__consumer_1_2.pop();
}
  __tail__2 = 0;
  __head__2 = 8388608;
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

 
void init__157__2(){
  init__45__137__2();
  init__55__147__2();
}
 
void init__45__137__2(){
}
 
void init__55__147__2(){
}
void save_file_pointer__2(object_write_buffer *buf) {}
void load_file_pointer__2(object_write_buffer *buf) {}
 
void work__156__2(int ____n){
  for (
  ; (0 < ____n); (____n--)) {{
      int ___POP_BUFFER_1_1[8388608] = {0};/* int[8388608] */
      int ___POP_INDEX_1_1 = 0;/* int */
      int ___PUSH_INDEX_1_1 = 0;/* int */
      int tmp1__46__138[8388608] = {0};/* int[8388608] */
      int tmp2__47__139[8388608] = {0};/* int[8388608] */
      int tmp3__48__140[8388608] = {0};/* int[8388608] */
      int i__conflict__2__49__141 = 0;/* int */
      int i__conflict__1__50__142 = 0;/* int */
      int i__conflict__0__51__143 = 0;/* int */
      int i__52__144 = 0;/* int */
      int tmp1__56__148[8388608] = {0};/* int[8388608] */
      int tmp2__57__149[8388608] = {0};/* int[8388608] */
      int tmp3__58__150[8388608] = {0};/* int[8388608] */
      int i__conflict__2__59__151 = 0;/* int */
      int i__conflict__1__60__152 = 0;/* int */
      int i__conflict__0__61__153 = 0;/* int */
      int i__62__154 = 0;/* int */

      (___POP_INDEX_1_1 = -1)/*int*/;
      (___PUSH_INDEX_1_1 = -1)/*int*/;
      // mark begin: SIRFilter process1

      for ((i__conflict__2__49__141 = 0)/*int*/; (i__conflict__2__49__141 < 8388608); (i__conflict__2__49__141++)) {(tmp1__46__138[(int)i__conflict__2__49__141]) = __pop_1_2();
;
      }
      for ((i__conflict__1__50__142 = 0)/*int*/; (i__conflict__1__50__142 < 4194304); (i__conflict__1__50__142++)) {{
          ((tmp2__47__139[(int)i__conflict__1__50__142]) = (tmp1__46__138[(int)i__conflict__1__50__142]))/*int*/;
          ((tmp2__47__139[(int)(i__conflict__1__50__142 + 4194304)]) = (tmp1__46__138[(int)(i__conflict__1__50__142 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__51__143 = 0)/*int*/; (i__conflict__0__51__143 < 8388608); (i__conflict__0__51__143++)) {((tmp3__48__140[(int)i__conflict__0__51__143]) = (tmp2__47__139[(int)i__conflict__0__51__143]))/*int*/;
      }
      for ((i__52__144 = 0)/*int*/; (i__52__144 < 8388608); (i__52__144++)) {((___POP_BUFFER_1_1[(int)(++___PUSH_INDEX_1_1)]) = (tmp3__48__140[(int)i__52__144]))/*int*/;
      }
      // mark end: SIRFilter process1

      // mark begin: SIRFilter process1

      for ((i__conflict__2__59__151 = 0)/*int*/; (i__conflict__2__59__151 < 8388608); (i__conflict__2__59__151++)) {((tmp1__56__148[(int)i__conflict__2__59__151]) = (___POP_BUFFER_1_1[(int)(++___POP_INDEX_1_1)]))/*int*/;
      }
      for ((i__conflict__1__60__152 = 0)/*int*/; (i__conflict__1__60__152 < 4194304); (i__conflict__1__60__152++)) {{
          ((tmp2__57__149[(int)i__conflict__1__60__152]) = (tmp1__56__148[(int)i__conflict__1__60__152]))/*int*/;
          ((tmp2__57__149[(int)(i__conflict__1__60__152 + 4194304)]) = (tmp1__56__148[(int)(i__conflict__1__60__152 + 4194304)]))/*int*/;
        }
      }
      for ((i__conflict__0__61__153 = 0)/*int*/; (i__conflict__0__61__153 < 8388608); (i__conflict__0__61__153++)) {((tmp3__58__150[(int)i__conflict__0__61__153]) = (tmp2__57__149[(int)i__conflict__0__61__153]))/*int*/;
      }
      for ((i__62__154 = 0)/*int*/; (i__62__154 < 8388608); (i__62__154++)) {__push_2_3((tmp3__58__150[(int)i__62__154]));
      }
      // mark end: SIRFilter process1

    }
  }
}

void __init_state_2() {
  init__157__2();
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
      //check_status__2();
      if (*__state_flag_2 == EXIT_THREAD) exit_thread(__thread_2);
      __update_pop_buf__2();
      work__156__2(1);
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
