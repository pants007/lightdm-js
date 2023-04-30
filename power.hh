#include <napi.h>
extern "C" {
  #include "lightdm.h"
}
namespace PowerManagement {
  Napi::Value SystemSuspend(const Napi::CallbackInfo& info);
  Napi::Value SystemRestart(const Napi::CallbackInfo& info);
  Napi::Value SystemShutdown(const Napi::CallbackInfo& info);
  Napi::Value SystemHibernate(const Napi::CallbackInfo& info);
  Napi::Value CanSystemSuspend(const Napi::CallbackInfo& info);
  Napi::Value CanSystemRestart(const Napi::CallbackInfo& info);
  Napi::Value CanSystemShutdown(const Napi::CallbackInfo& info);
  Napi::Value CanSystemHibernate(const Napi::CallbackInfo& info);
}