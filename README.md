# camflow-config

## Build Status

| Branch | Status                                                                                  | SonarQube |
|--------|-----------------------------------------------------------------------------------------|-----------|
| master | [![Master Build Status](https://api.travis-ci.org/CamFlow/camflow-config.svg)](https://travis-ci.org/CamFlow/camflow-config/branches)  |[![SonarQube Status](https://sonarqube.com//api/badges/gate?key=camflow%3Aconfig)](https://sonarqube.com/dashboard?id=camflow%3Aconfig)   |
| dev    | [![Dev Build Status](https://api.travis-ci.org/CamFlow/camflow-config.svg?branch=dev)](https://travis-ci.org/CamFlow/camflow-config/branches)      |[![SonarQube Status](https://sonarqube.com//api/badges/gate?key=camflow%3Aconfig%3Adev)](https://sonarqube.com/dashboard?id=camflow%3Aconfig%3Adev)   |

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
;set opaque file
opaque=/usr/bin/bash
;set tracked file
;tracked=/home/thomas/test.o
;propagate=/home/thomas/test.o
node_filter=directory
node_filter=inode_unknown
node_filter=char
;relation_filter=mmap_write
propagate_node_filter=directory
propagate_node_filter=char
propagate_node_filter=inode_unknown

[ipv4−egress]
; track and propagate on any connection operation on port 80 or 404
;propagate=0.0.0.0/0:80
;propagate=0.0.0.0/0:404

[ipv4−ingress]
; track and propagate on any bind operation
;propagate = 0.0.0.0/0:0
```

To check the loaded configuration use `journalctl -u camconfd.service`
