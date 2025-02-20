/*
 * MIT License
 *
 * Copyright (c) 2023 Davidson Francis <davidsondfgl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UTIL_H
#define UTIL_H

	#include <stdint.h>
	#include <stdio.h>
	#include <stdlib.h>

	/* Macros. */

	/*
	 * Expects a single char, and if match, increase the buffer
	 * and decrease the length.
	 */
	#define expect_char(c,buf,len) \
		do { \
			if ((c) != *(buf)) { \
				errw("Expected '%c', got '%c'\n", (c), *(buf)); \
				send_gdb_error(); \
				return (-1); \
			} \
			buf++; \
			len--; \
		} while(0)

	/*
	 * Expects a char range, and if match, increase the buffr
	 * and decreases the length.
	 */
	#define expect_char_range(c_start,c_end,buf,len) \
		do { \
			if (*(buf) < c_start || *(buf) > c_end) { \
				errw("Expected range %c-%c, got '%c'\n", \
					(c_start), (c_end), *(buf)); \
				send_gdb_error(); \
				return (-1); \
			} \
			buf++; \
			len--; \
		} while(0)

	/* Send a single byte to the serial device. */
	#define send_serial_byte(b) \
		do { \
			uint8_t byte = (b); \
			send_all(serial_fd, &byte, 1); \
		} while(0)

	/* Send a word (16-bit) to the serial device. */
	#define send_serial_word(w) \
		do { \
			uint16_t word = (w); \
			send_all(serial_fd, &word, 2); \
		} while(0)

	/* Send a double word (32-bit) to the serial device. */
	#define send_serial_dword(dw) \
		do { \
			uint32_t dword = (dw); \
			send_all(serial_fd, &dword, 4); \
		} while(0)

	/* Math macros. */
	#define ABS(N) (((N)<0)?(-(N)):(N))
	#define MIN(x, y) ((x) < (y) ? (x) : (y))

	/* Error and log macros. */
	#define errx(...) \
		do { \
			fprintf(stderr, __VA_ARGS__); \
			exit(1); \
		} while (0)

	#define errw(...) \
		do { \
			fprintf(stderr, __VA_ARGS__); \
			return 1; \
		} while (0)

#ifdef VERBOSE
	#define LOG_CMD_REC(...) \
		do { \
			fprintf(stderr, __VA_ARGS__); \
		} while (0)
#else
	#define LOG_CMD_REC
#endif

	extern char *encode_hex(const char *data, size_t len);
	extern char *decode_hex(const char *data, size_t len);
	extern uint32_t read_int(const char *buff, size_t *len,
		const char **endptr, int base);
	extern uint32_t simple_read_int(const char *buf, size_t len,
		int base);

#endif /* UTIL_H */
