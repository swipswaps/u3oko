#pragma once
/**
\file       video-diff-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace gens { namespace diff {
/**
\brief  Свойства алгоритма вычисления разности между двумя кадрами для всего фильтра в целом.
*/
class VideoDiffProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoDiffProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoDiffProp);
  UUU_DISABLE_ACOPY_TYPE (VideoDiffProp);
  using buff2info_type = std::pair<off_buff_type, InfoBuffVideoDiffProp>;

  explicit VideoDiffProp (const Acessor& = Acessor (0));

  virtual ~VideoDiffProp ()
  {}

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/videos/gens/diff/video-diff-prop";
    return _ret;
  }

  std::list<buff2info_type> diffs_;      //< Список буферов и параметров для вычсления разностЕй.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::gens::diff::VideoDiffProp);
