/**
 * Copyright 2014 (c) Baidu, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */

#include "bcesdk/bos/response/delete_multiple_objects_response.h"
#include "bcesdk/util/util.h"
#include <json/json.h>

BEGIN_CPPSDK_NAMESPACE

void DeleteMultipleObjectsResponse::do_handle_chain(HttpResponse &) {
    LOG(DEBUG) << "response body: " << _buffer;
    _errors.clear();
    if (_buffer.empty()) {
        return;
    }

    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(_buffer, root)) {
        LOG(ERROR) << "parse response fail";
        set_error(STATUS_INVALID_RESPONSE, "MalformedJson");
        return;
    }
    try {
        Json::Value &errors_arr = root["errors"];
        size_t num_of_errors = errors_arr.size();
        _errors.reserve(num_of_errors);
        for (unsigned int i = 0; i < num_of_errors; i++) {
            Json::Value &error_obj = errors_arr[i];
            DeleteError delete_error;
            delete_error.key = error_obj["key"].asString();
            delete_error.code = error_obj["code"].asString();
            delete_error.message = error_obj["message"].asString();
            _errors.push_back(delete_error);
        }
    } catch (...) {
        LOG(ERROR) << "invalid response json content: " <<  _buffer;
        set_error(STATUS_INVALID_RESPONSE, "InvalidContent");
    }
}

END_CPPSDK_NAMESPACE
