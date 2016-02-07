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
    PREVIOUS,
    FIRST,
    LAST,
    CURRENT,
    NONE
};

#endif // E_PAGE_ROLE

