# Redundancy Controller Daemon

This project is a daemon for monitoring and controlling redundant devices.  
It is cross-compiled for ARM64 using Clang and a sysroot.

---

## Prerequisites

- **Clang** (version 20 or newer recommended)  
- **CMake** (version 3.13 or newer)  
- **Ninja** build system  

---

## Setting up the Sysroot

Before building the project, you need the ARM64 sysroot.  

1. Download the sysroot from the following link:  
   [Download Sysroot](https://drive.google.com/file/d/1nUEV44cK6vcpAox6heVDkIXxbvaTXPDH/view?usp=drive_link)

2. Extract the archive **into the root directory of the project**:

   ```bash
   cd <project-root>
   tar -xzf OKT507-C_V2.1_SYSROOT.tar.gz
