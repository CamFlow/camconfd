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
#include "../inih/ini.h"

#define bool  uint8_t
#define true  1
#define false 0

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

#define CONFIG_PATH "camflow.ini"

int main(int argc, char* argv[])
{
    configuration config;

    // set everything to 0
    memset(&config, 0, sizeof(configuration));

    if (ini_parse(CONFIG_PATH, handler, &config) < 0) {
        printf("Can't load '%s'\n", CONFIG_PATH);
        return 1;
    }
    printf("Config loaded from '%s'\n", CONFIG_PATH);
    printf("Provenance machine_id=%u\n", config.machine_id);
    printf("Provenance enabled=%u\n", config.enabled);
    printf("Provenance all=%u\n", config.all);
    return 0;
}
