#ifndef BASE_UTIL_HASHIT_H_
#define BASE_UTIL_HASHIT_H_

#include "base/base_export.h"

namespace nbase
{
	BASE_EXPORT bool hash(unsigned char* data, unsigned int len, unsigned char* hashed, unsigned int * hashed_len);
}  // namespace nbase

#endif  // BASE_UTIL_HASHIT_H_
