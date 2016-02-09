/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: query_by_compensation_range_req.proto */

#ifndef PROTOBUF_C_query_5fby_5fcompensation_5frange_5freq_2eproto__INCLUDED
#define PROTOBUF_C_query_5fby_5fcompensation_5frange_5freq_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1001001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _QueryByCompensationRangeRequest QueryByCompensationRangeRequest;


/* --- enums --- */


/* --- messages --- */

struct  _QueryByCompensationRangeRequest
{
  ProtobufCMessage base;
  double min;
  double max;
};
#define QUERY_BY_COMPENSATION_RANGE_REQUEST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&query_by_compensation_range_request__descriptor) \
    , 0, 0 }


/* QueryByCompensationRangeRequest methods */
void   query_by_compensation_range_request__init
                     (QueryByCompensationRangeRequest         *message);
size_t query_by_compensation_range_request__get_packed_size
                     (const QueryByCompensationRangeRequest   *message);
size_t query_by_compensation_range_request__pack
                     (const QueryByCompensationRangeRequest   *message,
                      uint8_t             *out);
size_t query_by_compensation_range_request__pack_to_buffer
                     (const QueryByCompensationRangeRequest   *message,
                      ProtobufCBuffer     *buffer);
QueryByCompensationRangeRequest *
       query_by_compensation_range_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   query_by_compensation_range_request__free_unpacked
                     (QueryByCompensationRangeRequest *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*QueryByCompensationRangeRequest_Closure)
                 (const QueryByCompensationRangeRequest *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor query_by_compensation_range_request__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_query_5fby_5fcompensation_5frange_5freq_2eproto__INCLUDED */
