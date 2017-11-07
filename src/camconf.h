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

#define xstr(s) str(s)
#define str(s) #s

#define CONFIG_PATH       "/etc/camflow.ini"
#define APP_NAME          "camconfd"
#define MAX_PROPAGATE     256 // arbitrary
#define MAX_FILTER        256 // arbitrary
#define MAX_IP_SIZE       256 // arbitrary
#define MAX_NAME          256

#define CAMFLOW_MACHINE_ID_FILE "/etc/camflow-machine_id"
#define CAMFLOW_BOOT_ID_FILE "/etc/camflow-boot_id"

#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)
#define TRUE(s) (strcmp("true", s) == 0)

#define declare_filter(name, size) char name[MAX_FILTER][size]; size_t nb_ ## name



#define ADD_TO_LIST(name) if(pconfig->nb_ ## name +1 >= MAX_FILTER){ \
                            syslog(LOG_ERR, "Too many entries for" str(name) "(max is " xstr(MAX_FILTER) ")."); \
                            exit(-1); \
                          } \
                          strncpy(pconfig->name[ pconfig->nb_ ## name ], value, PATH_MAX); \
                          pconfig->nb_ ## name ++;

#define LOG_LIST(name)  for(i = 0; i < pconfig->nb_ ## name; i++){ \
                          syslog(LOG_INFO, "CamFlow " str(name) "=%s", pconfig->name[i]); \
                        }

#define APPLY_LIST(name, function) for(i = 0; i < pconfig->nb_ ## name; i++){ \
                                                    int err = function; \
                                                    if(err < 0){ \
                                                      syslog(LOG_ERR, "Error setting" str(name) " = %s (%d).", pconfig->name[i], err); \
                                                      exit(-1);\
                                                    } \
                                                  }

#endif
