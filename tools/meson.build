tools_req = tools.enabled()

if tools_req
  if decoder.enabled() and formatter.enabled() and minimal.disabled()
    executable(
      'ZydisDisasm',
      files(
        'ZydisDisasm.c',
        'ZydisToolsShared.c',
        'ZydisToolsShared.h',
      ),
      dependencies: [zydis_dep],
      install: true,
    )

    llvm_fuzz = get_option('llvm-fuzz')
    executable(
      'ZydisFuzzDecoder',
      files(
        'ZydisFuzzDecoder.c',
        'ZydisFuzzShared.c',
        'ZydisFuzzShared.h',
      ),
      dependencies: [zydis_dep],
      c_args: llvm_fuzz ? ['-DZYDIS_LIBFUZZER'] : [],
    )

    if encoder.enabled()
      executable(
        'ZydisFuzzEncoder',
        files(
          'ZydisFuzzEncoder.c',
          'ZydisFuzzShared.c',
          'ZydisFuzzShared.h',
        ),
        dependencies: [zydis_dep],
        c_args: llvm_fuzz ? ['-DZYDIS_LIBFUZZER'] : [],
      )
      executable(
        'ZydisFuzzReEncoding',
        files(
          'ZydisFuzzReEncoding.c',
          'ZydisFuzzShared.c',
          'ZydisFuzzShared.h',
        ),
        dependencies: [zydis_dep],
        c_args: llvm_fuzz ? ['-DZYDIS_LIBFUZZER'] : [],
      )
    endif

    executable(
      'ZydisInfo',
      files(
        'ZydisInfo.c',
        'ZydisToolsShared.c',
        'ZydisToolsShared.h',
      ),
      dependencies: [zydis_dep],
      install: true,
    )
  endif
endif

summary(
  {'tools': tools_req},
  section: 'Features',
)
