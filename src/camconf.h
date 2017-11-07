/*
*
* Author: Thomas Pasquier <tfjmp2@cam.ac.uk>
*
* Copyright (C) 2016-2017 University of Cambridge
* Copyright (C) 2017 Harvard University
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2, as
* published by the Free Software Foundation.
*
*/
#ifndef __CAMCONF_H
#define __CAMCONF_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <syslog.h>

#include "ini.h"
#include "provenance.h"
#include "provenanceutils.h"
#include "provenancefilter.h"

#define CONFIG_PATH       "/etc/camflow.ini"
#define APP_NAME          "camconfd"
#define MAX_PROPAGATE     256 // arbitrary
#define MAX_FILTER        256 // arbitrary
#define MAX_IP_SIZE       256 // arbitrary
#define MAX_NAME          256

#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)
#define TRUE(s) (strcmp("true", s) == 0)

#define declare_filter(name, size) char name[MAX_FILTER][size]; size_t nb_ ## name

#endif
