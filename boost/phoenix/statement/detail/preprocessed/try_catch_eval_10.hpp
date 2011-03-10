/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0>
        typename boost::enable_if<
            proto::matches<
                A0
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); }
        }
        template <typename Context, typename Try, typename A0>
        typename boost::disable_if<
            proto::matches<
                A0
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a0
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1>
        typename boost::enable_if<
            proto::matches<
                A1
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1>
        typename boost::disable_if<
            proto::matches<
                A1
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a1
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2>
        typename boost::enable_if<
            proto::matches<
                A2
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2>
        typename boost::disable_if<
            proto::matches<
                A2
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a2
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3>
        typename boost::enable_if<
            proto::matches<
                A3
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3>
        typename boost::disable_if<
            proto::matches<
                A3
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a3
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename boost::enable_if<
            proto::matches<
                A4
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename boost::disable_if<
            proto::matches<
                A4
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a4
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename boost::enable_if<
            proto::matches<
                A5
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename boost::disable_if<
            proto::matches<
                A5
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a5
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename boost::enable_if<
            proto::matches<
                A6
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename boost::disable_if<
            proto::matches<
                A6
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a6
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename boost::enable_if<
            proto::matches<
                A7
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename boost::disable_if<
            proto::matches<
                A7
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a7
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename boost::enable_if<
            proto::matches<
                A8
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename boost::disable_if<
            proto::matches<
                A8
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a8
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename boost::enable_if<
            proto::matches<
                A9
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename boost::disable_if<
            proto::matches<
                A9
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a9
                    )
                  , ctx);
            }
        }
