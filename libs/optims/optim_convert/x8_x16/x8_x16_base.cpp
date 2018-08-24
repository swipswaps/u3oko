//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       x8_x16_base.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "x8_x16.hpp"
#include "x8_x16_int.hpp"

namespace libs { namespace optim { namespace convert { namespace x8_x16 {

void
get_params (
  ::libs::optim::MCallInfo& _info,
  const ProxyBuff**         _x8,
  ProxyBuff**               _x16)
{
  CHECK_STATE (1 == _info.srcs_.size (), "failed, src not equal 1");
  CHECK_STATE (1 == _info.dsts_.size (), "failed, dst not equal 1");

  *_x8  = &_info.srcs_[0];
  *_x16 = &_info.dsts_[0];

  CHECK_STATE (*_x8, "failed, empty x8");
  CHECK_STATE (_x16, "failed, empty x16");

  (*_x8)->check ();
  (*_x16)->check ();

  return;
}

}}}}      // namespace libs::optim::convert::x8_x16
