# camflow-config

## Build Status

| Branch | Status                                                                                  |
|--------|-----------------------------------------------------------------------------------------|
| master | [![Master Build Status](https://api.travis-ci.org/CamFlow/camconfd.svg)](https://travis-ci.org/CamFlow/camflow-config/branches)  |
| dev    | [![Dev Build Status](https://api.travis-ci.org/CamFlow/camconfd.svg?branch=dev)](https://travis-ci.org/CamFlow/camflow-config/branches)      |

Automated Travis test run the following operation:
- run [SonarQube](https://sonarqube.com).

## Instruction

The CamFlow kernel configuration can be found at `/etc/camflow.ini`. Follow an example configuration:

```
[provenance]
;unique identifier for the machine, use hostid if set to 0
machine_id=0
;enable provenance capture
enabled=true
;record provenance of all kernel object
all=false
; enable node compression
compress=true
node_filter=directory
node_filter=inode_unknown
node_filter=char
relation_filter=sh_read
relation_filter=sh_write
propagate_node_filter=directory
propagate_node_filter=char
propagate_node_filter=inode_unknown

[file]
;set opaque file
opaque=/usr/bin/bash
;set tracked file
;track=/home/thomas/test.o
;propagate=/home/thomas/test.o

[ipv4−egress]
;propagate=0.0.0.0/0:80
;propagate=0.0.0.0/0:404
;record exchanged with local server
;record=127.0.0.1/32:80

[user]
;track=vagrant

[group]
;propagate=docker
```

To check the loaded configuration use `journalctl -b | grep camconfd`
