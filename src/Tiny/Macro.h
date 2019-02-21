#pragma once

#define DEF_INSTANCE(class) \
  static class& Instance(){\
    static class _inst;\
    return _inst;\
  }
