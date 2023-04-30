#include <napi.h>
extern "C" {
  #include "lightdm.h"
}
namespace Sessions {  
  Napi::Value Get(const Napi::CallbackInfo& info);
}