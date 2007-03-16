/*
 * Dropbear SSH
 * 
 * Copyright (c) 2002,2003 Matt Johnston
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#include "includes.h"

/* definitions are cleanest if we just put them here */
int dropbear_main(int argc, char ** argv);
int dropbearkey_main(int argc, char ** argv);
int dropbearconvert_main(int argc, char ** argv);
int scp_main(int argc, char ** argv);

int main(int argc, char ** argv) {

	char * progname;

	if (argc > 0) {
		/* figure which form we're being called as */
		progname = basename(argv[0]);

#ifdef DBMULTI_dropbear
		if (strcmp(progname, "dropbear") == 0) {
			return dropbear_main(argc, argv);
		}
#endif
#ifdef DBMULTI_dbclient
		if (strcmp(progname, "dbclient") == 0
				|| strcmp(progname, "ssh") == 0) {
			return cli_main(argc, argv);
		}
#endif
#ifdef DBMULTI_dropbearkey
		if (strcmp(progname, "dropbearkey") == 0) {
			return dropbearkey_main(argc, argv);
		}
#endif
#ifdef DBMULTI_dropbearconvert
		if (strcmp(progname, "dropbearconvert") == 0) {
			return dropbearconvert_main(argc, argv);
		}
#endif
#ifdef DBMULTI_scp
		if (strcmp(progname, "scp") == 0 || strcmp(progname, "dbscp") == 0) {
			return scp_main(argc, argv);
		}
#endif
	}

	fprintf(stderr, "Dropbear multi-purpose version %s\n"
			"Make a symlink pointing at this binary with one of the following names:\n"
#ifdef DBMULTI_dropbear
			"'dropbear' - the Dropbear server\n"
#endif
#ifdef DBMULTI_dbclient
			"'dbclient' or 'ssh' - the Dropbear client\n"
#endif
#ifdef DBMULTI_dropbearkey
			"'dropbearkey' - the key generator\n"
#endif
#ifdef DBMULTI_dropbearconvert
			"'dropbearconvert' - the key converter\n"
#endif
#ifdef DBMULTI_scp
			"'scp' - secure copy\n"
#endif
			,
			DROPBEAR_VERSION);
	exit(1);

}
