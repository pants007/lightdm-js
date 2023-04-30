#include "power.hh"
namespace PowerManagement {
  Napi::Value SystemSuspend(const Napi::CallbackInfo& info) {
    bool allowed = lightdm_get_can_suspend();
    if (allowed) {
      return Napi::Boolean::New(info.Env(), lightdm_suspend(NULL));
    }
    return Napi::Boolean::New(info.Env(), FALSE);
  }
  Napi::Value SystemRestart(const Napi::CallbackInfo& info) {
    bool allowed = lightdm_get_can_restart();
    if (allowed) {
      return Napi::Boolean::New(info.Env(), lightdm_restart(NULL));
    }
    return Napi::Boolean::New(info.Env(), FALSE);
  }
  Napi::Value SystemShutdown(const Napi::CallbackInfo& info) {
    bool allowed = lightdm_get_can_shutdown();
    if (allowed) {
      return Napi::Boolean::New(info.Env(), lightdm_shutdown(NULL));
    }
    return Napi::Boolean::New(info.Env(), FALSE);
  }
  Napi::Value SystemHibernate(const Napi::CallbackInfo& info) {
    bool allowed = lightdm_get_can_hibernate();
    if (allowed) {
      return Napi::Boolean::New(info.Env(), lightdm_hibernate(NULL));
    }
    return Napi::Boolean::New(info.Env(), FALSE);
  }
  Napi::Value CanSystemSuspend(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), lightdm_get_can_suspend());
  }
  Napi::Value CanSystemRestart(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), lightdm_get_can_restart());
  }
  Napi::Value CanSystemShutdown(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), lightdm_get_can_shutdown());
  }
  Napi::Value CanSystemHibernate(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), lightdm_get_can_hibernate());
  }
}
