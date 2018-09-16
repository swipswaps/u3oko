//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-http-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ihttp_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "base-http-event.hpp"

namespace libs { namespace ihttp_events { namespace events {

BaseHttpEvent::BaseHttpEvent (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


BaseHttpEvent::~BaseHttpEvent ()
{}


::libs::events::IEvent::ptr
BaseHttpEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<BaseHttpEvent> (this, _deep);
}


void
BaseHttpEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseHttpEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
BaseHttpEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ihttp_events::events::BaseHttpEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ihttp_events::events::BaseHttpEvent);
