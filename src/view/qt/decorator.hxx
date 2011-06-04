#ifndef DECORATOR_HXX_
# define DECORATOR_HXX_

# include "view/qt/decorator.hh"
# include "view/qt/gmsc/all.hh"

namespace view
{
  template<typename T>
  T* Decorator::recurse(T& node)
  {
    T* res = NULL;

    node.accept(*this);
    res = dynamic_cast<T*> (result_);
    if (res == NULL)
      res = &node;

    return res;
  }

  template<typename T>
  void Decorator::recurseList(std::vector<T>& vector, std::map<T, T>& map)
  {
    std::vector<T>                      gv;
    typename std::vector<T>::iterator   it;

    for (it = vector.begin(); it != vector.end(); ++it)
    {
      typename std::map<T, T>::iterator  decorated = map.find(*it);

      if (decorated != map.end())
        gv.push_back(decorated->second);
      else
      {
        T decoratedEvent = this->recurse(**it);

        gv.push_back(decoratedEvent);
        map.insert(std::pair<T, T>(*it, decoratedEvent));
      }
    }
    vector = gv;
  }
}

#endif /* !DECORATOR_HXX_ */
