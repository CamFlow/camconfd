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
#include <time.h>
#include <syslog.h>

#include "ini.h"
#include "provenancelib.h"
#include "provenanceutils.h"
#include "provenancefilter.h"

#define CONFIG_PATH       "/etc/camflow.ini"
#define APP_NAME          "camconfd"
#define MAX_BRIDGE        32 // arbitrary
#define MAX_TRUSTED       256 // arbitrary
#define MAX_OPAQUE        256 // arbitrary
#define MAX_TRACKED       256 // arbitrary
#define MAX_PROPAGATE     256 // arbitrary
#define MAX_FILTER        256 // filters are 32bits long for now
#define MAX_IP_FILTER     256 // filters are 32bits long for now

struct configuration{
  uint32_t machine_id;
  uint32_t boot_id;
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
  char track_ipv4_ingress_filter[MAX_FILTER][MAX_IP_FILTER];
  int nb_track_ipv4_ingress_filter;
  char propagate_ipv4_ingress_filter[MAX_FILTER][MAX_IP_FILTER];
  int nb_propagate_ipv4_ingress_filter;
  char record_ipv4_ingress_filter[MAX_FILTER][MAX_IP_FILTER];
  int nb_record_ipv4_ingress_filter;
  char track_ipv4_egress_filter[MAX_FILTER][MAX_IP_FILTER];
  int nb_track_ipv4_egress_filter;
  char propagate_ipv4_egress_filter[MAX_FILTER][MAX_IP_FILTER];
  int nb_propagate_ipv4_egress_filter;
  char record_ipv4_egress_filter[MAX_FILTER][MAX_IP_FILTER];
  int nb_record_ipv4_egress_filter;
};

#define ADD_TO_LIST(list, nb, max, error_msg) if(nb+1 >= max){ \
                                                syslog(LOG_ERR, error_msg); \
                                                exit(-1); \
                                              } \
                                              strncpy(list[nb], value, PATH_MAX); \
                                              nb++;

#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)
#define TRUE(s) (strcmp("true", s) == 0)

static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    struct configuration* pconfig = (struct configuration*)user;

    if(MATCH("provenance", "machine_id")) {
        pconfig->machine_id = atoi(value);
    } else if (MATCH("provenance", "enabled")) {
        if(TRUE(value))
          pconfig->enabled = true;
        else
          pconfig->enabled = false;
    } else if(MATCH("provenance", "all")) {
        if(TRUE(value))
          pconfig->all = true;
        else
          pconfig->all = false;
    } else if(MATCH("provenance", "opaque")){
      ADD_TO_LIST(pconfig->opaque, pconfig->nb_opaque, MAX_OPAQUE, "Too many opaque files.");
    } else if(MATCH("provenance", "track")){
      ADD_TO_LIST(pconfig->tracked, pconfig->nb_tracked, MAX_TRACKED, "Too many tracked files.");
    } else if(MATCH("provenance", "propagate")){
      ADD_TO_LIST(pconfig->propagate, pconfig->nb_propagate, MAX_PROPAGATE, "Too many propagate files.");
    } else if(MATCH("provenance", "node_filter")){
      ADD_TO_LIST(pconfig->node_filter, pconfig->nb_node_filter, MAX_FILTER, "Too many entries for filter (max is 32).");
    } else if(MATCH("provenance", "relation_filter")){
      ADD_TO_LIST(pconfig->relation_filter, pconfig->nb_relation_filter, MAX_FILTER, "Too many entries for filter (max is 32).");
    } else if(MATCH("provenance", "propagate_node_filter")){
      ADD_TO_LIST(pconfig->propagate_node_filter, pconfig->nb_propagate_node_filter, MAX_FILTER, "Too many entries for filter (max is 32).");
    } else if(MATCH("provenance", "propagate_relation_filter")){
      ADD_TO_LIST(pconfig->propagate_relation_filter, pconfig->nb_propagate_relation_filter, MAX_FILTER, "Too many entries for filter (max is 32).");
    } else if(MATCH("ipv4−ingress", "track")){
      ADD_TO_LIST(pconfig->track_ipv4_ingress_filter, pconfig->nb_track_ipv4_ingress_filter, MAX_FILTER, "Too many filters ipv4 track ingress.");
    } else if(MATCH("ipv4−ingress", "propagate")){
      ADD_TO_LIST(pconfig->propagate_ipv4_ingress_filter, pconfig->nb_propagate_ipv4_ingress_filter, MAX_FILTER, "Too many filters ipv4 propagate ingress.");
    } else if(MATCH("ipv4−ingress", "record")){
      ADD_TO_LIST(pconfig->record_ipv4_ingress_filter, pconfig->nb_record_ipv4_ingress_filter, MAX_FILTER, "Too many filters ipv4 record ingress.");
    } else if(MATCH("ipv4−egress", "track")){
      ADD_TO_LIST(pconfig->track_ipv4_egress_filter, pconfig->nb_track_ipv4_egress_filter, MAX_FILTER, "Too many filters ipv4 track egress.");
    } else if(MATCH("ipv4−egress", "propagate")){
      ADD_TO_LIST(pconfig->propagate_ipv4_egress_filter, pconfig->nb_propagate_ipv4_egress_filter, MAX_FILTER, "Too many filters ipv4 propagate egress.");
    } else if(MATCH("ipv4−egress", "record")){
      ADD_TO_LIST(pconfig->record_ipv4_egress_filter, pconfig->nb_record_ipv4_egress_filter, MAX_FILTER, "Too many filters ipv4 record egress.");
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

#define LOG_LIST(list, nb, msg) for(i = 0; i < nb; i++){ \
                                    syslog(LOG_INFO, "%s=%s", msg, list[i]); \
                                  }

void print_config(struct configuration* pconfig){
  int i;

  /*
  * PRINT PROVENANCE CONFIGURATION
  */
  if(provenance_is_present()){
    syslog(LOG_INFO, "Config loaded from '%s'", CONFIG_PATH);
    syslog(LOG_INFO, "Provenance machine_id=%u", pconfig->machine_id);
    syslog(LOG_INFO, "Provenance boot_id=%u", pconfig->boot_id);
    syslog(LOG_INFO, "Provenance enabled=%u", pconfig->enabled);
    syslog(LOG_INFO, "Provenance all=%u", pconfig->all);
    LOG_LIST(pconfig->opaque, pconfig->nb_opaque, "Provenance opaque=");
    LOG_LIST(pconfig->tracked, pconfig->nb_tracked, "Provenance track=");
    LOG_LIST(pconfig->propagate, pconfig->nb_propagate, "Provenance propagate=");
    LOG_LIST(pconfig->node_filter, pconfig->nb_node_filter, "Provenance node_filter=");
    LOG_LIST(pconfig->relation_filter, pconfig->nb_relation_filter, "Provenance relation_filer=");
    LOG_LIST(pconfig->propagate_node_filter, pconfig->nb_propagate_node_filter, "Provenance propagate_node_filter=");
    LOG_LIST(pconfig->propagate_relation_filter, pconfig->nb_propagate_relation_filter, "Provenance propagate_relation_filer=");
    LOG_LIST(pconfig->track_ipv4_ingress_filter, pconfig->nb_track_ipv4_ingress_filter, "Provenance track_ipv4_ingress_filter=");
    LOG_LIST(pconfig->propagate_ipv4_ingress_filter, pconfig->nb_propagate_ipv4_ingress_filter, "Provenance propagate_ipv4_ingress_filter=");
    LOG_LIST(pconfig->record_ipv4_ingress_filter, pconfig->nb_record_ipv4_ingress_filter, "Provenance record_ipv4_ingress_filter=");
    LOG_LIST(pconfig->track_ipv4_egress_filter, pconfig->nb_track_ipv4_egress_filter, "Provenance track_ipv4_egress_filter=");
    LOG_LIST(pconfig->propagate_ipv4_egress_filter, pconfig->nb_propagate_ipv4_egress_filter, "Provenance propagate_ipv4_egress_filter=");
    LOG_LIST(pconfig->record_ipv4_egress_filter, pconfig->nb_record_ipv4_egress_filter, "Provenance record_ipv4_egress_filter=");
  }
}

#define CAMFLOW_MACHINE_ID_FILE "/etc/camflow-machine_id"
uint32_t get_machine_id(void){
  FILE *fptr;
  uint32_t machine_id;
  int rc;

  fptr = fopen(CAMFLOW_MACHINE_ID_FILE, "rb+");
  if(!fptr) //if file does not exist, create it
  {
      fptr = fopen(CAMFLOW_MACHINE_ID_FILE, "wb");
      if(!fptr){
        syslog(LOG_ERR, "Failed opening machine ID file.");
        exit(-1);
      }
      srand(time(NULL)+gethostid());
      machine_id = rand();
      fwrite(&machine_id, sizeof(uint32_t), 1, fptr);
  }else{
    rc = fread(&machine_id, sizeof(uint32_t), 1, fptr);
    if(rc<0 && ferror(fptr))
        return rc;
  }
  if(fptr)
    fclose(fptr);
  return machine_id;
}

#define CAMFLOW_BOOT_ID_FILE "/etc/camflow-boot_id"
uint32_t get_boot_id(void){
  FILE *fptr;
  uint32_t boot_id=0;
  int rc;

  fptr = fopen(CAMFLOW_BOOT_ID_FILE, "rb+");
  if(!fptr) //if file does not exist, create it
  {
      fptr = fopen(CAMFLOW_BOOT_ID_FILE, "wb");
      if(!fptr){
        syslog(LOG_ERR, "Failed opening machine ID file.");
        exit(-1);
      }
      fwrite(&boot_id, sizeof(uint32_t), 1, fptr);
  }else{
    rc = fread(&boot_id, sizeof(uint32_t), 1, fptr);
    if(rc<0 && ferror(fptr))
        return rc;
    boot_id+=1;
    fseek(fptr, 0, SEEK_SET);
    fwrite(&boot_id, sizeof(uint32_t), 1, fptr);
  }
  if(fptr)
    fclose(fptr);
  return boot_id;
}

#define APPLY_LIST(list, nb, function, error_msg) for(i = 0; i < nb; i++){ \
                                                    int err = function; \
                                                    if(err < 0){ \
                                                      syslog(LOG_INFO, "%s %s %d", error_msg, list[i], err); \
                                                      exit(-1);\
                                                    } \
                                                  }

void apply_config(struct configuration* pconfig){
  int err;
  int i;
  syslog(LOG_INFO, "Applying configuration...");

  /*
  * APPLY PROVENANCE CONFIGURATION
  */
  if(provenance_is_present()){
    syslog(LOG_INFO, "Provenance module presence detected.");
    if(pconfig->machine_id==0)
      pconfig->machine_id=get_machine_id();
    if(err = provenance_set_machine_id(pconfig->machine_id)){
      syslog(LOG_ERR, "Error setting machine ID %d", err);
      exit(-1);
    }
    pconfig->boot_id=get_boot_id();
    if(err = provenance_set_boot_id(pconfig->boot_id)){
      syslog(LOG_ERR, "Error setting boot ID %d", err);
      exit(-1);
    }

    APPLY_LIST(pconfig->opaque, pconfig->nb_opaque, provenance_opaque_file(pconfig->opaque[i], true), "Error making file opaque");

    APPLY_LIST(pconfig->tracked, pconfig->nb_tracked, provenance_track_file(pconfig->tracked[i], true), "Error making file tracked");

    APPLY_LIST(pconfig->propagate, pconfig->nb_propagate, provenance_propagate_file(pconfig->propagate[i], true), "Error making file propagate");

    APPLY_LIST(pconfig->node_filter, pconfig->nb_node_filter, provenance_add_node_filter(node_id(pconfig->node_filter[i])), "Error setting node filter");

    APPLY_LIST(pconfig->relation_filter, pconfig->nb_relation_filter, provenance_add_relation_filter(relation_id(pconfig->relation_filter[i])), "Error setting relation filter");

    APPLY_LIST(pconfig->propagate_node_filter, pconfig->nb_propagate_node_filter, provenance_add_propagate_node_filter(node_id(pconfig->propagate_node_filter[i])), "Error setting propagate node filter");

    APPLY_LIST(pconfig->propagate_relation_filter, pconfig->nb_propagate_relation_filter, provenance_add_propagate_relation_filter(relation_id(pconfig->propagate_relation_filter[i])), "Error setting propagate relation filter");

    APPLY_LIST(pconfig->track_ipv4_ingress_filter, pconfig->nb_track_ipv4_ingress_filter, provenance_ingress_ipv4_track(pconfig->track_ipv4_ingress_filter[i]), "Error setting propagate ingress ipv4 track filter");

    APPLY_LIST(pconfig->propagate_ipv4_ingress_filter, pconfig->nb_propagate_ipv4_ingress_filter, provenance_ingress_ipv4_propagate(pconfig->propagate_ipv4_ingress_filter[i]), "Error setting propagate ingress ipv4 propagate filter");

    APPLY_LIST(pconfig->record_ipv4_ingress_filter, pconfig->nb_record_ipv4_ingress_filter, provenance_ingress_ipv4_record(pconfig->record_ipv4_ingress_filter[i]), "Error setting record ingress ipv4 record filter");

    APPLY_LIST(pconfig->track_ipv4_egress_filter, pconfig->nb_track_ipv4_egress_filter, provenance_egress_ipv4_track(pconfig->track_ipv4_egress_filter[i]), "Error setting propagate egress ipv4 track filter");

    APPLY_LIST(pconfig->propagate_ipv4_egress_filter, pconfig->nb_propagate_ipv4_egress_filter, provenance_egress_ipv4_propagate(pconfig->propagate_ipv4_egress_filter[i]), "Error setting propagate egress ipv4 propagate filter");

    APPLY_LIST(pconfig->record_ipv4_egress_filter, pconfig->nb_record_ipv4_egress_filter, provenance_egress_ipv4_record(pconfig->record_ipv4_egress_filter[i]), "Error setting record egress ipv4 record filter");

    if(err = provenance_set_enable(pconfig->enabled)){
      syslog(LOG_ERR, "Error enabling provenance %d", err);
      exit(-1);
    }

    if(err = provenance_set_all(pconfig->all)){
      syslog(LOG_ERR, "Error with all provenance %d", err);
      exit(-1);
    }
  } else {
    syslog(LOG_ERR, "CamFlow is not running in the kernel.");
  }
}

void _init_logs( void ){
  setlogmask(LOG_UPTO(LOG_INFO));
  openlog(APP_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_DAEMON);
}

int main( void )
{
    struct configuration config;

    _init_logs();

    // set everything to 0
    memset(&config, 0, sizeof(struct configuration));

    if (ini_parse(CONFIG_PATH, handler, &config) < 0) {
        syslog(LOG_ERR, "Can't load '%s'", CONFIG_PATH);
        exit(-1);
    }

    apply_config(&config);
    print_config(&config);
    return 0;
}
