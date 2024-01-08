//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "color.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// e_rgb_color_space
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_rgb_color_space
#define PFC_ENUM_PREFIX rgbcs_
#define PFC_ENUM_VALS PFC_ENUM_VAL_N(srgb,     "sRGB / Rec. 709 / BT.709")\
                      PFC_ENUM_VAL_N(rec2020,  "Rec. 2020 / BT.2020")\
                      PFC_ENUM_VAL_N(dcip3,    "DCI-P3")\
                      PFC_ENUM_VAL_N(dcip3t,   "DCI-P3 Theater")\
                      PFC_ENUM_VAL_N(adobe,    "Adobe RGB")\
                      PFC_ENUM_VAL_N(prophoto, "ProPhoto")\
                      PFC_ENUM_VAL_N(aces_ap0, "ACES AP0")\
                      PFC_ENUM_VAL_N(aces_ap1, "ACES AP1")
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_cie_white_point
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_cie_white_point
#define PFC_ENUM_PREFIX ciewpnt_
#define PFC_ENUM_VALS PFC_ENUM_VAL_N(2deg_a,       "A   (2856K) - Incandescent / Tungsten")\
                      PFC_ENUM_VAL_N(2deg_b,       "B   (4874K) - Direct sunlight at noon")\
                      PFC_ENUM_VAL_N(2deg_c,       "C   (6774K) - Average / North sky Daylight")\
                      PFC_ENUM_VAL_N(2deg_d50,     "D50 (5003K) - Horizon Light. ICC profile PCS")\
                      PFC_ENUM_VAL_N(2deg_d55,     "D55 (5503K) - Mid-morning / Mid-afternoon Daylight")\
                      PFC_ENUM_VAL_N(2deg_d60,     "D60 (6000K)")\
                      PFC_ENUM_VAL_N(2deg_d65,     "D65 (6504K) - Noon Daylight: Television, sRGB color space")\
                      PFC_ENUM_VAL_N(2deg_d65_p3t, "D65 DCI-P3 Theater")\
                      PFC_ENUM_VAL_N(2deg_d75,     "D75 (7504K) - North sky Daylight")\
                      PFC_ENUM_VAL_N(2deg_e,       "E   (5454K) - Equal energy")\
                      PFC_ENUM_VAL_N(2deg_f1,      "F1  (6430K) - Daylight Fluorescent")\
                      PFC_ENUM_VAL_N(2deg_f2,      "F2  (4230K) - Cool White Fluorescent")\
                      PFC_ENUM_VAL_N(2deg_f3,      "F3  (3450K) - White Fluorescent")\
                      PFC_ENUM_VAL_N(2deg_f4,      "F4  (2940K) - Warm White Fluorescent")\
                      PFC_ENUM_VAL_N(2deg_f5,      "F5  (6350K) - Daylight Fluorescent")\
                      PFC_ENUM_VAL_N(2deg_f6,      "F6  (4150K) - Lite White Fluorescent")\
                      PFC_ENUM_VAL_N(2deg_f7,      "F7  (6500K) - D65 simulator, Daylight simulator")\
                      PFC_ENUM_VAL_N(2deg_f8,      "F8  (5000K) - D50 simulator, Sylvania F40 Design 50t")\
                      PFC_ENUM_VAL_N(2deg_f9,      "F9  (4150K) - Cool White Deluxe Fluorescent")\
                      PFC_ENUM_VAL_N(2deg_f10,     "F10 (5000K) - Philips TL85, Ultralume 50")\
                      PFC_ENUM_VAL_N(2deg_f11,     "F11 (4000K) - Philips TL84, Ultralume 40")\
                      PFC_ENUM_VAL_N(2deg_f12,     "F12 (3000K) - Philips TL83, Ultralume 30")\
                      PFC_ENUM_VAL_N(10deg_a,      "A   (2856K) - Incandescent / Tungsten")\
                      PFC_ENUM_VAL_N(10deg_b,      "B   (4874K) - Direct sunlight at noon")\
                      PFC_ENUM_VAL_N(10deg_c,      "C   (6774K) - Average / North sky Daylight")\
                      PFC_ENUM_VAL_N(10deg_d50,    "D50 (5003K) - Horizon Light. ICC profile PCS")\
                      PFC_ENUM_VAL_N(10deg_d55,    "D55 (5503K) - Mid-morning / Mid-afternoon Daylight")\
                      PFC_ENUM_VAL_N(10deg_d65,    "D65 (6504K) - Noon Daylight: Television, sRGB color space")\
                      PFC_ENUM_VAL_N(10deg_d75,    "D75 (7504K) - North sky Daylight")\
                      PFC_ENUM_VAL_N(10deg_e,      "E   (5454K) - Equal energy")\
                      PFC_ENUM_VAL_N(10deg_f1,     "F1  (6430K) - Daylight Fluorescent")\
                      PFC_ENUM_VAL_N(10deg_f2,     "F2  (4230K) - Cool White Fluorescent")\
                      PFC_ENUM_VAL_N(10deg_f3,     "F3  (3450K) - White Fluorescent")\
                      PFC_ENUM_VAL_N(10deg_f4,     "F4  (2940K) - Warm White Fluorescent")\
                      PFC_ENUM_VAL_N(10deg_f5,     "F5  (6350K) - Daylight Fluorescent")\
                      PFC_ENUM_VAL_N(10deg_f6,     "F6  (4150K) - Lite White Fluorescent")\
                      PFC_ENUM_VAL_N(10deg_f7,     "F7  (6500K) - D65 simulator, Daylight simulator")\
                      PFC_ENUM_VAL_N(10deg_f8,     "F8  (5000K) - D50 simulator, Sylvania F40 Design 50t")\
                      PFC_ENUM_VAL_N(10deg_f9,     "F9  (4150K) - Cool White Deluxe Fluorescent")\
                      PFC_ENUM_VAL_N(10deg_f10,    "F10 (5000K) - Philips TL85, Ultralume 50")\
                      PFC_ENUM_VAL_N(10deg_f11,    "F11 (4000K) - Philips TL84, Ultralume 40")\
                      PFC_ENUM_VAL_N(10deg_f12,    "F12 (3000K) - Philips TL83, Ultralume 30")
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------
