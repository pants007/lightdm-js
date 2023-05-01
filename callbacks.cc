#include "greeter.hh"
#include "callbacks.hh"

namespace Callbacks {

  void ShowPromptSetup(Napi::Env env, Napi::Function jsCallback, ShowPromptData *data) {
      auto arg1 = Napi::String::New(env, data->text);
      // look up LightDMPromptType for event
      GType type = g_type_from_name("LightDMPromptType");
      GEnumClass *enum_class = G_ENUM_CLASS(g_type_class_ref(type));
      GEnumValue *value = g_enum_get_value(enum_class, data->type);
      auto arg2 = Napi::String::New(env, value->value_nick);
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
      // look up LightDMMessageType for event
      GType type = g_type_from_name("LightDMMessageType");
      GEnumClass *enum_class = G_ENUM_CLASS(g_type_class_ref(type));
      GEnumValue *value = g_enum_get_value(enum_class, data->type);
      auto arg2 = Napi::String::New(env, value->value_nick);
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
      showPromptCallback.Release();
      showMessageCallback.Release();
      authenticationCompleteCallback.Release();
      return info.Env().Undefined();
  }

  Napi::Value GetCallbackTypes(const Napi::CallbackInfo& info) {
    Napi::Object cbTypeObj = Napi::Object::New(info.Env());
    
    Napi::Object showPromptObject = Napi::Object::New(info.Env());
    showPromptObject.Set("signal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_SHOW_PROMPT));
    Napi::Object showPromptTypes = Napi::Object::New(info.Env());
    showPromptTypes = GEnumToJS("LightDMPromptType", showPromptTypes);
    showPromptObject.Set("types", showPromptTypes);
    cbTypeObj.Set("showPrompt", showPromptObject);

    Napi::Object showMessageObject = Napi::Object::New(info.Env());
    showMessageObject.Set("signal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_SHOW_MESSAGE));
    Napi::Object showMessageTypes = Napi::Object::New(info.Env());
    showMessageTypes = GEnumToJS("LightDMMessageType", showMessageTypes);
    showMessageObject.Set("types", showMessageTypes);
    cbTypeObj.Set("showMessage", showMessageObject);

    Napi::Object authenticationCompleteObject = Napi::Object::New(info.Env());
    authenticationCompleteObject.Set("signal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_AUTHENTICATION_COMPLETE));
    cbTypeObj.Set("authenticationComplete", authenticationCompleteObject);
    Napi::Object autologinTimerExpiredObject = Napi::Object::New(info.Env());
    autologinTimerExpiredObject.Set("signal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_AUTOLOGIN_TIMER_EXPIRED));
    cbTypeObj.Set("autologinTimerExpired", autologinTimerExpiredObject);
    Napi::Object idleObject = Napi::Object::New(info.Env());
    idleObject.Set("signal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_IDLE));
    cbTypeObj.Set("idle", idleObject);
    Napi::Object resetObject = Napi::Object::New(info.Env());
    resetObject.Set("signal", Napi::String::New(info.Env(), LIGHTDM_GREETER_SIGNAL_RESET));
    cbTypeObj.Set("reset", resetObject);
    return cbTypeObj;
  }

  Napi::Object GEnumToJS(char *name, Napi::Object obj) {
    GType type = g_type_from_name(name);
    GEnumClass *enum_class = G_ENUM_CLASS(g_type_class_ref(type));
    for(int i = 0; i < enum_class->n_values; i++) {
      GEnumValue enum_value = enum_class->values[i];
      obj.Set(enum_value.value_nick, enum_value.value);
    }
    return obj;
  }

  Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "setCallback"), Napi::Function::New(env, Set));
    exports.Set(Napi::String::New(env, "releaseCallbacks"), Napi::Function::New(env, Release));
    exports.Set(Napi::String::New(env, "callbackTypes"), Napi::Function::New(env, GetCallbackTypes));
    return exports;
  }
}
