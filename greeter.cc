#include "greeter.hh"

namespace Greeter {
  Napi::ThreadSafeFunction showPromptCallback;
  Napi::ThreadSafeFunction showMessageCallback;
  Napi::ThreadSafeFunction authenticationCompleteCallback;
  Napi::ThreadSafeFunction autologinTimerExpiredCallback;
  Napi::ThreadSafeFunction idleCallback;
  Napi::ThreadSafeFunction resetCallback;
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
  Napi::Value AuthenticationBeginGuest(const Napi::CallbackInfo& info) {
    bool request_sent = lightdm_greeter_authenticate_as_guest(instance, NULL);
    return Napi::Boolean::New(info.Env(), request_sent);
  }
  Napi::Value AuthenticationBeginAutologin(const Napi::CallbackInfo& info) {
    bool request_sent = lightdm_greeter_authenticate_autologin(instance, NULL);
    return Napi::Boolean::New(info.Env(), request_sent);
  }
  Napi::Value AuthenticationCancel(const Napi::CallbackInfo& info) {
    bool cancelled = lightdm_greeter_cancel_authentication(instance, NULL);
    return Napi::Boolean::New(info.Env(), cancelled);
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
  Napi::Value GetAuthenticationUser(const Napi::CallbackInfo& info) {
    auto status = lightdm_greeter_get_authentication_user(instance);
    return Napi::String::New(info.Env(), status);
  }
  Napi::Value SessionStartSync(const Napi::CallbackInfo& info) {
    if (info.Length() != 1 && !info[0].IsString()) {
      throw Napi::TypeError::New(info.Env(), "Expected a string");
    }
    std::string session_name = info[0].As<Napi::String>();
    bool status = lightdm_greeter_start_session_sync(instance, session_name.c_str(), NULL);
    return Napi::Boolean::New(info.Env(), status);
  }
  Napi::Object Init(Napi::Env env, Napi::Object exports) {
    instance = lightdm_greeter_new();
    if (instance == nullptr) {
      throw Napi::Error::New(env, "Failed to create a new greeter.");
    }
    exports.Set(Napi::String::New(env, "authenticationBegin"), Napi::Function::New(env, AuthenticationBegin));
    exports.Set(Napi::String::New(env, "authenticationRespond"), Napi::Function::New(env, AuthenticationRespond));
    exports.Set(Napi::String::New(env, "connectToDaemonSync"), Napi::Function::New(env, ConnectToDaemonSync));
    exports.Set(Napi::String::New(env, "isAuthenticated"), Napi::Function::New(env, IsAuthenticated));
    exports.Set(Napi::String::New(env, "inAuthentication"), Napi::Function::New(env, InAuthentication));
    exports.Set(Napi::String::New(env, "getHints"), Napi::Function::New(env, GetHints));

    return exports;
  }
  Napi::Value GetHints(const Napi::CallbackInfo& info) {
    auto env = info.Env();
    auto obj = Napi::Object::New(env);
    const char* temp = lightdm_greeter_get_autologin_user_hint(instance);
    if (temp == nullptr) {
      obj.Set("autologin_user", Napi::String::New(env, std::string("")));
    } else {
      obj.Set("autologin_user", Napi::String::New(env, std::string(temp)));
    }
    temp = lightdm_greeter_get_default_session_hint(instance);
    if (temp == nullptr) {
      obj.Set("default_session", Napi::String::New(env, std::string("")));
    } else {
      obj.Set("default_session", Napi::String::New(env, std::string(temp)));
    }
    temp = lightdm_greeter_get_select_user_hint(instance);
    if (temp == nullptr) {
      obj.Set("select_user", Napi::String::New(env, std::string("")));
    } else {
      obj.Set("select_user", Napi::String::New(env, std::string(temp)));
    }
    bool hide_users = lightdm_greeter_get_hide_users_hint(instance);
    bool show_manual_login = lightdm_greeter_get_show_manual_login_hint(instance);
    bool show_remote_login = lightdm_greeter_get_show_remote_login_hint(instance);
    bool lock = lightdm_greeter_get_lock_hint(instance);
    bool has_guest_account = lightdm_greeter_get_has_guest_account_hint(instance);
    bool select_guest = lightdm_greeter_get_select_guest_hint(instance);
    bool autologin_guest = lightdm_greeter_get_autologin_guest_hint(instance);
    int autologin_timeout = lightdm_greeter_get_autologin_timeout_hint(instance);
    obj.Set("hide_users", Napi::Boolean::New(env, hide_users));
    obj.Set("show_manual_login", Napi::Boolean::New(env, show_manual_login));
    obj.Set("show_remote_login", Napi::Boolean::New(env, show_remote_login));
    obj.Set("lock", Napi::Boolean::New(env, lock));
    obj.Set("has_guest_account", Napi::Boolean::New(env, has_guest_account));
    obj.Set("select_guest", Napi::Boolean::New(env, select_guest));
    obj.Set("autologin_guest", Napi::Boolean::New(env, autologin_guest));
    obj.Set("autologin_timeout", Napi::Number::New(env, autologin_timeout));
    return obj;
  }
  Napi::Value SetLanguage(const Napi::CallbackInfo& info) {
    if (info.Length() == 1 && info[0].IsString()) {
      std::string language = std::string(info[0].As<Napi::String>());
      bool request_sent = lightdm_greeter_set_language(instance, language.c_str(), NULL);
      return Napi::Boolean::New(info.Env(), request_sent);
    } else {
      throw Napi::TypeError::New(info.Env(), "Expected a string");
    }
  }
}
