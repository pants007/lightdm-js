#include "users.hh"

namespace Users {
  Napi::Value Get(const Napi::CallbackInfo& info) {
    LightDMUserList *userlist = lightdm_user_list_get_instance();
    GList *users = lightdm_user_list_get_users(userlist);
    Napi::Array user_array = Napi::Array::New(info.Env());
    int i = 0;
    while (users != nullptr) {
      LightDMUser *user = (LightDMUser*)users->data;
      Napi::Object obj = Napi::Object::New(info.Env());
      obj.Set("name", Napi::String::New(info.Env(), lightdm_user_get_name(user)));
      obj.Set("real_name", Napi::String::New(info.Env(), lightdm_user_get_real_name(user)));
      obj.Set("display_name", Napi::String::New(info.Env(), lightdm_user_get_display_name(user)));
      obj.Set("home_directory", Napi::String::New(info.Env(), lightdm_user_get_home_directory(user)));
      const gchar *image = lightdm_user_get_image(user);
      if (image == nullptr) {
        obj.Set("image", Napi::String::New(info.Env(), ""));
      } else {
        obj.Set("image", Napi::String::New(info.Env(), image));
      }
      const gchar *background = lightdm_user_get_background(user);
      if (background == nullptr) {
        obj.Set("background", Napi::String::New(info.Env(), ""));
      } else {
        obj.Set("background", Napi::String::New(info.Env(), background));
      }
      const gchar *language = lightdm_user_get_language(user);
      if (language == nullptr) {
        obj.Set("language", Napi::String::New(info.Env(), ""));
      } else {
        obj.Set("language", Napi::String::New(info.Env(), language));
      }
      const gchar *layout = lightdm_user_get_layout(user);
      if (layout == nullptr) {
        obj.Set("layout", Napi::String::New(info.Env(), ""));
      } else {
        obj.Set("layout", Napi::String::New(info.Env(), layout));
      }
      const gchar *session = lightdm_user_get_session(user);
      if (session == nullptr) {
        obj.Set("session", Napi::String::New(info.Env(), ""));
      } else {
        obj.Set("session", Napi::String::New(info.Env(), session));
      }
      obj.Set("logged_in", Napi::Boolean::New(info.Env(), lightdm_user_get_logged_in(user)));
      obj.Set("has_messages", Napi::Boolean::New(info.Env(), lightdm_user_get_has_messages(user)));
      obj.Set("uid", Napi::Number::New(info.Env(), lightdm_user_get_uid(user)));
      user_array[i] = obj;
      i++;
      users = users->next;
    }
    return user_array;
  }
  Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "getUsers"), Napi::Function::New(env, Get));
    return exports;
  }
  
}
