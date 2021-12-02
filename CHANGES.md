## Version

| Library version | Date       |
| --------------- | ---------- |
| 0.5.3           | N/A        |
| 0.5.2           | 29/11/2021 |
| 0.5.1           | 05/12/2020 |
| 0.5.0           | 09/07/2020 |
| 0.4.6           | 23/03/2020 |
| 0.4.5           | 17/06/2019 |
| 0.4.4           | 11/02/2019 |
| 0.4.3           | 31/01/2019 |
| 0.4.2           | 30/01/2019 |
| 0.4.1           | 26/05/2018 |
| 0.4.0           | 12/12/2017 |
| 0.3.4           | 29/09/2017 |
| 0.3.3           | 27/08/2017 |
| 0.3.2           | 02/08/2017 |
| 0.3.1           | 23/06/2017 |
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

### v0.5.3
```
```

### v0.5.2
```
- Release for fedora 35.
```

### v0.5.1
```
- Fix potential bug when retrieving boot_id and machine_id.
```

### v0.5.0
```
- Release for fedora 32.
```

### v0.4.6
```
- Release for fedora 31.
```

### v0.4.5
```
- Release for fedora 29.
```

### v0.4.4
```
- Ensure machine ID can never be set to zero.
```

### v0.4.3
```
- Fix boot ID 0 issue.
```

### v0.4.2
```
- Support Ubuntu package.
```

### v0.4.1
```
- Warning instead of error when not existing paths are used for file configuration.
- Support node duplication on/off.
```

### v0.4.0
```
- Create a compression subcategory.
- Default setting ignore envp.
- Add secctx support via configuration to further align with CLI options.
- Add support for opaque groups and users.
- Internal refactoring.
```

### v0.3.4
```
- Put file related option in their own category in the ini file.
- Add node compression option.
- Use libprovenance as a shared library.
```

### v0.3.3
```
- Reducing dependencies between kernel version and userspace software.
```

### v0.3.2
```
- Add support for user and group filters.
```

### v0.3.1
```
- Renamed camconfd.
- Use syslog instead of custom logging mechanism.
- Fix a bug that occurs on propagate (File does not exist when it does).
- Fail if the configuration contains an error.
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
