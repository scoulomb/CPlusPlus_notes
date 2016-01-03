// Boot iterator facade sample
// http://www.boost.org/doc/libs/1_47_0/libs/iterator/doc/iterator_facade.html#tutorial-example


# include <boost/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_convertible.hpp> // telling the truth
#include <boost/utility/enable_if.hpp> // telling the truth
# include <iostream>

struct node_base
{
    node_base() : m_next(0) {}

    // Each node manages all of its tail nodes
    virtual ~node_base() { delete m_next; }

    // Access the rest of the list
    node_base* next() const { return m_next; }

    // print to the stream
    virtual void print(std::ostream& s) const = 0;

    // double the value
    virtual void double_me() = 0;

    void append(node_base* p)
    {
        if (m_next)
            m_next->append(p);
        else
            m_next = p;
    }

    const node_base* begin()
    {
       return this;
    }

    const node_base* end()
    {
	return 0;
    }



 private:
    node_base* m_next;
};

template <class T>
struct node : node_base
{
    node(T x)
      : m_value(x)
    {}

    void print(std::ostream& s) const { s << this->m_value; }
    void double_me() { m_value += m_value; }


 private:
    T m_value;
};

inline std::ostream& operator<<(std::ostream& s, node_base const& n)
{
    n.print(s);
    return s;
}

// Interoperability sample with add from telling the truth and remove explicit keyword
template <class Value>
class node_iter
  : public boost::iterator_facade<
        node_iter<Value>
      , Value
      , boost::forward_traversal_tag
    >
{
 private:
    struct enabler {}; // telling the truth

 public:
    node_iter()
      : m_node(0) {}

    node_iter(Value* p) // removed explicit
      : m_node(p) {}
	
//    template <class OtherValue>
//    node_iter(node_iter<OtherValue> const& other)
//      : m_node(other.m_node) {}

      template <class OtherValue>
      node_iter(
          node_iter<OtherValue> const& other
        , typename boost::enable_if<
             boost::is_convertible<OtherValue*,Value*>
            , enabler
          >::type = enabler() // telling the truth
        )
        : m_node(other.m_node) {} 

 private:
    friend class boost::iterator_core_access;
    template <class> friend class node_iter;

    template <class OtherValue>
    bool equal(node_iter<OtherValue> const& other) const
    {
        return this->m_node == other.m_node;
    }

    void increment()
    { m_node = m_node->next(); }

    Value& dereference() const
    { return *m_node; }

    Value* m_node;
};
typedef node_iter<node_base> node_iterator; // error in boost documentation
typedef node_iter<node_base const> node_const_iterator; // same here
// see https://svn.boost.org/trac/boost/ticket/11882


int main()
{
    node<int>  * nodes = new node<int>(42);
    nodes->append(new node<std::string>(" is greater than "));
    nodes->append(new node<int>(13));

    //https://github.com/mousebird/boost/blob/master/libs/iterator/example/node_iterator3.cpp

    node_const_iterator it(nodes->begin()); 
    it++; 
    //std::cout << *it;
    node_const_iterator it2(nodes->end());
    it != it2;
     

    for(node_const_iterator it(nodes->begin()); it != node_const_iterator(nodes->end()); it++)
    {
          std::cout << *it;
    }

    std::cout << std::endl << "-----" << std::endl;

   // remove explicit keyword on iterator cstor enable to do it2 = nodes->begin() 
   // however still need for !=, otherwise template deduction fails
   for(node_const_iterator it2 = nodes->begin(); it2 != node_const_iterator(nodes->end()); it2++)
   {
          std::cout << *it2;
   }

   std::cout << std::endl << "-----" << std::endl;

}





