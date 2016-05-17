/*
*
* ifclib.h
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
#ifndef __IFCLIB_H
#define __IFCLIB_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <linux/ifc.h>

/* context functions */
int ifc_get_context(struct ifc_context* context);
int ifc_get_other_context(pid_t pid, struct ifc_context* context);
int ifc_get_file_context(const char name[PATH_MAX], struct ifc_context* context);
void ifc_context_print(struct ifc_context* context);

/* label manipulation */
int ifc_add_secrecy(struct ifc_context* context, tag_t tag);
int ifc_remove_secrecy(struct ifc_context* context, tag_t tag);
int ifc_add_integrity(struct ifc_context* context, tag_t tag);
int ifc_remove_integrity(struct ifc_context* context, tag_t tag);

/* file label manipulation */
int ifc_file_add_secrecy(const char name[PATH_MAX], struct ifc_context* context, tag_t tag);
int ifc_file_remove_secrecy(const char name[PATH_MAX], struct ifc_context* context, tag_t tag);
int ifc_file_add_integrity(const char name[PATH_MAX], struct ifc_context* context, tag_t tag);
int ifc_file_remove_integrity(const char name[PATH_MAX], struct ifc_context* context, tag_t tag);

/* privilege manipulation */
int ifc_add_secrecyp(struct ifc_context* context, tag_t tag);
int ifc_remove_secrecyp(struct ifc_context* context, tag_t tag);
int ifc_add_secrecyn(struct ifc_context* context, tag_t tag);
int ifc_remove_secrecyn(struct ifc_context* context, tag_t tag);
int ifc_add_integrityp(struct ifc_context* context, tag_t tag);
int ifc_remove_integrityp(struct ifc_context* context, tag_t tag);
int ifc_add_integrityn(struct ifc_context* context, tag_t tag);
int ifc_remove_integrityn(struct ifc_context* context, tag_t tag);
int ifc_pass_secrecyp(tag_t tag, pid_t pid);
int ifc_pass_secrecyn(tag_t tag, pid_t pid);
int ifc_pass_integrityp(tag_t tag, pid_t pid);
int ifc_pass_integrityn(tag_t tag, pid_t pid);


/* tag functions */
tag_t ifc_create_tag(struct ifc_context* context);

/* bridge usher */
int ifc_create_bridge_socket(void);
pid_t ifc_register_bridge(void);
int ifc_add_bridge(const char path[PATH_MAX]);
int ifc_start_bridge(const char path[PATH_MAX], const char param[PARAM_MAX]);
ssize_t ifc_sendmsg(int sock_fd, pid_t destination, void* data, size_t size, int flags);
ssize_t ifc_recvmsg(int sockfd, void *data, size_t len, int flags);

#endif
