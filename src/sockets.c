#include "sockets.h"

#include <sys/socket.h>

THROWS  err_t safe_sendto(fd_t sd, const void *const buf, size_t size, int flags, const struct sockaddr *destAddr,
								socklen_t addrlen, ssize_t *bytesWritten)
{
	err_t err = NO_ERRORCODE;
	ssize_t tempBytesWritten = 0;

	QUITE_CHECK(IS_VALID_FD(sd));
	QUITE_CHECK(destAddr != NULL);
	QUITE_CHECK(bytesWritten != NULL);
	QUITE_CHECK(buf != NULL);

	tempBytesWritten = sendto(sd.fd, buf, size, flags, destAddr, addrlen);
	QUITE_CHECK(tempBytesWritten != -1);

cleanup:
	*bytesWritten = tempBytesWritten;
	return err;
}

THROWS  err_t create_socket(int domain, int type, int protocal, fd_t *sd)
{
	err_t err = NO_ERRORCODE;
	QUITE_CHECK(sd != NULL);
	QUITE_CHECK(IS_INVALID_FD(*sd));

	sd->fd = socket(domain, type, protocal);
	QUITE_CHECK(IS_VALID_FD(*sd));

cleanup:
	return err;
}

THROWS  err_t safe_bind(fd_t sd, const struct sockaddr *const addr, socklen_t addrlen)
{
	err_t err = NO_ERRORCODE;
	QUITE_CHECK(IS_VALID_FD(sd));
	QUITE_CHECK(addr != NULL);

	CHECK(bind(sd.fd, addr, addrlen) == 0);
cleanup:
	return err;
}
