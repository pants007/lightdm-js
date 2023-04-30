#include "greeter.hh"

namespace Greeter {
  LightDMGreeter *instance = nullptr;
  Napi::Value ConnectToDaemonSync(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(),lightdm_greeter_connect_to_daemon_sync(instance, NULL));
  }
  Napi::Value AuthenticationBegin(const Napi::CallbackInfo& info) {
    if (info.Length() == 0) {
      return Napi::Boolean::New(info.Env(), lightdm_greeter_authenticate(instance, NULL, NULL));
    } else if (info.Length() == 1 && info[0].IsString()) {
      std::string username = std::string(info[0].As<Napi::String>());
      return Napi::Boolean::New(info.Env(), lightdm_greeter_authenticate(instance, username.c_str(), NULL));
    } else {
      throw Napi::TypeError::New(info.Env(), "Expected a string");
    }
  }
  Napi::Value AuthenticationRespond(const Napi::CallbackInfo& info) {
    if (info.Length() == 1 && info[0].IsString()) {
      std::string response = std::string(info[0].As<Napi::String>());
      return Napi::Boolean::New(info.Env(), lightdm_greeter_respond(instance, response.c_str(), NULL));
    } else {
      throw Napi::TypeError::New(info.Env(), "Expected a string");
    }
  }  
  Napi::Value IsAuthenticated(const Napi::CallbackInfo& info) {
    bool status = lightdm_greeter_get_is_authenticated(instance);
    return Napi::Boolean::New(info.Env(), status);
  }
  Napi::Value InAuthentication(const Napi::CallbackInfo& info) {
    bool status = lightdm_greeter_get_in_authentication(instance);
    return Napi::Boolean::New(info.Env(), status);
  }
  void init(Napi::Env env) {
    instance = lightdm_greeter_new();
    if (instance == nullptr) {
      throw Napi::Error::New(env, "Failed to create a new greeter.");
    }
  }
}
