/* Select the generated build information for the active mini_sxp target. */
#ifndef PFC_OPENSSL_BUILDINFO_SELECTOR_H
#define PFC_OPENSSL_BUILDINFO_SELECTOR_H

#if defined(PFC_PLATFORM_WIN64)
#  include "buildinf_win64.h"
#elif defined(PFC_PLATFORM_WIN32)
#  include "buildinf_win32.h"
#elif defined(PFC_PLATFORM_LINUX64)
#  include "buildinf_linux64.h"
#elif defined(PFC_PLATFORM_LINUX32)
#  include "buildinf_linux32.h"
#elif defined(PFC_PLATFORM_MACOS)
#  include "buildinf_macos.h"
#else
#  error "OpenSSL build information is not defined for this mini_sxp platform"
#endif

#endif /* PFC_OPENSSL_BUILDINFO_SELECTOR_H */
