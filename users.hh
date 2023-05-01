#include <napi.h>

extern "C" {
  #include "lightdm.h"
}
namespace Users {
  Napi::Value Get(const Napi::CallbackInfo& info);  
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
