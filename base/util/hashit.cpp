#include "hashit.h"

#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS

#include <winternl.h>
#include <ntstatus.h>
#include <bcrypt.h>
#include <sal.h>

#pragma comment(lib, "Bcrypt.lib")

namespace nbase {

bool hash(const wchar_t* pszAlgId, unsigned char* data, unsigned int len, unsigned char* hashed, unsigned int * hashed_len) {
	BCRYPT_ALG_HANDLE hAlg = NULL;
	BCRYPT_HASH_HANDLE hHash = NULL;
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	DWORD cbData = 0;
	DWORD cbHash = 0;
	DWORD cbHashObject = 0;
	PBYTE pbHashObject = NULL;
	PBYTE pbHash = NULL;

	//open an algorithm handle
	if (!NT_SUCCESS(status = BCryptOpenAlgorithmProvider(
		&hAlg,
		pszAlgId,
		NULL,
		0))) {
		goto Cleanup;
	}

	//calculate the size of the buffer to hold the hash object
	if (!NT_SUCCESS(status = BCryptGetProperty(
		hAlg,
		BCRYPT_OBJECT_LENGTH,
		(PBYTE)&cbHashObject,
		sizeof(DWORD),
		&cbData,
		0))) {
		goto Cleanup;
	}

	//allocate the hash object on the heap
	pbHashObject = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbHashObject);
	if (NULL == pbHashObject) {
		goto Cleanup;
	}

	//calculate the length of the hash
	if (!NT_SUCCESS(status = BCryptGetProperty(
		hAlg,
		BCRYPT_HASH_LENGTH,
		(PBYTE)&cbHash,
		sizeof(DWORD),
		&cbData,
		0))) {
		goto Cleanup;
	}

	//allocate the hash buffer on the heap
	pbHash = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbHash);
	if (NULL == pbHash) {
		goto Cleanup;
	}

	//create a hash
	if (!NT_SUCCESS(status = BCryptCreateHash(
		hAlg,
		&hHash,
		pbHashObject,
		cbHashObject,
		NULL,
		0,
		0))) {
		goto Cleanup;
	}

	//hash some data
	if (!NT_SUCCESS(status = BCryptHashData(
		hHash,
		(PBYTE)data,
		len,
		0))) {
		goto Cleanup;
	}

	//close the hash
	if (!NT_SUCCESS(status = BCryptFinishHash(
		hHash,
		pbHash,
		cbHash,
		0))) {
		goto Cleanup;
	}

	if(*hashed_len >= cbHash) {
		memcpy(hashed, pbHash, cbHash);		
		*hashed_len = cbHash;
	} else {
		status = STATUS_NO_MEMORY;
	}

Cleanup:

	if (hAlg) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
	}

	if (hHash) {
		BCryptDestroyHash(hHash);
	}

	if (pbHashObject) {
		HeapFree(GetProcessHeap(), 0, pbHashObject);
	}

	if (pbHash) {
		HeapFree(GetProcessHeap(), 0, pbHash);
	}

	if (!NT_SUCCESS(status)) {
		return false;
	}

	return true;
}

	
bool hash_sha256(unsigned char* data, unsigned len, unsigned char* hashed, unsigned* hashed_len)
{
	return hash(BCRYPT_SHA256_ALGORITHM, data, len, hashed, hashed_len);
}

bool hash_md5(unsigned char* data, unsigned len, unsigned char* hashed, unsigned* hashed_len)
{
	return hash(BCRYPT_MD5_ALGORITHM, data, len, hashed, hashed_len);
}
} // namespace nbase
