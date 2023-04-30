#include <napi.h>
extern "C" {
  #include "lightdm.h"
}
namespace Greeter {
  extern LightDMGreeter *instance;
  Napi::Value ConnectToDaemonSync(const Napi::CallbackInfo& info);
  Napi::Value AuthenticationBegin(const Napi::CallbackInfo& info);
  Napi::Value AuthenticationRespond(const Napi::CallbackInfo& info);
  Napi::Value IsAuthenticated(const Napi::CallbackInfo& info);
  Napi::Value InAuthentication(const Napi::CallbackInfo& info);
  void init(Napi::Env env);
}
