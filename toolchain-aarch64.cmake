set(CMAKE_SYSROOT ${CMAKE_SYSROOT})
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_C_COMPILER_TARGET aarch64-linux-gnu)
set(CMAKE_CXX_COMPILER_TARGET aarch64-linux-gnu)

set(CMAKE_EXE_LINKER_FLAGS
    "--sysroot=${CMAKE_SYSROOT} \
     -fuse-ld=lld \
     -L${CMAKE_SYSROOT}/usr/lib/gcc/aarch64-linux-gnu/7 \
     -Wl,-rpath-link,${CMAKE_SYSROOT}/usr/lib/gcc/aarch64-linux-gnu/7 \
     -L${CMAKE_SYSROOT}/lib/aarch64-linux-gnu \
     -Wl,-rpath-link,${CMAKE_SYSROOT}/lib/aarch64-linux-gnu"
)
