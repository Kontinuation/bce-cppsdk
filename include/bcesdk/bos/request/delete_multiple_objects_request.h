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
#ifndef BAIDU_BOS_CPPSDK_BOS_REQUEST_DELETE_MULTIPLE_OBJECTS_REQUEST_H
#define BAIDU_BOS_CPPSDK_BOS_REQUEST_DELETE_MULTIPLE_OBJECTS_REQUEST_H

#include "bcesdk/bos/request/bucket_request.h"
#include "bcesdk/common/memory_stream.h"

#include <string>
#include <vector>

BEGIN_CPPSDK_NAMESPACE

class DeleteMultipleObjectsRequest : public BucketRequest {
public:
    DeleteMultipleObjectsRequest(
        const std::string &bucket_name,
        const std::vector<std::string> &object_keys = std::vector<std::string>())
        : BucketRequest(bucket_name), _object_keys(object_keys),
          _content(NULL), _content_stream(NULL) {
    }

    virtual ~DeleteMultipleObjectsRequest() {
        if (_content_stream) {
            delete _content_stream;
            _content_stream = NULL;
        }

        if (_content) {
            delete _content;
            _content = NULL;
        }
    }

    void add_object_key(const std::string &object_key) {
        _object_keys.push_back(object_key);
    }

    int build_command_specific(HttpRequest *request);

private:
    std::vector<std::string> _object_keys;
    std::string             *_content;
    InputStream             *_content_stream;
};

END_CPPSDK_NAMESPACE
#endif

