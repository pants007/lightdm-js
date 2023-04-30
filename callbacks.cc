#include "greeter.hh"
#include "callbacks.hh"

namespace Callbacks {
  Napi::ThreadSafeFunction showPromptCallback = nullptr;
  Napi::ThreadSafeFunction showMessageCallback = nullptr;
  Napi::ThreadSafeFunction authenticationCompleteCallback = nullptr;
  Napi::ThreadSafeFunction autologinTimerExpiredCallback = nullptr;
  Napi::ThreadSafeFunction idleCallback = nullptr;
  Napi::ThreadSafeFunction resetCallback = nullptr;

  void ShowPromptSetup(Napi::Env env, Napi::Function jsCallback, ShowPromptData *data) {
      auto arg1 = Napi::String::New(env, data->text);
      auto arg2 = Napi::Number::New(env, data->type);
      jsCallback.Call({arg1, arg2});
      delete[] data->text;
      delete data;
  }
  void ShowPrompt(GObject *gobj, char *text, int type) {
      ShowPromptData *data = new ShowPromptData();
      data->text = g_strdup(text);
      data->type = type;
      showPromptCallback.BlockingCall(data, ShowPromptSetup);
  }
  void ShowMessageSetup(Napi::Env env, Napi::Function jsCallback, ShowMessageData *data) {
      auto arg1 = Napi::String::New(env, data->text);
      auto arg2 = Napi::Number::New(env, data->type);
      jsCallback.Call({arg1, arg2});
      delete[] data->text;
      delete data;
  }
  void ShowMessage(GObject *gobj, char *text, int type) {
      ShowMessageData *data = new ShowMessageData();
      data->text = g_strdup(text);
      data->type = type;
      showMessageCallback.BlockingCall(data, ShowMessageSetup);
  }
  void AuthenticationCompleteSetup(Napi::Env env, Napi::Function jsCallback, AuthenticationCompleteData *data) {
    jsCallback.Call({});
    delete data;
  }
  void AuthenticationComplete(GObject *gobj) {
    AuthenticationCompleteData *data = new AuthenticationCompleteData();
    authenticationCompleteCallback.BlockingCall(data, AuthenticationCompleteSetup);
  }
  void AutologinTimerExpiredSetup(Napi::Env env, Napi::Function jsCallback, AutologinTimerExpiredData *data) {
    jsCallback.Call({});
    delete data;
  }
  void AutologinTimerExpired(GObject *gobj) {
    AutologinTimerExpiredData *data = new AutologinTimerExpiredData();
    authenticationCompleteCallback.BlockingCall(data, AutologinTimerExpiredSetup);
  }
  void IdleSetup(Napi::Env env, Napi::Function jsCallback, IdleData *data) {
    jsCallback.Call({});
    delete data;
  }
  void Idle(GObject *gobj) {
    IdleData *data = new IdleData();
    authenticationCompleteCallback.BlockingCall(data, IdleSetup);
  }
  void ResetSetup(Napi::Env env, Napi::Function jsCallback, ResetData *data) {
    jsCallback.Call({});
    delete data;
  }
  void Reset(GObject *gobj) {
    ResetData *data = new ResetData();
    authenticationCompleteCallback.BlockingCall(data, ResetSetup);
  }

  Napi::Value Set(const Napi::CallbackInfo& info) {
    if (info.Length() != 2) {
      throw Napi::TypeError::New(info.Env(), "Expected a signal name (see callbacks.hh) and a callback function");
    }
    if (!info[0].IsString()) {
    }
    if (!info[1].IsFunction()) {
      throw Napi::TypeError::New(info.Env(), "Expected a callback function");
    }
    std::string signalName = info[0].As<Napi::String>();
    Napi::Function cb = info[1].As<Napi::Function>();
    if (signalName == LIGHTDM_GREETER_SIGNAL_SHOW_PROMPT) {
      showPromptCallback = Napi::ThreadSafeFunction::New(
          info.Env(), cb, "Resource Name", 0, 1, [](Napi::Env) {  });
      g_signal_connect(Greeter::instance, LIGHTDM_GREETER_SIGNAL_SHOW_PROMPT, G_CALLBACK(ShowPrompt), NULL);
    } else if (signalName == LIGHTDM_GREETER_SIGNAL_SHOW_MESSAGE) {
      showMessageCallback = Napi::ThreadSafeFunction::New(
          info.Env(), cb, "Resource Name", 0, 1, [](Napi::Env) {  });
      g_signal_connect(Greeter::instance, LIGHTDM_GREETER_SIGNAL_SHOW_MESSAGE, G_CALLBACK(ShowMessage), NULL);
    } else if (signalName == LIGHTDM_GREETER_SIGNAL_AUTHENTICATION_COMPLETE) {
      authenticationCompleteCallback = Napi::ThreadSafeFunction::New(
          info.Env(), cb, "Resource Name", 0, 1, [](Napi::Env) {  });
      g_signal_connect(Greeter::instance, LIGHTDM_GREETER_SIGNAL_AUTHENTICATION_COMPLETE, G_CALLBACK(AuthenticationComplete), NULL);
    } else if (signalName == LIGHTDM_GREETER_SIGNAL_AUTOLOGIN_TIMER_EXPIRED) {
      autologinTimerExpiredCallback = Napi::ThreadSafeFunction::New(
          info.Env(), cb, "Resource Name", 0, 1, [](Napi::Env) {  });
      g_signal_connect(Greeter::instance, LIGHTDM_GREETER_SIGNAL_AUTOLOGIN_TIMER_EXPIRED, G_CALLBACK(AutologinTimerExpired), NULL);
    } else if (signalName == LIGHTDM_GREETER_SIGNAL_IDLE) {
      idleCallback = Napi::ThreadSafeFunction::New(
          info.Env(), cb, "Resource Name", 0, 1, [](Napi::Env) { });
      g_signal_connect(Greeter::instance, LIGHTDM_GREETER_SIGNAL_IDLE, G_CALLBACK(Idle), NULL);
    } else if (signalName == LIGHTDM_GREETER_SIGNAL_RESET) {
      resetCallback = Napi::ThreadSafeFunction::New(
          info.Env(), cb, "Resource Name", 0, 1, [](Napi::Env) { });
      g_signal_connect(Greeter::instance, LIGHTDM_GREETER_SIGNAL_RESET, G_CALLBACK(Reset), NULL);
    }
    return info.Env().Undefined();
  }

  Napi::Value Release(const Napi::CallbackInfo& info) {
      if (showPromptCallback != nullptr) {
          showPromptCallback.Release();
      }
      if (showMessageCallback != nullptr) {
          showMessageCallback.Release();
      }
      if (authenticationCompleteCallback != nullptr) {
          authenticationCompleteCallback.Release();
      }
      return info.Env().Undefined();
  }

  Napi::Value GetCallbackTypes(const Napi::CallbackInfo& info) {
    Napi::Object cbTypeObj = Napi::Object::New(info.Env());
    cbTypeObj.Set("showPromptSignal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_SHOW_PROMPT));
    cbTypeObj.Set("showMessageSignal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_SHOW_MESSAGE));
    cbTypeObj.Set("authenticationCompleteSignal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_AUTHENTICATION_COMPLETE));
    cbTypeObj.Set("autologinTimerExpiredSignal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_AUTOLOGIN_TIMER_EXPIRED));
    cbTypeObj.Set("idleSignal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_IDLE));
    cbTypeObj.Set("resetSignal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_RESET));
    return cbTypeObj;
  }
}
