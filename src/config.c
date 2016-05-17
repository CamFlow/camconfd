/*
*
* provenancelib.c
*
* Author: Thomas Pasquier <tfjmp2@cam.ac.uk>
*
* Copyright (C) 2015 University of Cambridge
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

typedef struct{
  uint32_t machine_id;
} configuration;

static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    configuration* pconfig = (configuration*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("provenance", "machine_id")) {
        pconfig->machine_id = atoi(value);
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

#define CONFIG_PATH "/etc/camflow/camflow.ini"

int main(int argc, char* argv[])
{
    configuration config;

    if (ini_parse(CONFIG_PATH, handler, &config) < 0) {
        printf("Can't load '%s'\n", CONFIG_PATH);
        return 1;
    }
    printf("Config loaded from '%s': machine_id=%d\n",
        CONFIG_PATH, config.machine_id);
    return 0;
}
