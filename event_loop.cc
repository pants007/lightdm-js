#include "event_loop.hh"

namespace EventLoop {
  GMainLoop *loop = nullptr;
  void start_main_loop(gpointer data) {
    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
  }

  void stop_main_loop() {
    if (loop != nullptr) {
      g_main_loop_quit(loop);
      g_main_loop_unref(loop);
      loop = NULL;
    }
  }

  void init(Napi::Env env) {
    //spawn a new thread with a GMainLoop, otherwise we can't see messages from LightDM
    g_thread_new("main loop", (GThreadFunc)start_main_loop, NULL);
  } 
}
