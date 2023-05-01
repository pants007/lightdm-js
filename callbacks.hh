#include <napi.h>
#include <glib.h>

namespace Callbacks {
  struct ShowPromptData{
    char *text;
    int type;
  };
  struct ShowMessageData{
    char *text;
    int type;
  };
  struct AuthenticationCompleteData{};
  struct AutologinTimerExpiredData{};
  struct IdleData{};
  struct ResetData{};

  extern Napi::ThreadSafeFunction showPromptCallback;
  extern Napi::ThreadSafeFunction showMessageCallback;
  extern Napi::ThreadSafeFunction authenticationCompleteCallback;
  extern Napi::ThreadSafeFunction autologinTimerExpiredCallback;
  extern Napi::ThreadSafeFunction idleCallback;
  extern Napi::ThreadSafeFunction resetCallback;

  void ShowPromptSetup(Napi::Env env, Napi::Function jsCallback, ShowPromptData *data);
  void ShowPrompt(GObject *gobj, char *text, int type);
  void ShowMessageSetup(Napi::Env env, Napi::Function jsCallback, ShowMessageData *data);
  void ShowMessage(GObject *gobj, char *text, int type);
  void AuthenticationCompleteSetup(Napi::Env env, Napi::Function jsCallback, AuthenticationCompleteData *data);
  void AuthenticationComplete(GObject *gobj);
  void AutologinTimerExpiredSetup(Napi::Env env, Napi::Function jsCallback, AutologinTimerExpiredData *data);
  void AutologinTimerExpired(GObject *gobj);
  void IdleSetup(Napi::Env env, Napi::Function jsCallback, IdleData *data);
  void Idle(GObject *gobj);
  void ResetSetup(Napi::Env env, Napi::Function jsCallback, ResetData *data);
  void Reset(GObject *gobj);

  Napi::Value Set(const Napi::CallbackInfo& info);

  Napi::Value Release(const Napi::CallbackInfo& info);

  Napi::Value GetCallbackTypes(const Napi::CallbackInfo& info);

  Napi::Object GEnumToJS(const char *name, Napi::Object obj);

  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
