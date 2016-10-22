# camflow-config

## Version

| Library version | Date       |
| --------------- | ---------- |
| 0.1.5           | N/A        |
| 0.1.4           | 19/10/2016 |
| 0.1.3           | 04/10/2016 |
| 0.1.2           | 19/09/2016 |
| 0.1.1           | 02/09/2016 |
| 0.1.0           | 26/05/2016 |

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
