/*
* Copyright (c) 2004, Bull S.A..  All rights reserved.
* Created by: Sebastien Decugis

* This program is free software; you can redistribute it and/or modify it
* under the terms of version 2 of the GNU General Public License as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it would be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write the Free Software Foundation, Inc., 59
* Temple Place - Suite 330, Boston MA 02111-1307, USA.

* This sample test aims to check the following assertion:
*
* Memory mappings created in the parent are retained in the child process.
* If the mapping is MAP_PRIVATE, any modification done after the fork()
* is visible only to the process doing the modification.

* The steps are:
* -> create two shared memory segments.
* -> mmap both segment, one is MAP_SHARED and the other MAP_PRIVATE.
* -> Write some data into the segment.
* -> fork
* -> The child checks that the data is visible in the segments, then modifies it.
* -> child terminates
* -> The parent checks that the modifications are visible only in the MAP_SHARED segment.

* The test fails if one of the check is not verified.

*/

/* We are testing conformance to IEEE Std 1003.1, 2003 Edition */
#define _POSIX_C_SOURCE 200112L

/********************************************************************************************/
/****************************** standard includes *****************************************/
/********************************************************************************************/
#include <pthread.h>
 #include <stdarg.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>

#include <sys/wait.h>
 #include <errno.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
/********************************************************************************************/
/******************************   Test framework   *****************************************/
/********************************************************************************************/
#include "testfrmw.h"
 #include "testfrmw.c"
/* This header is responsible for defining the following macros:
 * UNRESOLVED(ret, descr);
 *    where descr is a description of the error and ret is an int (error code for example)
 * FAILED(descr);
 *    where descr is a short text saying why the test has failed.
 * PASSED();
 *    No parameter.
 *
 * Both three macros shall terminate the calling process.
 * The testcase shall not terminate in any other maneer.
 *
 * The other file defines the functions
 * void output_init()
 * void output(char * string, ...)
 *
 * Those may be used to output information.
 */

/********************************************************************************************/
/********************************** Configuration ******************************************/
/********************************************************************************************/
#ifndef VERBOSE
#define VERBOSE 1
#endif

/********************************************************************************************/
/***********************************    Test case   *****************************************/
/********************************************************************************************/
/* The main test function. */
int main(int argc, char * argv[])
{
	int ret, status;
	pid_t child, ctl;
	int fd_s, fd_ns;
	void *buf_s, *buf_ns;

	/* Initialize output */
	output_init();

	/* Create the shared memory segment */
	fd_s = shm_open("/fork_16_1s", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if (fd_s == -1)
	{
		UNRESOLVED(errno, "Failed to open shared memory segment");
	}

	fd_ns = shm_open("/fork_16_1ns", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if (fd_ns == -1)
	{
		UNRESOLVED(errno, "Failed to open shared memory segment");
	}

	/* Size the memory segment to 1 page size. */
	ret = ftruncate(fd_s, sysconf(_SC_PAGESIZE));

	if (ret != 0)
	{
		UNRESOLVED(errno, "Failed to size the shared memory segment");
	}

	ret = ftruncate(fd_ns, sysconf(_SC_PAGESIZE));

	if (ret != 0)
	{
		UNRESOLVED(errno, "Failed to size the shared memory segment");
	}

	/* Map these sengments in the process memory space */
	buf_s = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE, MAP_SHARED, fd_s, 0);

	if (buf_s == MAP_FAILED)
	{
		UNRESOLVED(errno, "Failed to mmap the shared memory segment");
	}

	buf_ns = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd_ns, 0);

	if (buf_ns == MAP_FAILED)
	{
		UNRESOLVED(errno, "Failed to mmap the shared memory segment in MAP_PRIVATE mode");
	}

	/* Write some data into the buffers */
	*(long *) buf_ns = 123456L;

	*(long *) buf_s = 654321L;

	/* Create the child */
	child = fork();

	if (child == -1)
	{
		UNRESOLVED(errno, "Failed to fork");
	}

	if (child == 0)
	{
		/* Check the values are read -- so that the mappings were inherited */

		if ((*(long *) buf_ns != 123456L) || (*(long *) buf_s != 654321L))
		{
			output("Read values: %ld, %ld\n", *(long *) buf_ns, *(long *) buf_s);
			FAILED("The memory mappings were not inherited by the child process");
		}

		/* Now modify the values */
		*(long *) buf_ns = 100000L;

		*(long *) buf_s = 200000L;

		/* We're done */
		exit(PTS_PASS);
	}

	/* Parent joins the child */
	ctl = waitpid(child, &status, 0);

	if (ctl != child)
	{
		UNRESOLVED(errno, "Waitpid returned the wrong PID");
	}

	if (!WIFEXITED(status) || (WEXITSTATUS(status) != PTS_PASS))
	{
		FAILED("Child exited abnormally");
	}

	/* Check that only the MAP_SHARED segment modification is visible */
	if ((*(long *) buf_ns != 123456L) || (*(long *) buf_s != 200000L))
	{
		output("Read values: %ld, %ld\n", *(long *) buf_ns, *(long *) buf_s);
		FAILED("The memory mappings were not inherited by the child process");
	}

	/* Free resources (everything will be removed at destruction time) */
	ret = shm_unlink("/fork_16_1ns");

	if (ret != 0)
	{
		UNRESOLVED(errno, "Failed to unlink the shared memory segment");
	}

	ret = shm_unlink("/fork_16_1s");

	if (ret != 0)
	{
		UNRESOLVED(errno, "Failed to unlink the shared memory segment");
	}

	/* Test passed */
#if VERBOSE > 0
	output("Test passed\n");

#endif
	PASSED;
}