/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: common.proto */

#ifndef PROTOBUF_C_common_2eproto__INCLUDED
#define PROTOBUF_C_common_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1001001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Employee Employee;


/* --- enums --- */

typedef enum _Employee__Gender {
  EMPLOYEE__GENDER__MALE = 0,
  EMPLOYEE__GENDER__FEMALE = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(EMPLOYEE__GENDER)
} Employee__Gender;

/* --- messages --- */

struct  _Employee
{
  ProtobufCMessage base;
  uint64_t id;
  char *name;
  Employee__Gender gender;
  uint64_t date_of_birth;
  double last_10_annual_salary;
  double last_10_annual_bonus;
  double last_10_annual_sales;
};
#define EMPLOYEE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&employee__descriptor) \
    , 0, NULL, 0, 0, 0, 0, 0 }


/* Employee methods */
void   employee__init
                     (Employee         *message);
size_t employee__get_packed_size
                     (const Employee   *message);
size_t employee__pack
                     (const Employee   *message,
                      uint8_t             *out);
size_t employee__pack_to_buffer
                     (const Employee   *message,
                      ProtobufCBuffer     *buffer);
Employee *
       employee__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   employee__free_unpacked
                     (Employee *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Employee_Closure)
                 (const Employee *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor employee__descriptor;
extern const ProtobufCEnumDescriptor    employee__gender__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_common_2eproto__INCLUDED */
