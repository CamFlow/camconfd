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
#include "provenanceutils.h"
#include "provenancefilter.h"
#include "ifclib.h"
#include "simplog.h"

#define CONFIG_PATH       "/etc/camflow.ini"
#define	LOG_FILE          "/tmp/camflow.clg"
#define MAX_BRIDGE        32 // arbitrary
#define MAX_TRUSTED       256 // arbitrary
#define MAX_OPAQUE        256 // arbitrary
#define MAX_TRACKED       256 // arbitrary
#define MAX_PROPAGATE     256 // arbitrary
#define MAX_FILTER        32 // filters are 32bits long for now

struct configuration{
  uint32_t machine_id;
  bool enabled;
  bool all;
  char bridge[MAX_BRIDGE][PATH_MAX];
  int nb_bridge;
  char trusted[MAX_BRIDGE][PATH_MAX];
  int nb_trusted;
  char opaque[MAX_OPAQUE][PATH_MAX];
  int nb_opaque;
  char tracked[MAX_TRACKED][PATH_MAX];
  int nb_tracked;
  char propagate[MAX_PROPAGATE][PATH_MAX];
  int nb_propagate;
  char node_filter[MAX_FILTER][PATH_MAX];
  int nb_node_filter;
  char relation_filter[MAX_FILTER][PATH_MAX];
  int nb_relation_filter;
  char propagate_node_filter[MAX_FILTER][PATH_MAX];
  int nb_propagate_node_filter;
  char propagate_relation_filter[MAX_FILTER][PATH_MAX];
  int nb_propagate_relation_filter;
};

#define ADD_TO_LIST(list, nb, max, error_msg) if(nb+1 >= max){ \
                                                simplog.writeLog(SIMPLOG_ERROR, error_msg); \
                                                exit(-1); \
                                              } \
                                              strncpy(list[nb], value, PATH_MAX); \
                                              nb++;

static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    struct configuration* pconfig = (struct configuration*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    #define TRUE(s) strcmp("true", s) == 0
    if(MATCH("provenance", "machine_id")) {
        pconfig->machine_id = atoi(value);
    } else if (MATCH("provenance", "enabled")) {
        if(TRUE(value)){
          pconfig->enabled = true;
        }else{
          pconfig->enabled = false;
        }
    } else if(MATCH("provenance", "all")) {
        if(TRUE(value)){
          pconfig->all = true;
        }else{
          pconfig->all = false;
        }
    } else if(MATCH("provenance", "opaque")){
      ADD_TO_LIST(pconfig->opaque, pconfig->nb_opaque, MAX_OPAQUE, "Too many opaque files.");
    } else if(MATCH("provenance", "tracked")){
      ADD_TO_LIST(pconfig->tracked, pconfig->nb_tracked, MAX_TRACKED, "Too many tracked files.");
    } else if(MATCH("provenance", "propagate")){
      ADD_TO_LIST(pconfig->propagate, pconfig->nb_propagate, MAX_PROPAGATE, "Too many propagate files.");
    }  else if(MATCH("provenance", "node_filter")){
      ADD_TO_LIST(pconfig->node_filter, pconfig->nb_node_filter, MAX_FILTER, "Too many entries for filter (max is 32).");
    }  else if(MATCH("provenance", "relation_filter")){
      ADD_TO_LIST(pconfig->relation_filter, pconfig->nb_relation_filter, MAX_FILTER, "Too many entries for filter (max is 32).");
    }   else if(MATCH("provenance", "propagate_node_filter")){
      ADD_TO_LIST(pconfig->propagate_node_filter, pconfig->nb_propagate_node_filter, MAX_FILTER, "Too many entries for filter (max is 32).");
    }  else if(MATCH("provenance", "propagate_relation_filter")){
      ADD_TO_LIST(pconfig->propagate_relation_filter, pconfig->nb_propagate_relation_filter, MAX_FILTER, "Too many entries for filter (max is 32).");
    } else if(MATCH("ifc", "bridge")){
      ADD_TO_LIST(pconfig->bridge, pconfig->nb_bridge, MAX_BRIDGE, "Too many IFC bridges.");
    } else if(MATCH("ifc", "trusted")){
      ADD_TO_LIST(pconfig->trusted, pconfig->nb_trusted, MAX_TRUSTED, "Too many IFC trusted.");
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

#define LOG_LIST(list, nb, msg) for(i = 0; i < nb; i++){ \
                                    simplog.writeLog(SIMPLOG_INFO, "%s=%s", msg, list[i]); \
                                  }

void print_config(struct configuration* pconfig){
  int i;

  /*
  * PRINT PROVENANCE CONFIGURATION
  */
  if(provenance_is_present()){
    simplog.writeLog(SIMPLOG_INFO, "Config loaded from '%s'", CONFIG_PATH);
    simplog.writeLog(SIMPLOG_INFO, "Provenance machine_id=%u", pconfig->machine_id);
    simplog.writeLog(SIMPLOG_INFO, "Provenance enabled=%u", pconfig->enabled);
    simplog.writeLog(SIMPLOG_INFO, "Provenance all=%u", pconfig->all);
    LOG_LIST(pconfig->opaque, pconfig->nb_opaque, "Provenance opaque=");
    LOG_LIST(pconfig->tracked, pconfig->nb_tracked, "Provenance tracked=");
    LOG_LIST(pconfig->propagate, pconfig->nb_propagate, "Provenance propagate=");
    LOG_LIST(pconfig->node_filter, pconfig->nb_node_filter, "Provenance node_filter=");
    LOG_LIST(pconfig->relation_filter, pconfig->nb_relation_filter, "Provenance relation_filer=");
    LOG_LIST(pconfig->propagate_node_filter, pconfig->nb_propagate_node_filter, "Provenance propagate_node_filter=");
    LOG_LIST(pconfig->propagate_relation_filter, pconfig->nb_propagate_relation_filter, "Provenance propagate_relation_filer=");
  }

  /*
  * PRINT IFC CONFIGURATION
  */

  if(ifc_is_present()){
    LOG_LIST(pconfig->bridge, pconfig->nb_bridge, "IFC bridge=");
    LOG_LIST(pconfig->trusted, pconfig->nb_trusted, "IFC trusted=");
  }
}

#define APPLY_LIST(list, nb, function, error_msg) for(i = 0; i < nb; i++){ \
                                                    err = function; \
                                                    if(err < 0){ \
                                                      simplog.writeLog(SIMPLOG_ERROR, "%s %s %d", error_msg, list[i], err); \
                                                      exit(-1); \
                                                    } \
                                                  }
void apply_config(struct configuration* pconfig){
  int err, i;
  simplog.writeLog(SIMPLOG_INFO, "Applying configuration...");
  if(pconfig->machine_id==0)
    pconfig->machine_id=gethostid();

  /*
  * APPLY PROVENANCE CONFIGURATION
  */
  if(provenance_is_present()){
    simplog.writeLog(SIMPLOG_INFO, "Provenance module presence detected.");
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

    APPLY_LIST(pconfig->opaque, pconfig->nb_opaque, provenance_opaque_file(pconfig->opaque[i], true), "Error making file opaque");

    APPLY_LIST(pconfig->tracked, pconfig->nb_tracked, provenance_track_file(pconfig->tracked[i], true), "Error making file tracked");

    APPLY_LIST(pconfig->propagate, pconfig->nb_propagate, provenance_propagate_file(pconfig->tracked[i], true), "Error making file tracked");

    APPLY_LIST(pconfig->node_filter, pconfig->nb_node_filter, provenance_add_node_filter(node_id(pconfig->node_filter[i])), "Error setting node filter");

    APPLY_LIST(pconfig->relation_filter, pconfig->nb_relation_filter, provenance_add_relation_filter(relation_id(pconfig->relation_filter[i])), "Error setting relation filrer");

    APPLY_LIST(pconfig->propagate_node_filter, pconfig->nb_propagate_node_filter, provenance_add_propagate_node_filter(node_id(pconfig->propagate_node_filter[i])), "Error setting propagate node filter");

    APPLY_LIST(pconfig->propagate_relation_filter, pconfig->nb_propagate_relation_filter, provenance_add_propagate_relation_filter(relation_id(pconfig->propagate_relation_filter[i])), "Error setting propagate relation filrer");
  }

  /*
  * APPLY IFC CONFIGURATION
  */
  if(ifc_is_present()){
    simplog.writeLog(SIMPLOG_INFO, "IFC module presence detected.");
    APPLY_LIST(pconfig->bridge, pconfig->nb_bridge, ifc_add_bridge(pconfig->bridge[i]), "Error adding IFC bridge");
    APPLY_LIST(pconfig->trusted, pconfig->nb_trusted, ifc_file_mark_as_trusted(pconfig->trusted[i], NULL), "Error adding IFC trusted");
  }
}

void _init_logs( void ){
  simplog.setLogFile(LOG_FILE);
  simplog.setLineWrap(false);
  simplog.setLogSilentMode(true);
  simplog.setLogDebugLevel(SIMPLOG_VERBOSE);
}

int main(int argc, char* argv[])
{
    struct configuration config;

    _init_logs();

    // set everything to 0
    memset(&config, 0, sizeof(struct configuration));

    if (ini_parse(CONFIG_PATH, handler, &config) < 0) {
        simplog.writeLog(SIMPLOG_ERROR, "Can't load '%s'", CONFIG_PATH);
        exit(-1);
    }

    apply_config(&config);
    print_config(&config);
    return 0;
}
