/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: delete_req.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "delete_req.pb-c.h"
void   delete_request__init
                     (DeleteRequest         *message)
{
  static DeleteRequest init_value = DELETE_REQUEST__INIT;
  *message = init_value;
}
size_t delete_request__get_packed_size
                     (const DeleteRequest *message)
{
  assert(message->base.descriptor == &delete_request__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t delete_request__pack
                     (const DeleteRequest *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &delete_request__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t delete_request__pack_to_buffer
                     (const DeleteRequest *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &delete_request__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
DeleteRequest *
       delete_request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (DeleteRequest *)
     protobuf_c_message_unpack (&delete_request__descriptor,
                                allocator, len, data);
}
void   delete_request__free_unpacked
                     (DeleteRequest *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &delete_request__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor delete_request__field_descriptors[1] =
{
  {
    "id",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT64,
    0,   /* quantifier_offset */
    offsetof(DeleteRequest, id),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned delete_request__field_indices_by_name[] = {
  0,   /* field[0] = id */
};
static const ProtobufCIntRange delete_request__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor delete_request__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "DeleteRequest",
  "DeleteRequest",
  "DeleteRequest",
  "",
  sizeof(DeleteRequest),
  1,
  delete_request__field_descriptors,
  delete_request__field_indices_by_name,
  1,  delete_request__number_ranges,
  (ProtobufCMessageInit) delete_request__init,
  NULL,NULL,NULL    /* reserved[123] */
};
