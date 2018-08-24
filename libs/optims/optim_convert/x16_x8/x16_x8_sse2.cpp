//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       x16_x8_sse2.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "x16_x8.hpp"
#include "x16_x8_int.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace convert { namespace x16_x8 {

UUU_SET_TARGET_CPU (sse2)
void
sse2 (::libs::optim::MCallInfo& _info)
{
#if 1
  return alu (_info);
#else
  X16_TO_X8_PREFIX (8);

  const __m128i _mask = _mm_setr_epi16 (0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF);

  for (std::size_t indx_y = 0; indx_y < _height; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < _width; indx_x += _ppc)
        {
          __m128i _data = _mm_load_si128 (UUU_MEM_CAST<const __m128i*> (_yuy2_buff));

          _data = _mm_and_si128 (_data, _mask);

          _mm_store_si128 (UUU_MEM_CAST<__m128i*> (_y16_buff), _data);

          _yuy2_buff += _dppc;
          _y16_buff += _ppc;
        }

      FAST_MOVE_CPTR (_yuy2_buff, _leak_yuy2);
      FAST_MOVE_PTR (_y16_buff, _leak_y16);
    }
#endif
  return;
}

}}}}      // namespace libs::optim::convert::x16_x8

#endif
