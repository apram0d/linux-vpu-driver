/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "ze_ddi_tables.hpp"
#include "ze_core_api_tables.hpp"

#if defined(__cplusplus)
extern "C" {
#endif
ZE_APIEXPORT ze_result_t ZE_APICALL zeGetDriverProcAddrTable(ze_api_version_t version,
                                                             ze_driver_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnGet = L0::zeDriverGet;
    pDdiTable->pfnGetApiVersion = L0::zeDriverGetApiVersion;
    pDdiTable->pfnGetProperties = L0::zeDriverGetProperties;
    pDdiTable->pfnGetIpcProperties = L0::zeDriverGetIpcProperties;
    pDdiTable->pfnGetExtensionProperties = L0::zeDriverGetExtensionProperties;
    pDdiTable->pfnGetExtensionFunctionAddress = L0::zeDriverGetExtensionFunctionAddress;
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zeGetMemProcAddrTable(ze_api_version_t version,
                                                          ze_mem_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnAllocShared = L0::zeMemAllocShared;
    pDdiTable->pfnAllocDevice = L0::zeMemAllocDevice;
    pDdiTable->pfnAllocHost = L0::zeMemAllocHost;
    pDdiTable->pfnFree = L0::zeMemFree;
    pDdiTable->pfnGetAllocProperties = L0::zeMemGetAllocProperties;
    pDdiTable->pfnGetAddressRange = L0::zeMemGetAddressRange;
    pDdiTable->pfnGetIpcHandle = L0::zeMemGetIpcHandle;
    pDdiTable->pfnOpenIpcHandle = L0::zeMemOpenIpcHandle;
    pDdiTable->pfnCloseIpcHandle = L0::zeMemCloseIpcHandle;
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL zeGetContextProcAddrTable(ze_api_version_t version,
                                                              ze_context_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnCreate = L0::zeContextCreate;
    pDdiTable->pfnDestroy = L0::zeContextDestroy;
    pDdiTable->pfnGetStatus = L0::zeContextGetStatus;
    pDdiTable->pfnSystemBarrier = L0::zeContextSystemBarrier;
    pDdiTable->pfnMakeMemoryResident = L0::zeContextMakeMemoryResident;
    pDdiTable->pfnEvictMemory = L0::zeContextEvictMemory;
    pDdiTable->pfnMakeImageResident = L0::zeContextMakeImageResident;
    pDdiTable->pfnEvictImage = L0::zeContextEvictImage;
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetPhysicalMemProcAddrTable(ze_api_version_t version, ze_physical_mem_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnCreate = L0::zePhysicalMemCreate;
    pDdiTable->pfnDestroy = L0::zePhysicalMemDestroy;
    return ZE_RESULT_SUCCESS;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetVirtualMemProcAddrTable(ze_api_version_t version, ze_virtual_mem_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnReserve = L0::zeVirtualMemReserve;
    pDdiTable->pfnFree = L0::zeVirtualMemFree;
    pDdiTable->pfnQueryPageSize = L0::zeVirtualMemQueryPageSize;
    pDdiTable->pfnMap = L0::zeVirtualMemMap;
    pDdiTable->pfnUnmap = L0::zeVirtualMemUnmap;
    pDdiTable->pfnSetAccessAttribute = L0::zeVirtualMemSetAccessAttribute;
    pDdiTable->pfnGetAccessAttribute = L0::zeVirtualMemGetAccessAttribute;
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetGlobalProcAddrTable(ze_api_version_t version,
                                                             ze_global_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnInit = L0::zeInit;
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetDeviceProcAddrTable(ze_api_version_t version,
                                                             ze_device_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnGet = L0::zeDeviceGet;
    pDdiTable->pfnGetCommandQueueGroupProperties = L0::zeDeviceGetCommandQueueGroupProperties;
    pDdiTable->pfnGetSubDevices = L0::zeDeviceGetSubDevices;
    pDdiTable->pfnGetProperties = L0::zeDeviceGetProperties;
    pDdiTable->pfnGetComputeProperties = L0::zeDeviceGetComputeProperties;
    pDdiTable->pfnGetModuleProperties = L0::zeDeviceGetModuleProperties;
    pDdiTable->pfnGetMemoryProperties = L0::zeDeviceGetMemoryProperties;
    pDdiTable->pfnGetMemoryAccessProperties = L0::zeDeviceGetMemoryAccessProperties;
    pDdiTable->pfnGetCacheProperties = L0::zeDeviceGetCacheProperties;
    pDdiTable->pfnGetImageProperties = L0::zeDeviceGetImageProperties;
    pDdiTable->pfnGetP2PProperties = L0::zeDeviceGetP2PProperties;
    pDdiTable->pfnCanAccessPeer = L0::zeDeviceCanAccessPeer;
    pDdiTable->pfnGetStatus = L0::zeDeviceGetStatus;
    pDdiTable->pfnGetExternalMemoryProperties = L0::zeDeviceGetExternalMemoryProperties;
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetCommandQueueProcAddrTable(ze_api_version_t version, ze_command_queue_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnCreate = L0::zeCommandQueueCreate;
    pDdiTable->pfnDestroy = L0::zeCommandQueueDestroy;
    pDdiTable->pfnExecuteCommandLists = L0::zeCommandQueueExecuteCommandLists;
    pDdiTable->pfnSynchronize = L0::zeCommandQueueSynchronize;
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetCommandListProcAddrTable(ze_api_version_t version, ze_command_list_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnAppendBarrier = L0::zeCommandListAppendBarrier;
    pDdiTable->pfnAppendMemoryRangesBarrier = L0::zeCommandListAppendMemoryRangesBarrier;
    pDdiTable->pfnCreate = L0::zeCommandListCreate;
    pDdiTable->pfnCreateImmediate = L0::zeCommandListCreateImmediate;
    pDdiTable->pfnDestroy = L0::zeCommandListDestroy;
    pDdiTable->pfnClose = L0::zeCommandListClose;
    pDdiTable->pfnReset = L0::zeCommandListReset;
    pDdiTable->pfnAppendMemoryCopy = L0::zeCommandListAppendMemoryCopy;
    pDdiTable->pfnAppendMemoryCopyRegion = L0::zeCommandListAppendMemoryCopyRegion;
    pDdiTable->pfnAppendMemoryFill = L0::zeCommandListAppendMemoryFill;
    pDdiTable->pfnAppendImageCopy = L0::zeCommandListAppendImageCopy;
    pDdiTable->pfnAppendImageCopyRegion = L0::zeCommandListAppendImageCopyRegion;
    pDdiTable->pfnAppendImageCopyToMemory = L0::zeCommandListAppendImageCopyToMemory;
    pDdiTable->pfnAppendImageCopyFromMemory = L0::zeCommandListAppendImageCopyFromMemory;
    pDdiTable->pfnAppendMemoryPrefetch = L0::zeCommandListAppendMemoryPrefetch;
    pDdiTable->pfnAppendMemAdvise = L0::zeCommandListAppendMemAdvise;
    pDdiTable->pfnAppendSignalEvent = L0::zeCommandListAppendSignalEvent;
    pDdiTable->pfnAppendWaitOnEvents = L0::zeCommandListAppendWaitOnEvents;
    pDdiTable->pfnAppendEventReset = L0::zeCommandListAppendEventReset;
    pDdiTable->pfnAppendLaunchCooperativeKernel =
        nullptr; // zeCommandListAppendLaunchCooperativeKernel
    pDdiTable->pfnAppendLaunchKernelIndirect = nullptr; // zeCommandListAppendLaunchKernelIndirect
    pDdiTable->pfnAppendLaunchMultipleKernelsIndirect =
        nullptr; // zeCommandListAppendLaunchMultipleKernelsIndirect
    pDdiTable->pfnAppendWriteGlobalTimestamp = L0::zeCommandListAppendWriteGlobalTimestamp;
    pDdiTable->pfnAppendMemoryCopyFromContext = L0::zeCommandListAppendMemoryCopyFromContext;
    pDdiTable->pfnAppendQueryKernelTimestamps = L0::zeCommandListAppendQueryKernelTimestamps;
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetFenceProcAddrTable(ze_api_version_t version,
                                                            ze_fence_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnCreate = L0::zeFenceCreate;
    pDdiTable->pfnDestroy = L0::zeFenceDestroy;
    pDdiTable->pfnHostSynchronize = L0::zeFenceHostSynchronize;
    pDdiTable->pfnQueryStatus = L0::zeFenceQueryStatus;
    pDdiTable->pfnReset = L0::zeFenceReset;
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetEventPoolProcAddrTable(ze_api_version_t version, ze_event_pool_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnCreate = L0::zeEventPoolCreate;
    pDdiTable->pfnDestroy = L0::zeEventPoolDestroy;
    pDdiTable->pfnGetIpcHandle = L0::zeEventPoolGetIpcHandle;
    pDdiTable->pfnOpenIpcHandle = L0::zeEventPoolOpenIpcHandle;
    pDdiTable->pfnCloseIpcHandle = L0::zeEventPoolCloseIpcHandle;
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetEventProcAddrTable(ze_api_version_t version,
                                                            ze_event_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnCreate = L0::zeEventCreate;
    pDdiTable->pfnDestroy = L0::zeEventDestroy;
    pDdiTable->pfnHostSignal = L0::zeEventHostSignal;
    pDdiTable->pfnHostSynchronize = L0::zeEventHostSynchronize;
    pDdiTable->pfnQueryStatus = L0::zeEventQueryStatus;
    pDdiTable->pfnHostReset = L0::zeEventHostReset;
    pDdiTable->pfnQueryKernelTimestamp = L0::zeEventQueryKernelTimestamp;
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetImageProcAddrTable(ze_api_version_t version,
                                                            ze_image_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnGetProperties = nullptr; // zeImageGetProperties
    pDdiTable->pfnCreate = nullptr;        // zeImageCreate
    pDdiTable->pfnDestroy = nullptr;       // zeImageDestroy
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetModuleProcAddrTable(ze_api_version_t version,
                                                             ze_module_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnCreate = nullptr;             // zeModuleCreate
    pDdiTable->pfnDestroy = nullptr;            // zeModuleDestroy
    pDdiTable->pfnDynamicLink = nullptr;        // zeModuleDynamicLink
    pDdiTable->pfnGetNativeBinary = nullptr;    // zeModuleGetNativeBinary
    pDdiTable->pfnGetGlobalPointer = nullptr;   // zeModuleGetGlobalPointer
    pDdiTable->pfnGetKernelNames = nullptr;     // zeModuleGetKernelNames
    pDdiTable->pfnGetFunctionPointer = nullptr; // zeModuleGetFunctionPointer
    pDdiTable->pfnGetProperties = nullptr;      // zeModuleGetProperties
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGetModuleBuildLogProcAddrTable(ze_api_version_t version,
                                 ze_module_build_log_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnDestroy = nullptr;   // zeModuleBuildLogDestroy
    pDdiTable->pfnGetString = nullptr; // zeModuleBuildLogGetString
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetKernelProcAddrTable(ze_api_version_t version,
                                                             ze_kernel_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnCreate = nullptr;           // zeKernelCreate
    pDdiTable->pfnDestroy = nullptr;          // zeKernelDestroy
    pDdiTable->pfnSetGroupSize = nullptr;     // zeKernelSetGroupSize
    pDdiTable->pfnSuggestGroupSize = nullptr; // zeKernelSuggestGroupSize
    pDdiTable->pfnSuggestMaxCooperativeGroupCount =
        nullptr;                                 // zeKernelSuggestMaxCooperativeGroupCount
    pDdiTable->pfnSetArgumentValue = nullptr;    // zeKernelSetArgumentValue
    pDdiTable->pfnSetIndirectAccess = nullptr;   // zeKernelSetIndirectAccess
    pDdiTable->pfnGetIndirectAccess = nullptr;   // zeKernelGetIndirectAccess
    pDdiTable->pfnGetSourceAttributes = nullptr; // zeKernelGetSourceAttributes
    pDdiTable->pfnGetProperties = nullptr;       // zeKernelGetProperties
    pDdiTable->pfnSetCacheConfig = nullptr;      // zeKernelSetCacheConfig
    pDdiTable->pfnGetName = nullptr;             // zeKernelGetName
    return ZE_RESULT_SUCCESS;
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGetSamplerProcAddrTable(ze_api_version_t version,
                                                              ze_sampler_dditable_t *pDdiTable) {
    if (nullptr == pDdiTable)
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    if (ZE_API_VERSION_CURRENT < version)
        return ZE_RESULT_ERROR_UNKNOWN;

    pDdiTable->pfnCreate = nullptr;  // zeSamplerCreate
    pDdiTable->pfnDestroy = nullptr; // zeSamplerDestroy
    return ZE_RESULT_SUCCESS;
}
#if defined(__cplusplus)
}
#endif
