#include <napi.h>
extern "C" {
  #include "lightdm.h"
}
namespace Greeter {
  extern LightDMGreeter *instance;
  Napi::Value ConnectToDaemonSync(const Napi::CallbackInfo& info);
  Napi::Value AuthenticationBegin(const Napi::CallbackInfo& info);
  Napi::Value AuthenticationBeginGuest(const Napi::CallbackInfo& info);
  Napi::Value AuthenticationBeginAutologin(const Napi::CallbackInfo& info);
  Napi::Value AuthenticationRespond(const Napi::CallbackInfo& info);
  Napi::Value SessionStartSync(const Napi::CallbackInfo& info);
  Napi::Value GetAuthenticationUser(const Napi::CallbackInfo& info);
  Napi::Value SetLanguage(const Napi::CallbackInfo& info);
  Napi::Value IsAuthenticated(const Napi::CallbackInfo& info);
  Napi::Value InAuthentication(const Napi::CallbackInfo& info);
  Napi::Value GetAuthenticationUser(const Napi::CallbackInfo& info);
  Napi::Value GetHints(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}

