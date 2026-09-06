/* Select the generated DSO configuration for the active target. */
#ifndef PFC_OPENSSL_DSO_CONFIGURATION_SELECTOR_H
#define PFC_OPENSSL_DSO_CONFIGURATION_SELECTOR_H

#if defined(PFC_PLATFORM_WIN64)
#  include "dso_conf_win64.h"
#elif defined(PFC_PLATFORM_WIN32)
#  include "dso_conf_win32.h"
#elif defined(PFC_PLATFORM_LINUX64)
#  include "dso_conf_linux64.h"
#elif defined(PFC_PLATFORM_LINUX32)
#  include "dso_conf_linux32.h"
#elif defined(PFC_PLATFORM_MACOS)
#  include "dso_conf_macos.h"
#else
#  error "OpenSSL DSO configuration is not defined for this mini_sxp platform"
#endif

#endif /* PFC_OPENSSL_DSO_CONFIGURATION_SELECTOR_H */
