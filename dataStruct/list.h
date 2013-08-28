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


typedef int elemType;
typedef struct Node{
    elemType element;
    struct Node*next;
}Node;
extern LIBLIST_API void initList(Node **pNode);
extern LIBLIST_API Node *creatList(Node *pHead);
extern LIBLIST_API void printList(Node *pHead);
extern LIBLIST_API void clearList(Node *pHead);
extern LIBLIST_API int sizeList(Node *pHead);
extern LIBLIST_API int isEmptyList(Node *pHead);
extern LIBLIST_API elemType getElement(Node *pHead, int pos);
extern LIBLIST_API elemType *getElemAddr(Node *pHead, elemType x);
extern LIBLIST_API int modifyElem(Node *pNode,int pos,elemType x);
extern LIBLIST_API int insertHeadList(Node **pNode,elemType insertElem);
extern LIBLIST_API int insertLastList(Node **pNode,elemType insertElem);
