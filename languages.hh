#include <napi.h>
extern "C" {
  #include "lightdm.h"
}
namespace Languages {
  Napi::Value Get(const Napi::CallbackInfo& info);
}
