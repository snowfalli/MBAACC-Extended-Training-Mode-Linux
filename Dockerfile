ARG BASE=msvc-wine
FROM $BASE AS build

RUN apt-get update && \
    apt-get install -y wget xz-utils && \
    apt-get clean -y && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y lsb-release && apt-get clean all

RUN apt-get install -y lsb-release wget software-properties-common gnupg

RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc

RUN wget -qO- https://apt.llvm.org/llvm.sh | bash -s -- 20

ENV PATH=/opt/clang/bin:$PATH

COPY ./ ./

RUN cd /opt/msvc/'Windows Kits'/10/Lib/10.0.26100.0/um/x86 \
    mv User32.Lib User32.lib \
    mv Gdi32.Lib Gdi32.lib \
    mv Advapi32.Lib Advapi32.lib \
    mv ComDlg32.Lib ComDlg32.lib \
    mv DbgHelp.Lib DbgHelp.lib

RUN mkdir -p /out

RUN \
    for arch in x86; do \
        [ ! -d /opt/msvc/kits/10/lib/*/um/$arch ] || \
        (BIN=/opt/msvc/bin/$arch . /opt/msvc/msvcenv-native.sh && \
            llvm-rc-20 -fo /out/ETM-x86.res Extended-Training-Mode-DLL/Extended-Training-Mode-DLL.rc -w \
        ) || exit 1; \
    done

RUN \
    for arch in x86; do \
        [ ! -d /opt/msvc/kits/10/lib/*/um/$arch ] || \
        (BIN=/opt/msvc/bin/$arch . /opt/msvc/msvcenv-native.sh && \
            #linking .res file here does not work, due to this not being run on windows? idrk
            #manually link it using wine and reshacker afterwards
            clang-20 --target=$TARGET_TRIPLE -c -o ETM-obj-$arch.o /out/ETM-x86.res Extended-Training-Mode-DLL/dllmain.cpp -ICommon -ICommon/d3dx9 -LCommon/d3dx9 -fuse-ld=lld -std=c++20 -w -Wno-unknown-pragmas && \
            clang-20 --target=$TARGET_TRIPLE -ICommon -LCommon/x86 -L/opt/msvc/kits/10/lib/*/um/$arch -ICommon/d3dx9 -LCommon/d3dx9 -lUser32 -lGdi32 -lDbgHelp -fuse-ld=lld -std=c++20 -shared -Wl,/SAFESEH:NO -v -g -o /out/ETM-x86.dll Extended-Training-Mode-DLL/DLLAsmFuncs.obj ETM-obj-x86.o \
        ) || exit 1; \
    done

RUN \
    for arch in x86; do \
        [ ! -d /opt/msvc/kits/10/lib/*/um/$arch ] || \
        (BIN=/opt/msvc/bin/$arch . /opt/msvc/msvcenv-native.sh && \
            clang-20 --target=$TARGET_TRIPLE -c -o ETM-$arch.o  MBAACC-Extended-Training-Mode/MBAACC-Extended-Training-Mode.cpp -ICommon/d3dx9 -LCommon/d3dx9 -ICommon -IMBAACC-Extended-Training-Mode/lib -LCommon -fuse-ld=lld -std=c++20 -w -Wno-unknown-pragmas && \
            clang-20 --target=$TARGET_TRIPLE -ICommon -LCommon/x86 -L/opt/msvc/kits/10/lib/*/um/$arch -ICommon/d3dx9 -LCommon/d3dx9 -lUser32 -lGdi32 -lGlU32 -lComDlg32 -fuse-ld=lld -std=c++20 -g -v -o /out/ETM-$arch.exe ETM-$arch.o \
        ) || exit 1; \
    done

FROM scratch
COPY --from=build /out /game
