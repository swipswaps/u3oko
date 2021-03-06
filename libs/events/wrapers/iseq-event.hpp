//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       iseq-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events {
/**
\brief  Событие последовательности событий. 
        Используется как флаг индентификации последовательности.
*/
class ISeqEvent : public IWrapBaseEvent
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  //  ext types
  using id_type = ::libs::helpers::utils::cuuid;
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ISeqEvent);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (ISeqEvent);
  UUU_DISABLE_ACOPY_TYPE (ISeqEvent);

  explicit ISeqEvent (const Acessor& = Acessor (0), IEvent::ptr _int = IEvent::ptr (), const id_type& _id = id_type ());

  virtual ~ISeqEvent ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/events/iseq-event";
    return _ret;
  }

  const id_type& get_seq_id () const;

  void set_seq_id (const id_type&);

  bool empty () const;


  protected:
  virtual IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void        copy_int (const IEvent::craw_ptr _src) override;


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (IWrapBaseEvent);

  id_type id_;      //< Уникальный идентификатор последовательности событий.

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
};

}}      // namespace libs::events

BOOST_CLASS_EXPORT_KEY (::libs::events::ISeqEvent);
