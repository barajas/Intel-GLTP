/*
 * Kernel Samepage Merging (KSM) for Memory Resource Controller and NUMA
 *
 * Basic tests were to start several programs with same and different
 * memory contents and ensure only to merge the ones with the same
 * contents. When changed the content of one of merged pages in a
 * process and to the mode "unmerging", it should discard all merged
 * pages there. Also tested it is possible to disable KSM. There are
 * also command-line options to specify the memory allocation size, and
 * number of processes have same memory contents so it is possible to
 * test more advanced things like KSM + OOM etc.
 *
 * Prerequisites:
 *
 * 1) ksm and ksmtuned daemons need to be disabled. Otherwise, it could
 *    distrub the testing as they also change some ksm tunables depends
 *    on current workloads.
 *
 * The test steps are:
 * - Check ksm feature and backup current run setting.
 * - Change run setting to 1 - merging.
 * - 3 memory allocation programs have the memory contents that 2 of
 *   them are all 'a' and one is all 'b'.
 * - Check ksm statistics and verify the content.
 * - 1 program changes the memory content from all 'a' to all 'b'.
 * - Check ksm statistics and verify the content.
 * - All programs change the memory content to all 'd'.
 * - Check ksm statistics and verify the content.
 * - Change one page of a process.
 * - Check ksm statistics and verify the content.
 * - Change run setting to 2 - unmerging.
 * - Check ksm statistics and verify the content.
 * - Change run setting to 0 - stop.
 *
 * Copyright (C) 2010  Red Hat, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Further, this software is distributed without any warranty that it
 * is free of the rightful claim of any third person regarding
 * infringement or the like.  Any license provided herein, whether
 * implied or otherwise, applies only to this software file.  Patent
 * licenses, if any, provided herein do not apply to combinations of
 * this program with other software, or any other product whatsoever.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include "test.h"
#include "usctest.h"
#include "config.h"

char *TCID = "ksm04";
int TST_TOTAL = 1;

#if HAVE_NUMA_H && HAVE_LINUX_MEMPOLICY_H && HAVE_NUMAIF_H \
	&& HAVE_MPOL_CONSTANTS
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <numaif.h>
#include "../include/mem.h"

option_t ksm_options[] = {
        { "n:", &opt_num,       &opt_numstr},
        { "s:", &opt_size,      &opt_sizestr},
        { "u:", &opt_unit,      &opt_unitstr},
        { NULL, NULL,           NULL}
};

int main(int argc, char *argv[])
{
	int lc;
	char *msg;
	int size = 128, num = 3, unit = 1;
	unsigned long nnodes = 1;
	unsigned long nmask = 2;

	msg = parse_opts(argc, argv, ksm_options, ksm_usage);
	if (msg != NULL)
		tst_brkm(TBROK, NULL, "OPTION PARSING ERROR - %s", msg);

	nnodes = count_numa();
	if (count_numa() == 1)
		tst_brkm(TCONF, NULL, "required a NUMA system.");

	setup();

	for (lc = 0; TEST_LOOPING(lc); lc++) {
		Tst_count = 0;
		check_ksm_options(&size, &num, &unit);

		write_memcg();

		if (set_mempolicy(MPOL_BIND, &nmask, MAXNODES) == -1)
			tst_brkm(TBROK|TERRNO, cleanup, "set_mempolicy");
		create_same_memory(size, num, unit);

		write_cpusets();
		create_same_memory(size, num, unit);
	}
	cleanup();
	tst_exit();
}

void cleanup(void)
{
	umount_mem(CPATH, CPATH_NEW);
	umount_mem(MEMCG_PATH, MEMCG_PATH_NEW);
	TEST_CLEANUP;
}

void setup(void)
{
	tst_require_root(NULL);

	tst_sig(FORK, DEF_HANDLER, cleanup);
	TEST_PAUSE;
	mount_mem("cpuset", "cpuset", NULL, CPATH, CPATH_NEW);
	mount_mem("memcg", "cgroup", "memory", MEMCG_PATH, MEMCG_PATH_NEW);
}

#else /* no NUMA */
int main(void)
{
	tst_resm(TCONF, "no NUMA development packages installed.");
	tst_exit();
}
#endif
