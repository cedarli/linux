#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#if defined(LIBCONFIG_STATIC)
#define LIBLIST_API
#elif defined(LIBCONFIG_EXPORTS)
#define LIBLIST_API __declspec(dllexport)
#else /* ! LIBCONFIG_EXPORTS */
#define LIBLIST_API __declspec(dllimport)
#endif /* LIBLIST_STATIC */
#else /* ! WIN32 */
#define LIBLIST_API
#endif /* WIN32 */
typedef struct Node{
    void *element;
    struct Node*next;
}Node;

typedef struct LISTHEAD{
    Node *list;
    void (*freeElement)(void *element);
    void (*printElement)(void *element);
    int (*compare)(void *elementA,void *elementB);
    void (*assignment)(void *element,void *newelement);
}LIST;

extern LIBLIST_API void *createList();
extern LIBLIST_API void deleteList(LIST *pList);
extern LIBLIST_API void printList(LIST *pList);
extern LIBLIST_API void clearList(LIST *pList);
extern LIBLIST_API int sizeList(LIST *pList);
extern LIBLIST_API int isEmptyList(LIST *pList);
extern LIBLIST_API void *getElement(LIST *pList, int pos);
extern LIBLIST_API void *getElemAddr(LIST *pList,void *x);
extern LIBLIST_API int modifyElem(LIST *pList,int pos,void *x);
extern LIBLIST_API int insertHead(LIST *pList,void *element);
extern LIBLIST_API int insertLast(LIST *pList,void *element);
