cmake_minimum_required (VERSION 3.1)
project (bossdk)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 14)
add_definitions(-Wall -Wextra -g)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include(thirdlib/jsoncpp/jsoncpp.cmake)

set(MAIN_SRCS
  src/auth/auth.cpp
  src/bos/client.cpp
  src/bos/client_impl.cpp
  src/bos/model/copy_request.cpp
  src/bos/model/object_meta_data.cpp
  src/bos/model/upload_request.cpp
  src/bos/request/complete_multipart_upload_request.cpp
  src/bos/request/object_request.cpp
  src/bos/request/delete_multiple_objects_request.cpp
  src/bos/response/append_object_response.cpp
  src/bos/response/complete_multipart_upload_response.cpp
  src/bos/response/copy_object_response.cpp
  src/bos/response/copy_part_response.cpp
  src/bos/response/get_bucket_acl_response.cpp
  src/bos/response/get_bucket_location_response.cpp
  src/bos/response/get_object_response.cpp
  src/bos/response/init_multi_upload_response.cpp
  src/bos/response/list_buckets_response.cpp
  src/bos/response/list_multipart_uploads_response.cpp
  src/bos/response/list_objects_response.cpp
  src/bos/response/list_parts_response.cpp
  src/bos/response/delete_multiple_objects_response.cpp
  src/http/http_client.cpp
  src/http/http_request.cpp
  src/http/http_response.cpp
  src/model/bce_request.cpp
  src/model/bce_response.cpp
  src/model/json_response.cpp
  src/util/openssl_crypto_impl.cpp
  src/util/util.cpp
  )

add_definitions(
	-DVERSION="1.0"
)

add_library(bossdk SHARED ${MAIN_SRCS})
target_include_directories(bossdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(bossdk PUBLIC jsoncpp_static curl uuid crypto ssl pthread)

add_executable(api_demo example/api_demo.cpp example/api_test.cpp)
target_include_directories(api_demo PRIVATE include)
target_link_libraries(api_demo bossdk jsoncpp_static)
