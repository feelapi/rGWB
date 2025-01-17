// Write / read to file or other sources...

#include "csmfwddecl.hxx"
#include "csmsave.hxx"

#ifdef __cplusplus
extern "C" {
#endif

// Write...

void csmsave_write_bool(struct csmsave_t *csmsave, CSMBOOL value);

void csmsave_write_uchar(struct csmsave_t *csmsave, unsigned char value);

void csmsave_write_ushort(struct csmsave_t *csmsave, unsigned short value);
#define csmsave_write_enum(csmsave, value) csmsave_write_ushort(csmsave, (unsigned short)value)

void csmsave_write_ulong(struct csmsave_t *csmsave, unsigned long value);

void csmsave_write_double(struct csmsave_t *csmsave, double value);

void csmsave_write_float(struct csmsave_t *csmsave, float value);

void csmsave_write_string(struct csmsave_t *csmsave, const char *value);

void csmsave_write_string_optional(struct csmsave_t *csmsave, const char *value);

void csmsave_write_arr_ulong(struct csmsave_t *csmsave, const csmArrULong *array);

void csmsave_dontuse_write_arr_st(
                        struct csmsave_t *csmsave,
                        const csmArrayStruct(csmsave_item_t) *array, const char *type_name,
                        csmsave_FPtr_write_struct func_write_struct);
#define csmsave_write_arr_st(csmsave, array, func_write_struct, type)\
(/*lint -save -e505*/\
    ((const csmArrayStruct(type) *)array == array),\
    CSMSAVE_CHECK_FUNC_WRITE_STRUCT(func_write_struct, type),\
    csmsave_dontuse_write_arr_st(csmsave, (const csmArrayStruct(csmsave_item_t) *)array, #type, (csmsave_FPtr_write_struct)func_write_struct)\
)/*lint -restore*/

void csmsave_dontuse_write_st(
                        struct csmsave_t *csmsave,
                        const struct csmsave_item_t *item, const char *type_name,
                        csmsave_FPtr_write_struct func_write_struct);
#define csmsave_write_st(csmsave, item, func_write_struct, type)\
(/*lint -save -e505*/\
    ((const struct type *)item == item),\
    CSMSAVE_CHECK_FUNC_WRITE_STRUCT(func_write_struct, type),\
    csmsave_dontuse_write_st(csmsave, (const struct csmsave_item_t *)item, #type, (csmsave_FPtr_write_struct)func_write_struct)\
)/*lint -restore*/

void csmsave_dontuse_write_optional_st(
                        struct csmsave_t *csmsave,
                        const struct csmsave_item_t *item, const char *type_name,
                        csmsave_FPtr_write_struct func_write_struct);
#define csmsave_write_optional_st(csmsave, item, func_write_struct, type)\
(/*lint -save -e505*/\
    ((const struct type *)item == item),\
    CSMSAVE_CHECK_FUNC_WRITE_STRUCT(func_write_struct, type),\
    csmsave_dontuse_write_optional_st(csmsave, (const struct csmsave_item_t *)item, #type, (csmsave_FPtr_write_struct)func_write_struct)\
)/*lint -restore*/


// Read...

CSMBOOL csmsave_read_bool(struct csmsave_t *csmsave);

unsigned char csmsave_read_uchar(struct csmsave_t *csmsave);

unsigned short csmsave_read_ushort(struct csmsave_t *csmsave);
#define csmsave_read_enum(csmsave, enum_type) (enum enum_type)csmsave_read_ushort(csmsave)

unsigned long csmsave_read_ulong(struct csmsave_t *csmsave);

double csmsave_read_double(struct csmsave_t *csmsave);

float csmsave_read_float(struct csmsave_t *csmsave);

CONSTRUCTOR(char *, csmsave_read_string, (struct csmsave_t *csmsave));

CONSTRUCTOR(char *, csmsave_read_string_optional, (struct csmsave_t *csmsave));

CONSTRUCTOR(csmArrULong *, csmsave_read_arr_ulong, (struct csmsave_t *csmsave));

CONSTRUCTOR(csmArrayStruct(csmsave_item_t) *, csmsave_dontuse_read_arr_st, (struct csmsave_t *csmsave, const char *type_name, csmsave_FPtr_read_struct func_read_struct));
#define csmsave_read_arr_st(csmsave, func_read_struct, type)\
(/*lint -save -e505*/\
    CSMSAVE_CHECK_FUNC_READ_STRUCT(func_read_struct, type),\
    (csmArrayStruct(type) *)csmsave_dontuse_read_arr_st(csmsave, #type, (csmsave_FPtr_read_struct)func_read_struct)\
)/*lint -restore*/

CONSTRUCTOR(struct csmsave_item_t *, csmsave_dontuse_read_st, (struct csmsave_t *csmsave, const char *type_name, csmsave_FPtr_read_struct func_read_struct));
#define csmsave_read_st(csmsave, func_read_struct, type)\
(/*lint -save -e505*/\
    CSMSAVE_CHECK_FUNC_READ_STRUCT(func_read_struct, type),\
    (struct type *)csmsave_dontuse_read_st(csmsave, #type, (csmsave_FPtr_read_struct)func_read_struct)\
)/*lint -restore*/

CONSTRUCTOR(struct csmsave_item_t *, csmsave_dontuse_read_optional_st, (struct csmsave_t *csmsave, const char *type_name, csmsave_FPtr_read_struct func_read_struct));
#define csmsave_read_optional_st(csmsave, func_read_struct, type)\
(/*lint -save -e505*/\
    CSMSAVE_CHECK_FUNC_READ_STRUCT(func_read_struct, type),\
    (struct type *)csmsave_dontuse_read_optional_st(csmsave, #type, (csmsave_FPtr_read_struct)func_read_struct)\
)/*lint -restore*/

#ifdef __cplusplus
}
#endif



