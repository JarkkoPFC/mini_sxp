# OpenSSL static sources

This directory contains the trimmed OpenSSL 3.5.8 source used by mini_sxp.
Only the library sources, public/internal headers, default provider sources,
and generated configuration headers are kept. Applications, tests, fuzzers,
documentation, assembly, dynamically loaded providers, and the OpenSSL
configure/build machinery are intentionally omitted.

The source is exposed through two generated projects:

- `libcrypto.sxproj` builds `libcrypto_<build>`.
- `libssl.sxproj` builds `libssl_<build>` and depends on `libcrypto_<build>` at
  final application link time.

Both archives are required when libcurl is configured with OpenSSL. The
application should continue to use libcurl only; it does not call OpenSSL
directly.

The Linux GCC makefile builds both archives and enables the OpenSSL libcurl
backend. For example: `make build=debug platform=linux64`.

The generated configuration headers are selected by the existing
`PFC_PLATFORM_*` definitions. When adding another target, generate and add
that target's `configuration_*.h`, `bn_conf_*.h`, `dso_conf_*.h`, and
`buildinf_*.h` files, then extend the four selector headers.

OpenSSL is licensed under the Apache License 2.0. See `LICENSE.txt`.
