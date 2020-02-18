FROM archlinux:latest

ENV LAST_UPDATE=2020-02-18

RUN pacman -Syu --noconfirm   \
 && pacman -S --noconfirm     \
      cmake                   \
      gcc                     \
      gcovr                   \
      git                     \
      make                    \
      ninja                   \
      python                  \
 && rm -rf /var/cache/pacman

RUN cd /tmp                                                                     \
 && git clone https://github.com/llvm/llvm-project.git -b llvmorg-10.0.0 clang  \
 && cd clang                                                                    \
 && cmake -Bbuild -Hllvm -DCMAKE_BUILD_TYPE=Release -G Ninja                    \
      -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;compiler-rt"              \
      -DLLVM_EXTERNAL_CLANG_SOURCE_DIR=/tmp/clang/clang                         \
      -DLLVM_EXTERNAL_COMPILER_RT_SOURCE_DIR=/tmp/clang/compiler-rt             \
      -DLLVM_EXTERNAL_CLANG_TOOLS_EXTRA_SOURCE_DIR=/tmp/clang/clang-tools-extra \
      -DLLVM_PARALLEL_LINK_JOBS=1                                               \
      -DLLVM_TARGETS_TO_BUILD="X86"                                             \
      -DCMAKE_INSTALL_PREFIX=/opt/clang                                         \
      -DLLVM_TOOL_CLANG_BUILD=ON                                                \
      -DLLVM_TOOL_COMPILER_RT_BUILD=ON                                          \
      -DLLVM_TOOL_CLANG_BUILD=ON                                                \
 && cmake --build build --target install                                        \
 && cd /tmp && rm -rf clang

ENV PATH $PATH:/opt/clang/bin
