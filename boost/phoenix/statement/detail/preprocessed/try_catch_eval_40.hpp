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
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        typename boost::enable_if<
            proto::matches<
                A10
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        typename boost::disable_if<
            proto::matches<
                A10
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a10
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        typename boost::enable_if<
            proto::matches<
                A11
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        typename boost::disable_if<
            proto::matches<
                A11
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a11
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        typename boost::enable_if<
            proto::matches<
                A12
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        typename boost::disable_if<
            proto::matches<
                A12
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a12
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        typename boost::enable_if<
            proto::matches<
                A13
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        typename boost::disable_if<
            proto::matches<
                A13
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a13
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        typename boost::enable_if<
            proto::matches<
                A14
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        typename boost::disable_if<
            proto::matches<
                A14
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a14
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        typename boost::enable_if<
            proto::matches<
                A15
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        typename boost::disable_if<
            proto::matches<
                A15
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a15
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        typename boost::enable_if<
            proto::matches<
                A16
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        typename boost::disable_if<
            proto::matches<
                A16
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a16
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        typename boost::enable_if<
            proto::matches<
                A17
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        typename boost::disable_if<
            proto::matches<
                A17
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a17
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        typename boost::enable_if<
            proto::matches<
                A18
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        typename boost::disable_if<
            proto::matches<
                A18
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a18
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        typename boost::enable_if<
            proto::matches<
                A19
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        typename boost::disable_if<
            proto::matches<
                A19
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a19
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        typename boost::enable_if<
            proto::matches<
                A20
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        typename boost::disable_if<
            proto::matches<
                A20
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a20
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        typename boost::enable_if<
            proto::matches<
                A21
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        typename boost::disable_if<
            proto::matches<
                A21
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a21
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        typename boost::enable_if<
            proto::matches<
                A22
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        typename boost::disable_if<
            proto::matches<
                A22
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a22
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        typename boost::enable_if<
            proto::matches<
                A23
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        typename boost::disable_if<
            proto::matches<
                A23
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a23
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        typename boost::enable_if<
            proto::matches<
                A24
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        typename boost::disable_if<
            proto::matches<
                A24
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a24
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        typename boost::enable_if<
            proto::matches<
                A25
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        typename boost::disable_if<
            proto::matches<
                A25
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a25
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        typename boost::enable_if<
            proto::matches<
                A26
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        typename boost::disable_if<
            proto::matches<
                A26
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a26
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        typename boost::enable_if<
            proto::matches<
                A27
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        typename boost::disable_if<
            proto::matches<
                A27
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a27
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        typename boost::enable_if<
            proto::matches<
                A28
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        typename boost::disable_if<
            proto::matches<
                A28
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a28
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        typename boost::enable_if<
            proto::matches<
                A29
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        typename boost::disable_if<
            proto::matches<
                A29
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a29
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        typename boost::enable_if<
            proto::matches<
                A30
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        typename boost::disable_if<
            proto::matches<
                A30
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a30
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        typename boost::enable_if<
            proto::matches<
                A31
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        typename boost::disable_if<
            proto::matches<
                A31
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a31
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        typename boost::enable_if<
            proto::matches<
                A32
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        typename boost::disable_if<
            proto::matches<
                A32
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a32
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        typename boost::enable_if<
            proto::matches<
                A33
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        typename boost::disable_if<
            proto::matches<
                A33
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a33
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        typename boost::enable_if<
            proto::matches<
                A34
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        typename boost::disable_if<
            proto::matches<
                A34
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a34
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        typename boost::enable_if<
            proto::matches<
                A35
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a35), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        typename boost::disable_if<
            proto::matches<
                A35
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a35
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        typename boost::enable_if<
            proto::matches<
                A36
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a35), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a36), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        typename boost::disable_if<
            proto::matches<
                A36
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a35), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a36
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        typename boost::enable_if<
            proto::matches<
                A37
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a35), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a36), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a37), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        typename boost::disable_if<
            proto::matches<
                A37
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a35), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a36), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a37
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        typename boost::enable_if<
            proto::matches<
                A38
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a35), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a36), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a37), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A38 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a38), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        typename boost::disable_if<
            proto::matches<
                A38
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a35), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a36), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a37), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a38
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        typename boost::enable_if<
            proto::matches<
                A39
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a35), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a36), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a37), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A38 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a38), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A39 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a39), ctx); }
        }
        template <typename Context, typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        typename boost::disable_if<
            proto::matches<
                A39
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Context & ctx, Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39) const
        {
            try
            {
                eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a0), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a1), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a2), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a3), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a4), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a5), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a6), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a7), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a8), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a9), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a10), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a11), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a12), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a13), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a14), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a15), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a16), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a17), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a18), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a19), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a20), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a21), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a22), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a23), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a24), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a25), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a26), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a27), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a28), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a29), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a30), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a31), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a32), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a33), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a34), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a35), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a36), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a37), ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A38 , 0 >::type >::type::type & ) { eval(proto::child_c<1>(a38), ctx); }
            catch(...)
            {
                eval(
                    proto::child_c<0>(
                        a39
                    )
                  , ctx);
            }
        }
