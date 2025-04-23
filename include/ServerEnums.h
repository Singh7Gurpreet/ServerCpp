#pragma once

enum ServerType {
  HTTP,
  HTTPS
};

enum ServerFlags {
  NONE            = 0,
  SECURE          = 1 << 0,  // 1
  TLS             = 1 << 1,  // 2
  MULTITHREADED   = 1 << 2,  // 4
  SINGLETHREADED  = 1 << 3,  // 8
  LOGGING_ENABLED = 1 << 4,  // 16
  CACHING_ENABLED = 1 << 5   // 32
};