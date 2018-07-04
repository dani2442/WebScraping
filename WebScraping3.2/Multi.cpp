#include <stdio.h>
#include <string.h>

 #define CURL_STATICLIB
/* curl stuff */ 
#include "curl/curl.h"
 
#ifdef _WIN32
#define WAITMS(x) Sleep(x)
#else
/* Portable sleep for platforms other than Windows. */ 
#define WAITMS(x)                               \ 
  struct timeval wait = { 0, (x) * 1000 };      \ 
  (void)select(0, NULL, NULL, NULL, &wait);
#endif
 #ifdef _DEBUG
# pragma comment(lib,"curl/libcurl_a_debug.lib")
#else
# pragma comment(lib,"curl/libcurl_a.lib")
#endif

/*
 * Simply download a HTTP file.
 */ 
int main(void)
{
  CURL *http[2];
  CURLM *multi_handle;
 
  int still_running; /* keep number of running handles */ 
  int repeats = 0;
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  http[0] = curl_easy_init();
  http[1] = curl_easy_init();
 
  /* set the options (I left out a few, you'll get the point anyway) */ 
  curl_easy_setopt(http[0], CURLOPT_URL, "https://www.google.com/");
  curl_easy_setopt(http[1], CURLOPT_URL, "https://manpages.debian.org/testing/libcurl4-doc/curl_multi_perform.3.en.html");
  
 
  /* init a multi stack */ 
  multi_handle = curl_multi_init();
 
  /* add the individual transfers */ 
  curl_multi_add_handle(multi_handle, http[0]);
  curl_multi_add_handle(multi_handle, http[1]);
 
  /* we start some action by calling perform right away */ 
  curl_multi_perform(multi_handle, &still_running);
 
  do {
    CURLMcode mc; /* curl_multi_wait() return code */ 
    int numfds;
 
    /* wait for activity, timeout or "nothing" */ 
    mc = curl_multi_wait(multi_handle, NULL, 0, 1000, &numfds);
 
    if(mc != CURLM_OK) {
      fprintf(stderr, "curl_multi_wait() failed, code %d.\n", mc);
      break;
    }
 
    /* 'numfds' being zero means either a timeout or no file descriptors to
       wait for. Try timeout on first occurrence, then assume no file
       descriptors and no file descriptors to wait for means wait for 100
       milliseconds. */ 
 
    if(!numfds) {
      repeats++; /* count number of repeated zero numfds */ 
      if(repeats > 1) {
        WAITMS(100); /* sleep 100 milliseconds */ 
      }
    }
    else
      repeats = 0;
 
    curl_multi_perform(multi_handle, &still_running);
  } while(still_running);
 
  curl_multi_remove_handle(multi_handle, http[0]);
  curl_multi_remove_handle(multi_handle, http[1]);
 
  curl_easy_cleanup(http[0]);
  curl_easy_cleanup(http[1]);
 
  curl_multi_cleanup(multi_handle);
 
  curl_global_cleanup();
 
  return 0;
}