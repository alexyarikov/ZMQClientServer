/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: query_by_compensation_range_res.proto */

#ifndef PROTOBUF_C_query_5fby_5fcompensation_5frange_5fres_2eproto__INCLUDED
#define PROTOBUF_C_query_5fby_5fcompensation_5frange_5fres_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1001001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _QueryByCompensationRangeResponse QueryByCompensationRangeResponse;


/* --- enums --- */


/* --- messages --- */

struct  _QueryByCompensationRangeResponse
{
  ProtobufCMessage base;
  uint64_t count;
};
#define QUERY_BY_COMPENSATION_RANGE_RESPONSE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&query_by_compensation_range_response__descriptor) \
    , 0 }


/* QueryByCompensationRangeResponse methods */
void   query_by_compensation_range_response__init
                     (QueryByCompensationRangeResponse         *message);
size_t query_by_compensation_range_response__get_packed_size
                     (const QueryByCompensationRangeResponse   *message);
size_t query_by_compensation_range_response__pack
                     (const QueryByCompensationRangeResponse   *message,
                      uint8_t             *out);
size_t query_by_compensation_range_response__pack_to_buffer
                     (const QueryByCompensationRangeResponse   *message,
                      ProtobufCBuffer     *buffer);
QueryByCompensationRangeResponse *
       query_by_compensation_range_response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   query_by_compensation_range_response__free_unpacked
                     (QueryByCompensationRangeResponse *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*QueryByCompensationRangeResponse_Closure)
                 (const QueryByCompensationRangeResponse *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor query_by_compensation_range_response__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_query_5fby_5fcompensation_5frange_5fres_2eproto__INCLUDED */