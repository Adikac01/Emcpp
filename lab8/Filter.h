#ifndef LAB6_FILTER_H
#define LAB6_FILTER_H

#include <iterator>
#include <type_traits>
#include <utility>

template<typename Container, typename Predicate>
class Filter{
   Container container;
   Predicate predicate;

public:
   class iterator{
      typename Container::iterator current;
      typename Container::iterator end;
      Predicate pred;

   public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = typename std::iterator_traits<typename Container::iterator>::value_type;
      using difference_type = typename std::iterator_traits<typename Container::iterator>::difference_type;
      using pointer = typename std::iterator_traits<typename Container::iterator>::pointer;
      using reference = typename std::iterator_traits<typename Container::iterator>::reference;

      iterator() = default;

      explicit iterator(typename Container::iterator it, 
         typename Container::iterator end, Predicate pred):
          current(it), end(end), pred(pred){
            findNext();
          }

      iterator& operator++() {
         ++current;
         findNext();
         return *this;
      }

      iterator operator++(int){
         iterator temp = *this;
         ++(*this);
         return temp;
      }

      bool operator==(const iterator& other) const {
         return current == other.current;
      }

      bool operator!=(const iterator& other) const {
         return !(*this == other);
      }

      reference operator*() const {
         return *current;
      }

      pointer operator->() const {
         return current.operator->();
      }


   private:
      void findNext() {
         while (current != end && !pred(*current)) {
            ++current;
         }
      }   
   };
   Filter(Container c, Predicate p) : container(c), predicate(p){}
   
   iterator begin() {
      return iterator(std::begin(container), std::end(container), predicate);
   }

   iterator end() {
      return iterator(std::end(container), std::end(container), predicate);
   }

};

template<typename Container, typename Predicate>
auto make_filter(Container&& container, Predicate&& pred) {
    using ContainerType = std::decay_t<Container>;
    using PredicateType = std::decay_t<Predicate>;
    return Filter<ContainerType, PredicateType>(std::forward<Container>(container), std::forward<Predicate>(pred));
}

#endif //LAB6_FILTER_H
