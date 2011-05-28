#ifndef MISC_UNIQUE_HXX
# define MISC_UNIQUE_HXX

# include "misc/unique.hh"

namespace misc
{
  template <typename  T, class C>
  Unique<T, C>::Unique(const data_type& s)
  {
    object_set_type& inst = object_set_instance();

    typename object_set_type::iterator it = inst.find(s);

    if (it == inst.end())
      it = inst.insert(inst.end(), s);

    obj_ = &(*it);
  }

  template <typename T, class C>
  Unique<T, C>::~Unique()
  {
  }

  template <typename T, class C>
  inline typename Unique<T, C>::object_set_type&
  Unique<T, C>::object_set_instance()
  {
    static object_set_type global_set;

    return global_set;
  }

  template <typename T, class C>
  inline typename Unique<T, C>::object_size_type
  Unique<T, C>::object_map_size()
  {
    object_set_type& inst = object_set_instance();

    return inst.size ();
  }

  template <typename T, class C>
  inline const typename Unique<T, C>::data_type&
  Unique<T, C>::object_get() const
  {
    return *obj_;
  }

  template <typename T, class C>
  Unique<T, C>::operator const data_type&() const
  {
    return *obj_;
  }

  template <typename  T, class C>
  inline typename Unique<T, C>::value_type&
  Unique<T, C>::operator=(const value_type& rhs)
  {
    if (this != &rhs)
      obj_ = rhs.obj_;
    return *this;
  }

  template <typename T, class C>
  inline bool
  Unique<T, C>::operator==(const value_type& rhs) const
  {
    return obj_ == rhs.obj_;
  }

  template <typename T, class C>
  inline bool
  Unique<T, C>::operator!=(const value_type& rhs) const
  {
    return !operator==(rhs);
  }

  template <typename T, class C>
  inline bool
  Unique<T, C>::operator<(const value_type& rhs) const
  {
    C cmp;
    return cmp(*obj_, *rhs.obj_);
  }

  template <typename T, class C>
  inline std::ostream&
  operator<< (std::ostream& ostr, const Unique<T, C>& the)
  {
    return ostr << the.object_get ();
  }
}

#endif // !MISC_UNIQUE_HXX
