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

#include "bcesdk/bos/response/get_bucket_acl_response.h"
#include "bcesdk/util/util.h"
#include <json/json.h>

BEGIN_CPPSDK_NAMESPACE

int GetBucketAclResponse::deserialize(Json::Value &root) {
    _owner.id = root["owner"]["id"].asString();

    Json::Value &arr = root["accessControlList"];
    _access_control_list.resize(arr.size());
    for (unsigned int i = 0; i < arr.size(); i++) {
        Json::Value &access_control = arr[i];
        Grant &ac = _access_control_list[i];
        Json::Value &grantee = access_control["grantee"];
        ac.grantee.resize(grantee.size());
        for (unsigned int j = 0; j < grantee.size(); ++j) {
            ac.grantee[j].id = grantee[j]["id"].asString();
        }
        Json::Value &permission = access_control["permission"];
        for (unsigned int j = 0; j < permission.size(); ++j) {
            ac.permission.push_back(permission[j].asString()); 
        }
    }

    return RET_OK;
}

END_CPPSDK_NAMESPACE

