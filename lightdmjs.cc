#include <napi.h>
#include "greeter.hh"
#include "event_loop.hh"
#include "users.hh"
#include "languages.hh"
#include "sessions.hh"
#include "power.hh"
#include "callbacks.hh"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  Greeter::init(env);
  EventLoop::init(env);
  exports.Set(Napi::String::New(env, "getUsers"), Napi::Function::New(env, Users::Get));
  exports.Set(Napi::String::New(env, "getLanguages"), Napi::Function::New(env, Languages::Get));
  exports.Set(Napi::String::New(env, "getSessions"), Napi::Function::New(env, Sessions::Get));
  exports.Set(Napi::String::New(env, "setCallback"), Napi::Function::New(env, Callbacks::Set));
  exports.Set(Napi::String::New(env, "releaseCallbacks"), Napi::Function::New(env, Callbacks::Release));
  exports.Set(Napi::String::New(env, "authenticationBegin"), Napi::Function::New(env, Greeter::AuthenticationBegin));
  exports.Set(Napi::String::New(env, "authenticationRespond"), Napi::Function::New(env, Greeter::AuthenticationRespond));
  exports.Set(Napi::String::New(env, "connectToDaemonSync"), Napi::Function::New(env, Greeter::ConnectToDaemonSync));
  exports.Set(Napi::String::New(env, "isAuthenticated"), Napi::Function::New(env, Greeter::IsAuthenticated));
  exports.Set(Napi::String::New(env, "inAuthentication"), Napi::Function::New(env, Greeter::InAuthentication));
  exports.Set(Napi::String::New(env, "callbackTypes"), Napi::Function::New(env, Callbacks::GetCallbackTypes));
  return exports;
}

NODE_API_MODULE(addon, Init)