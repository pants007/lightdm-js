#include <napi.h>
#include <glib.h>
namespace EventLoop {
  extern GMainLoop *loop;
  void start_main_loop(gpointer data);
  void stop_main_loop();
  void init(Napi::Env env);
}
