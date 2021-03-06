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
#ifndef BAIDU_BOS_CPPSDK_BOS_REQUEST_PUT_BUCKET_ACL_REQUEST_H
#define BAIDU_BOS_CPPSDK_BOS_REQUEST_PUT_BUCKET_ACL_REQUEST_H

#include "bcesdk/bos/request/bucket_request.h"

BEGIN_CPPSDK_NAMESPACE

class PutBucketAclRequest : public  BucketRequest {
public:
    PutBucketAclRequest(const std::string &bucket_name, const std::string &acl) :
        BucketRequest(bucket_name), _acl(acl) {
    }

    virtual ~PutBucketAclRequest() {}

    int build_command_specific(HttpRequest *request) {
        request->set_method(HTTP_METHOD_PUT);
        request->add_parameter("acl");
        request->append_header("x-bce-acl", _acl);
        return RET_OK;
    }

private:
    std::string _acl;
};

END_CPPSDK_NAMESPACE
#endif
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
