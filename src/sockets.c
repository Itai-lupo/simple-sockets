#include "sockets.h"

#include "defaultTrace.h"
#include "err.h"
#include <sys/socket.h>

/**
 * @brief how many times the io opreations will retry to handle EINTR or EAGAIN
 * @see safeSendto
 */
#define NAX_IO_RETRIES 3

THROWS err_t safeSendto(fd_t sd, const void *const buf, size_t size, int flags, const struct sockaddr *destAddr,
						socklen_t addrlen, ssize_t *bytesWritten)
{
	err_t err = NO_ERRORCODE;
	ssize_t tempBytesWritten = -1;
	errno = 0;

	QUITE_CHECK(IS_VALID_FD(sd));
	QUITE_CHECK(destAddr != NULL);
	QUITE_CHECK(bytesWritten != NULL);
	QUITE_CHECK(buf != NULL);

	for (size_t i = 0; i < NAX_IO_RETRIES && tempBytesWritten == -1; i++)
	{
		tempBytesWritten = sendto(sd.fd, buf, size, flags, destAddr, addrlen);
		QUITE_CHECK(tempBytesWritten != -1 || EINTR || EAGAIN || EWOULDBLOCK);
	}

	QUITE_CHECK(tempBytesWritten != -1);

cleanup:
	errno = 0;
	*bytesWritten = tempBytesWritten;
	return err;
}

THROWS err_t createSocket(int domain, int type, int protocal, fd_t *sd)
{
	err_t err = NO_ERRORCODE;
	errno = 0;

	QUITE_CHECK(sd != NULL);
	QUITE_CHECK(IS_INVALID_FD(*sd));
	sd->fd = socket(domain, type, protocal);
	QUITE_CHECK(IS_VALID_FD(*sd));

cleanup:
	errno = 0;
	return err;
}

THROWS err_t safeBind(fd_t sd, const struct sockaddr *const addr, socklen_t addrlen)
{
	err_t err = NO_ERRORCODE;
	errno = 0;

	QUITE_CHECK(IS_VALID_FD(sd));
	QUITE_CHECK(addr != NULL);

	CHECK(bind(sd.fd, addr, addrlen) == 0);
	errno = 0;
cleanup:
	return err;
}
