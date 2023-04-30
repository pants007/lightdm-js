#include "languages.hh"

namespace Languages {
  
  Napi::Value Get(const Napi::CallbackInfo& info) {
    GList *languages = lightdm_get_languages();
    Napi::Array lang_array = Napi::Array::New(info.Env());
    int i = 0;
    while (languages != nullptr) {
      LightDMLanguage *language = (LightDMLanguage*)languages->data;

      Napi::Object obj = Napi::Object::New(info.Env());
      obj.Set("code", lightdm_language_get_code(language));
      obj.Set("name", lightdm_language_get_name(language));
      obj.Set("territory", lightdm_language_get_territory(language));
      lang_array[i] = obj;
      i++;
      languages = languages->next;
    }
    return lang_array;
  }
}
