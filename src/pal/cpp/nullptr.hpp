#ifndef WEBSERV_PAL_CPP_NULLPTR_HPP
#define WEBSERV_PAL_CPP_NULLPTR_HPP

/*
 * Compatibility hack, based on:
 *
 *   https://stackoverflow.com/questions/44517556/how-to-define-our-own-nullptr-in-c98
 * 
 * Not sure if we're gonna keep it, but it might be useful...
 *                                            - nijakow
 */

namespace webserv {

    const                         /* this is a const object...     */
    class nullptr_t
    {
    public:
    template<class T>          /* convertible to any type       */
    operator T*() const        /* of null non-member            */
        { return NULL; }           /* pointer...                    */

    template<class C, class T> /* or any type of null           */
        operator T C::*() const /* member pointer...             */
        { return NULL; }   

    private:
    void operator&() const;    /* Can't take address of nullptr */

    } null = {};               /* and whose name is null     */

}

#endif
