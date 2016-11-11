# camflow-config

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

[ifc]
bridge=/usr/local/bin/camflow-ifc-logger
;bridge=/your/own/bridge
;trusted=/home/thomas/test/test
```

## Version

| Library version | Date       |
| --------------- | ---------- |
| 0.1.6           | 11/11/2016 |
| 0.1.5           | 28/10/2016 |
| 0.1.4           | 19/10/2016 |
| 0.1.3           | 04/10/2016 |
| 0.1.2           | 19/09/2016 |
| 0.1.1           | 02/09/2016 |
| 0.1.0           | 26/05/2016 |

### v0.1.6
```
- In configuration file "tracked" becomes "track"
- Support IPv4 ingress and egress tracking.
```

### v0.1.5
```
- Rework configuration order (always finish by with enabling/disabling).
```

### v0.1.4
```
- Removed mmap_write from excluded propagate in default config.
```

### v0.1.3
```
- If machine_id is not set in /etc/camflow.ini it is read from /etc/camflow-machine_id.
If the file does not exist it is created and a random number is generated.
```

### v0.1.2
```
- Handle trusted files.
```

### v0.1.1
```
- Build configuration service from installed library.
- Can set opaque or tracked file from configuration file.
```


### v0.1.0
```
- Initial release.
```
