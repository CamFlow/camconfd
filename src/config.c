/*
*
* provenancelib.c
*
* Author: Thomas Pasquier <tfjmp2@cam.ac.uk>
*
* Copyright (C) 2016 University of Cambridge
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2, as
* published by the Free Software Foundation.
*
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ini.h"
#include "provenancelib.h"
#include "ifclib.h"
#include "simplog.h"

#define CONFIG_PATH "/etc/camflow.ini"
#define	LOG_FILE "/tmp/camflow.clg"

typedef struct{
  uint32_t machine_id;
  bool enabled;
  bool all;
} configuration;

static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    configuration* pconfig = (configuration*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    #define TRUE(s) strcmp("true", s) == 0
    if (MATCH("provenance", "machine_id")) {
        pconfig->machine_id = atoi(value);
    } else if (MATCH("provenance", "enabled")) {
        if(TRUE(value)){
          pconfig->enabled = true;
        }else{
          pconfig->enabled = false;
        }
    } else if (MATCH("provenance", "all")) {
        if(TRUE(value)){
          pconfig->all = true;
        }else{
          pconfig->all = false;
        }
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

void print_config(configuration* pconfig){
  simplog.writeLog(SIMPLOG_INFO, "Config loaded from '%s'", CONFIG_PATH);
  simplog.writeLog(SIMPLOG_INFO, "Provenance machine_id=%u", pconfig->machine_id);
  simplog.writeLog(SIMPLOG_INFO, "Provenance enabled=%u", pconfig->enabled);
  simplog.writeLog(SIMPLOG_INFO, "Provenance all=%u", pconfig->all);
}

void apply_config(configuration* pconfig){
  int err;
  simplog.writeLog(SIMPLOG_INFO, "Applying configuration...");
  if(pconfig->machine_id==0)
    pconfig->machine_id=gethostid();

  if(err = provenance_set_machine_id(pconfig->machine_id)){
    simplog.writeLog(SIMPLOG_ERROR, "Error setting machine ID %d", err);
    exit(-1);
  }

  if(err = provenance_set_enable(pconfig->enabled)){
    simplog.writeLog(SIMPLOG_ERROR, "Error enabling provenance %d", err);
    exit(-1);
  }

  if(err = provenance_set_all(pconfig->all)){
    simplog.writeLog(SIMPLOG_ERROR, "Error with all provenance %d", err);
    exit(-1);
  }
}

void _init_logs( void ){
  simplog.setLogFile(LOG_FILE);
  simplog.setLineWrap(false);
  //simplog.setLogSilentMode(true);
  //simplog.setLogDebugLevel(SIMPLOG_VERBOSE);
}

int main(int argc, char* argv[])
{
    configuration config;

    _init_logs();

    // set everything to 0
    memset(&config, 0, sizeof(configuration));

    if (ini_parse(CONFIG_PATH, handler, &config) < 0) {
        simplog.writeLog(SIMPLOG_ERROR, "Can't load '%s'", CONFIG_PATH);
        return 1;
    }

    apply_config(&config);
    print_config(&config);
    return 0;
}
