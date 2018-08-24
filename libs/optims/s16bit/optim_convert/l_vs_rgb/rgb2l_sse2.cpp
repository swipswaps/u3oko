//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       rgb2l_sse2.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb.hpp"
#include "rgb_to_l_int.hpp"
#include "../hsl_vs_rgb/rgb_to_hsl_int.hpp"

#if defined(UUU_CPU_X86)

#if 0
#define RGB2L_PREFIX_SSE2                                                                                                                        \
                                                                                                                                                 \
  const __m128i _permute32 = _mm128_setr_epi32 (0, 1, 2, 0, 3, 4, 5, 3);                                                                         \
                                                                                                                                                 \
  const __m128i _permute_b8 = _mm128_setr_epi8 (0x00, 0x80, 0x80, 0x80, 0x03, 0x80, 0x80, 0x80, 0x06, 0x80, 0x80, 0x80, 0x09, 0x80, 0x80, 0x80); \
                                                                                                                                                 \
  const __m128i _permute_g8 = _mm128_setr_epi8 (0x01, 0x80, 0x80, 0x80, 0x04, 0x80, 0x80, 0x80, 0x07, 0x80, 0x80, 0x80, 0x0A, 0x80, 0x80, 0x80); \
                                                                                                                                                 \
  const __m128i _permute_r8 = _mm128_setr_epi8 (0x02, 0x80, 0x80, 0x80, 0x05, 0x80, 0x80, 0x80, 0x08, 0x80, 0x80, 0x80, 0x0B, 0x80, 0x80, 0x80);
#endif

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace l_vs_rgb {

UUU_SET_TARGET_CPU (sse2)
void
rgb24_to_l_sse2_float (::libs::optim::MCallInfo& _info)
{
  RGB2L_PREFIX (4);

  const __m128 _const_255      = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d255[0]);
  const __m128 _const_1_to_2   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_2[0]);
  const __m128 _const_1_to_255 = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_255[0]);

  __m128i _ir8;
  __m128i _ig8;
  __m128i _ib8;

  __m128i _i128_1;
  __m128i _i128_2;

  SPLIT_RGB24_SSE2_DEFINE_REGS;

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          _i128_1 = _mm_loadu_si128 (UUU_MEM_CAST<const __m128i*> (_rgb24));      //BOG0R0B1G1R1B2G2R2B3G3R3B4G4R4
          //_i128_1 = _mm_setr_epi8( 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F );//debug

          SPLIT_RGB24_SSE2 (_i128_1, _ir8, _ig8, _ib8);

          //convert RGB double word from 8 pixel to float;
          __m128 _temp_r = _mm_cvtepi32_ps (_ir8);
          __m128 _temp_g = _mm_cvtepi32_ps (_ig8);
          __m128 _temp_b = _mm_cvtepi32_ps (_ib8);

          //normalization from 0..255 to 0.0f..1.0f;
          _temp_r = _mm_mul_ps (_temp_r, _const_1_to_255);
          _temp_g = _mm_mul_ps (_temp_g, _const_1_to_255);
          _temp_b = _mm_mul_ps (_temp_b, _const_1_to_255);

          _rgb24 += 3;

          //float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
          __m128 _var_min = _mm_min_ps (_temp_g, _temp_r);
          _var_min        = _mm_min_ps (_temp_b, _var_min);

          //float _max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
          __m128 _max = _mm_max_ps (_temp_g, _temp_r);
          _max        = _mm_max_ps (_temp_b, _max);

          //_max_min = _max + var_Min;
          const __m128 _max_min = _mm_add_ps (_var_min, _max);

          //L = ( _max + var_Min ) / 2.0f;
          __m128 _l8 = _mm_mul_ps (_const_1_to_2, _max_min);

          _l8     = _mm_mul_ps (_l8, _const_255);
          _i128_1 = _mm_cvtps_epi32 (_l8);
          _i128_2 = _mm_castpd_si128 (_mm_shuffle_pd (_mm_castsi128_pd (_i128_1), _mm_castsi128_pd (_i128_1), 1));
          _i128_1 = _mm_packs_epi32 (_i128_1, _i128_2);
          _mm_storeu_si128 (UUU_MEM_CAST<__m128i*> (_l), _i128_1);

          _l += 4;
        }

      FAST_MOVE_CPTR (_rgb24, _leak_rgb);
      FAST_MOVE_PTR (_l, _leak_hsl);
    }

  return;
}


UUU_SET_TARGET_CPU (sse2)
void
rgb24_to_l_sse2 (::libs::optim::MCallInfo& _info)
{
  RGB2L_PREFIX (4);

  __m128i _ir8 = _mm_setzero_si128 ();
  __m128i _ig8 = _mm_setzero_si128 ();
  __m128i _ib8 = _mm_setzero_si128 ();

  SPLIT_RGB24_SSE2_DEFINE_REGS;

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          __m128i _i128_1 = _mm_loadu_si128 (UUU_MEM_CAST<const __m128i*> (_rgb24));      //BOG0R0B1 G1R1B2G2 R2B3G3R3 B4G4R4B5
          //_i128_1 = _mm_setr_epi8( 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F );//debug

          SPLIT_RGB24_SSE2 (_i128_1, _ir8, _ig8, _ib8);

          _rgb24 += 3;

          //select by 16 bit, 32 bit exist for sse4.1
          //float var_Min = min( var_R, min(var_G, var_B) )     Min. value of RGB
          __m128i _var_min = _mm_min_epi16 (_ig8, _ir8);          // 16bit as 32
          _var_min         = _mm_min_epi16 (_ib8, _var_min);      // 16bit as 32

          //float _max = max( var_R, max(var_G, var_B) )        //Max. value of RGB
          __m128i _max = _mm_max_epi16 (_ig8, _ir8);      // 16bit as 32
          _max         = _mm_max_epi16 (_ib8, _max);      // 16bit as 32

          //_max_min = _max + var_Min;
          const __m128i _max_min = _mm_add_epi16 (_var_min, _max);

          //L = ( _max + var_Min ) / 2.0f;
          __m128i _l8 = _mm_srai_epi16 (_max_min, 1);

          _i128_1 = _mm_castpd_si128 (_mm_shuffle_pd (_mm_castsi128_pd (_l8), _mm_castsi128_pd (_l8), 1));
          _l8     = _mm_packs_epi32 (_l8, _i128_1);
          _mm_storeu_si128 (UUU_MEM_CAST<__m128i*> (_l), _l8);
          _l += 4;
        }

      FAST_MOVE_CPTR (_rgb24, _leak_rgb);
      FAST_MOVE_PTR (_l, _leak_hsl);
    }

  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::l_vs_rgb

#endif
