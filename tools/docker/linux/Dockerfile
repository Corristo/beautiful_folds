FROM archlinux:latest

RUN pacman -Syu --noconfirm  && \
    pacman -S --noconfirm       \
      cmake                     \
      gcc                       \
      git                       \
      ninja                     \
      python                 && \
    rm -rf /var/cache/pacman

RUN cd /tmp                                                                && \
    git clone https://github.com/saarraz/clang-concepts-monorepo.git clang && \
    cd clang                                                               && \
    cmake -Bbuild -Hllvm -DCMAKE_BUILD_TYPE=Release -G Ninja                  \
      -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra"                        \
      -DLLVM_EXTERNAL_CLANG_SOURCE_DIR=/tmp/clang/clang                       \
      -DLLVM_PARALLEL_LINK_JOBS=1                                             \
      -DLLVM_TARGETS_TO_BUILD="X86"                                           \
      -DCMAKE_INSTALL_PREFIX=/opt/clang                                       \
      -DLLVM_TOOL_CLANG_BUILD=ON                                           && \
    cmake --build build --target install                                   && \
    cd /tmp && rm -rf clang

ENV PATH $PATH:/opt/clang/bin
