/* Select the generated OpenSSL configuration for the active mini_sxp target. */
#ifndef PFC_OPENSSL_CONFIGURATION_SELECTOR_H
#define PFC_OPENSSL_CONFIGURATION_SELECTOR_H

#if defined(PFC_PLATFORM_WIN64)
#  include <openssl/configuration_win64.h>
#elif defined(PFC_PLATFORM_WIN32)
#  include <openssl/configuration_win32.h>
#elif defined(PFC_PLATFORM_LINUX64)
#  include <openssl/configuration_linux64.h>
#elif defined(PFC_PLATFORM_LINUX32)
#  include <openssl/configuration_linux32.h>
#elif defined(PFC_PLATFORM_MACOS)
#  include <openssl/configuration_macos.h>
#else
#  error "OpenSSL configuration is not defined for this mini_sxp platform"
#endif

#endif /* PFC_OPENSSL_CONFIGURATION_SELECTOR_H */
