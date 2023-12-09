#pragma once

#include "files.h"

#include "defines/errType.h"
#include <sys/socket.h>

#ifdef __cplusplus
extern "C"
{
#endif

	THROWS err_t safe_sendto(fd_t sd, const void *const buf, size_t size, int flags, const struct sockaddr *destAddr,
							 socklen_t addrlen, ssize_t *bytesWritten);

	THROWS err_t create_socket(int domain, int type, int protocal, fd_t *sd);

	THROWS err_t safe_bind(fd_t sd, const struct sockaddr *const addr, socklen_t addrlen);


#ifdef __cplusplus
}
#endif
