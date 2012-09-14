/* Do not edit. File generated by rastro. */

#include "auto-generated.h"

/* Rastro function implementation for 'lws' */
void rst_event_lws_ptr(rst_buffer_t *ptr, u_int16_t type, u_int64_t l0, u_int16_t w0, const char* s0)
{
  rst_startevent(ptr, type<<18|0x24510);
  RST_PUT(ptr, u_int64_t, l0);
  RST_PUT(ptr, u_int16_t, w0);
  RST_PUT_STR(ptr, s0);
  rst_endevent(ptr);
}
/* Rastro function implementation for 'lws' - fortran support */
void rst_event_lws_f_( int16_t *type, int64_t* l0, int16_t* w0, const char* s0)
{
  rst_event_lws ((u_int16_t)* type, (u_int64_t)* l0, (u_int16_t)* w0,  s0);
}

/* Rastro function implementation for 'wlsfcd' */
void rst_event_wlsfcd_ptr(rst_buffer_t *ptr, u_int16_t type, u_int16_t w0, u_int64_t l0, const char* s0, float f0, u_int8_t c0, double d0)
{
  rst_startevent(ptr, type<<18|0x2435);
  RST_PUT(ptr, u_int32_t, 0x26100000);
  RST_PUT(ptr, double, d0);
  RST_PUT(ptr, u_int64_t, l0);
  RST_PUT(ptr, float, f0);
  RST_PUT(ptr, u_int16_t, w0);
  RST_PUT(ptr, u_int8_t, c0);
  RST_PUT_STR(ptr, s0);
  rst_endevent(ptr);
}
/* Rastro function implementation for 'wlsfcd' - fortran support */
void rst_event_wlsfcd_f_( int16_t *type, int16_t* w0, int64_t* l0, const char* s0, float* f0, int8_t* c0, double* d0)
{
  rst_event_wlsfcd ((u_int16_t)* type, (u_int16_t)* w0, (u_int64_t)* l0,  s0, (float)* f0, (u_int8_t)* c0, (double)* d0);
}

/* Rastro function implementation for 'iwlsifcd' */
void rst_event_iwlsifcd_ptr(rst_buffer_t *ptr, u_int16_t type, u_int32_t i0, u_int16_t w0, u_int64_t l0, const char* s0, u_int32_t i1, float f0, u_int8_t c0, double d0)
{
  rst_startevent(ptr, type<<18|0x2437);
  RST_PUT(ptr, u_int32_t, 0x27561000);
  RST_PUT(ptr, double, d0);
  RST_PUT(ptr, u_int64_t, l0);
  RST_PUT(ptr, float, f0);
  RST_PUT(ptr, u_int32_t, i0);
  RST_PUT(ptr, u_int32_t, i1);
  RST_PUT(ptr, u_int16_t, w0);
  RST_PUT(ptr, u_int8_t, c0);
  RST_PUT_STR(ptr, s0);
  rst_endevent(ptr);
}
/* Rastro function implementation for 'iwlsifcd' - fortran support */
void rst_event_iwlsifcd_f_( int16_t *type, int32_t* i0, int16_t* w0, int64_t* l0, const char* s0, int32_t* i1, float* f0, int8_t* c0, double* d0)
{
  rst_event_iwlsifcd ((u_int16_t)* type, (u_int32_t)* i0, (u_int16_t)* w0, (u_int64_t)* l0,  s0, (u_int32_t)* i1, (float)* f0, (u_int8_t)* c0, (double)* d0);
}

void rst_init_f_(int64_t *id1, int64_t *id2)
{
  rst_init((u_int64_t)* id1, (u_int64_t)* id2);
}
void rst_finalize_f_ ()
{
  rst_finalize();
}