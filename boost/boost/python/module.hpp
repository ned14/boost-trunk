// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef MODULE_DWA2001128_HPP
# define MODULE_DWA2001128_HPP

# include <boost/python/errors.hpp>
# include <boost/python/detail/config.hpp>
# include <boost/python/make_function.hpp>
# include <boost/python/class_fwd.hpp>
# include <boost/python/detail/module_base.hpp>
# include <boost/python/module_init.hpp>
# include <boost/python/object_core.hpp>
# include <boost/python/detail/def_helper.hpp>

namespace boost { namespace python {

class module : public detail::module_base
{
 public:
    typedef detail::module_base base;

    module(char const* name, char const* doc = 0)
        : base(name, doc) {}

    // Add elements to the module
    template <class T>
    module& setattr(const char* name, T const& x)
    {
        this->module_base::setattr_doc(name, python::object(x), 0);
        return *this;
    }
    
    module& add(type_handle x); // just use the type's name
    
    template <class T1, class T2 , class T3, class T4>
    module& add(class_<T1,T2,T3,T4> const& c)
    {
        this->add_class(type_handle(borrowed((PyTypeObject*)c.ptr())));
        return *this;
    }
    
    template <class Fn>
    module& def(char const* name, Fn fn)
    {
        this->setattr_doc(
            name, boost::python::make_function(fn), 0);
        
        return *this;
    }
    template <class Fn, class CallPolicyOrDoc>
    module& def(char const* name, Fn fn, CallPolicyOrDoc const& policy_or_doc, char const* doc = 0)
    {
        typedef detail::def_helper<CallPolicyOrDoc> helper;
        
        this->setattr_doc(
            name, boost::python::make_function(fn, helper::get_policy(policy_or_doc)),
            helper::get_doc(policy_or_doc, doc));
        
        return *this;
    }
};

//
// inline implementations
//
inline module& module::add(type_handle x)
{
    this->base::add(x);
    return *this;
}

}} // namespace boost::python

#endif // MODULE_DWA20011221_HPP
