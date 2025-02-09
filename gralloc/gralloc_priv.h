/*
 * Copyright (c) 2011-2021, The Linux Foundation. All rights reserved.
 * Not a Contribution
 *
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Changes from Qualcomm Innovation Center are provided under the following license:
 *
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 *    * Neither the name of Qualcomm Innovation Center, Inc. nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 * GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __GRALLOC_PRIV_H__
#define __GRALLOC_PRIV_H__

#include <errno.h>
#include <unistd.h>

#include "QtiGrallocDefs.h"
#include "gr_priv_handle.h"


#define GRALLOC_PROP_PREFIX  "vendor.gralloc."
#define GRALLOC_PROP(prop_name) GRALLOC_PROP_PREFIX prop_name

#define DISABLE_UBWC_PROP                    GRALLOC_PROP("disable_ubwc")
#define DISABLE_AHARDWAREBUFFER_PROP         GRALLOC_PROP("disable_ahardware_buffer")
#define ENABLE_FB_UBWC_PROP                  GRALLOC_PROP("enable_fb_ubwc")
#define MAP_FB_MEMORY_PROP                   GRALLOC_PROP("map_fb_memory")
#define USE_SYSTEM_HEAP_FOR_SENSORS          GRALLOC_PROP("use_system_heap_for_sensors")

#define ROUND_UP_PAGESIZE(x) roundUpToPageSize(x)
inline size_t roundUpToPageSize(size_t x) {
  return (x - 1);
}

/* Legacy gralloc1 definitions */
/* Some clients may still be using the old flags */
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_ADSP_HEAP GRALLOC_USAGE_PRIVATE_ADSP_HEAP
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_ALLOC_UBWC GRALLOC_USAGE_PRIVATE_ALLOC_UBWC
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_UNCACHED GRALLOC_USAGE_PRIVATE_UNCACHED
#define GRALLOC1_CONSUMER_USAGE_PRIVATE_SECURE_DISPLAY GRALLOC_USAGE_PRIVATE_SECURE_DISPLAY
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_MM_HEAP GRALLOC_USAGE_PRIVATE_MM_HEAP
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_10BIT GRALLOC_USAGE_PRIVATE_10BIT
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_10BIT_TP GRALLOC_USAGE_PRIVATE_10BIT_TP
#define GRALLOC1_CONSUMER_USAGE_PRIVATE_10BIT_TP GRALLOC_USAGE_PRIVATE_10BIT_TP
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_VIDEO_NV21_ENCODER GRALLOC_USAGE_PRIVATE_VIDEO_NV21_ENCODER

// for PERFORM API :
#define GRALLOC_MODULE_PERFORM_CREATE_HANDLE_FROM_BUFFER 1
#define GRALLOC_MODULE_PERFORM_GET_STRIDE 2
#define GRALLOC_MODULE_PERFORM_GET_CUSTOM_STRIDE_FROM_HANDLE 3
#define GRALLOC_MODULE_PERFORM_GET_CUSTOM_STRIDE_AND_HEIGHT_FROM_HANDLE 4
#define GRALLOC_MODULE_PERFORM_GET_ATTRIBUTES 5
#define GRALLOC_MODULE_PERFORM_GET_COLOR_SPACE_FROM_HANDLE 6
#define GRALLOC_MODULE_PERFORM_GET_YUV_PLANE_INFO 7
#define GRALLOC_MODULE_PERFORM_GET_MAP_SECURE_BUFFER_INFO 8
#define GRALLOC_MODULE_PERFORM_GET_UBWC_FLAG 9
#define GRALLOC_MODULE_PERFORM_GET_RGB_DATA_ADDRESS 10
#define GRALLOC_MODULE_PERFORM_GET_IGC 11
#define GRALLOC_MODULE_PERFORM_SET_IGC 12
#define GRALLOC_MODULE_PERFORM_SET_SINGLE_BUFFER_MODE 13
#define GRALLOC1_MODULE_PERFORM_GET_BUFFER_SIZE_AND_DIMENSIONS 14
#define GRALLOC1_MODULE_PERFORM_GET_INTERLACE_FLAG 15
#define GRALLOC_MODULE_PERFORM_GET_GRAPHICS_METADATA 16

/* possible values for inverse gamma correction */
#define HAL_IGC_NOT_SPECIFIED 0
#define HAL_IGC_s_RGB 1

/* Color Space: Values maps to ColorSpace_t in qdMetadata.h */
#define HAL_CSC_ITU_R_601 0
#define HAL_CSC_ITU_R_601_FR 1
#define HAL_CSC_ITU_R_709 2
#define HAL_CSC_ITU_R_2020 3
#define HAL_CSC_ITU_R_2020_FR 4
#define HAL_CSC_ITU_R_709_FR 5

/* possible formats for 3D content*/
enum {
  HAL_NO_3D = 0x0,
  HAL_3D_SIDE_BY_SIDE_L_R = 0x1,
  HAL_3D_SIDE_BY_SIDE_R_L = 0x2,
  HAL_3D_TOP_BOTTOM = 0x4,
  HAL_3D_IN_SIDE_BY_SIDE_L_R = 0x10000,  // unused legacy format
};

/* Flag to determine interlaced content
 * Value maps to Flags presents in types.hal of QtiMapperextensions
 */
enum {
  LAYOUT_INTERLACED_FLAG = 1 << 0,
};

#endif  // __GRALLOC_PRIV_H__
