#ifndef E_PAGE_ROLE
#define E_PAGE_ROLE


/********************************************************
*   e_pages_roles
* -------------------------------------------------------
*   Énumération définissant le rôle des PageManager dans
*   le PagesBuffer.
********************************************************/

enum e_pages_roles
{
    NEXT = 0,
    PREVIOUS = 1,
    FIRST = 2,
    LAST = 3,
    CURRENT = 4,
    NONE = 5
};

#endif // E_PAGE_ROLE

