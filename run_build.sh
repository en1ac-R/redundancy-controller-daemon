#!/bin/zsh

script_dir="$(dirname "$(realpath "$0")")"

# Fullpath to SYSROOT
SYSROOT_PATH=$script_dir/OKT507-C_V2.1_SYSROOT

cmake --fresh -S $script_dir -B $script_dir/_builds -G Ninja \
  --toolchain=$script_dir/toolchain-aarch64.cmake \
  -DCMAKE_SYSROOT=$SYSROOT_PATH -DCMAKE_EXPORT_COMPILE_COMMANDS=ON  

cmake --build $script_dir/_builds -- -j$(nproc)
