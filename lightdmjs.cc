#include <napi.h>
#include "greeter.hh"
#include "event_loop.hh"
#include "users.hh"
#include "languages.hh"
#include "sessions.hh"
#include "power.hh"
#include "callbacks.hh"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  EventLoop::init(env); // initializes and maintains a GMainLoop, necessary for gobject signals.
  Greeter::Init(env, exports); // must be called first, initializes the shared LightDMGreeter instance.
  Users::Init(env, exports); // for now, exports a "getUsers" function.
  Sessions::Init(env, exports); // for now, exports a "getSessions" function.
  Languages::Init(env, exports); // for now, exports a "getLanguages" function.
  Callbacks::Init(env, exports); // everything that has to do with signals and callbacks, minus the event loop.
  return exports;
}

NODE_API_MODULE(addon, Init)