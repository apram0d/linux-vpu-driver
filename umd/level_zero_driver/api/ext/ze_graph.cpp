/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "level_zero_driver/api/ext/ze_graph.hpp"
#include "level_zero/ze_graph_profiling_ext.h"
#include "level_zero_driver/ext/source/graph/graph.hpp"
#include "level_zero_driver/core/source/cmdlist/cmdlist.hpp"
#include "vpu_driver/source/utilities/log.hpp"

#include <dlfcn.h>
#include <memory>
#include <third_party/level-zero/include/loader/ze_loader.h>

namespace L0 {
static ze_result_t translateHandle(zel_handle_type_t type, void *handler, void **pHandler) {
    static void *loaderHandle = dlopen("libze_loader.so.1", RTLD_LAZY | RTLD_LOCAL);
    if (loaderHandle == nullptr) {
        LOG_E("Failed to open libze_loader.so.1 library");
        return ZE_RESULT_ERROR_UNKNOWN;
    }

    static void *functionPointer = dlsym(loaderHandle, "zelLoaderTranslateHandle");
    if (functionPointer == nullptr) {
        LOG_E("Failed to get 'zelLoaderTranslateHandle' from libze_loader.so.1, reason: %s",
              dlerror());
        return ZE_RESULT_ERROR_UNKNOWN;
    }

    static auto *pLoaderTranslateHandler =
        reinterpret_cast<decltype(zelLoaderTranslateHandle) *>(functionPointer);

    auto result = pLoaderTranslateHandler(type, handler, pHandler);
    if (result != ZE_RESULT_SUCCESS)
        LOG_E("Failed to translate handler of type %i", type);

    return result;
}

template <class T>
static inline ze_result_t translateHandle(zel_handle_type_t type, T handler, T *pHandler) {
    return translateHandle(type, handler, reinterpret_cast<void **>(pHandler));
}

template <class T>
static inline ze_result_t translateHandle(zel_handle_type_t type, T &handler) {
    return translateHandle(type, handler, &handler);
}

ze_result_t ZE_APICALL zeGraphCreate(ze_context_handle_t hContext,
                                     ze_device_handle_t hDevice,
                                     const ze_graph_desc_t *pDesc,
                                     ze_graph_handle_t *phGraph) {
    if (hDevice == nullptr || hContext == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    auto result = translateHandle(ZEL_HANDLE_CONTEXT, hContext);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    result = translateHandle(ZEL_HANDLE_DEVICE, hDevice);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    return L0::Graph::create(hContext, hDevice, pDesc, phGraph);
}

ze_result_t ZE_APICALL zeGraphDestroy(ze_graph_handle_t hGraph) {
    if (hGraph == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::Graph::fromHandle(hGraph)->destroy();
}

ze_result_t ZE_APICALL zeGraphGetNativeBinary(ze_graph_handle_t hGraph,
                                              size_t *pSize,
                                              uint8_t *pGraphNativeBinary) {
    if (hGraph == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::Graph::fromHandle(hGraph)->getNativeBinary(pSize, pGraphNativeBinary);
}

ze_result_t ZE_APICALL zeGraphGetProperties(ze_graph_handle_t hGraph,
                                            ze_graph_properties_t *pGraphProperties) {
    if (hGraph == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::Graph::fromHandle(hGraph)->getProperties(pGraphProperties);
}

ze_result_t ZE_APICALL
zeGraphGetArgumentProperties(ze_graph_handle_t hGraph,
                             uint32_t argIndex,
                             ze_graph_argument_properties_t *pGraphArgumentProperties) {
    if (hGraph == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::Graph::fromHandle(hGraph)->getArgumentProperties(argIndex, pGraphArgumentProperties);
}

ze_result_t ZE_APICALL zeGraphSetArgumentValue(ze_graph_handle_t hGraph,
                                               uint32_t argIndex,
                                               const void *pArgValue) {
    if (hGraph == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::Graph::fromHandle(hGraph)->setArgumentValue(argIndex, pArgValue);
}

ze_result_t ZE_APICALL zeAppendGraphInitialize(ze_command_list_handle_t hCommandList,
                                               ze_graph_handle_t hGraph,
                                               ze_event_handle_t hSignalEvent,
                                               uint32_t numWaitEvents,
                                               ze_event_handle_t *phWaitEvents) {
    if (hCommandList == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    auto result = translateHandle(ZEL_HANDLE_COMMAND_LIST, hCommandList);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    if (hSignalEvent != nullptr) {
        auto result = translateHandle(ZEL_HANDLE_EVENT, hSignalEvent);
        if (result != ZE_RESULT_SUCCESS)
            return result;
    }

    std::unique_ptr<ze_event_handle_t[]> phWaitEventsTranslated = nullptr;
    if (numWaitEvents > 0) {
        if (phWaitEvents == nullptr)
            return ZE_RESULT_ERROR_INVALID_SIZE;

        phWaitEventsTranslated =
            std::unique_ptr<ze_event_handle_t[]>(new ze_event_handle_t[numWaitEvents]);
        for (uint32_t i = 0; i < numWaitEvents; i++) {
            auto result =
                translateHandle(ZEL_HANDLE_EVENT, phWaitEvents[i], &phWaitEventsTranslated[i]);
            if (result != ZE_RESULT_SUCCESS)
                return result;
        }
    }

    return L0::CommandList::fromHandle(hCommandList)
        ->appendGraphInitialize(hGraph, hSignalEvent, numWaitEvents, phWaitEventsTranslated.get());
}

ze_result_t ZE_APICALL zeAppendGraphExecute(ze_command_list_handle_t hCommandList,
                                            ze_graph_handle_t hGraph,
                                            ze_graph_profiling_query_handle_t hProfilingQuery,
                                            ze_event_handle_t hSignalEvent,
                                            uint32_t numWaitEvents,
                                            ze_event_handle_t *phWaitEvents) {
    if (hCommandList == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    auto result = translateHandle(ZEL_HANDLE_COMMAND_LIST, hCommandList);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    if (hSignalEvent != nullptr) {
        auto result = translateHandle(ZEL_HANDLE_EVENT, hSignalEvent);
        if (result != ZE_RESULT_SUCCESS)
            return result;
    }

    std::unique_ptr<ze_event_handle_t[]> phWaitEventsTranslated = nullptr;
    if (numWaitEvents > 0) {
        if (phWaitEvents == nullptr)
            return ZE_RESULT_ERROR_INVALID_SIZE;

        phWaitEventsTranslated =
            std::unique_ptr<ze_event_handle_t[]>(new ze_event_handle_t[numWaitEvents]);
        for (uint32_t i = 0; i < numWaitEvents; i++) {
            auto result =
                translateHandle(ZEL_HANDLE_EVENT, phWaitEvents[i], &phWaitEventsTranslated[i]);
            if (result != ZE_RESULT_SUCCESS)
                return result;
        }
    }

    return L0::CommandList::fromHandle(hCommandList)
        ->appendGraphExecute(hGraph,
                             hProfilingQuery,
                             hSignalEvent,
                             numWaitEvents,
                             phWaitEventsTranslated.get());
}

ze_result_t ZE_APICALL
zeDeviceGetGraphProperties(ze_device_handle_t hDevice,
                           ze_device_graph_properties_t *pDeviceGraphProperties) {
    if (hDevice == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    auto result = translateHandle(ZEL_HANDLE_DEVICE, hDevice);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    return L0::Graph::getDeviceGraphProperties(pDeviceGraphProperties);
}

ze_result_t ZE_APICALL
zeGraphProfilingPoolCreate(ze_graph_handle_t hGraph,
                           uint32_t count,
                           ze_graph_profiling_pool_handle_t *phProfilingPool) {
    if (hGraph == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::Graph::fromHandle(hGraph)->createProfilingPool(count, phProfilingPool);
}

ze_result_t ZE_APICALL
zeGraphProfilingPoolDestroy(ze_graph_profiling_pool_handle_t hProfilingPool) {
    if (hProfilingPool == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::GraphProfilingPool::fromHandle(hProfilingPool)->destroy();
}

ze_result_t ZE_APICALL
zeGraphProfilingQueryCreate(ze_graph_profiling_pool_handle_t hProfilingPool,
                            uint32_t index,
                            ze_graph_profiling_query_handle_t *phProfilingQuery) {
    if (hProfilingPool == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::GraphProfilingPool::fromHandle(hProfilingPool)
        ->createProfilingQuery(index, phProfilingQuery);
}

ze_result_t ZE_APICALL
zeGraphProfilingQueryDestroy(ze_graph_profiling_query_handle_t hProfilingQuery) {
    if (hProfilingQuery == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::GraphProfilingQuery::fromHandle(hProfilingQuery)->destroy();
}

ze_result_t ZE_APICALL
zeGraphProfilingQueryGetData(ze_graph_profiling_query_handle_t hProfilingQuery,
                             ze_graph_profiling_type_t type,
                             uint32_t *pSize,
                             uint8_t *pData) {
    if (hProfilingQuery == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    return L0::GraphProfilingQuery::fromHandle(hProfilingQuery)->getData(type, pSize, pData);
}

ze_result_t ZE_APICALL zeDeviceGetProfilingDataProperties(
    ze_device_handle_t hDevice,
    ze_device_profiling_data_properties_t *pDeviceProfilingDataProperties) {
    if (hDevice == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
    }

    auto result = translateHandle(ZEL_HANDLE_DEVICE, hDevice);
    if (result != ZE_RESULT_SUCCESS) {
        return result;
    }

    return L0::Graph::getProfilingDataProperties(pDeviceProfilingDataProperties);
}
} // namespace L0

extern "C" {
ZE_APIEXPORT ze_result_t ZE_APICALL zeGraphCreate(ze_context_handle_t hContext,
                                                  ze_device_handle_t hDevice,
                                                  const ze_graph_desc_t *pDesc,
                                                  ze_graph_handle_t *phGraph) {
    return L0::zeGraphCreate(hContext, hDevice, pDesc, phGraph);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGraphDestroy(ze_graph_handle_t hGraph) {
    return L0::zeGraphDestroy(hGraph);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGraphGetNativeBinary(ze_graph_handle_t hGraph,
                                                           size_t *pSize,
                                                           uint8_t *pGraphNativeBinary) {
    return L0::zeGraphGetNativeBinary(hGraph, pSize, pGraphNativeBinary);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGraphGetProperties(ze_graph_handle_t hGraph,
                                                         ze_graph_properties_t *pGraphProperties) {
    return L0::zeGraphGetProperties(hGraph, pGraphProperties);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGraphGetArgumentProperties(ze_graph_handle_t hGraph,
                             uint32_t argIndex,
                             ze_graph_argument_properties_t *pGraphArgumentProperties) {
    return L0::zeGraphGetArgumentProperties(hGraph, argIndex, pGraphArgumentProperties);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeGraphSetArgumentValue(ze_graph_handle_t hGraph,
                                                            uint32_t argIndex,
                                                            const void *pArgValue) {
    return L0::zeGraphSetArgumentValue(hGraph, argIndex, pArgValue);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeAppendGraphInitialize(ze_command_list_handle_t hCommandList,
                                                            ze_graph_handle_t hGraph,
                                                            ze_event_handle_t hSignalEvent,
                                                            uint32_t numWaitEvents,
                                                            ze_event_handle_t *phWaitEvents) {
    return L0::zeAppendGraphInitialize(hCommandList,
                                       hGraph,
                                       hSignalEvent,
                                       numWaitEvents,
                                       phWaitEvents);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeAppendGraphExecute(ze_command_list_handle_t hCommandList,
                     ze_graph_handle_t hGraph,
                     ze_graph_profiling_query_handle_t hProfilingQuery,
                     ze_event_handle_t hSignalEvent,
                     uint32_t numWaitEvents,
                     ze_event_handle_t *phWaitEvents) {
    return L0::zeAppendGraphExecute(hCommandList,
                                    hGraph,
                                    hProfilingQuery,
                                    hSignalEvent,
                                    numWaitEvents,
                                    phWaitEvents);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeDeviceGetGraphProperties(ze_device_handle_t hDevice,
                           ze_device_graph_properties_t *pDeviceGraphProperties) {
    return L0::zeDeviceGetGraphProperties(hDevice, pDeviceGraphProperties);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGraphProfilingPoolCreate(ze_graph_handle_t hGraph,
                           uint32_t count,
                           ze_graph_profiling_pool_handle_t *phProfilingPool) {
    return L0::zeGraphProfilingPoolCreate(hGraph, count, phProfilingPool);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGraphProfilingPoolDestroy(ze_graph_profiling_pool_handle_t hProfilingPool) {
    return L0::zeGraphProfilingPoolDestroy(hProfilingPool);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGraphProfilingQueryCreate(ze_graph_profiling_pool_handle_t hProfilingPool,
                            uint32_t index,
                            ze_graph_profiling_query_handle_t *phProfilingQuery) {
    return L0::zeGraphProfilingQueryCreate(hProfilingPool, index, phProfilingQuery);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGraphProfilingQueryDestroy(ze_graph_profiling_query_handle_t hProfilingQuery) {
    return L0::zeGraphProfilingQueryDestroy(hProfilingQuery);
}

ZE_APIEXPORT ze_result_t ZE_APICALL
zeGraphProfilingQueryGetData(ze_graph_profiling_query_handle_t hProfilingQuery,
                             ze_graph_profiling_type_t type,
                             uint32_t *pSize,
                             uint8_t *pData) {
    return L0::zeGraphProfilingQueryGetData(hProfilingQuery, type, pSize, pData);
}

ZE_APIEXPORT ze_result_t ZE_APICALL zeDeviceGetProfilingDataProperties(
    ze_device_handle_t hDevice,
    ze_device_profiling_data_properties_t *pDeviceProfilingDataProperties) {
    return L0::zeDeviceGetProfilingDataProperties(hDevice, pDeviceProfilingDataProperties);
}
} // extern "C"
