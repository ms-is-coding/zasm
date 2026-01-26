#pragma once

#include "token.h"

typedef struct {
  const char       *name;
  const char       *data;
  const zasm_token *token;
} zasm_error;
