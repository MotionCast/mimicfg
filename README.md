# MimicConfig

A custom configuration module using [`toml11`][toml11] to read initial settings for [Pilot][pilot] and [Linear][linear].


## Requirements

- C++17
- CMake >=3.10
- [toml11][toml11]
- [googletest][gtest]


## Sections

### Signaling Server

```toml
[signaling]
ip = "0.0.0.0"
port = 8000
local = ""
remote = ""
```


### ICE Servers

```toml
[ice]
urls = [
  "stun.stunprotocol.org:3478",
  "stun.l.google.com:19302"
]
```

### Kalman

```toml
[kalman]
process_noise = [ 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 ]
estimate_error = [ 500.0, 500.0, 500.0, 500.0, 500.0, 500.0 ]
measurement_noise = [ 0.250, 0.250, 0.250, 0.009, 0.009, 0.009 ]
```

### Nodes

```toml
[[nodes]]
id = 0
parent = 0
name = "ROOT"

[[nodes]]
id = 1
parent = 0
name = "RARM"
```


## Build

```bash
$ cmake -B build -DBUILD_TESTS=1 -DBUILD_DOCS=1
$ cmake --build build # will build docs in ./docs
```


## Testing

```bash
# Build first, then run the following
$ ctest --test-dir build --output-on-failure
```


## Authorship

Jacob SP \<jacob@moca.st>


## Licence

![GPLv2][shield-gpl]

This software is distributed under the [General Public License v2.0][license], more information available at the [Free Software Foundation][gnu].

<!-- LINKS -->

[toml11]: https://github.com/ToruNiina/toml11.git	"toml11"
[gtest]: https://github.com/google/googletest	"gtest"

[license]: LICENSE "General Public License"
[gnu]: https://www.gnu.org/licenses/old-licenses/gpl-2.0.html "Free Software Foundation"

<!-- MOCAST -->
[pilot]: https://github.com/MotionCast/Pilot	"Pilot"
[linear]: https://github.com/MotionCast/Linear	"Linear"

<!-- SHIELDS -->

[shield-gpl]: https://img.shields.io/github/license/MotionCast/MimicConfig
