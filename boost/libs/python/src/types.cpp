//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

#include <boost/python/detail/types.hpp>
#include <boost/python/reference.hpp> // for handle_exception()
#include <boost/python/module_builder.hpp>
#include <boost/python/detail/none.hpp>
#include <cstring>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <boost/smart_ptr.hpp>
#include <boost/python/objects.hpp>
#include <boost/type_traits.hpp>

namespace boost { namespace python {

namespace {

  using detail::type_object_base;

  PyObject* call(PyObject* obj, PyObject* (type_object_base::*f)(PyObject*) const)
  {
      try
      {
          return (static_cast<type_object_base*>(obj->ob_type)->*f)(obj);
      }
      catch(...)
      {
          handle_exception();
          return 0;
      }
  }

  // Naming this differently allows us to use it for functions returning long on
  // compilers without partial ordering
  template <class R>
  R int_call(PyObject* obj, R (type_object_base::*f)(PyObject*) const)
  {
      try
      {
          return (static_cast<type_object_base*>(obj->ob_type)->*f)(obj);
      }
      catch(...)
      {
          handle_exception();
          return -1;
      }
  }

  // Implemented in terms of int_call, above
  int call(PyObject* obj, int (type_object_base::*f)(PyObject*) const)
  {
      return int_call(obj, f);
  }

  template <class A1>
  PyObject* call(PyObject* obj, PyObject* (type_object_base::*f)(PyObject*, A1) const, A1 a1)
  {
      try
      {
          return (static_cast<type_object_base*>(obj->ob_type)->*f)(obj, a1);
      }
      catch(...)
      {
          handle_exception();
          return 0;
      }
  }

  template <class A1>
  int call(PyObject* obj, int (type_object_base::*f)(PyObject*, A1) const, A1 a1)
  {
      try
      {
          return (static_cast<type_object_base*>(obj->ob_type)->*f)(obj, a1);
      }
      catch(...)
      {
          handle_exception();
          return -1;
      }
  }

  template <class A1, class A2>
  PyObject* call(PyObject* obj, PyObject* (type_object_base::*f)(PyObject*, A1, A2) const, A1 a1, A2 a2)
  {
      try
      {
          return (static_cast<type_object_base*>(obj->ob_type)->*f)(obj, a1, a2);
      }
      catch(...)
      {
          handle_exception();
          return 0;
      }
  }

  template <class A1, class A2>
  int call(PyObject* obj, int (type_object_base::*f)(PyObject*, A1, A2) const, A1 a1, A2 a2)
  {
      try
      {
          return (static_cast<type_object_base*>(obj->ob_type)->*f)(obj, a1, a2);
      }
      catch(...)
      {
          handle_exception();
          return -1;
      }
  }

  template <class A1, class A2, class A3>
  int call(PyObject* obj, int (type_object_base::*f)(PyObject*, A1, A2, A3) const, A1 a1, A2 a2, A3 a3)
  {
      try
      {
          return (static_cast<type_object_base*>(obj->ob_type)->*f)(obj, a1, a2, a3);
      }
      catch(...)
      {
          handle_exception();
          return -1;
      }
  }

  int call_length_function(PyObject* obj, int (type_object_base::*f)(PyObject*) const)
  {
      try
      {
          const int outcome =
              (static_cast<type_object_base*>(obj->ob_type)->*f)(obj);

          if (outcome < 0)
          {
              PyErr_SetString(PyExc_ValueError, "__len__() should return >= 0");
              return -1;
          }
          return outcome;
      }
      catch(...)
      {
          handle_exception();
          return -1;
      }
  }

}  // anonymous namespace

extern "C" {

static PyObject* do_instance_repr(PyObject* obj)
{
    return call(obj, &type_object_base::instance_repr);
}

static int do_instance_compare(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_compare, other);
}

static PyObject* do_instance_str(PyObject* obj)
{
    return call(obj, &type_object_base::instance_str);
}

static long do_instance_hash(PyObject* obj)
{
    return int_call(obj, &type_object_base::instance_hash);
}
    
static PyObject* do_instance_call(PyObject* obj, PyObject* args, PyObject* keywords)
{
    return call(obj, &type_object_base::instance_call, args, keywords);
}

static void do_instance_dealloc(PyObject* obj)
{
    try
    {
        static_cast<type_object_base*>(obj->ob_type)
            ->instance_dealloc(obj);
    }
    catch(...)
    {
        assert(!"exception during destruction!");
        handle_exception();
    }
}

static PyObject* do_instance_getattr(PyObject* obj, char* name)
{
    const char* name_ = name;
    return call(obj, &type_object_base::instance_getattr, name_);
}

static int do_instance_setattr(PyObject* obj, char* name, PyObject* value)
{
    const char* name_ = name;
    return call(obj, &type_object_base::instance_setattr, name_, value);
}

static int do_instance_mp_length(PyObject* obj)
{
    return call_length_function(obj, &type_object_base::instance_mapping_length);
}

static int do_instance_sq_length(PyObject* obj)
{
    return call_length_function(obj, &type_object_base::instance_sequence_length);
}

static PyObject* do_instance_mp_subscript(PyObject* obj, PyObject* index)
{
    return call(obj, &type_object_base::instance_mapping_subscript, index);
}

static PyObject* do_instance_sq_item(PyObject* obj, int index)
{
    try
    {
        const PyTypeObject* const type = obj->ob_type;
        
        // This is an extension to standard class behavior. If sequence_length
        // is implemented and n >= sequence_length(), raise an IndexError. That
        // keeps users from having to worry about raising it themselves
        if (type->tp_as_sequence != 0 && type->tp_as_sequence->sq_length != 0
            && index >= type->tp_as_sequence->sq_length(obj))
        {
            PyErr_SetString(PyExc_IndexError, type->tp_name);
            return 0;
        }
    
        return static_cast<type_object_base*>(obj->ob_type)
            ->instance_sequence_item(obj, index);
    }
    catch(...)
    {
        handle_exception();
        return 0;
    }
}

static int do_instance_mp_ass_subscript(PyObject* obj, PyObject* index, PyObject* value)
{
    return call(obj, &type_object_base::instance_mapping_ass_subscript, index, value);
}

static int do_instance_sq_ass_item(PyObject* obj, int index, PyObject* value)
{
    return call(obj, &type_object_base::instance_sequence_ass_item, index, value);
}

static PyObject* do_instance_sq_concat(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_sequence_concat, other);
}

static PyObject* do_instance_sq_repeat(PyObject* obj, int n)
{
    return call(obj, &type_object_base::instance_sequence_repeat, n);
}

static PyObject* do_instance_sq_slice(
    PyObject* obj, int start, int finish)
{
    return call(obj, &type_object_base::instance_sequence_slice, start, finish);
}

static int do_instance_sq_ass_slice(
    PyObject* obj, int start, int finish, PyObject* value)
{
    return call(obj, &type_object_base::instance_sequence_ass_slice, start, finish, value);
}

static PyObject* do_instance_nb_add(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_add, other);
}

static PyObject* do_instance_nb_subtract(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_subtract, other);
}

static PyObject* do_instance_nb_multiply(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_multiply, other);
}

static PyObject* do_instance_nb_divide(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_divide, other);
}

static PyObject* do_instance_nb_remainder(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_remainder, other);
}

static PyObject* do_instance_nb_divmod(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_divmod, other);
}

static PyObject* do_instance_nb_power(PyObject* obj, PyObject* exponent, PyObject* modulus)
{
    return call(obj, &type_object_base::instance_number_power, exponent, modulus);
}

static PyObject* do_instance_nb_negative(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_negative);
}

static PyObject* do_instance_nb_positive(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_positive);
}

static PyObject* do_instance_nb_absolute(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_absolute);
}

static int do_instance_nb_nonzero(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_nonzero);
}

static PyObject* do_instance_nb_invert(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_invert);
}

    
static PyObject* do_instance_nb_lshift(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_lshift, other);
}

static PyObject* do_instance_nb_rshift(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_rshift, other);
}

static PyObject* do_instance_nb_and(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_and, other);
}

static PyObject* do_instance_nb_xor(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_xor, other);
}

static PyObject* do_instance_nb_or(PyObject* obj, PyObject* other)
{
    return call(obj, &type_object_base::instance_number_or, other);
}

static int do_instance_nb_coerce(PyObject**obj, PyObject**other)
{
    return call(*obj, &type_object_base::instance_number_coerce, obj, other);
}
static PyObject* do_instance_nb_int(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_int);
}

static PyObject* do_instance_nb_long(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_long);
}

static PyObject* do_instance_nb_float(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_float);
}

static PyObject* do_instance_nb_oct(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_oct);
}

static PyObject* do_instance_nb_hex(PyObject* obj)
{
    return call(obj, &type_object_base::instance_number_hex);
}

} // extern "C"

namespace
{

#define ENABLE_GENERAL_CAPABILITY(field) \
    case type_object_base::field: \
        dest->tp_##field = &do_instance_##field; \
        return true

bool add_capability_general(type_object_base::capability capability, PyTypeObject* dest)
{
    assert(dest != 0);
    
    switch(capability)
    {
        ENABLE_GENERAL_CAPABILITY(hash);
        ENABLE_GENERAL_CAPABILITY(call);
        ENABLE_GENERAL_CAPABILITY(str);
        ENABLE_GENERAL_CAPABILITY(getattr);
        ENABLE_GENERAL_CAPABILITY(setattr);
        ENABLE_GENERAL_CAPABILITY(compare);
        ENABLE_GENERAL_CAPABILITY(repr);
        default:
            return false;
    }
}


template <class T>
void create_method_table_if_null(T*& table)
{
    if(table == 0)
    {
        detail::shared_pod_manager::create(table);
    }
    else
    {
        detail::shared_pod_manager::make_unique_copy(table);
    }
}

#define ENABLE_MAPPING_CAPABILITY(field) \
    case type_object_base::mapping_##field: \
        create_method_table_if_null(dest); \
        dest->mp_##field = &do_instance_mp_##field; \
        detail::shared_pod_manager::replace_if_equal(dest); \
        return true

bool add_capability_mapping(type_object_base::capability capability, PyMappingMethods*& dest)
{
    switch(capability)
    {
        ENABLE_MAPPING_CAPABILITY(length);
        ENABLE_MAPPING_CAPABILITY(subscript);
        ENABLE_MAPPING_CAPABILITY(ass_subscript);
        default:
            return false;
    }
}

#define ENABLE_SEQUENCE_CAPABILITY(field) \
    case type_object_base::sequence_##field: \
        create_method_table_if_null(dest); \
        dest->sq_##field = &do_instance_sq_##field; \
        detail::shared_pod_manager::replace_if_equal(dest); \
        return true

bool add_capability_sequence(type_object_base::capability capability, PySequenceMethods*& dest)
{
    switch(capability)
    {
        ENABLE_SEQUENCE_CAPABILITY(length);
        ENABLE_SEQUENCE_CAPABILITY(item);
        ENABLE_SEQUENCE_CAPABILITY(ass_item);
        ENABLE_SEQUENCE_CAPABILITY(concat);
        ENABLE_SEQUENCE_CAPABILITY(repeat);
        ENABLE_SEQUENCE_CAPABILITY(slice);
        ENABLE_SEQUENCE_CAPABILITY(ass_slice);
        default:
            return false;
    }
}

#define ENABLE_NUMBER_CAPABILITY(field) \
    case type_object_base::number_##field: \
        create_method_table_if_null(dest); \
        dest->nb_##field = &do_instance_nb_##field; \
        detail::shared_pod_manager::replace_if_equal(dest); \
        return true

bool add_capability_number(type_object_base::capability capability, PyNumberMethods*& dest)
{
    switch(capability)
    {
        ENABLE_NUMBER_CAPABILITY(add);
        ENABLE_NUMBER_CAPABILITY(subtract);
        ENABLE_NUMBER_CAPABILITY(multiply);
        ENABLE_NUMBER_CAPABILITY(divide);
        ENABLE_NUMBER_CAPABILITY(remainder);
        ENABLE_NUMBER_CAPABILITY(divmod);
        ENABLE_NUMBER_CAPABILITY(power);
        ENABLE_NUMBER_CAPABILITY(negative);
        ENABLE_NUMBER_CAPABILITY(positive);
        ENABLE_NUMBER_CAPABILITY(absolute);
        ENABLE_NUMBER_CAPABILITY(nonzero);
        ENABLE_NUMBER_CAPABILITY(invert);
        ENABLE_NUMBER_CAPABILITY(lshift);
        ENABLE_NUMBER_CAPABILITY(rshift);
        ENABLE_NUMBER_CAPABILITY(and);
        ENABLE_NUMBER_CAPABILITY(xor);
        ENABLE_NUMBER_CAPABILITY(or);
        ENABLE_NUMBER_CAPABILITY(coerce);
        ENABLE_NUMBER_CAPABILITY(int);
        ENABLE_NUMBER_CAPABILITY(long);
        ENABLE_NUMBER_CAPABILITY(float);
        ENABLE_NUMBER_CAPABILITY(oct);
        ENABLE_NUMBER_CAPABILITY(hex);
        default:
            return false;
    }
}

#define ENABLE_BUFFER_CAPABILITY(field) \
    case type_object_base::buffer_##field: \
        create_method_table_if_null(dest); \
        dest->bf_##field = &do_instance_bf_##field; \
        detail::shared_pod_manager::replace_if_equal(dest); \
        return true

bool add_capability_buffer(type_object_base::capability capability, PyBufferProcs*& dest)
{
    (void)dest; // suppress unused argument warning
    (void)capability; // likwise
#if 0
    switch(capability)
    {
        // nothing defined yet
        default:
            return false;
    }
#endif
    return false;
}

} // anonymous namespace

namespace detail  {

  void add_capability(
      type_object_base::capability capability,
      PyTypeObject* dest_)
  {
    if(add_capability_general(capability, dest_))
        return;
    if(add_capability_mapping(capability, dest_->tp_as_mapping))
        return;
    if(add_capability_sequence(capability, dest_->tp_as_sequence))
        return;
    if(add_capability_number(capability, dest_->tp_as_number))
        return;
    if(add_capability_buffer(capability, dest_->tp_as_buffer))
        return;

    // no one recognized the capability
    throw std::runtime_error("py::detail::add_capability(): unknown capability");
  }
} // namespace detail

type_object_base::~type_object_base()
{
    detail::shared_pod_manager::dispose(tp_as_mapping);
    detail::shared_pod_manager::dispose(tp_as_sequence);
    detail::shared_pod_manager::dispose(tp_as_number);
    detail::shared_pod_manager::dispose(tp_as_buffer);
}

void type_object_base::enable(type_object_base::capability capability)
{
    detail::add_capability(capability, this);
}

type_object_base::type_object_base(PyTypeObject* t)
    : python_type(t)
{
    this->tp_dealloc = do_instance_dealloc;
}

namespace
{
  typedef long pod_refcount;

  inline pod_refcount pod_refcount_offset(std::size_t size)
  {
      const std::size_t alignment = boost::alignment_of<pod_refcount>::value;
      return (size + alignment - 1) / alignment * alignment;
  }

  inline pod_refcount* counted_pod_refcount(char* pod, std::size_t size)
  {
      if(pod == 0)
          return 0;
      
      return reinterpret_cast<pod_refcount*>(pod + pod_refcount_offset(size));
  }

  #ifdef TYPE_OBJECT_BASE_STANDALONE_TEST
  int pod_instance_counter = 0;
  #endif

  inline pod_refcount counted_pod_getref(char* pod, std::size_t size)
  {
      pod_refcount* ref_count = counted_pod_refcount(pod, size);
      return ref_count == 0 ? -1 : *ref_count;
  }

  inline pod_refcount counted_pod_decref(char* pod, std::size_t size)
  {
      pod_refcount* const ref_count = counted_pod_refcount(pod, size);
      if (ref_count == 0)
          return -1;
      --(*ref_count);
      if (*ref_count <= 0)
      {
  #ifdef TYPE_OBJECT_BASE_STANDALONE_TEST
          --pod_instance_counter;
  #endif
          ::operator delete(pod);
          return 0;
      }
      return *ref_count;
  }

  pod_refcount counted_pod_incref(char* pod, std::size_t size)
  {
      pod_refcount* ref_count = counted_pod_refcount(pod, size);
      return ref_count == 0 ? -1 : ++(*ref_count);
  }

} // anonymous namespace

namespace detail
{
  struct shared_pod_manager::compare
  {
      bool operator()(const std::pair<char*, std::size_t>& x1,
                      const std::pair<char*, std::size_t>& x2) const
      {
          const std::size_t n1 = x1.second;
          const std::size_t n2 = x2.second;
          return n1 < n2 || n1 == n2 && BOOST_CSTD_::memcmp(x1.first, x2.first, n1) < 0;
      }
  };

  struct shared_pod_manager::identical
  {
      identical(char* p) : pod(p) {}

      bool operator()(const std::pair<char*, std::size_t>& x) const
      {
          return pod == x.first;
      }

      char* pod;
  };

  shared_pod_manager& shared_pod_manager::obj()
  {
      static shared_pod_manager spm;
      return spm;
  }

  shared_pod_manager::~shared_pod_manager()
  {
  }

  void* shared_pod_manager::replace_if_equal(void* pod, std::size_t size)
  {
      if(pod == 0)
          return 0;

      const holder element(static_cast<char*>(pod), size);

      const storage::iterator found
          = std::lower_bound(m_storage.begin(), m_storage.end(), element, compare());

      if (found != m_storage.end() && pod == found->first)
      {
          // pod already in list => do nothing
          return pod;
      }
      else if (found != m_storage.end() && !compare()(element, *found))
      {
          // equal element in list => replace
          void* replacement = found->first;
          counted_pod_incref(found->first, size);   
          dec_ref(element.first, size); // invalidates iterator 'found'
          return replacement;
      }
      else
      {
          // new element => insert
          m_storage.insert(found, element);
          return pod;
      }
  }

  void* shared_pod_manager::make_unique_copy(void* pod, std::size_t size)
  {
      if(pod == 0)
          return 0;
      if(counted_pod_getref(static_cast<char*>(pod), size) == 1)
      {
          erase_from_list(pod);
          return pod;
      }
      else
      {
          void* copy = create(size);
          memmove(copy, pod, size);
          dec_ref(pod, size);
          return copy;
      }
  }

  void* shared_pod_manager::create(std::size_t size)
  {
      std::size_t total_size = pod_refcount_offset(size) + sizeof(pod_refcount);
      char* pod = static_cast<char*>(::operator new(total_size));
  #ifdef TYPE_OBJECT_BASE_STANDALONE_TEST
      ++pod_instance_counter;
  #endif
      memset(pod, 0, total_size);

      *counted_pod_refcount(pod, size) = 1;

      return pod;
  }

  void shared_pod_manager::dec_ref(void* pod, std::size_t size)
  {
      if(pod == 0)
          return;

      int ref_count = counted_pod_decref(static_cast<char*>(pod), size);
      
      if(ref_count <= 0) 
          erase_from_list(pod);
  }

  void shared_pod_manager::erase_from_list(void* pod)
  {
      if(pod == 0)
          return;

      const storage::iterator found =
          std::find_if(m_storage.begin(), m_storage.end(), 
          identical(static_cast<char*>(pod)));

      if(found != m_storage.end())
      {
          m_storage.erase(found);
      }
  }
} // namespace detail

namespace {
  struct error_type {
      operator PyObject*() const { return 0; }
      operator int() const { return -1; }
  };

  error_type unimplemented(const char* name)
  {
      assert(!"Control should never reach here");
      string s("Unimplemented ");
      s += string(name);
      PyErr_SetObject(PyExc_RuntimeError, s.get());
      return error_type();
  }
}

PyObject* type_object_base::instance_repr(PyObject*) const
{
    return unimplemented("instance_repr");
}

int type_object_base::instance_compare(PyObject*, PyObject*) const
{
    return unimplemented("instance_compare");
}

PyObject* type_object_base::instance_str(PyObject*) const
{
    return unimplemented("instance_str");
}

long type_object_base::instance_hash(PyObject* /* obj */) const
{
    return unimplemented("instance_hash");
}

PyObject* type_object_base::instance_call(PyObject* /*obj*/, PyObject* /*args*/, PyObject* /*kw*/) const
{
    return unimplemented("instance_call");
}

PyObject* type_object_base::instance_getattr(PyObject* /*obj*/, const char* /*name*/) const
{
    return unimplemented("instance_getattr");
}

int type_object_base::instance_setattr(PyObject* /*obj*/, const char* /*name*/, PyObject* /*value*/) const
{
    return unimplemented("instance_setattr");
}

int type_object_base::instance_mapping_length(PyObject*) const
{
    return unimplemented("instance_mapping_length");
}

int type_object_base::instance_sequence_length(PyObject*) const
{
    return unimplemented("instance_sequence_length");
}

PyObject* type_object_base::instance_mapping_subscript(PyObject*, PyObject*) const
{
    return unimplemented("instance_mapping_subscript");
}

PyObject* type_object_base::instance_sequence_item(PyObject*, int) const
{
    return unimplemented("instance_sequence_item");
}

int type_object_base::instance_mapping_ass_subscript(PyObject*, PyObject*, PyObject*) const
{
    return unimplemented("instance_mapping_ass_subscript");
}

int type_object_base::instance_sequence_ass_item(PyObject*, int, PyObject*) const
{
    return unimplemented("instance_sequence_ass_item");
}

PyObject* type_object_base::instance_sequence_concat(PyObject*, PyObject*) const
{
    return unimplemented("instance_sequence_concat");
}

PyObject* type_object_base::instance_sequence_repeat(PyObject*, int) const
{
    return unimplemented("instance_sequence_repeat");
}

PyObject* type_object_base::instance_sequence_slice(PyObject*, int, int) const
{
    return unimplemented("instance_sequence_slice");
}

int type_object_base::instance_sequence_ass_slice(PyObject*, int, int, PyObject*) const
{
    return unimplemented("instance_sequence_ass_slice");
}

PyObject* type_object_base::instance_number_add(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_add");
}

PyObject* type_object_base::instance_number_subtract(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_subtract");
}

PyObject* type_object_base::instance_number_multiply(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_multiply");
}

PyObject* type_object_base::instance_number_divide(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_divide");
}

PyObject* type_object_base::instance_number_remainder(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_remainder");
}

PyObject* type_object_base::instance_number_divmod(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_divmod");
}

PyObject* type_object_base::instance_number_power(PyObject*, PyObject*, PyObject*) const
{
    return unimplemented("instance_number_divmod");
}

PyObject* type_object_base::instance_number_negative(PyObject*) const
{
    return unimplemented("instance_number_negative");
}

PyObject* type_object_base::instance_number_positive(PyObject*) const
{
    return unimplemented("instance_number_positive");
}

PyObject* type_object_base::instance_number_absolute(PyObject*) const
{
    return unimplemented("instance_number_absolute");
}

int type_object_base::instance_number_nonzero(PyObject*) const
{
    return unimplemented("instance_number_nonzero");
}

PyObject* type_object_base::instance_number_invert(PyObject*) const
{
    return unimplemented("instance_number_invert");
}

PyObject* type_object_base::instance_number_lshift(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_lshift");
}

PyObject* type_object_base::instance_number_rshift(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_rshift");
}

PyObject* type_object_base::instance_number_and(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_and");
}

PyObject* type_object_base::instance_number_xor(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_xor");
}

PyObject* type_object_base::instance_number_or(PyObject*, PyObject*) const
{
    return unimplemented("instance_number_or");
}

int type_object_base::instance_number_coerce(PyObject*, PyObject**, PyObject**) const
{
    return unimplemented("instance_number_coerce");
}

PyObject* type_object_base::instance_number_int(PyObject*) const
{
    return unimplemented("instance_number_int");
}

PyObject* type_object_base::instance_number_long(PyObject*) const
{
    return unimplemented("instance_number_long");
}

PyObject* type_object_base::instance_number_float(PyObject*) const
{
    return unimplemented("instance_number_float");
}

PyObject* type_object_base::instance_number_oct(PyObject*) const
{
    return unimplemented("instance_number_oct");
}

PyObject* type_object_base::instance_number_hex(PyObject*) const
{
    return unimplemented("instance_number_hex");
}

}} // namespace boost::python

#ifdef TYPE_OBJECT_BASE_STANDALONE_TEST

struct TestTypeObject : boost::python::type_object_base
{
    TestTypeObject()
    : boost::python::type_object_base(Py_None->ob_type->ob_type)
    {}
    
    void instance_dealloc(PyObject*) const {}
};

struct POD1
{
    unsigned char data;
};

int main()
{
    boost::python::type_object_base *o1, *o2, *o3;
    
//    POD1 * pod1;
//    boost::python::detail::shared_pod_manager::create(pod1);
    
    o1 = new TestTypeObject;
    o2 = new TestTypeObject;
    o3 = new TestTypeObject;
    
    assert(boost::python::pod_instance_counter == 0);
    
    o1->enable(boost::python::type_object_base::number_add);
    o1->enable(boost::python::type_object_base::compare);

    o2->enable(boost::python::type_object_base::number_add);
    o2->enable(boost::python::type_object_base::mapping_length);
    
    o3->enable(boost::python::type_object_base::number_add);
    o3->enable(boost::python::type_object_base::sequence_length);

    assert(boost::python::pod_instance_counter == 3);
    assert(o1->tp_as_number && !o1->tp_as_mapping && !o1->tp_as_sequence);
    assert(o2->tp_as_number && o2->tp_as_mapping && !o2->tp_as_sequence);
    assert(o3->tp_as_number && !o3->tp_as_mapping && o3->tp_as_sequence);
    assert(o1->tp_as_number == o2->tp_as_number);
    assert(o1->tp_as_number == o3->tp_as_number);
    assert((void*)o2->tp_as_number != o2->tp_as_mapping);
    assert((void*)o2->tp_as_mapping != o3->tp_as_sequence);
    
    o1->enable(boost::python::type_object_base::number_subtract);
    
    assert(boost::python::pod_instance_counter == 4);
    assert(o1->tp_as_number != o2->tp_as_number);
    assert(o2->tp_as_number == o3->tp_as_number);
    
    o3->enable(boost::python::type_object_base::mapping_subscript);

    assert(boost::python::pod_instance_counter == 5);
    assert(o3->tp_as_number && o3->tp_as_mapping && o3->tp_as_sequence);
    assert(o2->tp_as_mapping != o3->tp_as_mapping);
    
    o2->enable(boost::python::type_object_base::mapping_subscript);
    o3->enable(boost::python::type_object_base::mapping_length);

    assert(boost::python::pod_instance_counter == 4);
    assert(o2->tp_as_number && o2->tp_as_mapping && !o2->tp_as_sequence);
    assert(o3->tp_as_number && o3->tp_as_mapping && o3->tp_as_sequence);
    assert(o2->tp_as_mapping == o3->tp_as_mapping);
    
    boost::python::type_object_base *o4 = new TestTypeObject;

    assert(boost::python::pod_instance_counter == 4);

    o4->enable(boost::python::type_object_base::number_add);

    assert(boost::python::pod_instance_counter == 4);
    assert(o4->tp_as_number && !o4->tp_as_mapping && !o4->tp_as_sequence);
    assert(o4->tp_as_number == o3->tp_as_number);
    
    delete o3;

    assert(boost::python::pod_instance_counter == 3);
    assert(o1->tp_as_number && !o1->tp_as_mapping && !o1->tp_as_sequence);
    assert(o2->tp_as_number && o2->tp_as_mapping && !o2->tp_as_sequence);
    assert(o4->tp_as_number && !o4->tp_as_mapping && !o4->tp_as_sequence);
    assert(o4->tp_as_number == o2->tp_as_number);
    
    o3 =  new TestTypeObject;
    
    assert(boost::python::pod_instance_counter == 3);

    o3->enable(boost::python::type_object_base::number_add);
    o3->enable(boost::python::type_object_base::sequence_length);

    assert(boost::python::pod_instance_counter == 4);
    assert(o3->tp_as_number && !o3->tp_as_mapping && o3->tp_as_sequence);
    assert(o1->tp_as_number != o3->tp_as_number);
    assert(o2->tp_as_number == o3->tp_as_number);
    
    delete o1;
    
    assert(boost::python::pod_instance_counter == 3);
    
    delete o4;
    
    assert(boost::python::pod_instance_counter == 3);
    
    delete o3;
    
    assert(boost::python::pod_instance_counter == 2);
    
    delete o2;
    
    assert(boost::python::pod_instance_counter == 0);
    
    assert(boost::python::detail::shared_pod_manager::obj().m_storage.size() == 0);
}

#endif

