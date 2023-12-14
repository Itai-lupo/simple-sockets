#pragma once

#include "types/err_t.h"
#include "types/fd_t.h"

#include <sys/socket.h>

#ifdef __cplusplus
extern "C"
{
#endif
	/**
	 * @brief
	 *
	 * @param sd the socket descriptor to send to
	 * @param buf the buffer to send
	 * @param size the size of the buffer
	 * @param flags the flags to send with
	 * @param destAddr the address to send t o
	 * @param addrlen the address length
	 * @param bytesWritten how many bytes were were send, should be the same as size on full send
	 * @return err_t err_t if there was an error in sendto or in one of the parms
	 * @see https://man7.org/linux/man-pages/man2/sendto.2.html
	 *
	 */
	THROWS err_t safeSendto(fd_t sd, const void *const buf, size_t size, int flags, const struct sockaddr *destAddr,
							socklen_t addrlen, ssize_t *bytesWritten);

	/**
	 * @brief create a new socket descriptor
	 *
	 * @param domain the protocol family which will be used for communication.
	 * @param type the communication semantics and flags to modify the behavior of the socket.
	 * @param protocal a particular protocol to be used with the socket, can be 0 if there is only one option.
	 * @param sd the resulted socket descriptor
	 * @return err_t if there was an error while creating the socket or in one of the parms
	 *
	 * @see https://man7.org/linux/man-pages/man2/socket.2.html
	 * @see https://man7.org/linux/man-pages/man7/address_families.7.html
	 * @see https://man7.org/linux/man-pages/man5/protocols.5.html
	 */
	THROWS err_t createSocket(int domain, int type, int protocal, fd_t *sd);

	/**
	 * @brief bind sd to addr
	 *
	 * @param sd the file descriptor of the socket to bind
	 * @param addr the address to bind to
	 * @param addrlen the length of the address
	 * @return err_t if there was an error while binding or in one of the parms
	 *
	 * @see https://man7.org/linux/man-pages/man2/bind.2.html
	 */
	THROWS err_t safeBind(fd_t sd, const struct sockaddr *const addr, socklen_t addrlen);

#ifdef __cplusplus
}
#endif
