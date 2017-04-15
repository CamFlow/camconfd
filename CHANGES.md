## Version

| Library version | Date       |
| --------------- | ---------- |
| 0.3.0           | 15/04/2017 |
| 0.2.1           | 09/03/2017 |
| 0.2.0           | 23/01/2017 |
| 0.1.7           | 05/12/2016 |
| 0.1.6           | 11/11/2016 |
| 0.1.5           | 28/10/2016 |
| 0.1.4           | 19/10/2016 |
| 0.1.3           | 04/10/2016 |
| 0.1.2           | 19/09/2016 |
| 0.1.1           | 02/09/2016 |
| 0.1.0           | 26/05/2016 |

### v0.2.1
```
- Add support for boot id.
```

### v0.2.1
```
- Travis inclusion.
- Code quality improvement.
```

### v0.2.0
```
- Deal with recording IP packet content.
- IFC support on hold.
- Fix a warning relating to stored machine_id.
- Go through even when config cannot be fully applied (errors in log file).
```

### v0.1.7
```
- Error now catched when not running as root.
```

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