/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: insert_res.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "insert_res.pb-c.h"
void   insert_response__init
                     (InsertResponse         *message)
{
  static InsertResponse init_value = INSERT_RESPONSE__INIT;
  *message = init_value;
}
size_t insert_response__get_packed_size
                     (const InsertResponse *message)
{
  assert(message->base.descriptor == &insert_response__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insert_response__pack
                     (const InsertResponse *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insert_response__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insert_response__pack_to_buffer
                     (const InsertResponse *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insert_response__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
InsertResponse *
       insert_response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (InsertResponse *)
     protobuf_c_message_unpack (&insert_response__descriptor,
                                allocator, len, data);
}
void   insert_response__free_unpacked
                     (InsertResponse *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &insert_response__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor insert_response__field_descriptors[2] =
{
  {
    "result",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(InsertResponse, result),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "result_msg",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(InsertResponse, result_msg),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insert_response__field_indices_by_name[] = {
  0,   /* field[0] = result */
  1,   /* field[1] = result_msg */
};
static const ProtobufCIntRange insert_response__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor insert_response__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "InsertResponse",
  "InsertResponse",
  "InsertResponse",
  "",
  sizeof(InsertResponse),
  2,
  insert_response__field_descriptors,
  insert_response__field_indices_by_name,
  1,  insert_response__number_ranges,
  (ProtobufCMessageInit) insert_response__init,
  NULL,NULL,NULL    /* reserved[123] */
};
