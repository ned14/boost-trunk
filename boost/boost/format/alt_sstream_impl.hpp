// ------------------------------------------------------------------------------
//  alt_sstream_impl.hpp : alternative stringstream, templates implementation 
// ------------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ------------------------------------------------------------------------------

#ifndef BOOST_SK_ALT_SSTREAM_IMPL_HPP
#define BOOST_SK_ALT_SSTREAM_IMPL_HPP

namespace boost {
    namespace io {
// ---- Implementation  ------------------------------------------------------//

        template<class Ch, class Tr, class Alloc>
        void basic_altstringbuf<Ch, Tr, Alloc>:: 
        clear_buffer () {
            const Ch * p = pptr();
            const Ch * b = pbase();
            if(p != NULL && p != b) {
                pos_type pos = seekpos(0, ios_base::out); 
                assert( pos != pos_type(std::streamoff(-1)) ); 
            }
            p = gptr();
            b = eback();
            if(p != NULL && p != b) {
                pos_type pos = seekpos(0, ios_base::in); 
                assert( pos != pos_type(std::streamoff(-1)) ); 
            }
        }

        template<class Ch, class Tr, class Alloc>
        void basic_altstringbuf<Ch, Tr, Alloc>:: 
        str (const string_type& s) {
            dealloc();
            std::size_t sz=s.size();
            if(sz != 0 && mode_ & (ios_base::in | ios_base::out) ) {
                Ch *new_ptr = alloc_.allocate(sz);
                s.copy(new_ptr);
                putend_ = new_ptr + sz;
                if(mode_ & ios_base::in)
                    streambuf_t::setg(new_ptr, new_ptr, new_ptr + sz);
                if(mode_ & ios_base::out) {
                    streambuf_t::setp(new_ptr, new_ptr + sz);
                    if(mode_ & (ios_base::app | ios_base::ate))
                        streambuf_t::pbump(sz);
                    if(gptr() == NULL)
                        streambuf_t::setg(new_ptr, NULL, new_ptr);
                }
                is_allocated_ = true;
            }
        }
        template<class Ch, class Tr, class Alloc>
        Ch*   basic_altstringbuf<Ch, Tr, Alloc>:: 
        begin () const {
            if(mode_ & ios_base::out && pptr() != NULL)
                return pbase();
            else if(mode_ & ios_base::in && gptr() != NULL)
                return eback();
            return NULL;
        }

        template<class Ch, class Tr, class Alloc>
        std::streamsize  basic_altstringbuf<Ch, Tr, Alloc>:: 
        size () const { 
            if(mode_ & ios_base::out && pptr())
                return static_cast<streamsize>( pend() - pbase());
            else if(mode_ & ios_base::in && gptr())
                return static_cast<streamsize>( egptr() - eback());
            else 
                return 0;
        }

        template<class Ch, class Tr, class Alloc>
        std::streamsize  basic_altstringbuf<Ch, Tr, Alloc>:: 
        cur_size () const { 
            if(mode_ & ios_base::out && pptr())
                return static_cast<streamsize>( pptr() - pbase());
            else if(mode_ & ios_base::in && gptr())
                return static_cast<streamsize>( gptr() - eback());
            else 
                return 0;
        }

        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::pos_type  basic_altstringbuf<Ch, Tr, Alloc>:: 
        seekoff (off_type off, ios_base::seekdir way, ios_base::openmode which) {
            if(pptr() != NULL && putend_ < pptr())
                putend_ = pptr();
            if(which & ios_base::in && gptr() != NULL) {
                // get area
                if(way == ios_base::end)
                    off += putend_ - eback();
                else if(way == ios_base::cur && (which & ios_base::out) == 0)
                    off += gptr() - eback();
                else if(way != ios_base::beg)
                    off = std::streamoff(-1);
                if(0 <= off && off <= putend_ - eback()) {
                    // set gptr
                    streambuf_t::gbump(off + (eback() - gptr()));
                    if(which & ios_base::out && pptr() != NULL)
                        // update pptr to match gptr
                        streambuf_t::pbump(gptr()-pptr());
                }
                else
                    off = std::streamoff(-1);
            }
            else if(which & ios_base::out && pptr() != NULL) {
                // put area
                if(way == ios_base::end)
                    off += putend_ - eback();
                else if(way == ios_base::cur)
                    off += pptr() - eback();
                else if(way != ios_base::beg)
                    off = std::streamoff(-1);

                if(0 <= off && off <= putend_ - eback())
                    // set pptr
                    streambuf_t::pbump((int)(eback() - pptr() + off)); 
                else
                    off = std::streamoff(-1);
            }
            else // neither in nor out
                off = std::streamoff(-1);
            return (pos_type(off));
        } 
        //- end seekoff(..)

        
        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::pos_type basic_altstringbuf<Ch, Tr, Alloc>:: 
        seekpos (pos_type pos, ios_base::openmode which) {
            std::streamoff off = pos; // properly converted by operator
            if(pptr() != NULL && putend_ < pptr())
                putend_ = pptr();
            if(off == std::streamoff(-1)) ;
            else if(which & ios_base::in && gptr() != NULL) {
                // get area
                if(0 <= off && off <= putend_ - eback()) {
                    gbump((int)(eback() - gptr() + off));
                    if(which & ios_base::out && pptr() != NULL) {
                        // update pptr to match gptr
                        streambuf_t::pbump(gptr()-pptr());
                    }
                }
                else
                    off = std::streamoff(-1);
            }
            else if(which & ios_base::out && pptr() != NULL) {
                // put area
                if(0 <= off && off <= putend_ - eback())
                    streambuf_t::pbump(eback() - pptr() + off);
                else
                    off = std::streamoff(-1);
            }
            else // neither in nor out
                off = std::streamoff(-1);
            return (std::streampos(off));
        }
        // -end seekpos(..)


        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::int_type basic_altstringbuf<Ch, Tr, Alloc>:: 
        underflow () {
            if(gptr() == NULL) // no get area -> nothing to get.
                return (traits_type::eof()); 
            else if(gptr() < egptr())  // ok, in buffer
                return (traits_type::to_int_type(*gptr())); 
            else if(mode_ & ios_base::in && pptr() != NULL
                    && (gptr() < pptr() || gptr() < putend_) )
                {  // expand get area 
                    if(putend_ < pptr()) 
                        putend_ = pptr(); // remember pptr reached this far
                    streambuf_t::setg(eback(), gptr(), putend_);
                    return (traits_type::to_int_type(*gptr()));
                }
            else // couldnt get anything. EOF.
                return (traits_type::eof());
        }
        // -end underflow(..)


        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::int_type basic_altstringbuf<Ch, Tr, Alloc>:: 
        pbackfail (int_type meta) {
            if(gptr() != NULL  &&  (eback() < gptr()) 
               && (mode_ & (ios_base::out)
                   || traits_type::eq_int_type(traits_type::eof(), meta)
                   || traits_type::eq(traits_type::to_char_type(meta), gptr()[-1]) ) ) { 
                streambuf_t::gbump(-1); // back one character
                if(!traits_type::eq_int_type(traits_type::eof(), meta))
                    //  put-back meta into get area
                    *gptr() = traits_type::to_char_type(meta);
                return (traits_type::not_eof(meta));
                }
            else
                return (traits_type::eof());  // failed putback
        }
        // -end pbackfail(..)


        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::int_type basic_altstringbuf<Ch, Tr, Alloc>:: 
        overflow (int_type meta) {
            if(traits_type::eq_int_type(traits_type::eof(), meta))
                return traits_type::not_eof(meta); // nothing to do
            else if(pptr() != NULL && pptr() < epptr()) {
                streambuf_t::sputc(traits_type::to_char_type(meta));
                return meta;
            }
            else if(! (mode_ & ios_base::out)) // no write position, and cant make one
                return traits_type::eof(); 
            else { // make a write position available
                std::size_t prev_size = pptr() == NULL ? 0 : epptr() - eback();
                std::size_t new_size = prev_size;
                std::size_t add_size = new_size / 2;  // exponential growth : size *= 1.5
                if(add_size < alloc_min)
                    add_size = alloc_min;
                Ch * newptr = NULL,  *oldptr = eback();

                while (0 < add_size && (std::numeric_limits<std::size_t>::max()-add_size < new_size) )
                    add_size /= 2;  // make sure adding add_size wont overflow size_t
                if(0 < add_size) {
                    new_size += add_size;
                    newptr = alloc_.allocate(new_size);
                }

                if(0 < prev_size)
                    traits_type::copy(newptr, oldptr, prev_size);
                if(is_allocated_)
                    alloc_.deallocate(oldptr, prev_size);
                is_allocated_=true;

                if(prev_size == 0) { // first allocation
                    putend_ = newptr;
                    streambuf_t::setp(newptr, newptr + new_size);
                    if(mode_ & ios_base::in)
                        streambuf_t::setg(newptr, newptr, newptr + 1);
                    else
                        streambuf_t::setg(newptr, 0, newptr);
                }
                else { // update pointers
                    putend_ = putend_ - oldptr + newptr;
                    int pptr_count = pptr()-pbase();
                    int gptr_count = gptr()-eback();
                    streambuf_t::setp(pbase() - oldptr + newptr, newptr + new_size);
                    streambuf_t::pbump(pptr_count);
                    if(mode_ & ios_base::in)
                        streambuf_t::setg(newptr, newptr + gptr_count, pptr() + 1);
                    else
                        streambuf_t::setg(newptr, 0, newptr);
                }
                streambuf_t::sputc(traits_type::to_char_type(meta));
                return meta;
            }
        }
        // -end overflow(..)

        template<class Ch, class Tr, class Alloc>
        void basic_altstringbuf<Ch, Tr, Alloc>:: dealloc() {
            if(is_allocated_)
                alloc_.deallocate(eback(), (pptr() != NULL ? epptr() : egptr()) - eback());
            is_allocated_ = false;
            streambuf_t::setg(0, 0, 0);
            streambuf_t::setp(0, 0);
            putend_ = NULL;
        }

    }// N.S. io
} // N.S. boost

#endif // include guard

