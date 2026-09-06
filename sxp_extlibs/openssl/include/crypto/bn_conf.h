/* Select the generated BIGNUM configuration for the active target. */
#ifndef PFC_OPENSSL_BN_CONFIGURATION_SELECTOR_H
#define PFC_OPENSSL_BN_CONFIGURATION_SELECTOR_H

#if defined(PFC_PLATFORM_WIN64)
#  include "bn_conf_win64.h"
#elif defined(PFC_PLATFORM_WIN32)
#  include "bn_conf_win32.h"
#elif defined(PFC_PLATFORM_LINUX64)
#  include "bn_conf_linux64.h"
#elif defined(PFC_PLATFORM_LINUX32)
#  include "bn_conf_linux32.h"
#elif defined(PFC_PLATFORM_MACOS)
#  include "bn_conf_macos.h"
#else
#  error "OpenSSL BIGNUM configuration is not defined for this mini_sxp platform"
#endif

#endif /* PFC_OPENSSL_BN_CONFIGURATION_SELECTOR_H */
