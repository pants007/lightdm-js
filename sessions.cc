#include "sessions.hh"
namespace Sessions {  
  Napi::Value Get(const Napi::CallbackInfo& info) {
    GList *sessions = lightdm_get_sessions();
    Napi::Array session_array = Napi::Array::New(info.Env());
    int i = 0;
    while (sessions != nullptr) {
      LightDMSession *session = (LightDMSession*)sessions->data;
      Napi::Object obj = Napi::Object::New(info.Env());
      obj.Set("key", lightdm_session_get_key(session));
      obj.Set("session_type", lightdm_session_get_session_type(session));
      obj.Set("name", lightdm_session_get_name(session));
      obj.Set("comment", lightdm_session_get_comment(session));
      session_array[i] = obj;
      i++;
      sessions = sessions->next;
    }
    return session_array;
  }
  Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "getSessions"), Napi::Function::New(env, Get));
    return exports;
  }
}