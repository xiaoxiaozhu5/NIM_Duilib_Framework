#ifndef BASE_UTIL_HASHIT_H_
#define BASE_UTIL_HASHIT_H_

#include "base/base_export.h"

namespace nbase
{
	BASE_EXPORT bool hash(const wchar_t* pszAlgId, unsigned char* data, unsigned int len, unsigned char* hashed, unsigned int * hashed_len);
	BASE_EXPORT bool hash_sha256(unsigned char* data, unsigned int len, unsigned char* hashed, unsigned int * hashed_len);
	BASE_EXPORT bool hash_md5(unsigned char* data, unsigned int len, unsigned char* hashed, unsigned int * hashed_len);
}  // namespace nbase

#endif  // BASE_UTIL_HASHIT_H_
