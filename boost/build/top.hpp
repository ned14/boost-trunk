#if defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN__)
#   if defined(TOP_BUILD_DLL)
#       define TOP_EXPIMP __declspec(dllexport)
#   elif defined(TOP_USE_DLL)
#       define TOP_EXPIMP __declspec(dllimport)
#   else // neither build nor use dll
#       define TOP_EXPIMP
#   endif // neither build nor use dll
#else // __WIN32__
#   define TOP_EXPIMP
#endif // __WIN32__

TOP_EXPIMP void top(); //
